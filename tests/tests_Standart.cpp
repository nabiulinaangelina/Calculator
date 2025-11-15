#include <gtest/gtest.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <cmath>
#include <stdexcept>

#include "Standard.hpp"

TEST(StandardTests, BasicArithmetic) {
    

    EXPECT_EQ(add(2, 3), 5);
    EXPECT_EQ(substract(5, 3), 2);
    EXPECT_EQ(multiply(4, 3), 12);
    EXPECT_EQ(divide(10, 2), 5);

    //TODO: Add more tests for edge cases and error handling
}