#ifndef APPCALCULATOR_HPP
#define APPCALCULATOR_HPP

#include <string>

class AppCalculator
{
private:
    static AppCalculator *instance;
    
    AppCalculator();

public:
    AppCalculator(const AppCalculator &) = delete;
    AppCalculator &operator=(const AppCalculator &) = delete;
    ~AppCalculator();

    static AppCalculator *getInstance();
    
    void run(int argc, char *argv[]);

private:
    // Методы меню
    void showStandardCalculator();
    void showScientificCalculator();
    void showProgrammerCalculator();
    void showExpressionEvaluation();
    void showNumberOperations();
    void showStringOperations();
    void showDateOperations();
    void showSortingOperations();
    void showHistory();

    // Демо-функции
    void demoBasicArithmetic();
    void demoStandardOperations();
    void demoCalculatorWithCommands();
    void demoScientificFunctions();
    void demoProgrammerFunctions(); 
    void demoHistoryOperations();
};

#endif // APPCALCULATOR_HPP