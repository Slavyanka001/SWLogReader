#include "args.hpp"

#include <iostream>

bool Args::Initialize( 
    const int arg_count,
    char **args) {

    if (arg_count != c_required_arg_count) {
        std::cout << "Args count must be equal " << c_required_arg_count << std::endl;
        return false;
    }

    for (auto i = 1; i<arg_count-1; i+=2) {
        if (std::string(args[i]) == "--path") {
            path_to_dir = args[i+1];
        }
        else if (std::string(args[i]) == "--concurrency") {
            concurrency = std::atoi(args[i+1]);
        }
        else if (std::string(args[i]) == "--file_count") {
            file_count = std::atoi(args[i+1]);
        }
    }

    if (!file_count || file_count.value() < 1 || !concurrency ||
        concurrency.value() < 1 || !path_to_dir) {
        std::cout << "Something wrong with parameters" << std::endl;
        return false;
    }
    return true;
}

int Args::GetConcurrency() const {
    return concurrency.value();
}

int Args::GetFileCount() const {
    return file_count.value();
}

std::string Args::GetPathToDir() const {
    return path_to_dir.value();
}
