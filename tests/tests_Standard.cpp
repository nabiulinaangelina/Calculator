#include <gtest/gtest.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <cmath>
#include <stdexcept>
#include <climits>

#include "Standard.hpp"

TEST(StandardTests, BasicArithmetic) {
    // Тестирование сложения
    EXPECT_EQ(add(2, 3), 5);
    EXPECT_EQ(add(-5, 10), 5);
    EXPECT_EQ(add(0, 0), 0);

    // Тестирование вычитания
    EXPECT_EQ(substract(5, 3), 2);
    EXPECT_EQ(substract(10, 15), -5);
    EXPECT_EQ(substract(0, 0), 0);

    // Тестирование умножения
    EXPECT_EQ(multiply(4, 3), 12);
    EXPECT_EQ(multiply(-2, 5), -10);
    EXPECT_EQ(multiply(0, 100), 0);

    // Тестирование деления
    EXPECT_EQ(divide(10, 2), 5);
    EXPECT_EQ(divide(9, 3), 3);
    EXPECT_EQ(divide(0, 5), 0);
}

TEST(StandardTests, DivisionByZero) {
    // Тестирование деления на ноль
    EXPECT_THROW(divide(10, 0), std::invalid_argument);
    EXPECT_THROW(divide(0, 0), std::invalid_argument);
    EXPECT_THROW(divide(-5, 0), std::invalid_argument);
}

TEST(StandardTests, EdgeCases) {
    // Граничные случаи
    EXPECT_EQ(add(INT_MAX, 0), INT_MAX);
    EXPECT_EQ(substract(INT_MIN, 0), INT_MIN);

    // Деление с остатком
    EXPECT_EQ(divide(7, 2), 3); // целочисленное деление
    EXPECT_EQ(divide(-7, 2), -3);
}