//
// Created by SamiH on 20/08/2024.
//

#ifndef ALERTMANAGER_H
#define ALERTMANAGER_H

#include <string>
#include <vector>

class AlertManager {
public:
    AlertManager(const std::vector<std::pair<double, std::string>>& conditions);
    void checkAlerts(const std::vector<double>& prices);
    void addAlertCondition(double threshold, const std::string& message);

private:
    std::vector<std::pair<double, std::string>> alertConditions;

    void triggerAlert(const std::string& message);
};

#endif // ALERTMANAGER_H
