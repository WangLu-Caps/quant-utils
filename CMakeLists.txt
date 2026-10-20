cmake_minimum_required(VERSION 3.16)
project(quant_utils VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# BUILD_TESTING option (default ON) + enable_testing()
include(CTest)

option(BUILD_BENCHMARK "Build the benchmark targets" ON)

# ---------------------------------------------------------------------------
# Core library: quant
# ---------------------------------------------------------------------------
add_library(quant src/indicators.cpp)
target_include_directories(quant PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(MSVC)
    target_compile_options(quant PRIVATE /W4)
else()
    target_compile_options(quant PRIVATE -Wall -Wextra)
endif()

# ---------------------------------------------------------------------------
# Demo executable
# ---------------------------------------------------------------------------
add_executable(quant_demo apps/main.cpp)
target_link_libraries(quant_demo PRIVATE quant)

# ---------------------------------------------------------------------------
# Unit tests (GoogleTest)
# ---------------------------------------------------------------------------
if(BUILD_TESTING)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.14.0
    )
    # Avoid runtime mismatch on MSVC between /MT and /MD builds.
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    add_subdirectory(tests)
endif()

# ---------------------------------------------------------------------------
# Benchmarks (Google Benchmark)
# ---------------------------------------------------------------------------
if(BUILD_BENCHMARK)
    include(FetchContent)
    FetchContent_Declare(
        googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG        v1.8.3
    )
    # Do not build google/benchmark's own tests.
    set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googlebenchmark)
    add_subdirectory(benchmark)
endif()
