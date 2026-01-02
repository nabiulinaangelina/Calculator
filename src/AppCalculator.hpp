#ifndef APPCALCULATOR_HPP
#define APPCALCULATOR_HPP

#include <string>
#include <vector>

class AppCalculator
{
private:
    static AppCalculator *instance; // статический указатель на единственный объект

    // Приватные методы для меню
    void showStandardCalculator();
    void showScientificCalculator();
    void showProgrammerCalculator();
    void showExpressionEvaluation();
    void showNumberOperations();
    void showStringOperations();
    void showDateOperations();
    void showSortingOperations();
    void showHistory();

    // Демо-функции для тестирования
    void demoStandardOperations();
    void demoBasicArithmetic();
    
    // приватный ctor
    AppCalculator();

public:
    // запрет копирования и присваивания
    AppCalculator(const AppCalculator &) = delete;
    AppCalculator &operator=(const AppCalculator &) = delete;

    ~AppCalculator();

    // метод доступа к единственному объекту
    static AppCalculator *getInstance();

    // метод run — принимает аргументы командной строки
    void run(int argc, char *argv[]);
};

#endif // APPCALCULATOR_HPP