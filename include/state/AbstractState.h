#ifndef PROMISE_INTERFERENCE_ABSTRACT_STATE_H
#define PROMISE_INTERFERENCE_ABSTRACT_STATE_H

#include "AbstractValue.h"
#include "Variable.h"
#include "scope/scope.h"
#include <optional>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

namespace state {

class AbstractState {
  public:
    explicit AbstractState() : scope_stack_{scope::TopLevelScope{}} {}

    void enter_scope(const scope::scope_t &scope) {
        scope_stack_.push_back(scope);
    }

    scope::scope_t exit_scope() {
        scope::scope_t element{scope_stack_.back()};
        scope_stack_.pop_back();
        return element;
    }

    const scope::scope_t &get_current_scope() const {
        return scope_stack_.back();
    }

    void assign_variable(const Variable variable,
                         const AbstractValue abstract_value) {
        bindings_.insert_or_assign(variable, abstract_value);
    }

    void remove_variable(const Variable &variable) {

        auto iter{bindings_.find(variable)};

        if (iter == bindings_.end()) {
            add_free_variable(variable);
            // std::cerr << "variable absent" << std::endl;
            // std::cerr << "expected: " << variable << std::endl;
            // std::cerr << "but is not present in the bindings." << std::endl;
            // TODO - handle this case appropriately.
        } else {

            // AbstractValue abstract_value{iter->second};

            bindings_.erase(iter);

            // return abstract_value;
        }
    }

    std::optional<AbstractValue> lookup_variable(const Variable &variable) {
        auto iter{bindings_.find(variable)};
        return (iter == bindings_.end())
                   ? std::optional<AbstractValue>{}
                   : std::optional<AbstractValue>{iter->second};
    }

    void associate_lookup(const Variable variable,
                          const AbstractValue abstract_value) {
        scope::scope_t scope{get_current_scope()};

        auto result = lookups_.insert({scope, {{variable, {abstract_value}}}});
        if (result.second) {
            return;
        }
        auto subresult =
            result.first->second.insert({variable, {abstract_value}});

        if (!subresult.second) {
            subresult.first->second.push_back(abstract_value);
        }
    }

    void add_free_variable(const Variable &variable) {
        free_variables_.insert(variable);
    }

  private:
    template <typename T> void associate_lookup_() {}
    std::vector<scope::scope_t> scope_stack_;
    std::unordered_map<Variable, AbstractValue> bindings_;
    std::unordered_map<scope::scope_t,
                       std::unordered_map<Variable, std::vector<AbstractValue>>>
        lookups_;
    std::unordered_set<Variable> free_variables_;
};
}

#endif /* PROMISE_INTERFERENCE_ABSTRACT_STATE_H */
