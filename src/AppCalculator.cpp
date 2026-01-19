#include "AppCalculator.hpp"
#include "Menu.hpp"
#include "Standard.hpp"
#include "Calculator.hpp"
#include "data_structures/MyStack.hpp"
#include "commands/arithmetic/AddCommand.hpp"
#include "commands/arithmetic/SubtractCommand.hpp"
#include "commands/arithmetic/SqrtCommand.hpp"
#include "utils/NumberConverter.hpp"
#include "commands/programmer/BitwiseAndCommand.hpp"
#include "commands/programmer/BitwiseOrCommand.hpp"
#include "commands/programmer/BitwiseXorCommand.hpp"
#include "commands/programmer/BitwiseNotCommand.hpp"
#include "commands/programmer/ShiftLeftCommand.hpp"
#include "commands/programmer/ShiftRightCommand.hpp"
#include <spdlog/spdlog.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <map>

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

    calcMenu.addItem("Умножение", [&calc, &num1, &num2]() {
        std::cout << "\nВведите два числа:\n";
        std::cout << "Первое число: ";
        std::cin >> num1;
        std::cout << "Второе число: ";
        std::cin >> num2;
        
        try {
            double result = calc->executeCommand("multiply", {num1, num2});
            std::cout << num1 << " * " << num2 << " = " << result << "\n";
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << "\n";
        }
    });
    
    calcMenu.addItem("Деление", [&calc, &num1, &num2]() {
        std::cout << "\nВведите два числа:\n";
        std::cout << "Первое число: ";
        std::cin >> num1;
        std::cout << "Второе число: ";
        std::cin >> num2;
        
        try {
            double result = calc->executeCommand("divide", {num1, num2});
            std::cout << num1 << " / " << num2 << " = " << result << "\n";
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
    Menu sciMenu("Инженерный калькулятор");
    
    Calculator* calc = Calculator::getInstance();
    
    // Переменные для хранения ввода
    double num1 = 0, num2 = 0;
    
    sciMenu.addItem("Синус (sin)", [calc]() {
        std::cout << "\nВведите угол: ";
        double angle;
        std::cin >> angle;
        
        // Используем текущие настройки калькулятора
        std::string unit = calc->getUseRadians() ? "рад" : "°";
        std::cout << "Единицы: " << calc->getAngleModeString() << "\n";
        
        try {
            double result = calc->executeCommand("sin", {angle});
            std::cout << "sin(" << angle << unit << ") = " << result << "\n";
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << "\n";
        }
    });
    
    sciMenu.addItem("Косинус (cos)", [calc]() {
        std::cout << "\nВведите угол: ";
        double angle;
        std::cin >> angle;
        
        std::string unit = calc->getUseRadians() ? "рад" : "°";
        std::cout << "Единицы: " << calc->getAngleModeString() << "\n";
        
        try {
            double result = calc->executeCommand("cos", {angle});
            std::cout << "cos(" << angle << unit << ") = " << result << "\n";
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << "\n";
        }
    });
    
    sciMenu.addItem("Тангенс (tan)", [calc]() {
        std::cout << "\nВведите угол: ";
        double angle;
        std::cin >> angle;
        
        std::string unit = calc->getUseRadians() ? "рад" : "°";
        std::cout << "Единицы: " << calc->getAngleModeString() << "\n";
        
        try {
            double result = calc->executeCommand("tan", {angle});
            std::cout << "tan(" << angle << unit << ") = " << result << "\n";
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << "\n";
        }
    });
    
    sciMenu.addItem("Возведение в степень (x^y)", [calc]() {
        std::cout << "\nВведите основание (x): ";
        double base;
        std::cin >> base;
        std::cout << "Введите степень (y): ";
        double exponent;
        std::cin >> exponent;
        
        try {
            double result = calc->executeCommand("pow", {base, exponent});
            std::cout << base << "^" << exponent << " = " << result << "\n";
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << "\n";
        }
    });
    
    sciMenu.addItem("Натуральный логарифм (ln)", [calc]() {
        std::cout << "\nВведите число: ";
        double value;
        std::cin >> value;
        
        try {
            double result = calc->executeCommand("log", {value});
            std::cout << "ln(" << value << ") = " << result << "\n";
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << "\n";
        }
    });
    
    sciMenu.addItem("Экспонента (e^x)", [calc]() {
        std::cout << "\nВведите показатель степени: ";
        double exponent;
        std::cin >> exponent;
        
        try {
            double result = calc->executeCommand("exp", {exponent});
            std::cout << "e^" << exponent << " = " << result << "\n";
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << "\n";
        }
    });
    
    sciMenu.addItem("Переключить единицы измерения", [calc]() {
        calc->toggleAngleMode();
        std::cout << "\nТеперь используются: " 
                  << calc->getAngleModeString() << "\n";
    });
    
    sciMenu.addItem("Текущие настройки", [calc]() {
        std::cout << "\nТекущие настройки:\n";
        std::cout << "- Единицы измерения: " 
                  << calc->getAngleModeString() << "\n";
        std::cout << "- Доступных команд: " 
                  << calc->getAvailableCommands().size() << "\n";
    });
    
    sciMenu.addItem("Демо научных функций", [this]() {
        this->demoScientificFunctions();
    });
    
    sciMenu.run();
}

void AppCalculator::demoScientificFunctions() {
    std::cout << "\n=== Демонстрация научных функций ===\n\n";
    
    Calculator* calc = Calculator::getInstance();
    calc->clearHistory();
    
    // Сохраняем текущий режим
    bool originalMode = calc->getUseRadians();
    
    // Демонстрация в радианах
    std::cout << "1. Тригонометрические функции (в радианах):\n";
    calc->setUseRadians(true);
    try {
        double sinResult = calc->executeCommand("sin", {M_PI/6}); // 30 градусов
        std::cout << "   sin(π/6) = " << sinResult << " (ожидается ~0.5)\n";
        
        double cosResult = calc->executeCommand("cos", {M_PI/3}); // 60 градусов
        std::cout << "   cos(π/3) = " << cosResult << " (ожидается ~0.5)\n";
        
        double tanResult = calc->executeCommand("tan", {M_PI/4}); // 45 градусов
        std::cout << "   tan(π/4) = " << tanResult << " (ожидается ~1.0)\n";
    } catch (const std::exception& e) {
        std::cout << "   Ошибка: " << e.what() << "\n";
    }
    
    // Демонстрация в градусах
    std::cout << "\n2. Тригонометрические функции (в градусах):\n";
    calc->setUseRadians(false);
    try {
        double sinResult = calc->executeCommand("sin", {30.0});
        std::cout << "   sin(30°) = " << sinResult << " (ожидается ~0.5)\n";
        
        double cosResult = calc->executeCommand("cos", {60.0});
        std::cout << "   cos(60°) = " << cosResult << " (ожидается ~0.5)\n";
        
        double tanResult = calc->executeCommand("tan", {45.0});
        std::cout << "   tan(45°) = " << tanResult << " (ожидается ~1.0)\n";
    } catch (const std::exception& e) {
        std::cout << "   Ошибка: " << e.what() << "\n";
    }
    
    std::cout << "\n3. Экспонента и логарифм:\n";
    try {
        double expResult = calc->executeCommand("exp", {1.0});
        std::cout << "   e^1 = " << expResult << " (ожидается ~2.71828)\n";
        
        double logResult = calc->executeCommand("log", {expResult});
        std::cout << "   ln(" << expResult << ") = " << logResult << " (ожидается ~1.0)\n";
    } catch (const std::exception& e) {
        std::cout << "   Ошибка: " << e.what() << "\n";
    }
    
    std::cout << "\n4. Возведение в степень:\n";
    try {
        double powResult = calc->executeCommand("pow", {2.0, 3.0});
        std::cout << "   2^3 = " << powResult << " (ожидается 8.0)\n";
        
        double sqrtResult = calc->executeCommand("pow", {9.0, 0.5});
        std::cout << "   9^0.5 = " << sqrtResult << " (ожидается 3.0)\n";
    } catch (const std::exception& e) {
        std::cout << "   Ошибка: " << e.what() << "\n";
    }
    
    // Восстанавливаем исходный режим
    calc->setUseRadians(originalMode);
    
    std::cout << "\n=== Демонстрация завершена ===\n";
}

void AppCalculator::showProgrammerCalculator() {
    Menu progMenu("Калькулятор программиста");
    
    Calculator* calc = Calculator::getInstance();
    
    // Переменные для хранения ввода
    std::string input1, input2;
    int num1 = 0, num2 = 0;
    int bits = 32; // Количество битов для отображения
    
    // Функция для парсинга ввода
    auto parseInput = [](const std::string& input) -> int {
        try {
            return NumberConverter::parseNumber(input);
        } catch (const std::exception& e) {
            std::cout << "Ошибка парсинга: " << e.what() << "\n";
            return 0;
        }
    };
    
    // Функция для отображения числа во всех системах
    auto displayNumber = [bits](int number, const std::string& label = "Результат") {
        std::cout << "\n=== " << label << " ===\n";
        std::cout << NumberConverter::formatNumber(number, bits) << "\n";
        
        // Дополнительная информация
        std::cout << "\nДополнительно:\n";
        std::cout << "  Дополнительный код: " 
                  << NumberConverter::decimalToBinary(number, bits) << "\n";
        std::cout << "  Без знака: " 
                  << static_cast<unsigned int>(number) << "\n";
        
        if (number < 0) {
            std::cout << "  Абсолютное значение: " << std::abs(number) << "\n";
        }
    };
    
    progMenu.addItem("Побитовое И (AND)", [&calc, &input1, &input2, &parseInput, &displayNumber]() {
        std::cout << "\nВведите первое число (dec, bin, hex): ";
        std::getline(std::cin >> std::ws, input1);
        std::cout << "Введите второе число (dec, bin, hex): ";
        std::getline(std::cin >> std::ws, input2);
        
        int num1 = parseInput(input1);
        int num2 = parseInput(input2);
        
        if (num1 == 0 && num2 == 0 && (input1 != "0" || input2 != "0")) {
            return; // Была ошибка парсинга
        }
        
        try {
            std::cout << "\n=== Побитовое И ===\n";
            std::cout << NumberConverter::formatNumber(num1) << "\n";
            std::cout << "AND\n";
            std::cout << NumberConverter::formatNumber(num2) << "\n";
            std::cout << "================\n";
            
            double result = calc->executeCommand("bit_and", {static_cast<double>(num1), 
                                                           static_cast<double>(num2)});
            displayNumber(static_cast<int>(result));
            
            // Показываем бинарное представление
            BitwiseAndCommand andCmd(num1, num2);
            andCmd.execute();
            std::cout << "\nБинарное представление:\n";
            std::cout << andCmd.toBinaryString() << "\n";
            
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << "\n";
        }
    });
    
    progMenu.addItem("Побитовое ИЛИ (OR)", [&calc, &input1, &input2, &parseInput, &displayNumber]() {
        std::cout << "\nВведите первое число (dec, bin, hex): ";
        std::getline(std::cin >> std::ws, input1);
        std::cout << "Введите второе число (dec, bin, hex): ";
        std::getline(std::cin >> std::ws, input2);
        
        int num1 = parseInput(input1);
        int num2 = parseInput(input2);
        
        if (num1 == 0 && num2 == 0 && (input1 != "0" || input2 != "0")) {
            return;
        }
        
        try {
            double result = calc->executeCommand("bit_or", {static_cast<double>(num1), 
                                                          static_cast<double>(num2)});
            displayNumber(static_cast<int>(result), "Побитовое ИЛИ");
            
            BitwiseOrCommand orCmd(num1, num2);
            orCmd.execute();
            std::cout << "\nБинарное представление:\n";
            std::cout << orCmd.toBinaryString() << "\n";
            
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << "\n";
        }
    });
    
    progMenu.addItem("Побитовое исключающее ИЛИ (XOR)", [&calc, &input1, &input2, &parseInput, &displayNumber]() {
        std::cout << "\nВведите первое число (dec, bin, hex): ";
        std::getline(std::cin >> std::ws, input1);
        std::cout << "Введите второе число (dec, bin, hex): ";
        std::getline(std::cin >> std::ws, input2);
        
        int num1 = parseInput(input1);
        int num2 = parseInput(input2);
        
        if (num1 == 0 && num2 == 0 && (input1 != "0" || input2 != "0")) {
            return;
        }
        
        try {
            double result = calc->executeCommand("bit_xor", {static_cast<double>(num1), 
                                                           static_cast<double>(num2)});
            displayNumber(static_cast<int>(result), "Побитовое XOR");
            
            BitwiseXorCommand xorCmd(num1, num2);
            xorCmd.execute();
            std::cout << "\nБинарное представление:\n";
            std::cout << xorCmd.toBinaryString() << "\n";
            
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << "\n";
        }
    });
    
    progMenu.addItem("Побитовое НЕ (NOT)", [&calc, &input1, &parseInput, &displayNumber]() {
        std::cout << "\nВведите число (dec, bin, hex): ";
        std::getline(std::cin >> std::ws, input1);
        
        int num1 = parseInput(input1);
        
        if (num1 == 0 && input1 != "0") {
            return;
        }
        
        try {
            double result = calc->executeCommand("bit_not", {static_cast<double>(num1)});
            displayNumber(static_cast<int>(result), "Побитовое НЕ");
            
            BitwiseNotCommand notCmd(num1);
            notCmd.execute();
            std::cout << "\nБинарное представление:\n";
            std::cout << notCmd.toBinaryString() << "\n";
            
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << "\n";
        }
    });
    
    progMenu.addItem("Сдвиг влево (<<)", [&calc, &input1, &input2, &parseInput, &displayNumber]() {
        std::cout << "\nВведите число для сдвига (dec, bin, hex): ";
        std::getline(std::cin >> std::ws, input1);
        std::cout << "Введите количество битов для сдвига: ";
        std::getline(std::cin >> std::ws, input2);
        
        int num1 = parseInput(input1);
        int shift = parseInput(input2);
        
        if ((num1 == 0 && input1 != "0") || (shift == 0 && input2 != "0")) {
            return;
        }
        
        try {
            double result = calc->executeCommand("shift_left", {static_cast<double>(num1), 
                                                              static_cast<double>(shift)});
            displayNumber(static_cast<int>(result), "Сдвиг влево");
            
            ShiftLeftCommand shiftCmd(num1, shift);
            shiftCmd.execute();
            std::cout << "\nБинарное представление:\n";
            std::cout << shiftCmd.toBinaryString() << "\n";
            
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << "\n";
        }
    });
    
    progMenu.addItem("Сдвиг вправо (>>)", [&calc, &input1, &input2, &parseInput, &displayNumber]() {
        std::cout << "\nВведите число для сдвига (dec, bin, hex): ";
        std::getline(std::cin >> std::ws, input1);
        std::cout << "Введите количество битов для сдвига: ";
        std::getline(std::cin >> std::ws, input2);
        
        int num1 = parseInput(input1);
        int shift = parseInput(input2);
        
        if ((num1 == 0 && input1 != "0") || (shift == 0 && input2 != "0")) {
            return;
        }
        
        try {
            double result = calc->executeCommand("shift_right", {static_cast<double>(num1), 
                                                               static_cast<double>(shift)});
            displayNumber(static_cast<int>(result), "Сдвиг вправо");
            
            ShiftRightCommand shiftCmd(num1, shift);
            shiftCmd.execute();
            std::cout << "\nБинарное представление:\n";
            std::cout << shiftCmd.toBinaryString() << "\n";
            
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << "\n";
        }
    });
    
    progMenu.addItem("Конвертер систем счисления", [&input1, &bits]() {
        std::cout << "\nВведите число (dec, bin, hex): ";
        std::getline(std::cin >> std::ws, input1);
        
        try {
            int number = NumberConverter::parseNumber(input1);
            std::cout << "\n=== Конвертация ===\n";
            std::cout << NumberConverter::formatNumber(number, bits) << "\n";
            
            // Показываем разные форматы
            std::cout << "\nДругие форматы:\n";
            std::cout << "  8-бит:  " << NumberConverter::decimalToBinary(number, 8) << "\n";
            std::cout << "  16-бит: " << NumberConverter::decimalToBinary(number, 16) << "\n";
            std::cout << "  32-бит: " << NumberConverter::decimalToBinary(number, 32) << "\n";
            std::cout << "  64-бит: " << NumberConverter::decimalToBinary(number, 64) << "\n";
            
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << "\n";
        }
    });
    
    progMenu.addItem("Изменить разрядность (биты)", [&bits]() {
        std::cout << "\nТекущая разрядность: " << bits << " бит\n";
        std::cout << "Новая разрядность (8, 16, 32, 64): ";
        int newBits;
        std::cin >> newBits;
        
        if (newBits == 8 || newBits == 16 || newBits == 32 || newBits == 64) {
            bits = newBits;
            std::cout << "Разрядность изменена на " << bits << " бит\n";
        } else {
            std::cout << "Неподдерживаемая разрядность\n";
        }
    });
    
    progMenu.addItem("Демо программистских функций", [this]() {
        this->demoProgrammerFunctions();
    });
    
    progMenu.run();
}

// Добавляем демо-функцию в класс AppCalculator
void AppCalculator::demoProgrammerFunctions() {
    std::cout << "\n=== Демонстрация программистских функций ===\n\n";
    
    Calculator* calc = Calculator::getInstance();
    calc->clearHistory();
    
    std::cout << "1. Базовые битовые операции:\n";
    
    // AND
    int a = 0b1100; // 12
    int b = 0b1010; // 10
    double andResult = calc->executeCommand("bit_and", {static_cast<double>(a), 
                                                      static_cast<double>(b)});
    std::cout << "   " << a << " AND " << b << " = " << static_cast<int>(andResult) 
              << " (binary: " << NumberConverter::decimalToBinary(static_cast<int>(andResult), 4) 
              << ")\n";
    
    // OR
    double orResult = calc->executeCommand("bit_or", {static_cast<double>(a), 
                                                    static_cast<double>(b)});
    std::cout << "   " << a << " OR " << b << " = " << static_cast<int>(orResult) 
              << " (binary: " << NumberConverter::decimalToBinary(static_cast<int>(orResult), 4) 
              << ")\n";
    
    // XOR
    double xorResult = calc->executeCommand("bit_xor", {static_cast<double>(a), 
                                                      static_cast<double>(b)});
    std::cout << "   " << a << " XOR " << b << " = " << static_cast<int>(xorResult) 
              << " (binary: " << NumberConverter::decimalToBinary(static_cast<int>(xorResult), 4) 
              << ")\n";
    
    // NOT
    double notResult = calc->executeCommand("bit_not", {static_cast<double>(a)});
    std::cout << "   NOT " << a << " = " << static_cast<int>(notResult) << "\n";
    
    std::cout << "\n2. Сдвиги:\n";
    
    // Left shift
    int value = 0b0001; // 1
    int shift = 3;
    double shiftLeftResult = calc->executeCommand("shift_left", {static_cast<double>(value), 
                                                               static_cast<double>(shift)});
    std::cout << "   " << value << " << " << shift << " = " << static_cast<int>(shiftLeftResult) 
              << " (binary: " << NumberConverter::decimalToBinary(static_cast<int>(shiftLeftResult), 8) 
              << ")\n";
    
    // Right shift
    value = 0b1000; // 8
    shift = 2;
    double shiftRightResult = calc->executeCommand("shift_right", {static_cast<double>(value), 
                                                                static_cast<double>(shift)});
    std::cout << "   " << value << " >> " << shift << " = " << static_cast<int>(shiftRightResult) 
              << " (binary: " << NumberConverter::decimalToBinary(static_cast<int>(shiftRightResult), 8) 
              << ")\n";
    
    std::cout << "\n3. Конвертация систем счисления:\n";
    
    int testNumber = 255;
    std::cout << "   Десятичное: " << testNumber << "\n";
    std::cout << "   Двоичное:   " << NumberConverter::decimalToBinary(testNumber, 8) << "\n";
    std::cout << "   Шестнадцатеричное: " << NumberConverter::decimalToHex(testNumber) << "\n";
    
    std::cout << "\n=== Демонстрация завершена ===\n";
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
    Menu historyMenu("История операций");
    
    Calculator* calc = Calculator::getInstance();
    
    historyMenu.addItem("Показать историю", [calc]() {
        auto history = calc->getHistory();
        if (history.empty()) {
            std::cout << "\nИстория операций пуста.\n";
        } else {
            std::cout << "\n=== История операций ===\n\n";
            for (size_t i = 0; i < history.size(); ++i) {
                std::cout << i + 1 << ". " << history[i]->toString() << "\n";
            }
            
            // Статистика
            std::cout << "\nСтатистика:\n";
            std::cout << "  Всего операций: " << history.size() << "\n";
            
            // Подсчет по типам операций
            std::map<std::string, int> operationCount;
            for (const auto& cmd : history) {
                operationCount[cmd->getName()]++;
            }
            
            std::cout << "  По типам операций:\n";
            for (const auto& [op, count] : operationCount) {
                std::cout << "    " << op << ": " << count << "\n";
            }
        }
    });
    
    historyMenu.addItem("Очистить историю", [calc]() {
        calc->clearHistory();
        std::cout << "\nИстория операций очищена.\n";
    });
    
    historyMenu.addItem("Отменить последнюю операцию (Undo)", [calc]() {
        if (calc->undo()) {
            std::cout << "\nОперация отменена.\n";
            std::cout << "Текущий результат: " << calc->getCurrentResult() << "\n";
        } else {
            std::cout << "\nНечего отменять.\n";
        }
    });
    
    historyMenu.addItem("Повторить отмененную операцию (Redo)", [calc]() {
        if (calc->redo()) {
            std::cout << "\nОперация повторена.\n";
            std::cout << "Текущий результат: " << calc->getCurrentResult() << "\n";
        } else {
            std::cout << "\nНечего повторять.\n";
        }
    });
    
    historyMenu.addItem("Экспорт истории в файл", [calc]() {
        std::cout << "\nВведите имя файла для экспорта: ";
        std::string filename;
        std::cin >> filename;
        
        auto history = calc->getHistory();
        if (history.empty()) {
            std::cout << "История пуста, экспорт отменен.\n";
            return;
        }
        
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cout << "Ошибка открытия файла.\n";
            return;
        }
        
        file << "История операций калькулятора\n";
        file << "==============================\n\n";
        
        for (size_t i = 0; i < history.size(); ++i) {
            file << i + 1 << ". " << history[i]->toString() << "\n";
        }
        
        file.close();
        std::cout << "История экспортирована в файл: " << filename << "\n";
    });
    
    historyMenu.addItem("Импорт истории из файла", []() {
        std::cout << "\nВведите имя файла для импорта: ";
        std::string filename;
        std::cin >> filename;
        
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "Ошибка открытия файла.\n";
            return;
        }
        
        std::string line;
        std::cout << "\nСодержимое файла:\n";
        std::cout << "==================\n";
        while (std::getline(file, line)) {
            std::cout << line << "\n";
        }
        file.close();
        
        std::cout << "\nПримечание: Импорт истории операций в текущей версии\n";
        std::cout << "только отображает содержимое файла. Для полного импорта\n";
        std::cout << "необходима реализация парсера команд.\n";
    });
    
    historyMenu.addItem("Поиск в истории", [calc]() {
        std::cout << "\nВведите текст для поиска: ";
        std::string searchText;
        std::cin.ignore();
        std::getline(std::cin, searchText);
        
        auto history = calc->getHistory();
        std::vector<std::shared_ptr<Command>> searchResults;
        
        for (const auto& cmd : history) {
            std::string cmdStr = cmd->toString();
            if (cmdStr.find(searchText) != std::string::npos ||
                cmd->getName().find(searchText) != std::string::npos) {
                searchResults.push_back(cmd);
            }
        }
        
        if (searchResults.empty()) {
            std::cout << "\nПо запросу '" << searchText << "' ничего не найдено.\n";
        } else {
            std::cout << "\nНайдено " << searchResults.size() << " операций:\n\n";
            for (size_t i = 0; i < searchResults.size(); ++i) {
                std::cout << i + 1 << ". " << searchResults[i]->toString() << "\n";
            }
        }
    });
    
    historyMenu.addItem("Статистика операций", [calc]() {
        auto history = calc->getHistory();
        if (history.empty()) {
            std::cout << "\nИстория операций пуста.\n";
            return;
        }
        
        std::map<std::string, int> operationStats;
        double totalSum = 0.0;
        int totalOperations = history.size();
        
        for (const auto& cmd : history) {
            operationStats[cmd->getName()]++;
            
            // Пытаемся получить числовой результат из строки
            std::string cmdStr = cmd->toString();
            size_t equalsPos = cmdStr.find('=');
            if (equalsPos != std::string::npos) {
                try {
                    std::string resultStr = cmdStr.substr(equalsPos + 2);
                    double result = std::stod(resultStr);
                    totalSum += result;
                } catch (...) {
                    // Игнорируем ошибки парсинга
                }
            }
        }
        
        std::cout << "\n=== Статистика операций ===\n\n";
        std::cout << "Общая статистика:\n";
        std::cout << "  Всего операций: " << totalOperations << "\n";
        std::cout << "  Сумма результатов: " << totalSum << "\n";
        
        if (totalOperations > 0) {
            std::cout << "  Средний результат: " << (totalSum / totalOperations) << "\n";
        }
        
        std::cout << "\nРаспределение по типам операций:\n";
        for (const auto& [op, count] : operationStats) {
            double percentage = (static_cast<double>(count) / totalOperations) * 100.0;
            std::cout << "  " << std::setw(15) << std::left << op 
                      << ": " << std::setw(4) << count 
                      << " (" << std::fixed << std::setprecision(1) << percentage << "%)\n";
        }
        
        // Наиболее часто используемая операция
        auto mostCommon = std::max_element(
            operationStats.begin(), operationStats.end(),
            [](const auto& a, const auto& b) { return a.second < b.second; }
        );
        
        if (mostCommon != operationStats.end()) {
            std::cout << "\nНаиболее частая операция: " << mostCommon->first 
                      << " (" << mostCommon->second << " раз)\n";
        }
    });
    
    historyMenu.addItem("Демо работы с историей", [this]() {
        this->demoHistoryOperations();
    });
    
    historyMenu.run();
}

// Добавляем демо-функцию для истории
void AppCalculator::demoHistoryOperations() {
    std::cout << "\n=== Демонстрация работы с историей ===\n\n";
    
    Calculator* calc = Calculator::getInstance();
    calc->clearHistory();
    
    std::cout << "1. Выполняем несколько операций:\n";
    
    // Выполняем операции
    double r1 = calc->executeCommand("add", {10, 5});
    std::cout << "   - 10 + 5 = " << r1 << "\n";
    
    double r2 = calc->executeCommand("subtract", {r1, 3});
    std::cout << "   - " << r1 << " - 3 = " << r2 << "\n";
    
    double r3 = calc->executeCommand("multiply", {r2, 2});
    std::cout << "   - " << r2 << " * 2 = " << r3 << "\n";
    
    double r4 = calc->executeCommand("sin", {30.0}); // В градусах
    std::cout << "   - sin(30°) = " << r4 << "\n";
    
    std::cout << "\n2. Показываем историю:\n";
    auto history = calc->getHistory();
    for (size_t i = 0; i < history.size(); ++i) {
        std::cout << "   " << i + 1 << ". " << history[i]->toString() << "\n";
    }
    
    std::cout << "\n3. Тестируем Undo:\n";
    calc->undo();
    std::cout << "   - Отменена последняя операция\n";
    std::cout << "   - Текущий результат: " << calc->getCurrentResult() << "\n";
    
    std::cout << "\n4. Тестируем Redo:\n";
    calc->redo();
    std::cout << "   - Повторена отмененная операция\n";
    std::cout << "   - Текущий результат: " << calc->getCurrentResult() << "\n";
    
    std::cout << "\n5. Очищаем историю:\n";
    calc->clearHistory();
    std::cout << "   - История очищена. Всего операций: " 
              << calc->getHistory().size() << "\n";
    
    std::cout << "\n=== Демонстрация завершена ===\n";
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
        
        // mainMenu.addItem("Вычисление выражений", 
        //     [this]() { this->showExpressionEvaluation(); });
        
        // mainMenu.addItem("Работа с числами", 
        //     [this]() { this->showNumberOperations(); });
        
        // mainMenu.addItem("Работа со строками", 
        //     [this]() { this->showStringOperations(); });
        
        // mainMenu.addItem("Работа с датами", 
        //     [this]() { this->showDateOperations(); });
        
        // mainMenu.addItem("Сортировки массивов", 
        //     [this]() { this->showSortingOperations(); });
        
        mainMenu.addItem("История операций", 
            [this]() { this->showHistory(); });
        
        // Запускаем меню
        mainMenu.run();
    }

    spdlog::info("Завершение работы калькулятора...");
}