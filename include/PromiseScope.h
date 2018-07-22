#ifndef PROMISE_INTERFERENCE_PROMISE_SCOPE_H
#define PROMISE_INTERFERENCE_PROMISE_SCOPE_H

#include "utilities.h"
#include <sstream>

class PromiseScope {
  public:
    explicit PromiseScope(const promise_id_t id) : id_{id} {}

    const promise_id_t get_id() const { return id_; }

    const std::string to_string() const {
        std::stringstream stream;
        stream << "PromiseScope(" << get_id() << ")";
        return stream.str();
    }

    bool operator==(const PromiseScope &rhs) const {
        return (get_id() == rhs.get_id());
    }

    bool operator!=(const PromiseScope &rhs) const {
        return !(operator==(rhs));
    }

  private:
    promise_id_t id_;
};

std::ostream &operator<<(std::ostream &os, const PromiseScope &promise_scope);

namespace std {

template <> struct hash<PromiseScope> {

    std::size_t operator()(const PromiseScope &promise_scope) const {
        // http://stackoverflow.com/a/1646913/126995
        std::size_t res = 17;
        res = res * 31 + std::hash<promise_id_t>()(promise_scope.get_id());
        return res;
    }
};
}

#endif /* PROMISE_INTERFERENCE_PROMISE_SCOPE_H */
