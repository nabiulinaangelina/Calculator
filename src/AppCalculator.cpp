//#include <iostream>
#include <string>
//#include <vector>
#include <spdlog/spdlog.h>
#include "AppCalculator.hpp"

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

    spdlog::info("Завершение работы калькулятора...");
};

