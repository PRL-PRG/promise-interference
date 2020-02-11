#ifndef PROMISE_INTERFERENCE_ANALYSIS_STRICTNESS_NODE_H
#define PROMISE_INTERFERENCE_ANALYSIS_STRICTNESS_NODE_H

#include "utilities.h"
#include <iostream>
#include <unordered_set>
#include <variant>
// #include "EnvironmentAction.h"
// #include "PromiseCreate.h"
// #include "PromiseForce.h"

namespace analysis::strictness {

class PromiseCreate {
  public:
    explicit PromiseCreate(promise_id_t promise_id) : promise_id_{promise_id} {}
    promise_id_t get_promise_id() const { return promise_id_; }

  private:
    promise_id_t promise_id_;
};

class PromiseForce {
  public:
    explicit PromiseForce(promise_id_t promise_id) : promise_id_{promise_id} {}
    promise_id_t get_promise_id() const { return promise_id_; }

  private:
    promise_id_t promise_id_;
};

class EnvironmentAction {
  public:
    explicit EnvironmentAction(const std::unordered_set<variable_id_t> &reads,
                               const std::unordered_set<variable_id_t> &writes)
        : reads_{reads}, writes_{writes} {}

    const std::unordered_set<variable_id_t> &get_reads() const {
        return reads_;
    }

    const std::unordered_set<variable_id_t> &get_writes() const {
        return writes_;
    }

  private:
    std::unordered_set<variable_id_t> reads_;
    std::unordered_set<variable_id_t> writes_;
};

class Begin {
  public:
    explicit Begin() {}
};

using node_t =
    std::variant<Begin, PromiseCreate, PromiseForce, EnvironmentAction>;
} // namespace analysis::strictness

inline std::ostream &
operator<<(std::ostream &os,
           const analysis::strictness::EnvironmentAction &environment_action) {
    os << "EnvironmentAction({";
    for (const auto &variable_id : environment_action.get_reads()) {
        os << variable_id << " ";
    }
    os << "}, {";
    for (const auto &variable_id : environment_action.get_writes()) {
        os << variable_id << " ";
    }
    os << "})";
    return os;
}

inline std::ostream &
operator<<(std::ostream &os,
           const analysis::strictness::PromiseCreate &promise_create) {
    os << "PromiseCreate(" << promise_create.get_promise_id() << ")";
    return os;
}

inline std::ostream &
operator<<(std::ostream &os,
           const analysis::strictness::PromiseForce &promise_force) {
    os << "PromiseForce(" << promise_force.get_promise_id() << ")";
    return os;
}

inline std::ostream &operator<<(std::ostream &os,
                                const analysis::strictness::Begin &begin) {
    os << "Begin()";
    return os;
}

inline std::ostream &operator<<(std::ostream &os,
                                const analysis::strictness::node_t &node) {
    std::visit([&](auto const &n) { os << n; }, node);
    return os;
}

#endif /* PROMISE_INTERFERENCE_ANALYSIS_STRICTNESS_NODE_H */
