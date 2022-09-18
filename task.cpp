#include "task.hpp"

#include <iostream>
#include <fstream>

#include "parsed_line.hpp"

Task::Task(
    LogData& common_data,
    std::shared_mutex& common_mutex,
    const std::string& path, 
    int first,
    int last)
:   path_to_dir(path),    
    first_file_number(first),
    last_file_number(last),
    mutex(common_mutex),
    data(common_data)
    {};

void Task::work() {
    auto i = first_file_number;
    while (i < last_file_number) {
        auto path_to_file = MakePathToFile(i);
        std::ifstream file(path_to_file);

        std::string line;
        LogData local_data;
    
        while(getline(file, line)) {
            Json::Reader reader;
            Json::Value obj;

            reader.parse(line, obj);
            local_data.Add(ParsedLine(obj));
        }
   
        {
            std::unique_lock write_lock(mutex);
            data.Append(std::move(local_data.GetData()));

            std::cout << path_to_file << " finished." << std::endl;
        }
         ++i;
    }   
}

std::string Task::MakePathToFile(int file_number) {
    return path_to_dir + "/file" + std::to_string(file_number) + ".log";
}