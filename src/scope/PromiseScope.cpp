#include "scope/PromiseScope.h"

std::ostream &operator<<(std::ostream &os,
                         const scope::PromiseScope &promise_scope) {
    return os << promise_scope.to_string();
}
