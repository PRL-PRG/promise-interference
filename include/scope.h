#ifndef PROMISE_INTERFERENCE_SCOPE_H
#define PROMISE_INTERFERENCE_SCOPE_H

#include "FunctionScope.h"
#include "PromiseScope.h"
#include "TopLevelScope.h"
#include <variant>

using scope_t = std::variant<TopLevelScope, FunctionScope, PromiseScope>;

std::string scope_to_string(const scope_t &scope);

std::ostream &operator<<(std::ostream &os, const scope_t &scope);

#endif /* PROMISE_INTERFERENCE_SCOPE_H */
