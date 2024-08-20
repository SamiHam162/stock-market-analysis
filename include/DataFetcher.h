//
// Created by SamiH on 20/08/2024.
//

#ifndef DATAFETCHER_H
#define DATAFETCHER_H

#include <string>
#include <vector>
#include "utils/HttpClient.h"
#include "utils/JSONParser.h"

class DataFetcher {
public:
    // Constructor with an API key and base URL
    DataFetcher(const std::string& apiKey = "7YWXXHB280VU6DKX" , const std::string& baseUrl = "https://www.alphavantage.co");

    // Method to fetch intraday stock data by symbol
    nlohmann::json fetchIntradayData(const std::string& symbol, const std::string& interval = "5min");

    // Method to fetch historical stock data
    std::vector<nlohmann::json> fetchHistoricalData(const std::string& symbol, const std::string& startDate, const std::string& endDate);

private:
    // Helper method to build the full API URL
    std::string buildUrl(const std::string& function, const std::string& symbol, const std::string& additionalParams = "");

    std::string apiKey;
    std::string baseUrl;
    HttpClient httpClient;
};

#endif // DATAFETCHER_H