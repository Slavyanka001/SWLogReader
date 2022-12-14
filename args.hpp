#pragma once

#include <string>
#include <optional>

class Args {
    public:
        bool Initialize( 
            const int arg_count,
            char **args);

        std::string GetPathToDir() const;
        int GetFileCount() const;
        int GetConcurrency() const;
    
    private:
      std::optional<int> concurrency;
      std::optional<int> file_count;
      std::optional<std::string> path_to_dir;
};