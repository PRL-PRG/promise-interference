#ifndef PROMISE_INTERFERENCE_ANALYSIS_BINDING_SCOPE_H
#define PROMISE_INTERFERENCE_ANALYSIS_BINDING_SCOPE_H

#include "Function.h"
#include "Promise.h"
#include "TopLevel.h"
#include <variant>

namespace analysis::binding {

using scope_t = std::variant<TopLevel, Function, Promise>;

inline std::string to_string(const scope_t &scope) {
    std::string scope_string;
    std::visit([&](const auto &s) { scope_string = s.to_string(); }, scope);
    return scope_string;
}
}

inline std::ostream &operator<<(std::ostream &os,
                                const analysis::binding::scope_t &scope) {
    std::visit([&](auto const &s) { os << s; }, scope);
    return os;
}

#endif /* PROMISE_INTERFERENCE_ANALYSIS_BINDING_SCOPE_H */
