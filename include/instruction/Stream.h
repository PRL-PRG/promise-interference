#ifndef PROMISE_INTERFERENCE_INSTRUCTION_STREAM_H
#define PROMISE_INTERFERENCE_INSTRUCTION_STREAM_H

#include "instruction/instruction.h"
#include <filesystem>
#include <iostream>
#include <variant>
#include <vector>

namespace instruction {

class Stream {
  public:
    using iterator = std::vector<instruction_t>::iterator;
    using const_iterator = std::vector<instruction_t>::const_iterator;
    using reverse_iterator = std::vector<instruction_t>::reverse_iterator;
    using const_reverse_iterator =
        std::vector<instruction_t>::const_reverse_iterator;
    using size_type = std::vector<instruction_t>::size_type;

    explicit Stream(size_type capacity) : instructions_{} {
        instructions_.reserve(capacity);
    }

    explicit Stream(std::vector<instruction_t> instructions)
        : instructions_{std::move(instructions)} {}

    void reserve(size_type new_capacity) {
        instructions_.reserve(new_capacity);
    }

    size_type capacity() const noexcept { return instructions_.capacity(); }

    instruction_t &at(size_type pos) { return instructions_.at(pos); }

    const instruction_t &at(size_type pos) const {
        return instructions_.at(pos);
    }

    instruction_t &operator[](size_type pos) { return instructions_[pos]; }

    const instruction_t &operator[](size_type pos) const {
        return instructions_[pos];
    }

    size_type size() const { return instructions_.size(); }

    iterator begin() { return instructions_.begin(); }

    const_iterator begin() const { return instructions_.begin(); }

    const_iterator cbegin() const { return instructions_.cbegin(); }

    iterator end() { return instructions_.end(); }

    const_iterator end() const { return instructions_.end(); }

    const_iterator cend() const { return instructions_.cend(); }

    void push_back(const instruction_t &instruction) {
        instructions_.push_back(instruction);
    }

    static Stream parse(std::filesystem::path trace_file);

    static instruction_t parse_instruction(const char *begin, char **end);

  private:
    std::vector<instruction_t> instructions_;
};
}

inline std::ostream &operator<<(std::ostream &os,
                                const instruction::Stream &stream) {
    for (const auto &instruction : stream) {
        os << instruction << std::endl;
    }
    return os;
}

#endif /* PROMISE_INTERFERENCE_INSTRUCTION_STREAM_H */
