#include "analysis/strictness.h"
#include "instruction/Stream.h"
#include "instruction/instruction.h"
#include "utilities.h"

namespace analysis::strictness {

struct promise_strictness_t {
    promise_id_t id;
    line_number_t creation;
    line_number_t entry;
    line_number_t exit;
    bool strict;
};

using promise_strictness_map_t =
    std::unordered_map<promise_id_t, promise_strictness_t>;

using promise_strictness_stack_t = std::vector<promise_strictness_t *>;

bool create_promise(const instruction::PromiseCreate &prc,
                    promise_strictness_map_t &map,
                    promise_strictness_stack_t &stack) {
    // assume that the promise is not strict because the entry point is not
    // known and may be absent, which implies that the promise is never forced
    return map
        .insert({prc.get_id(),
                 {prc.get_id(), prc.get_line_number(),
                  std::numeric_limits<line_number_t>::max(),
                  std::numeric_limits<line_number_t>::max(), false}})
        .second;
}

void enter_promise(const instruction::PromiseEntry &prb,
                   promise_strictness_map_t &map,
                   promise_strictness_stack_t &stack) {

    auto result =
        map.insert({prb.get_id(),
                    {prb.get_id(), std::numeric_limits<line_number_t>::max(),
                     prb.get_line_number(),
                     std::numeric_limits<line_number_t>::max(), false}});

    if (!result.second) {
        result.first->second.entry = prb.get_line_number();
        // since both creation and entry points exist, assume that the promise
        // is strict. If it is not, the logic below will set this field to false
        result.first->second.strict = true;
    }

    auto *current_promise_strictness{&(result.first->second)};

    stack.push_back(current_promise_strictness);

    if (stack.size() < 2)
        return;

    if (current_promise_strictness->creation ==
        std::numeric_limits<line_number_t>::max())
        return;

    // this loop condition relies upon the wrap around of unsigned ints
    for (size_t index = stack.size() - 2; index < stack.size(); --index) {
        auto *promise_strictness{stack[index]};

        if (promise_strictness->entry < current_promise_strictness->creation) {
            return;
        }

        if (current_promise_strictness->creation > promise_strictness->creation)
            promise_strictness->strict = false;
    }
}

void exit_promise(const instruction::PromiseExit &prf,
                  promise_strictness_map_t &map,
                  promise_strictness_stack_t &stack) {
    stack.back()->exit = prf.get_line_number();
    stack.pop_back();
}

promise_strictness_map_t analyze(const instruction::Stream &stream) {
    promise_strictness_map_t map;
    promise_strictness_stack_t stack;

    for (const auto &instruction : stream) {

        if (std::holds_alternative<instruction::PromiseCreate>(instruction)) {
            if (!create_promise(
                    std::get<instruction::PromiseCreate>(instruction), map,
                    stack)) {
                std::cerr << "Error inserting promise: " << instruction;
                exit(EXIT_FAILURE);
            }
        } else if (std::holds_alternative<instruction::PromiseEntry>(
                       instruction)) {
            enter_promise(std::get<instruction::PromiseEntry>(instruction), map,
                          stack);
        } else if (std::holds_alternative<instruction::PromiseExit>(
                       instruction)) {
            exit_promise(std::get<instruction::PromiseExit>(instruction), map,
                         stack);
        }
    }

    return map;
}

instruction::Stream rewrite(const instruction::Stream &lazy_stream) {
    auto promise_strictness_map{analyze(lazy_stream)};
    instruction::Stream strict_stream{lazy_stream.size()};
    instruction::Stream::size_type lazy_index = 0;
    std::vector<promise_strictness_t> stack;
    std::vector<bool> copied{std::vector(lazy_stream.size(), false)};

    while (lazy_index < lazy_stream.size()) {

        while (copied[lazy_index]) {
            lazy_index++;
            if (lazy_index >= lazy_stream.size())
                break;
        }

        const instruction::instruction_t &instruction{lazy_stream[lazy_index]};
        strict_stream.push_back(instruction);
        copied[lazy_index] = true;

        if (std::holds_alternative<instruction::PromiseCreate>(instruction)) {

            const auto &prc{std::get<instruction::PromiseCreate>(instruction)};
            auto promise_strictness{promise_strictness_map[prc.get_id()]};
            if (promise_strictness.strict) {
                stack.push_back(promise_strictness);
                lazy_index = promise_strictness.entry;
            } else {
                lazy_index = lazy_index + 1;
            }

        } else if (std::holds_alternative<instruction::PromiseExit>(
                       instruction)) {

            auto promise_id{
                std::get<instruction::PromiseExit>(instruction).get_id()};

            bool strict = promise_strictness_map[promise_id].strict;

            if (!strict) {
                ++lazy_index;
                continue;
            }

            auto promise_strictness{stack.back()};

            if (promise_strictness.id != promise_id ||
                promise_strictness.exit != lazy_index) {
                for (const auto &strictness : stack) {
                    std::cerr << strictness.id << " " << strictness.creation
                              << " " << strictness.entry << " "
                              << strictness.exit << " " << strictness.strict
                              << std::endl;
                }
                std::cerr << "lazy index " << lazy_index << std::endl;
                std::cerr << "Stack exit does not match on rewriting!";
                exit(EXIT_FAILURE);
            }

            stack.pop_back();

            lazy_index = promise_strictness.creation + 1;
        } else {
            ++lazy_index;
        }
    }

    return strict_stream;
}
}
