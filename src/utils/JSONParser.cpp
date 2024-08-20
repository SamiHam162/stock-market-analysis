//
// Created by SamiH on 20/08/2024.
//

#include "../../include/utils/JSONParser.h"

nlohmann::json JSONParser::parse(const std::string& jsonString) {
    return nlohmann::json::parse(jsonString);
}

std::string JSONParser::serialize(const nlohmann::json& jsonObj) {
    return jsonObj.dump();
}