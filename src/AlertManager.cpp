//
// Created by SamiH on 20/08/2024.
//

#include "../include/AlertManager.h"
#include <iostream>

// Constructor with alert conditions
AlertManager::AlertManager(const std::vector<std::pair<double, std::string>>& conditions)
        : alertConditions(conditions) {
    // Constructor implementation
}

void AlertManager::checkAlerts(const std::vector<double>& prices) {
    for (const auto& condition : alertConditions) {
        double threshold = condition.first;
        const std::string& message = condition.second;

        for (double price : prices) {
            if (price > threshold) {
                triggerAlert(message);
                break; // Assuming we only need to trigger the alert once per condition
            }
        }
    }
}

void AlertManager::addAlertCondition(double threshold, const std::string& message) {
    alertConditions.emplace_back(threshold, message);
}

void AlertManager::triggerAlert(const std::string& message) {
    // For simplicity, we'll just print the alert message to the console.
    // You can modify this to send emails, notifications, etc.
    std::cout << "ALERT: " << message << std::endl;
}