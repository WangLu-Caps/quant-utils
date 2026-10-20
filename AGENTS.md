# AGENTS.md

Guidance for AI coding agents (Claude Code, Cursor, Copilot, etc.) working
on this repository.

## Project purpose

`quant-utils` is a small C++17 library of quantitative-finance indicators
(simple moving average and daily returns), used as the project scaffold for
the course *"Software Engineering and C++ for quantitative analysis and
algorithmic trading"*. It is intentionally small: the goal of the repository
is a clean, fully automated C++ project (build, tests, benchmarks, docs)
rather than a large feature set.

## Project structure

- `include/quant/` — public headers (this is the library API).
- `src/` — implementation files.
- `apps/` — executable(s) built on top of the library.
- `tests/` — unit tests (GoogleTest).
- `benchmark/` — benchmarks (Google Benchmark).
- `.github/workflows/` — CI/CD (GitHub Actions).
- `docs/` — generated Doxygen output (do not edit by hand).

## Commands

```bash
# Configure + build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j

# Run the demo
./build/quant_demo

# Run unit tests
ctest --test-dir build --output-on-failure

# Run benchmarks
./build/benchmark/bench_indicators

# Generate documentation
doxygen Doxyfile
```

## Code style

- C++17, no compiler extensions (`-std=c++17`, `CMAKE_CXX_EXTENSIONS OFF`).
- Everything lives in the `quant::` namespace.
- Use `#pragma once` for header guards.
- Public headers carry Doxygen `///` comments documenting parameters,
  return values, and thrown exceptions.
- Keep functions small and pure (no global mutable state).

## Rules and constraints for agents

- Before finishing any task: configure, build the project, and run the
  tests. All tests must pass.
- Do not modify `.github/workflows/` or CI/CD configuration unless
  explicitly asked.
- Do not change the public API in `include/quant/` without updating the
  corresponding tests, benchmarks, and Doxygen comments.
- Do not add third-party dependencies beyond GoogleTest and Google
  Benchmark without an explicit request.
- Do not commit build artifacts (`build/`, `docs/html/`).
