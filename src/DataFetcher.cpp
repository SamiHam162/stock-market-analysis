//
// Created by SamiH on 20/08/2024.
//

#include "../include/DataFetcher.h"
#include <sstream>

DataFetcher::DataFetcher(const std::string& apiKey, const std::string& baseUrl)
        : apiKey(apiKey), baseUrl(baseUrl) {}

nlohmann::json DataFetcher::fetchIntradayData(const std::string& symbol, const std::string& interval) {
    std::string function = "TIME_SERIES_INTRADAY";
    std::string additionalParams = "&interval=" + interval;
    std::string url = buildUrl(function, symbol, additionalParams);

    std::string response = httpClient.get(url);
    return JSONParser::parse(response);
}

std::vector<nlohmann::json> DataFetcher::fetchHistoricalData(const std::string& symbol, const std::string& startDate, const std::string& endDate) {
    std::string function = "TIME_SERIES_DAILY";
    std::string url = buildUrl(function, symbol);

    std::string response = httpClient.get(url);
    nlohmann::json jsonData = JSONParser::parse(response);

    std::vector<nlohmann::json> historicalData;

    if (jsonData.contains("Time Series (Daily)")) {
        auto timeSeries = jsonData["Time Series (Daily)"];
        for (auto it = timeSeries.begin(); it != timeSeries.end(); ++it) {
            std::string date = it.key();
            if (date >= startDate && date <= endDate) {
                nlohmann::json dayData = it.value();
                dayData["date"] = date;
                historicalData.push_back(dayData);
            }
        }
    }

    return historicalData;
}

std::string DataFetcher::buildUrl(const std::string& function, const std::string& symbol, const std::string& additionalParams) {
    std::ostringstream urlStream;
    urlStream << baseUrl << "/query?function=" << function
              << "&symbol=" << symbol
              << "&apikey=" << apiKey
              << additionalParams;
    return urlStream.str();
}