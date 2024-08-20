//
// Created by SamiH on 20/08/2024.
//

#ifndef PREDICTOR_H
#define PREDICTOR_H

#include "DataProcessor.h"
#include <vector>

class Predictor {
public:
    // Method to predict future stock price using linear regression
    double predictNextPrice(const std::vector<DataProcessor::StockData>& data);

    // Method to predict stock prices for the next N periods
    std::vector<double> predictNextNPrices(const std::vector<DataProcessor::StockData>& data, int periods);

private:
    // Helper method to perform linear regression
    std::pair<double, double> linearRegression(const std::vector<double>& x, const std::vector<double>& y);
};

#endif // PREDICTOR_H
