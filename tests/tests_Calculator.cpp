#include <gtest/gtest.h>
#include "Calculator.hpp"
#include "data_structures/MyStack.hpp"

TEST(CalculatorTests, SingletonPattern) {
    Calculator* calc1 = Calculator::getInstance();
    Calculator* calc2 = Calculator::getInstance();
    
    EXPECT_EQ(calc1, calc2) << "Singleton should return same instance";
}

TEST(CalculatorTests, CommandExecution) {
    Calculator* calc = Calculator::getInstance();
    calc->clearHistory(); // Очищаем перед тестом
    
    // Тестирование сложения
    double result = calc->executeCommand("add", {10.5, 20.3});
    EXPECT_DOUBLE_EQ(result, 30.8);
    
    // Тестирование вычитания
    result = calc->executeCommand("subtract", {30.8, 10.5});
    EXPECT_DOUBLE_EQ(result, 20.3);
    
    // Тестирование квадратного корня
    result = calc->executeCommand("sqrt", {25.0});
    EXPECT_DOUBLE_EQ(result, 5.0);
}

TEST(CalculatorTests, InvalidCommand) {
    Calculator* calc = Calculator::getInstance();
    
    EXPECT_THROW(calc->executeCommand("invalid_command", {}), std::invalid_argument);
    EXPECT_THROW(calc->executeCommand("add", {10.0}), std::invalid_argument); // Не хватает операндов
}

TEST(CalculatorTests, HistoryManagement) {
    Calculator* calc = Calculator::getInstance();
    calc->clearHistory();
    
    calc->executeCommand("add", {1, 2});
    calc->executeCommand("subtract", {5, 3});
    
    auto history = calc->getHistory();
    EXPECT_EQ(history.size(), 2);
    
    calc->clearHistory();
    EXPECT_TRUE(calc->getHistory().empty());
}

TEST(MyStackTests, BasicOperations) {
    MyStack<int> stack;
    
    EXPECT_TRUE(stack.isEmpty());
    EXPECT_EQ(stack.size(), 0);
    
    stack.push(10);
    stack.push(20);
    stack.push(30);
    
    EXPECT_FALSE(stack.isEmpty());
    EXPECT_EQ(stack.size(), 3);
    EXPECT_EQ(stack.peek(), 30);
    
    EXPECT_EQ(stack.pop(), 30);
    EXPECT_EQ(stack.pop(), 20);
    EXPECT_EQ(stack.pop(), 10);
    EXPECT_TRUE(stack.isEmpty());
}

TEST(MyStackTests, ExceptionHandling) {
    MyStack<int> stack;
    
    EXPECT_THROW(stack.pop(), std::runtime_error);
    EXPECT_THROW(stack.peek(), std::runtime_error);
}

TEST(MyStackTests, CopyConstructor) {
    MyStack<int> stack1;
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);
    
    MyStack<int> stack2 = stack1; // Копирующий конструктор
    
    EXPECT_EQ(stack1.size(), 3);
    EXPECT_EQ(stack2.size(), 3);
    
    // Обе стека должны иметь одинаковые элементы
    while (!stack1.isEmpty() && !stack2.isEmpty()) {
        EXPECT_EQ(stack1.pop(), stack2.pop());
    }
}

TEST(MyStackTests, AssignmentOperator) {
    MyStack<int> stack1;
    stack1.push(10);
    stack1.push(20);
    
    MyStack<int> stack2;
    stack2.push(30);
    stack2 = stack1; // Оператор присваивания
    
    EXPECT_EQ(stack2.size(), 2);
    EXPECT_EQ(stack2.pop(), 20);
    EXPECT_EQ(stack2.pop(), 10);
}