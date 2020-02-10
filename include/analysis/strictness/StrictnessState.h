#ifndef PROMISE_INTERFERENCE_ANALYSIS_STRICTNESS_STRICTNESS_STATE_H
#define PROMISE_INTERFERENCE_ANALYSIS_STRICTNESS_STRICTNESS_STATE_H

#include "node.h"
#include "utilities.h"
//#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/* There are 5 kinds of edges:
   - write-read edge: An edge from write of x to a subsequent read of x
   - read-write edge: An edge from read of x to a subsequent write of x
   - create-force edge: An edge from creation point of promise to its forcing
   point
   - force-create edge: An edge from forcing point of a promise to the creation
   point
                        of the first promise in its body.
   - creation-creation edge: An edge from the creation point of a promise to the
   next
                             promise created in the same parent promise.

 */
namespace analysis::strictness {
class StrictnessState {
  public:
    std::size_t UNDEFINED_INDEX = std::numeric_limits<std::size_t>::max();
    StrictnessState() : nodes_{{Begin{}}}, previous_{{0}} {}

    void define_variable(const variable_id_t variable_id) {
        writes_.insert(variable_id);
    }

    void assign_variable(const variable_id_t variable_id) {
        writes_.insert(variable_id);
    }

    void lookup_variable(const variable_id_t variable_id) {
        reads_.insert(variable_id);
    }

    void remove_variable(const variable_id_t variable_id) {
        writes_.insert(variable_id);
    }

    // TODO - connect this with edges as well.
    std::size_t add_environment_action_node() {
        auto index{UNDEFINED_INDEX};

        if (reads_.size() != 0 || writes_.size() != 0) {
            nodes_.push_back(EnvironmentAction{reads_, writes_});
            index = nodes_.size() - 1;
            add_edge(previous_.back(), index);
            previous_[previous_.size() - 1] = index;
            add_read_write_edges();
            add_write_read_edges();
            reads_.clear();
            writes_.clear();
        }

        return index;
    }

    void create_promise(const promise_id_t promise_id) {
        const auto &index{add_environment_action_node()};

        nodes_.push_back(PromiseCreate{promise_id});

        promise_creation_index_[promise_id] = nodes_.size() - 1;

        add_edge(previous_.back(), nodes_.size() - 1);
        // a new promise has been created, so this is the previous
        // node to which we will connect upcoming creation points
        // and environment nodes.
        previous_[previous_.size() - 1] = nodes_.size() - 1;
    }

    void enter_promise(const promise_id_t promise_id) {
        add_environment_action_node();
        nodes_.push_back(PromiseForce{promise_id});
        scope_.push_back(nodes_.size() - 1);
        previous_.push_back(nodes_.size() - 1);

        const auto &promise_creation_index{
            get_promise_creation_index(promise_id)};

        if (promise_creation_index != UNDEFINED_INDEX) {
            add_edge(promise_creation_index, nodes_.size() - 1);
        }
    }

    void exit_promise(const promise_id_t promise_id) {
        add_environment_action_node();
        const auto &node_index{scope_.back()};
        const auto &promise_force{std::get<PromiseForce>(nodes_[node_index])};
        if (promise_force.get_promise_id() != promise_id) {
            std::cerr << "Promise entry id mismatches promise exit id.";
            exit(EXIT_FAILURE);
        }
        scope_.pop_back();
        previous_.pop_back();
    }

    void add_write_read_edges() {
        for (auto const variable_id : writes_) {
            const auto reader_index{get_last_reader(variable_id)};
            // If no one has read from this variable before, there are
            // no write edges to be made because there is nothing
            // constraining this promise from moving up and affecting
            // the read of the variable in question.
            if (reader_index == UNDEFINED_INDEX)
                continue;

            // If we didn't bail out in the previous check, it means
            // that the variable has been read from before and we know the
            // index of the object in the node vector which represents
            // that read. Now, we need to make sure that moving this
            // promise does not affect the read of this variable. The
            // only way this can happen is that this promise always
            // stays below the point where the variable was read
            // because once the variable is read, writes made to it
            // by this promise will not affect that read.

            // First we find the promise which caused the writes.
            // To do that, we lookup the scope that gives an index
            // into the nodes_ vector to a PromiseForce node. We
            // know that this is always a PromiseForce node because
            // all insertions into the scope_ vector are indices
            // to PromiseForce objects added to nodes_ vector.
            // Furthermore, nodes vector is only appended to, thus
            // this index always remains valid.
            const auto &promise_force_index{scope_.back()};

            // Now, our aim is to make edges. We know the read point
            // of the variable. We also know that the promise in question
            // is writing to this variable. Clearly there is an edge
            // between this promise and the read point.
            add_edge(reader_index, promise_force_index);
        }
    }

    void add_read_write_edges() {
        for (auto const variable_id : reads_) {
            const auto writer_index{get_last_writer(variable_id)};
            // If no one has written to this variable before, there are
            // no lookup edges to be made because there is nothing
            // constraining this promise from moving up and reading
            // a different value of the variable in question.
            if (writer_index == UNDEFINED_INDEX)
                continue;

            // If we didn't bail out in the previous check, it means
            // that the variable has been written to before and we know
            // the index of the object in the node vector which represents
            // that write. Now, we need to make sure that moving this
            // promise does not cause it to read a difference value of
            // this variable. The
            // only way this can happen is that this promise always
            // stays below the point where the variable was written to.

            // First we find the promise which caused the read.
            // To do that, we lookup the scope that gives an index
            // into the nodes_ vector to a PromiseForce node. We
            // know that this is always a PromiseForce node because
            // all insertions into the scope_ vector are indices
            // to PromiseForce objects added to nodes_ vector.
            // Furthermore, nodes vector is only appended to, thus
            // this index always remains valid.
            const auto &promise_force_index{scope_.back()};

            // Now, our aim is to make edges. We know the write point
            // of the variable. We also know that the promise in question
            // is reading this variable. Clearly there is an edge
            // between the write point and this promise.
            add_edge(writer_index, promise_force_index);
        }
    }

    void add_edge(std::size_t parent, std::size_t child) {
        edges_[parent].insert(child);
        // if (iter == edges_.end) {
        //     std::cerr << "Id " << parent << " not found in edges." <<
        //     std::endl;
        //     exit(EXIT_FAILURE);
        // }
        // iter->second.insert(child);
    }

    std::size_t get_last_reader(const variable_id_t variable_id) {
        auto iter{last_reader_.find(variable_id)};
        if (iter == last_reader_.end())
            return UNDEFINED_INDEX;
        return iter->second;
    }

    std::size_t get_last_writer(const variable_id_t variable_id) {
        auto iter{last_writer_.find(variable_id)};
        if (iter == last_writer_.end())
            return UNDEFINED_INDEX;
        return iter->second;
    }

    std::size_t get_promise_creation_index(const promise_id_t promise_id) {
        auto iter{promise_creation_index_.find(promise_id)};
        if (iter == promise_creation_index_.end())
            return UNDEFINED_INDEX;
        return iter->second;
    }

    int largest() {
        int max = 0;
        for (const auto &kv : edges_) {
            if (kv.second.size() > max)
                max = kv.second.size();
        }
        return max;
    }

    std::unordered_map<std::size_t, std::unordered_set<std::size_t>>
    get_edges() const {
        return edges_;
    }

    const node_t &get_node(std::size_t index) const { return nodes_[index]; }

    void topological_sort() {
        std::vector<std::size_t> s{{0}};
        while (!s.empty()) {
            const auto parent{s.back()};
            s.pop_back();
            result.push_back(parent);
            for (const auto &child : edges_[parent]) {
            }
        }
    }

  private:
    std::unordered_set<variable_id_t> reads_;
    std::unordered_set<variable_id_t> writes_;
    std::unordered_map<std::size_t, std::unordered_set<std::size_t>> edges_;
    std::unordered_map<variable_id_t, std::size_t> last_writer_;
    std::unordered_map<variable_id_t, std::size_t> last_reader_;
    std::vector<std::size_t> scope_;
    std::vector<node_t> nodes_;
    std::vector<std::size_t> previous_;
    std::unordered_map<promise_id_t, std::size_t> promise_creation_index_;
};
} // namespace analysis::strictness

inline std::ostream &
operator<<(std::ostream &os,
           const analysis::strictness::StrictnessState &state) {
    for (const auto &kv : state.get_edges()) {
        os << state.get_node(kv.first) << " : ";
        for (const auto &value : kv.second) {
            os << state.get_node(value) << " ";
        }
        os << std::endl;
    }
    return os;
}

#endif /* PROMISE_INTERFERENCE_ANALYSIS_STRICTNESS_STRICTNESS_STATE_H */
