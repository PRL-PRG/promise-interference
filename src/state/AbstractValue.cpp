#include "state/AbstractValue.h"

std::ostream &operator<<(std::ostream &os,
                         const state::AbstractValue &abstract_value) {
    return os << abstract_value.to_string();
}
