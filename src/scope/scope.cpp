#include "scope/scope.h"

namespace scope {

std::string to_string(const scope_t &scope) {
    std::string scope_string;
    std::visit([&](const auto &s) { scope_string = s.to_string(); }, scope);
    return scope_string;
}
}

std::ostream &operator<<(std::ostream &os, const scope::scope_t &scope) {
    return os << scope::to_string(scope);
}
