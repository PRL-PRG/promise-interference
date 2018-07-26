#ifndef PROMISE_INTERFERENCE_SCOPE_H
#define PROMISE_INTERFERENCE_SCOPE_H

#include "FunctionScope.h"
#include "PromiseScope.h"
#include "TopLevelScope.h"
#include <variant>

namespace scope {

using scope_t = std::variant<TopLevelScope, FunctionScope, PromiseScope>;

inline std::string to_string(const scope_t &scope) {
    std::string scope_string;
    std::visit([&](const auto &s) { scope_string = s.to_string(); }, scope);
    return scope_string;
}
}

inline std::ostream &operator<<(std::ostream &os, const scope::scope_t &scope) {
    std::visit([&](auto const &s) { os << s; }, scope);
    return os;
}

#endif /* PROMISE_INTERFERENCE_SCOPE_H */
