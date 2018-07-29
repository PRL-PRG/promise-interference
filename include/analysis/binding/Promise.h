#ifndef PROMISE_INTERFERENCE_ANALYSIS_BINDING_PROMISE_H
#define PROMISE_INTERFERENCE_ANALYSIS_BINDING_PROMISE_H

#include "utilities.h"
#include <sstream>

namespace analysis::binding {

class Promise {
  public:
    explicit Promise(const promise_id_t id) : id_{id} {}

    const promise_id_t get_id() const { return id_; }

    const std::string to_string() const {
        std::stringstream stream;
        stream << "Promise(" << get_id() << ")";
        return stream.str();
    }

    bool operator==(const Promise &rhs) const {
        return (get_id() == rhs.get_id());
    }

    bool operator!=(const Promise &rhs) const { return !(operator==(rhs)); }

  private:
    promise_id_t id_;
};
}

inline std::ostream &operator<<(std::ostream &os,
                                const analysis::binding::Promise &promise) {
    return os << promise.to_string();
}

namespace std {

template <> struct hash<analysis::binding::Promise> {

    std::size_t operator()(const analysis::binding::Promise &promise) const {
        // http://stackoverflow.com/a/1646913/126995
        std::size_t res = 17;
        res = res * 31 + std::hash<promise_id_t>()(promise.get_id());
        return res;
    }
};
}

#endif /* PROMISE_INTERFERENCE_ANALYSIS_BINDING_PROMISE_H */
