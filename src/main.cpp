#include "analysis/strictness/interpreter.h"
#include "instruction/Stream.h"
#include "instruction/instruction.h"
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {

    using std::chrono::duration;
    using std::chrono::duration_cast;
    using std::chrono::high_resolution_clock;

    if (argc < 4) {
        std::cerr << "incorrect number of arguments passed.\n";
        std::cerr << argv[0]
                  << " <lazy-trace-filepath>"
                     " <eager-trace-filepath>"
                     " <trace-comparison-filepath>\n";
        return EXIT_FAILURE;
    }

    std::string lazy_trace_filepath{argv[1]};
    std::string strict_trace_filepath{argv[2]};
    std::string trace_comparison_filepath{argv[3]};

    high_resolution_clock::time_point t1, t2;

    t1 = high_resolution_clock::now();
    auto lazy_stream{instruction::Stream::parse(lazy_trace_filepath)};
    t2 = high_resolution_clock::now();

    std::cout << lazy_stream.size() << " "
              << duration_cast<duration<double>>(t2 - t1).count() << " "
              << std::flush;

    std::cout << "Here\n";

    t1 = high_resolution_clock::now();
    auto strictness_state{analysis::strictness::interpret(lazy_stream)};
    t2 = high_resolution_clock::now();

    std::ofstream trace_comparison_file{trace_comparison_filepath};

    trace_comparison_file << strictness_state;

    trace_comparison_file.close();

    // std::cout << strict_stream.size() << " "
    //           << duration_cast<duration<double>>(t2 - t1).count() << " "
    //           << std::flush;

    // t1 = high_resolution_clock::now();
    // auto
    // strict_binding_state{analysis::binding::interpret(strict_stream)}; t2
    // = high_resolution_clock::now();

    // std::cout << duration_cast<duration<double>>(t2 - t1).count() << " "
    //           << std::flush;

    // t1 = high_resolution_clock::now();
    // std::ofstream strict_trace_file{strict_trace_filepath};
    // strict_trace_file << strict_stream;
    // strict_trace_file.close();
    // t2 = high_resolution_clock::now();

    // std::cout << duration_cast<duration<double>>(t2 - t1).count() <<
    // std::endl;

    return EXIT_SUCCESS;
}
