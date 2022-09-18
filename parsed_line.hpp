#pragma once

#include <string>

#include <jsoncpp/json/json.h>

class ParsedLine {
    public:

        ParsedLine(const Json::Value& data);

        std::string GetDateKey() const;
        std::string GetFactName() const;
        std::string GetProps() const;

    private:

        std::string GetFormatTime(time_t timestamp);
        std::string ParseProps(const Json::Value& data);

        std::string date_key;
        std::string fact_name;
        std::string props;
};