#pragma once

#include "itask.hpp"

#include <string>
#include <shared_mutex>

#include "data.hpp"

class Task: public ITask{
    public:
        Task(
            LogData& common_data,
            std::shared_mutex& common_mutex,
            const std::string& path, 
            int first,
            int last);

        ~Task(){};
    
        void work() final;

    private:

        std::string MakePathToFile(int file_number);

        const std::string path_to_dir;

        const int first_file_number;
        const int last_file_number;

        std::shared_mutex& mutex;
        LogData& data;
};