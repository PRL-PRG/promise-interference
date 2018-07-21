#ifndef PROMISE_INTERFERENCE_ABSTRACT_STATE_H
#define PROMISE_INTERFERENCE_ABSTRACT_STATE_H

#include "AbstractValue.h"
#include "Variable.h"
#include "scope.h"
#include <optional>
#include <unordered_map>
#include <variant>
#include <vector>

class AbstractState {
  public:
    explicit AbstractState() : scope_stack_{TopLevelScope{}} {}

    void enter_scope(const scope_t &scope) { scope_stack_.push_back(scope); }

    scope_t exit_scope() {
        scope_t element{scope_stack_.back()};
        scope_stack_.pop_back();
        return element;
    }

    const scope_t &get_current_scope() const { return scope_stack_.back(); }

    void assign_variable(const Variable variable,
                         const AbstractValue abstract_value) {
        bindings_.insert_or_assign(variable, abstract_value);
    }

    const AbstractValue remove_variable(const Variable &variable) {

        auto iter{bindings_.find(variable)};

        if (iter == bindings_.end()) {
            std::cerr << "variable absent" << std::endl;
            std::cerr << "expected: " << variable << std::endl;
            std::cerr << "but is not present in the bindings." << std::endl;
            exit(EXIT_FAILURE);
        }

        AbstractValue abstract_value{iter->second};

        bindings_.erase(iter);

        return abstract_value;
    }

    std::optional<AbstractValue> lookup_variable(const Variable &variable) {
        auto iter{bindings_.find(variable)};
        return (iter == bindings_.end())
                   ? std::optional<AbstractValue>{}
                   : std::optional<AbstractValue>{iter->second};
    }

    void associate_lookup(const Variable variable,
                          const AbstractValue abstract_value) {
        scope_t scope{get_current_scope()};
        // if (std::holds_alternative<FunctionScope>(scope)) {
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

  private:
    template <typename T> void associate_lookup_() {}
    std::vector<scope_t> scope_stack_;
    std::unordered_map<Variable, AbstractValue> bindings_;
    std::unordered_map<scope_t,
                       std::unordered_map<Variable, std::vector<AbstractValue>>>
        lookups_;
};

#endif /* PROMISE_INTERFERENCE_ABSTRACT_STATE_H */
