#ifndef PROMISE_INTERFERENCE_ANALYSIS_BINDING_TOP_LEVEL_H
#define PROMISE_INTERFERENCE_ANALYSIS_BINDING_TOP_LEVEL_H

#include "utilities.h"
#include <sstream>

namespace analysis::binding {

class TopLevel {
  public:
    explicit TopLevel() {}

    const std::string to_string() const { return "TopLevel()"; }

    bool operator==(const TopLevel &rhs) const { return true; }

    bool operator!=(const TopLevel &rhs) const { return !(operator==(rhs)); }
};
}

inline std::ostream &operator<<(std::ostream &os,
                                const analysis::binding::TopLevel &top_level) {
    return os << top_level.to_string();
}

namespace std {

template <> struct hash<analysis::binding::TopLevel> {
    std::size_t operator()(const analysis::binding::TopLevel &top_level) const {
        // http://stackoverflow.com/a/1646913/126995
        std::size_t res = 17;
        return res;
    }
};
}

#endif /* PROMISE_INTERFERENCE_ANALYSIS_BINDING_TOP_LEVEL_H */
