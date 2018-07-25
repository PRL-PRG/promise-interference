#include "scope/FunctionScope.h"

std::ostream &operator<<(std::ostream &os,
                         const scope::FunctionScope &function_scope) {
    return os << function_scope.to_string();
}
