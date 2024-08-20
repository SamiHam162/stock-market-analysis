//
// Created by SamiH on 20/08/2024.
//

//#include "../include/DataFetcher.h"
//#include <iostream>
//
//int main() {
//    std::string apiKey = "7YWXXHB280VU6DKX";
//    DataFetcher dataFetcher(apiKey);
//    //This means we are getting Apple stock!!!!!!!!!
//    std::string symbol = "AAPL";
//    auto intradayData = dataFetcher.fetchIntradayData(symbol);
//    std::cout << intradayData.dump(4) << std::endl;
//
//    std::string startDate = "2023-01-01";
//    std::string endDate = "2023-12-31";
//    auto historicalData = dataFetcher.fetchHistoricalData(symbol, startDate, endDate);
//
//    for (const auto& dayData : historicalData) {
//        std::cout << "Date: " << dayData["date"] << " - Open: " << dayData["1. open"] << std::endl;
//    }
//
//    return 0;
//}

#include <iostream>
#include <fstream>
//#include <nlohmann/json.hpp>
#include "../include/json.hpp"
#include "../include/DataFetcher.h"
#include "../include/DataProcessor.h"
#include "../include/Predictor.h"
#include "../include/Visualizer.h"
#include "../include/AlertManager.h"
#include "../include/utils/HttpClient.h"
#include "../include/utils/JSONParser.h"
#include "../include/utils/ThreadPool.h"

using json = nlohmann::json;

void createFileIfNotExists(const std::string& filePath) {
    std::filesystem::path path(filePath);
    if (!std::filesystem::exists(path.parent_path())) {
        std::filesystem::create_directories(path.parent_path());
    }

    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error opening file to write data: " << filePath << std::endl;
        std::exit(1);
    }
    file.close();
}

// Function to load configuration from config.json
void loadConfig(const std::string& filename, json& config) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening config file: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }
    file >> config;
}

// Function to convert historical data to a CSV file
void saveHistoricalDataToCSV(const std::string& filePath, const std::vector<nlohmann::json>& historicalData) {
    std::ofstream outFile(filePath);
    if (outFile.is_open()) {
        // Write header
        outFile << "Date,Open,High,Low,Close,Volume\n";

        // Write data
        for (const auto& dayData : historicalData) {
            outFile << dayData["date"] << ","
                    << dayData["1. open"] << ","
                    << dayData["2. high"] << ","
                    << dayData["3. low"] << ","
                    << dayData["4. close"] << ","
                    << dayData["5. volume"] << "\n";
        }
        outFile.close();
    } else {
        std::cerr << "Error opening file to write data: " << filePath << std::endl;
        exit(EXIT_FAILURE);
    }
}

// Function to convert historical data to a map of maps
std::map<std::string, std::map<std::string, std::string>> convertJSONToMap(const std::vector<nlohmann::json>& historicalData) {
    std::map<std::string, std::map<std::string, std::string>> dataMap;

    for (const auto& dayData : historicalData) {
        std::string date = dayData["date"];
        std::map<std::string, std::string> dataPoints;
        dataPoints["1. open"] = dayData["1. open"];
        dataPoints["2. high"] = dayData["2. high"];
        dataPoints["3. low"] = dayData["3. low"];
        dataPoints["4. close"] = dayData["4. close"];
        dataPoints["5. volume"] = dayData["5. volume"];
        dataMap[date] = dataPoints;
    }

    return dataMap;
}


// Main function
int main() {
    // Load configuration
    json config;
    loadConfig("../data/config.json", config);

    std::string apiKey = config["api_key"];
    std::string baseUrl = config["base_url"];
    std::string symbol = config["symbol"];
    std::string startDate = config["start_date"];
    std::string endDate = config["end_date"];
    std::string dataFilePath = config["data_file_path"];
    auto alertConditionsJson = config["alert_conditions"];
    createFileIfNotExists(dataFilePath);
    // Convert JSON alert conditions to vector of pairs
    std::vector<std::pair<double, std::string>> alertConditions;
    for (const auto& alertCondition : alertConditionsJson) {
        double threshold = alertCondition["threshold"];
        std::string message = alertCondition["message"];
        alertConditions.emplace_back(threshold, message);
    }

    // Create instances of classes
    DataFetcher dataFetcher(apiKey, baseUrl);
    DataProcessor dataProcessor;
    Predictor predictor;
    Visualizer visualizer;
    AlertManager alertManager(alertConditions);

    // Fetch historical data
    std::cout << "Fetching historical data..." << std::endl;
    std::vector<nlohmann::json> historicalData = dataFetcher.fetchHistoricalData(symbol, startDate, endDate);

    // Save the fetched data to the historical_data directory
    saveHistoricalDataToCSV(dataFilePath, historicalData);

    // Convert JSON data to map format for DataProcessor
    std::cout << "Loading data into DataProcessor..." << std::endl;
    auto dataMap = convertJSONToMap(historicalData);
    dataProcessor.loadData(dataMap);

    // Calculate moving averages or other metrics
    std::cout << "Calculating moving averages..." << std::endl;
    std::vector<double> smaValues = dataProcessor.calculateSMA(10); // Example period

    // Predict future stock prices
    std::cout << "Predicting data..." << std::endl;
    int predictionPeriods = 10; // Example number of periods to predict
    std::vector<double> predictions = predictor.predictNextNPrices(dataProcessor.getAllData(), predictionPeriods);


    // Visualize data
    std::cout << "Visualizing data..." << std::endl;
    visualizer.plotStockPrices(dataProcessor.getAllData(), predictions, symbol);

    // Visualize data
    std::cout << "Visualizing data..." << std::endl;
    visualizer.visualize(predictions);

    // Manage alerts
    std::cout << "Checking alerts..." << std::endl;
    alertManager.checkAlerts(predictions);

    std::cout << "Process completed." << std::endl;

    return 0;
}


