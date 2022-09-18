#include "args.hpp"

#include <iostream>


namespace args {
    const std::string kPath = "--path";
    const std::string kConcurrency = "--concurrency";
    const std::string kFileCount = "--file_count";
}

bool Args::Initialize( 
    const int arg_count,
    char **args) {

    static const int kRequiredArgCount = 7;
    if (arg_count < kRequiredArgCount) {
        std::cout << "Args count must be more then " << kRequiredArgCount << std::endl;
        return false;
    }

    for (auto i = 1; i<arg_count-1; i+=2) {
        if (std::string(args[i]) == args::kPath) {
            path_to_dir = args[i+1];
        }
        else if (std::string(args[i]) == args::kConcurrency) {
            concurrency = std::atoi(args[i+1]);
        }
        else if (std::string(args[i]) == args::kFileCount) {
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
