# quant-utils

A small C++17 library of quantitative-finance indicators, built as the
project scaffold for the course *"Software Engineering and C++ for
quantitative analysis and algorithmic trading"*.

Currently implemented:

- `quant::simple_moving_average(prices, window)` — simple moving average
  with a rolling window (`NaN` where the window is incomplete).
- `quant::daily_returns(prices)` — period-over-period (daily) returns.

## Project structure

```
quant-utils/
├── include/quant/    # public headers
├── src/              # library implementation
├── apps/             # demo executable
├── tests/            # unit tests (GoogleTest)
├── benchmark/        # benchmarks (Google Benchmark)
├── .github/workflows # CI/CD (GitHub Actions)
└── docs/             # generated documentation (Doxygen)
```

## Requirements

- CMake >= 3.16
- A C++17 compiler (GCC, Clang or MSVC)
- Git (the build downloads GoogleTest and Google Benchmark automatically)

## Build

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
```

Run the demo:

```bash
./build/quant_demo
```

## Tests

Tests use [GoogleTest](https://github.com/google/googletest) and are
enabled by default (`BUILD_TESTING=ON`):

```bash
cmake -S . -B build
cmake --build build -j
ctest --test-dir build --output-on-failure
```

## Benchmarks

Benchmarks use [Google Benchmark](https://github.com/google/benchmark)
and are enabled by default (`BUILD_BENCHMARK=ON`):

```bash
./build/benchmark/bench_indicators
```

## Documentation

Documentation is generated with [Doxygen](https://www.doxygen.nl/) and
published automatically to GitHub Pages on every push to `main`:

[Project documentation](https://WangLu-Caps.github.io/quant-utils/)

To generate it locally:

```bash
doxygen Doxyfile   # HTML output in docs/html/
```

## CI/CD

On every push and pull request, GitHub Actions:

1. builds the project,
2. runs the unit tests (`ctest`),
3. runs the benchmark and prints its results to the CI log,

and on every push to `main` it also builds and publishes the Doxygen
documentation to GitHub Pages.
