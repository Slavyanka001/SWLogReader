#include "data.hpp"

#include <fstream>

#include "parsed_line.hpp"

void LogData::Add(ParsedLine&& object) {
    auto found_day = file_data.find(object.GetDateKey());
    if (found_day == file_data.end()) {
        AddDay(file_data, object.GetDateKey(), object.GetFactName(), object.GetProps());
        return;
    }

    auto found_name = found_day->second.find(object.GetFactName());
    if (found_name == found_day->second.end()) {
        AddName(
            found_day->second,
            object.GetFactName(),
            object.GetProps());
        return;
    }

    auto found_combination = found_name->second.find(object.GetProps());
    if (found_combination == found_name->second.end()) {
        AddCombination(found_name->second, object.GetProps());
        return;
    }

    found_combination->second++;
}

void LogData::Append(DayToNames&& log_data) {
    for (auto& day: log_data) {
        auto found_day = file_data.find(day.first);
        if (found_day == file_data.end()) {
            file_data[day.first] = std::move(day.second);
            continue;
        }

        for (auto& name: day.second) {
            auto found_name = found_day->second.find(name.first);
            if (found_name == found_day->second.end()) {
                found_day->second[name.first] = std::move(name.second);
                continue;
            }

            for (auto& combination: name.second) {
                auto found_combination = found_name->second.find(combination.first);
                if (found_combination == found_name->second.end()) {
                    found_name->second[combination.first]  = std::move(combination.second);
                    continue;
                }

                found_combination->second += combination.second;
            }
        }
    }
}


void LogData::WriteToFile(const std::string& path) {
    std::ofstream file;        
    file.open(path); 
    if (file.is_open()) {
        file << MakeJson() << std::endl;
    }
}

DayToNames& LogData::GetData() {
    return file_data;
}

Json::Value LogData::MakeJson() {
    Json::Value result;
    for (auto date: file_data) {
        result[date.first] = MakeNameJson(date.second);
    }
    return result;
}

Json::Value LogData::MakeNameJson(const NamesToProps& names) {
    Json::Value result;
    for (auto name: names) {
        result[name.first] = MakeCombinationJson(name.second);
    }
    return result;
}

Json::Value LogData::MakeCombinationJson(const PropsToNumber& combinations) {
    Json::Value result;
    for (auto combination: combinations) {
        result[combination.first] = combination.second;
    }
    return result;
}

void LogData::AddCombination(
    PropsToNumber& map, 
    const std::string& props) {
    map.insert({props,1});
}

void LogData::AddName(
    NamesToProps& map, 
    const std::string& fact_name,
    const std::string& props) {
    AddCombination(map[fact_name], props);
}

void LogData::AddDay(
    DayToNames& map,
    const std::string& day,
    const std::string& fact_name,
    const std::string& props)
{
    AddName(file_data[day], fact_name, props);
}