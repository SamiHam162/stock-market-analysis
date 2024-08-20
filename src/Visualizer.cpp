//
// Created by SamiH on 20/08/2024.
//

#include "../include/Visualizer.h"

namespace plt = matplotlibcpp;  // Alias for matplotlibcpp

void Visualizer::visualize(const std::vector<double>& predictedPrices) {
    // For simplicity, visualize predictions only
    // Historical data is not passed here, so we will not include it in the plot
    plot(predictedPrices, "Predicted Prices", "red");

    // Set the title and labels
    plt::title("Predicted Stock Prices");
    plt::xlabel("Time (Days)");
    plt::ylabel("Price");

    // Add a legend
    plt::legend();

    // Show the plot
    plt::show();
}

void Visualizer::plotStockPrices(const std::vector<DataProcessor::StockData>& historicalData,
                                 const std::vector<double>& predictedPrices,
                                 const std::string& stockSymbol)
{
    std::vector<double> historicalPrices;
    for (const auto& data : historicalData) {
        historicalPrices.push_back(data.close);
    }

    // Plot historical data
    plot(historicalPrices, "Historical Prices", "blue");

    // Plot predicted data
    plot(predictedPrices, "Predicted Prices", "red");

    // Set the title and labels
    plt::title("Stock Prices for " + stockSymbol);
    plt::xlabel("Time (Days)");
    plt::ylabel("Price");

    // Add a legend
    plt::legend();

    // Show the plot
    plt::show();
}

void Visualizer::plot(const std::vector<double>& data, const std::string& label, const std::string& color) {
    // Generate a time vector for the x-axis
    std::vector<int> time(data.size());
    for (size_t i = 0; i < time.size(); ++i) {
        time[i] = static_cast<int>(i);
    }

    // Plot the data
//    plt::plot(time, data, {{"label", label}, {"color", color}});
    plt::plot(time, data);
}