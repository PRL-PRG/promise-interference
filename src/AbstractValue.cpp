#include "AbstractValue.h"

std::ostream &operator<<(std::ostream &os,
                         const AbstractValue &abstract_value) {
    return os << abstract_value.to_string();
}
