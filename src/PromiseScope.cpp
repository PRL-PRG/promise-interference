#include "include/PromiseScope.h"

std::ostream &operator<<(std::ostream &os, const PromiseScope &promise_scope) {
    return os << promise_scope.to_string();
}
