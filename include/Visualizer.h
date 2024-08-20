//
// Created by SamiH on 20/08/2024.
//

#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <vector>
#include <string>
#include "DataProcessor.h"
#include "matplotlibcpp.h"  // Assuming you're using matplotlib-cpp for visualization

class Visualizer {
public:
    // Method to visualize predicted prices
    void visualize(const std::vector<double>& predictedPrices);

    // Method to plot historical and predicted stock prices
    void plotStockPrices(const std::vector<DataProcessor::StockData>& historicalData,
                         const std::vector<double>& predictedPrices,
                         const std::string& stockSymbol);

private:
    // Helper function to plot data using matplotlib
    void plot(const std::vector<double>& data, const std::string& label, const std::string& color);
};

#endif // VISUALIZER_H
