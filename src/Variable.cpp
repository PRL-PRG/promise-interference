#include "include/Variable.h"

std::ostream &operator<<(std::ostream &os, const Variable &variable) {
    return os << variable.to_string();
}
