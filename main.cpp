//// This program does not do anything. Use the ctf.hpp header as a drop in to parse args and flags
// testing suite for the library

#include <iostream>
#include <string>
#include <vector>

#include "ctf.hpp"


int main(int argc, char *argv[]) {

    // Just for testing, does not actually do anything.

    auto args = process_cli_arguments(argc, argv);

    std::cout << "Length of the arg list: " << args.arg_lst.size() << "\n";

    std::string arg_dump = args.dump_args();
    std::cout << "Dumping arg content:\n" << arg_dump << "\n";

    return 0;
}