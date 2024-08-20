//
// Created by SamiH on 20/08/2024.
//

#include "../include/DataProcessor.h"
#include <stdexcept>
#include <numeric>

// Helper method to parse individual data points
DataProcessor::StockData DataProcessor::parseStockData(const std::map<std::string, std::string>& data) {
    StockData stockData;
    stockData.open = std::stod(data.at("1. open"));
    stockData.high = std::stod(data.at("2. high"));
    stockData.low = std::stod(data.at("3. low"));
    stockData.close = std::stod(data.at("4. close"));
    stockData.volume = std::stol(data.at("5. volume"));
    return stockData;
}

// Method to load JSON data into the internal structure
void DataProcessor::loadData(const std::map<std::string, std::map<std::string, std::string>>& jsonData) {
    for (const auto& [time, data] : jsonData) {
        StockData stockData = parseStockData(data);
        this->stockData.push_back(stockData);
    }
}

// Method to calculate simple moving average (SMA)
std::vector<double> DataProcessor::calculateSMA(int period) {
    if (period <= 0 || period > stockData.size()) {
        throw std::invalid_argument("Invalid period for SMA calculation.");
    }

    std::vector<double> smaValues;
    for (size_t i = 0; i <= stockData.size() - period; ++i) {
        double sum = 0.0;
        for (size_t j = 0; j < period; ++j) {
            sum += stockData[i + j].close;
        }
        smaValues.push_back(sum / period);
    }
    return smaValues;
}

// Method to retrieve all the data
const std::vector<DataProcessor::StockData>& DataProcessor::getAllData() const {
    return stockData;
}