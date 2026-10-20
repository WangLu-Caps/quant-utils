#include "quant/indicators.hpp"

#include <gtest/gtest.h>

#include <cmath>
#include <vector>

namespace {

bool is_nan(double x) { return std::isnan(x); }

TEST(SimpleMovingAverage, BasicWindow) {
    const std::vector<double> prices = {1.0, 2.0, 3.0, 4.0, 5.0};
    const auto sma = quant::simple_moving_average(prices, 3);

    ASSERT_EQ(sma.size(), prices.size());
    EXPECT_TRUE(is_nan(sma[0]));
    EXPECT_TRUE(is_nan(sma[1]));
    EXPECT_DOUBLE_EQ(sma[2], 2.0); // mean(1,2,3)
    EXPECT_DOUBLE_EQ(sma[3], 3.0); // mean(2,3,4)
    EXPECT_DOUBLE_EQ(sma[4], 4.0); // mean(3,4,5)
}

TEST(SimpleMovingAverage, WindowEqualToOne) {
    const std::vector<double> prices = {7.0, 8.0, 9.0};
    const auto sma = quant::simple_moving_average(prices, 1);
    ASSERT_EQ(sma.size(), prices.size());
    EXPECT_DOUBLE_EQ(sma[0], 7.0);
    EXPECT_DOUBLE_EQ(sma[1], 8.0);
    EXPECT_DOUBLE_EQ(sma[2], 9.0);
}

TEST(SimpleMovingAverage, WindowLargerThanData) {
    const std::vector<double> prices = {1.0, 2.0};
    const auto sma = quant::simple_moving_average(prices, 5);
    ASSERT_EQ(sma.size(), prices.size());
    for (double v : sma) {
        EXPECT_TRUE(is_nan(v));
    }
}

TEST(SimpleMovingAverage, ZeroWindowThrows) {
    const std::vector<double> prices = {1.0, 2.0, 3.0};
    EXPECT_THROW(quant::simple_moving_average(prices, 0), std::invalid_argument);
}

TEST(DailyReturns, Basic) {
    const std::vector<double> prices = {100.0, 110.0, 121.0};
    const auto r = quant::daily_returns(prices);
    ASSERT_EQ(r.size(), 2u);
    EXPECT_NEAR(r[0], 0.10, 1e-12); // (110-100)/100
    EXPECT_NEAR(r[1], 0.10, 1e-12); // (121-110)/110
}

TEST(DailyReturns, NegativeReturn) {
    const std::vector<double> prices = {100.0, 90.0};
    const auto r = quant::daily_returns(prices);
    ASSERT_EQ(r.size(), 1u);
    EXPECT_NEAR(r[0], -0.10, 1e-12);
}

TEST(DailyReturns, TooFewPrices) {
    const std::vector<double> one = {100.0};
    EXPECT_TRUE(quant::daily_returns(one).empty());
    EXPECT_TRUE(quant::daily_returns(std::vector<double>{}).empty());
}

} // namespace
