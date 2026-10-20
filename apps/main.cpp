#include "quant/indicators.hpp"

#include <cstddef>
#include <iostream>
#include <vector>

int main() {
    const std::vector<double> prices = {100.0, 101.5, 103.0, 102.5, 105.0, 108.0};
    const std::size_t window = 3;

    std::cout << "Daily returns:\n";
    for (double r : quant::daily_returns(prices)) {
        std::cout << "  " << r << '\n';
    }

    std::cout << "Simple moving average (window = " << window << "):\n";
    for (double v : quant::simple_moving_average(prices, window)) {
        std::cout << "  " << v << '\n';
    }

    return 0;
}
