#ifndef PROMISE_INTERFERENCE_LOGGER_H
#define PROMISE_INTERFERENCE_LOGGER_H

#include <iostream>

#define log_error(...)                                                         \
    std::cerr << "error"                                                       \
              << " " << __FILE__ << " " << __LINE__;                           \
    exit(EXIT_FAILURE);
//log_impl(std::cerr, "error", __FILE__, __func__, __LINE__, __VA_ARGS__); \


#define log_info(...)
// log_impl(std::cout, "info", __FILE__, __func__, __LINE__, __VA_ARGS__);

// template <typename T> void log_error_internal_impl(std::ostream &os, T v) {
//     os << v;
// }

// template <typename T, typename... Args>
// void log_error_internal_impl(std::ostream &os, T first, Args... rest) {
//     os << first;
//     log_error_internal_impl(os, rest...);
// }

// template <typename T, typename... Args>
// void log_impl(std::ostream &os, const char *type, const char *filename,
//               const char *line_number, const char *function_name,
//               Args... messages) {
//     os << "[" << type << "]-[" << filename "]-[" << function_name << "]-["
//        << line_number << "]" << std::endl;
//     log_error_internal_impl(os, messages...);
// }

template <typename... Args>
void log_impl(std::ostream &os, const char *type, const char *filename,
              const char *functionname, const int line_number,
              Args &&... args) {
    os << "[" << type << "]-[" << filename << "]-[" << functionname << "]-["
       << line_number << "]" << std::endl;
    (os << ... << args);
}

#endif /* PROMISE_INTERFERENCE_LOGGER_H */
