
cmake_minimum_required(VERSION 3.20)

project(NeuralNetCpp VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)
include(FetchContent)

add_library(neuralnet
    src/matrix.cpp
)

target_include_directories(neuralnet PUBLIC include)

if(MSVC)
    target_compile_options(neuralnet PRIVATE
        /W4
        /permissive-
    )
else()
    target_compile_options(neuralnet PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
    )
endif()

add_executable(matrix_demo
    examples/matrix_demo.cpp
)

target_link_libraries(matrix_demo PRIVATE neuralnet)

if(BUILD_TESTING)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    add_executable(neuralnet_tests
        tests/test_matrix.cpp
    )

    target_link_libraries(neuralnet_tests
        PRIVATE neuralnet GTest::gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(neuralnet_tests)
endif()