#include "include/AbstractInterpreter.h"
#include "include/AbstractState.h"
#include "include/InstructionStream.h"
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {

    if (argc < 4) {
        std::cerr << "incorrect number of arguments passed.\n";
        std::cerr << argv[0] << " <lazy-trace-filepath>"
                                " <eager-trace-filepath>"
                                " <trace-comparison-filepath>\n";
        return EXIT_FAILURE;
    }

    std::string lazy_trace_filepath{argv[1]};
    std::string eager_trace_filepath{argv[2]};
    std::string trace_comparison_filepath{argv[3]};

    std::chrono::high_resolution_clock::time_point t1, t2;
    std::chrono::duration<double> time_span;

    std::cerr << "Reading from '" << lazy_trace_filepath << "' : ";
    t1 = std::chrono::high_resolution_clock::now();
    auto instruction_stream{InstructionStream::parse(lazy_trace_filepath)};
    t2 = std::chrono::high_resolution_clock::now();
    time_span =
        std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    std::cerr << time_span.count() << " seconds" << std::endl;

    std::cerr << "Writing to '" << eager_trace_filepath << "' : ";
    t1 = std::chrono::high_resolution_clock::now();
    std::ofstream eager_trace_file{eager_trace_filepath};
    eager_trace_file << instruction_stream;
    eager_trace_file.close();
    t2 = std::chrono::high_resolution_clock::now();
    time_span =
        std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    std::cerr << time_span.count() << " seconds" << std::endl;

    AbstractState state{};
    std::cerr << "Interpreting " << instruction_stream.size()
              << " instructions : ";
    t1 = std::chrono::high_resolution_clock::now();
    // interpret(instructions, state);
    t2 = std::chrono::high_resolution_clock::now();
    time_span =
        std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    std::cerr << time_span.count() << " seconds" << std::endl;

    return EXIT_SUCCESS;
}
