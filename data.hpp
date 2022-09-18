#pragma once

#include <unordered_map>
#include <string>

#include "parsed_line.hpp"

using PropsToNumber = std::unordered_map<std::string, unsigned int>;
using NamesToProps = std::unordered_map<std::string, PropsToNumber>;
using DayToNames = std::unordered_map<std::string,NamesToProps>;

class LogData {

    public:

        void Add(ParsedLine&& object);
        void Append(DayToNames&& log_data);
        void WriteToFile(const std::string& path);

        DayToNames& GetData();

    private:
        
        Json::Value MakeJson();
        Json::Value MakeNameJson(const NamesToProps& names);
        Json::Value MakeCombinationJson(const PropsToNumber& combinations);

        void AddCombination(
            PropsToNumber& map, 
            const std::string& props);

        void AddName(
            NamesToProps& map, 
            const std::string& fact_name,
            const std::string& props);

        void AddDay(
            DayToNames& map,
            const std::string& day,
            const std::string& fact_name,
            const std::string& props);

        DayToNames file_data;
};