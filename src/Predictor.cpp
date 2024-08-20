//
// Created by SamiH on 20/08/2024.
//

#include "../include/Predictor.h"
#include <stdexcept>
#include <numeric>

// Helper method to perform linear regression
std::pair<double, double> Predictor::linearRegression(const std::vector<double>& x, const std::vector<double>& y) {
    if (x.size() != y.size() || x.empty()) {
        throw std::invalid_argument("Vectors x and y must have the same size and cannot be empty.");
    }

    double n = x.size();
    double sum_x = std::accumulate(x.begin(), x.end(), 0.0);
    double sum_y = std::accumulate(y.begin(), y.end(), 0.0);
    double sum_xy = 0.0;
    double sum_x_squared = 0.0;

    for (size_t i = 0; i < n; ++i) {
        sum_xy += x[i] * y[i];
        sum_x_squared += x[i] * x[i];
    }

    double slope = (n * sum_xy - sum_x * sum_y) / (n * sum_x_squared - sum_x * sum_x);
    double intercept = (sum_y - slope * sum_x) / n;

    return {slope, intercept};
}

// Method to predict future stock price using linear regression
double Predictor::predictNextPrice(const std::vector<DataProcessor::StockData>& data) {
    std::vector<double> x(data.size());
    std::vector<double> y(data.size());

    for (size_t i = 0; i < data.size(); ++i) {
        x[i] = static_cast<double>(i);
        y[i] = data[i].close;
    }

    auto [slope, intercept] = linearRegression(x, y);

    double nextX = static_cast<double>(data.size());
    return slope * nextX + intercept;
}

// Method to predict stock prices for the next N periods
std::vector<double> Predictor::predictNextNPrices(const std::vector<DataProcessor::StockData>& data, int periods) {
    if (periods <= 0) {
        throw std::invalid_argument("Number of periods must be greater than zero.");
    }

    std::vector<double> predictions;
    std::vector<DataProcessor::StockData> dataCopy = data; // Create a copy of the data

    for (int i = 0; i < periods; ++i) {
        double nextPrice = predictNextPrice(dataCopy);
        predictions.push_back(nextPrice);

        // Simulate the next period by adding the predicted value to the data copy
        DataProcessor::StockData simulatedData = dataCopy.back();
        simulatedData.close = nextPrice;
        dataCopy.push_back(simulatedData);
    }

    return predictions;
}