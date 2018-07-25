#include "state/Variable.h"

std::ostream &operator<<(std::ostream &os, const state::Variable &variable) {
    return os << variable.to_string();
}
