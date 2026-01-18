#include <gtest/gtest.h>
#include <cmath>
#include "Calculator.hpp"
#include "commands/scientific/SinCommand.hpp"
#include "commands/scientific/CosCommand.hpp"
#include "commands/scientific/TanCommand.hpp"
#include "commands/scientific/PowCommand.hpp"
#include "commands/scientific/LogCommand.hpp"
#include "commands/scientific/ExpCommand.hpp"

TEST(ScientificTests, SinCommand) {
    SinCommand sinCmd(M_PI/2, true); // 90 градусов в радианах
    EXPECT_NEAR(sinCmd.execute(), 1.0, 1e-10);
    
    SinCommand sinDeg(90.0, false); // 90 градусов
    EXPECT_NEAR(sinDeg.execute(), 1.0, 1e-10);
}

TEST(ScientificTests, CosCommand) {
    CosCommand cosCmd(0.0, true); // 0 радиан
    EXPECT_NEAR(cosCmd.execute(), 1.0, 1e-10);
    
    CosCommand cosDeg(60.0, false); // 60 градусов
    EXPECT_NEAR(cosDeg.execute(), 0.5, 1e-10);
}

TEST(ScientificTests, TanCommand) {
    TanCommand tanCmd(M_PI/4, true); // 45 градусов в радианах
    EXPECT_NEAR(tanCmd.execute(), 1.0, 1e-10);
}

TEST(ScientificTests, TanCommandEdgeCases) {
    // tan(π/2) должен выбросить исключение
    TanCommand tanCmd(M_PI/2, true);
    EXPECT_THROW(tanCmd.execute(), std::invalid_argument);
}

TEST(ScientificTests, PowCommand) {
    PowCommand powCmd(2.0, 3.0);
    EXPECT_DOUBLE_EQ(powCmd.execute(), 8.0);
    
    PowCommand powSqrt(9.0, 0.5);
    EXPECT_DOUBLE_EQ(powSqrt.execute(), 3.0);
}

TEST(ScientificTests, PowCommandEdgeCases) {
    // 0 в отрицательной степени
    PowCommand powCmd(0.0, -2.0);
    EXPECT_THROW(powCmd.execute(), std::invalid_argument);
}

TEST(ScientificTests, LogCommand) {
    LogCommand logCmd(std::exp(1.0)); // ln(e) = 1
    EXPECT_NEAR(logCmd.execute(), 1.0, 1e-10);
    
    LogCommand logTen(std::exp(2.0)); // ln(e^2) = 2
    EXPECT_NEAR(logTen.execute(), 2.0, 1e-10);
}

TEST(ScientificTests, LogCommandEdgeCases) {
    // ln(0) и ln(-1) должны выбросить исключение
    LogCommand logZero(0.0);
    EXPECT_THROW(logZero.execute(), std::invalid_argument);
    
    LogCommand logNegative(-1.0);
    EXPECT_THROW(logNegative.execute(), std::invalid_argument);
}

TEST(ScientificTests, ExpCommand) {
    ExpCommand expCmd(1.0);
    EXPECT_NEAR(expCmd.execute(), std::exp(1.0), 1e-10);
    
    ExpCommand expZero(0.0);
    EXPECT_NEAR(expZero.execute(), 1.0, 1e-10);
}

TEST(ScientificTests, CalculatorIntegration) {
    Calculator* calc = Calculator::getInstance();
    calc->clearHistory();
    
    // Тест через Calculator
    double sinResult = calc->executeCommand("sin", {M_PI/6});
    EXPECT_NEAR(sinResult, 0.5, 1e-10);
    
    double powResult = calc->executeCommand("pow", {2.0, 3.0});
    EXPECT_DOUBLE_EQ(powResult, 8.0);
    
    double logResult = calc->executeCommand("log", {std::exp(1.0)});
    EXPECT_NEAR(logResult, 1.0, 1e-10);
}

TEST(ScientificTests, UndoRedoScientific) {
    Calculator* calc = Calculator::getInstance();
    calc->clearHistory();
    
    double result1 = calc->executeCommand("sin", {M_PI/2});
    EXPECT_NEAR(result1, 1.0, 1e-10);
    
    double result2 = calc->executeCommand("cos", {0.0});
    EXPECT_NEAR(result2, 1.0, 1e-10);
    
    // Undo
    EXPECT_TRUE(calc->undo());
    EXPECT_NEAR(calc->getCurrentResult(), 1.0, 1e-10); // Возвращаемся к sin(π/2)
    
    // Redo
    EXPECT_TRUE(calc->redo());
    EXPECT_NEAR(calc->getCurrentResult(), 1.0, 1e-10); // Снова cos(0)
}