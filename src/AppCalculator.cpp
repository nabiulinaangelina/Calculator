#include "AppCalculator.hpp"
#include "Menu.hpp"
#include "Standard.hpp"
#include <spdlog/spdlog.h>
#include <iostream>
#include <string>
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
// Методы меню (заглушки - будут реализованы позже)
void AppCalculator::showStandardCalculator() { demoStandardOperations(); }
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