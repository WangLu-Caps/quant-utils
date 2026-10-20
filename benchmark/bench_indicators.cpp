#include "quant/indicators.hpp"

#include <benchmark/benchmark.h>

#include <cstddef>
#include <random>
#include <vector>

namespace {

std::vector<double> make_prices(std::size_t n) {
    std::mt19937 rng(42);
    std::uniform_real_distribution<double> dist(1.0, 1000.0);
    std::vector<double> prices(n);
    for (double& p : prices) {
        p = dist(rng);
    }
    return prices;
}

static void BM_SimpleMovingAverage(benchmark::State& state) {
    const std::vector<double> prices = make_prices(state.range(0));
    for (auto _ : state) {
        benchmark::DoNotOptimize(quant::simple_moving_average(prices, 20));
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_SimpleMovingAverage)
    ->RangeMultiplier(10)
    ->Range(1 << 10, 1 << 20)
    ->Complexity();

static void BM_DailyReturns(benchmark::State& state) {
    const std::vector<double> prices = make_prices(state.range(0));
    for (auto _ : state) {
        benchmark::DoNotOptimize(quant::daily_returns(prices));
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_DailyReturns)
    ->RangeMultiplier(10)
    ->Range(1 << 10, 1 << 20)
    ->Complexity();

} // namespace

BENCHMARK_MAIN();
