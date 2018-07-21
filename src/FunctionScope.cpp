#include "include/FunctionScope.h"

std::ostream &operator<<(std::ostream &os,
                         const FunctionScope &function_scope) {
    return os << function_scope.to_string();
}
