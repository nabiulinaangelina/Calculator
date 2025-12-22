#include "AppCalculator.hpp"
#include "Menu.hpp"
#include "Standard.hpp"
#include "Calculator.hpp"
#include "data_structures/MyStack.hpp"
#include "commands/arithmetic/AddCommand.hpp"
#include "commands/arithmetic/SubtractCommand.hpp"
#include "commands/arithmetic/SqrtCommand.hpp"
#include <spdlog/spdlog.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

// инициализация статического указателя
AppCalculator *AppCalculator::instance = nullptr;
// приватный ctor
AppCalculator::AppCalculator(){}
AppCalculator::~AppCalculator()
{
    spdlog::trace("AppCalculator destructor called.");
    if (instance)
    {
        delete instance;
    }
}
// метод доступа к единственному объекту
AppCalculator *AppCalculator::getInstance()
{
    spdlog::trace("AppCalculator getInstance() called.");
    if (instance == nullptr)
    {
        instance = new AppCalculator();
    }
    return instance;
}
// Демо-функции для тестирования
void AppCalculator::demoBasicArithmetic() {
    std::cout << "\n=== Демонстрация базовых операций ===\n\n";
    int a = 10, b = 5;
    std::cout << "a = " << a << ", b = " << b << "\n";
    std::cout << "a + b = " << add(a, b) << "\n";
    std::cout << "a - b = " << substract(a, b) << "\n";
    std::cout << "a * b = " << multiply(a, b) << "\n";
    try {
        std::cout << "a / b = " << divide(a, b) << "\n";
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << "\n";
    }
    // Тест деления на 0
    std::cout << "\nТест деления на 0:\n";
    try {
        std::cout << "a / 0 = " << divide(a, 0) << "\n";
    } catch (const std::exception& e) {
        std::cout << "Поймано исключение: " << e.what() << "\n";
    }
}
void AppCalculator::demoStandardOperations() {
    std::cout << "\n=== Режим стандартного калькулятора ===\n\n";
    std::cout << "Эта функциональность будет реализована позже.\n";
    std::cout << "Сейчас доступна только демонстрация базовых операций.\n";
    demoBasicArithmetic();
}

void AppCalculator::demoCalculatorWithCommands() {
    std::cout << "\n=== Демонстрация паттерна Command ===\n\n";
    
    Calculator* calc = Calculator::getInstance();
    
    std::cout << "Доступные команды: ";
    auto commands = calc->getAvailableCommands();
    for (const auto& cmd : commands) {
        std::cout << cmd << " ";
    }
    std::cout << "\n\n";
    
    // Демонстрация выполнения команд
    try {
        std::cout << "1. Сложение: 10 + 5 = ";
        double result1 = calc->executeCommand("add", {10, 5});
        std::cout << result1 << "\n";
        
        std::cout << "2. Вычитание: 10 - 5 = ";
        double result2 = calc->executeCommand("subtract", {10, 5});
        std::cout << result2 << "\n";
        
        std::cout << "3. Квадратный корень: sqrt(25) = ";
        double result3 = calc->executeCommand("sqrt", {25});
        std::cout << result3 << "\n";
        
        std::cout << "\nТекущий результат: " << calc->getCurrentResult() << "\n";
        
        // Демонстрация стека
        std::cout << "\n=== Демонстрация собственного стека ===\n";
        MyStack<double> stack;
        
        stack.push(1.5);
        stack.push(2.7);
        stack.push(3.9);
        
        std::cout << "Размер стека: " << stack.size() << "\n";
        std::cout << "Верхний элемент: " << stack.peek() << "\n";
        
        std::cout << "Извлечение элементов: ";
        while (!stack.isEmpty()) {
            std::cout << stack.pop() << " ";
        }
        std::cout << "\n";
        
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << "\n";
    }
}

// Методы меню (заглушки - будут реализованы позже)
void AppCalculator::showStandardCalculator() {
    Menu calcMenu("Стандартный калькулятор");
    
    // Создаем экземпляр калькулятора
    Calculator* calc = Calculator::getInstance();
    
    // Переменные для хранения ввода
    double num1 = 0, num2 = 0;
    
    calcMenu.addItem("Сложение", [&calc, &num1, &num2]() {
        std::cout << "\nВведите два числа:\n";
        std::cout << "Первое число: ";
        std::cin >> num1;
        std::cout << "Второе число: ";
        std::cin >> num2;
        
        try {
            double result = calc->executeCommand("add", {num1, num2});
            std::cout << num1 << " + " << num2 << " = " << result << "\n";
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << "\n";
        }
    });
    
    calcMenu.addItem("Вычитание", [&calc, &num1, &num2]() {
        std::cout << "\nВведите два числа:\n";
        std::cout << "Первое число: ";
        std::cin >> num1;
        std::cout << "Второе число: ";
        std::cin >> num2;
        
        try {
            double result = calc->executeCommand("subtract", {num1, num2});
            std::cout << num1 << " - " << num2 << " = " << result << "\n";
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << "\n";
        }
    });
    
    calcMenu.addItem("Квадратный корень", [&calc, &num1]() {
        std::cout << "\nВведите число: ";
        std::cin >> num1;
        
        try {
            double result = calc->executeCommand("sqrt", {num1});
            std::cout << "sqrt(" << num1 << ") = " << result << "\n";
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << "\n";
        }
    });
    
    calcMenu.addItem("Отменить (Undo)", [&calc]() {
        if (calc->undo()) {
            std::cout << "Команда отменена\n";
            std::cout << "Текущий результат: " << calc->getCurrentResult() << "\n";
        } else {
            std::cout << "Нечего отменять\n";
        }
    });
    
    calcMenu.addItem("Повторить (Redo)", [&calc]() {
        if (calc->redo()) {
            std::cout << "Команда повторена\n";
            std::cout << "Текущий результат: " << calc->getCurrentResult() << "\n";
        } else {
            std::cout << "Нечего повторять\n";
        }
    });
    
    calcMenu.addItem("Показать историю", [&calc]() {
        auto history = calc->getHistory();
        if (history.empty()) {
            std::cout << "История пуста\n";
        } else {
            std::cout << "\n=== История операций ===\n";
            for (size_t i = 0; i < history.size(); ++i) {
                std::cout << i + 1 << ". " << history[i]->toString() << "\n";
            }
        }
    });
    
    calcMenu.addItem("Очистить историю", [&calc]() {
        calc->clearHistory();
        std::cout << "История очищена\n";
    });
    
    calcMenu.addItem("Демо паттерна Command", [this]() {
        this->demoCalculatorWithCommands();
    });
    
    calcMenu.run();
}


void AppCalculator::showScientificCalculator() { 
    std::cout << "\n=== Инженерный калькулятор ===\n\n";
    std::cout << "Эта функциональность будет реализована на 3 этапе.\n";
}
void AppCalculator::showProgrammerCalculator() { 
    std::cout << "\n=== Калькулятор программиста ===\n\n";
    std::cout << "Эта функциональность будет реализована на 4 этапе.\n";
}
void AppCalculator::showExpressionEvaluation() { 
    std::cout << "\n=== Вычисление выражений ===\n\n";
    std::cout << "Эта функциональность будет реализована на 5 этапе.\n";
}
void AppCalculator::showNumberOperations() { 
    std::cout << "\n=== Работа с числами ===\n\n";
    std::cout << "Эта функциональность будет реализована на 6 этапе.\n";
}
void AppCalculator::showStringOperations() { 
    std::cout << "\n=== Работа со строками ===\n\n";
    std::cout << "Эта функциональность будет реализована на 7 этапе.\n";
}
void AppCalculator::showDateOperations() { 
    std::cout << "\n=== Работа с датами ===\n\n";
    std::cout << "Эта функциональность будет реализована на 8 этапе.\n";
}
void AppCalculator::showSortingOperations() { 
    std::cout << "\n=== Сортировки массивов ===\n\n";
    std::cout << "Эта функциональность будет реализована на 9 этапе.\n";
}
void AppCalculator::showHistory() { 
    std::cout << "\n=== История операций ===\n\n";
    std::cout << "Эта функциональность будет реализована на 10 этапе.\n";
}
// метод run — принимает аргументы командной строки
void AppCalculator::run(int argc, char *argv[])
{
    // Настройка spdlog
    spdlog::set_level(spdlog::level::trace); // уровень логирования приложения
    spdlog::info("Запуск калькулятора...");
    // обработка аргументов командной строки
    spdlog::trace("AppCalculator run() called with {} arguments.", argc);
    spdlog::debug("AppCalculator is running with {} arguments.", argc);
    for (int i = 0; i < argc; ++i)
    {
        spdlog::debug("Argument {}: {}", i, argv[i]);
    }
    // Проверка аргументов командной строки
    bool directMode = false;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--demo" || arg == "-d") {
            spdlog::info("Запуск в демо-режиме...");
            demoBasicArithmetic();
            directMode = true;
            break;
        }
        else if (arg == "--test" || arg == "-t") {
            spdlog::info("Запуск тестового режима...");
            demoStandardOperations();
            directMode = true;
            break;
        }
        else if (arg.find("--calculate=") == 0) {
            std::string expression = arg.substr(12);
            spdlog::info("Вычисление выражения: {}", expression);
            std::cout << "\nВычисление выражения: " << expression << "\n";
            std::cout << "Эта функциональность будет реализована позже.\n";
            directMode = true;
            break;
        }
    }
    // Если не прямой режим - показываем меню
    if (!directMode) {
        // Создаем главное меню
        Menu mainMenu("Главное меню");
         // Добавляем пункты согласно требованиям
        mainMenu.addItem("Стандартный калькулятор", 
            [this]() { this->showStandardCalculator(); });
        mainMenu.addItem("Инженерный калькулятор", 
            [this]() { this->showScientificCalculator(); });
        mainMenu.addItem("Калькулятор программиста", 
            [this]() { this->showProgrammerCalculator(); });
        mainMenu.addItem("Вычисление выражений", 
            [this]() { this->showExpressionEvaluation(); });
        mainMenu.addItem("Работа с числами", 
            [this]() { this->showNumberOperations(); });
        mainMenu.addItem("Работа со строками", 
            [this]() { this->showStringOperations(); });
        mainMenu.addItem("Работа с датами", 
            [this]() { this->showDateOperations(); });
        mainMenu.addItem("Сортировки массивов", 
            [this]() { this->showSortingOperations(); });
        mainMenu.addItem("История операций", 
            [this]() { this->showHistory(); });
        // Запускаем меню
        mainMenu.run();
    }
    spdlog::info("Завершение работы калькулятора...");
}