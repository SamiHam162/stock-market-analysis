//
// Created by SamiH on 20/08/2024.
//

#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include <string>
#include <map>
#include <vector>

class DataProcessor {
public:
    // Structure to hold OHLCV data
    struct StockData {
        double open;
        double high;
        double low;
        double close;
        long volume;
    };

    // Method to load JSON data into the internal structure
    void loadData(const std::map<std::string, std::map<std::string, std::string>>& jsonData);

    // Method to calculate simple moving average (SMA)
    std::vector<double> calculateSMA(int period);

    // Method to retrieve all the data
    const std::vector<StockData>& getAllData() const;

private:
    // Vector to hold processed stock data
    std::vector<StockData> stockData;

    // Helper method to parse individual data points
    StockData parseStockData(const std::map<std::string, std::string>& data);
};

#endif // DATAPROCESSOR_H
