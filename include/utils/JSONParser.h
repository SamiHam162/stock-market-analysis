//
// Created by SamiH on 20/08/2024.
//

#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <string>
#include <nlohmann/json.hpp>

class JSONParser {
public:
    // Method to parse a JSON string into a JSON object
    static nlohmann::json parse(const std::string& jsonString);

    // Method to serialize a JSON object into a string
    static std::string serialize(const nlohmann::json& jsonObj);
};

#endif // JSONPARSER_H
