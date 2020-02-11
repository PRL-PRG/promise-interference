#ifndef PROMISE_INTERFERENCE_UTILITIES_H
#define PROMISE_INTERFERENCE_UTILITIES_H

#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <utility>

using opcode_t = std::string;
using function_id_t = std::string;
using call_id_t = std::uintptr_t;
using environment_id_t = int;
using promise_id_t = std::intptr_t;
using variable_name_t = std::string;
using sexp_type_t = std::string;
using variable_id_t = int;
using expression_t = std::string;
using line_number_t = std::size_t;
using position_t = std::size_t;

std::pair<void *, std::size_t> mmap_file(const std::string &filepath);

void munmap_file(void *data, std::size_t size);

extern const char RECORD_SEPARATOR;
extern const char UNIT_SEPARATOR;
extern const line_number_t UNDEFINED_LINE_NUMBER;

static inline std::string parse_upto_separator(const char *begin, char **end) {
    std::size_t size = 0;

    while (begin[size] != RECORD_SEPARATOR && begin[size] != UNIT_SEPARATOR)
        ++size;
    *end = const_cast<char *>(begin) + size;
    return std::string(begin, size);
}

inline call_id_t parse_call_id(const char *begin, char **end) {
    return std::strtoul(begin, end, 10);
}

inline environment_id_t parse_environment_id(const char *begin, char **end) {
    return std::strtol(begin, end, 10);
}

inline promise_id_t parse_promise_id(const char *begin, char **end) {
    return std::strtol(begin, end, 10);
}

inline function_id_t parse_function_id(const char *begin, char **end) {
    return parse_upto_separator(begin, end);
}

inline std::string parse_function_names(const char *begin, char **end) {
    return parse_upto_separator(begin, end);
}

inline sexp_type_t parse_sexp_type(const char *begin, char **end) {
    return parse_upto_separator(begin, end);
}

inline variable_id_t parse_variable_id(const char *begin, char **end) {
    return std::strtol(begin, end, 10);
}

inline variable_name_t parse_variable_name(const char *begin, char **end) {
    return parse_upto_separator(begin, end);
}

inline expression_t parse_expression(const char *begin, char **end) {
    return parse_upto_separator(begin, end);
}

inline bool starts_with(const char *begin, const std::string &prefix) {
    return std::strncmp(begin, prefix.c_str(), prefix.length()) == 0;
}

inline bool parse_boolean(const char *begin, char **end) {
    return std::strtol(begin, end, 10);
}

inline position_t parse_position(const char *begin, char **end) {
    return std::strtoul(begin, end, 10);
}

inline void parse_instruction_separator(const char *begin, char **end) {
    assert(*begin == RECORD_SEPARATOR);
    *end = *end + 1;
}

inline void parse_operand_separator(const char *begin, char **end) {
    assert(*begin == UNIT_SEPARATOR);
    *end = *end + 1;
}

inline std::size_t count_instructions(const char *begin, const char *end) {
    std::size_t line_count = 0;
    if (begin == end)
        return line_count;
    ++begin;
    while (begin != end) {
        if (*(begin - 1) == RECORD_SEPARATOR && *begin == '\n')
            ++line_count;
        ++begin;
    }
    return line_count;
}
#endif /* PROMISE_INTERFERENCE_UTILITIES_H */
