#include "parsed_line.hpp"

#include <iomanip>
#include <set>

namespace consts {
    const std::string kTimeKey = "ts_fact";
    const std::string kNameKey = "fact_name";
    const std::string kPropsKey = "props";
    const std::string kPropKey = "prop";
    
    const int kPropsCount = 10;
}

ParsedLine::ParsedLine(const Json::Value& data):
    date_key{GetFormatTime(data[consts::kTimeKey].asUInt())},
    fact_name{data[consts::kNameKey].asString()},
    props{ParseProps(data[consts::kPropsKey])}
{};

std::string ParsedLine::GetDateKey() const {
    return date_key;
}

std::string ParsedLine::GetFactName() const {
    return fact_name;
}

std::string ParsedLine::GetProps() const {
    return props;
}

std::string ParsedLine::GetFormatTime(time_t timestamp) {    
    std::tm timetm;
    gmtime_r(&timestamp, &timetm);

    std::ostringstream os;
    os << std::put_time(&timetm, "%F");
    return os.str();
}

std::string ParsedLine::ParseProps(const Json::Value& data) {
    std::string result;

    std::set<int32_t> temp;
    for (auto i = 0;i < consts::kPropsCount;++i) {
        auto value = data[consts::kPropKey + std::to_string(i+1)].asInt();
        temp.insert(value);
    }

    for (auto elem: temp) {
        result += std::to_string(elem) + ",";
    }
    result.erase(result.size() - 1);

    return result;
}
