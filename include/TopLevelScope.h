#ifndef PROMISE_INTERFERENCE_TOP_LEVEL_SCOPE_H
#define PROMISE_INTERFERENCE_TOP_LEVEL_SCOPE_H

#include "utilities.h"
#include <sstream>

class TopLevelScope {
  public:
    explicit TopLevelScope() {}

    const std::string to_string() const { return "TopLevelScope()"; }

    bool operator==(const TopLevelScope &rhs) const { return true; }

    bool operator!=(const TopLevelScope &rhs) const {
        return !(operator==(rhs));
    }
};

std::ostream &operator<<(std::ostream &os, const TopLevelScope &promise_scope);

namespace std {

template <> struct hash<TopLevelScope> {
    std::size_t operator()(const TopLevelScope &top_level_scope) const {
        // http://stackoverflow.com/a/1646913/126995
        std::size_t res = 17;
        return res;
    }
};
}

#endif /* PROMISE_INTERFERENCE_TOP_LEVEL_SCOPE_H */
