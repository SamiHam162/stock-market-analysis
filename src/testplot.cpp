//
// Created by SamiH on 20/08/2024.
//


#include "../include/matplotlibcpp.h"
#include <vector>

namespace plt = matplotlibcpp;

int main() {
    std::vector<double> x = {1, 2, 3, 4};
    std::vector<double> y = {1, 4, 9, 16};

    plt::plot(x, y);
    plt::title("Test Plot");
    plt::show();

    return 0;
}