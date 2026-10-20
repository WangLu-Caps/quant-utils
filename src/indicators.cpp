#include "quant/indicators.hpp"

#include <limits>
#include <stdexcept>

namespace quant {

std::vector<double> simple_moving_average(const std::vector<double>& prices,
                                          std::size_t window) {
    if (window == 0) {
        throw std::invalid_argument("simple_moving_average: window must be > 0");
    }

    const std::size_t n = prices.size();
    std::vector<double> result(n, std::numeric_limits<double>::quiet_NaN());

    if (window > n) {
        return result; // every position lacks a complete window
    }

    double running_sum = 0.0;
    for (std::size_t i = 0; i < n; ++i) {
        running_sum += prices[i];
        if (i >= window) {
            running_sum -= prices[i - window];
        }
        if (i + 1 >= window) {
            result[i] = running_sum / static_cast<double>(window);
        }
    }
    return result;
}

std::vector<double> daily_returns(const std::vector<double>& prices) {
    if (prices.size() < 2) {
        return {};
    }

    std::vector<double> result;
    result.reserve(prices.size() - 1);
    for (std::size_t i = 1; i < prices.size(); ++i) {
        result.push_back((prices[i] - prices[i - 1]) / prices[i - 1]);
    }
    return result;
}

} // namespace quant
