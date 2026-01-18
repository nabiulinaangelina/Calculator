#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <memory>
#include <vector>
#include <stack>
#include <map>
#include <string>
#include <functional>
#include "commands/Command.hpp"

class Calculator {
private:
    static Calculator* instance;
    
    // История команд для undo/redo
    std::vector<std::shared_ptr<Command>> commandHistory;
    std::stack<std::shared_ptr<Command>> undoStack;
    std::stack<std::shared_ptr<Command>> redoStack;
    
    // Регистр команд
    std::map<std::string, std::function<std::shared_ptr<Command>()>> commandRegistry;
    
    // Текущий результат
    double currentResult;
    std::vector<double> resultHistory;
    
    // Приватный конструктор
    Calculator();
    
    // Инициализация регистра команд
    void initializeCommandRegistry();
    
public:
    // Запрет копирования и присваивания
    Calculator(const Calculator&) = delete;
    Calculator& operator=(const Calculator&) = delete;
    
    ~Calculator();
    
    // Получение экземпляра Singleton
    static Calculator* getInstance();
    
    // Выполнение команды
    double executeCommand(std::shared_ptr<Command> cmd);
    
    // Выполнение команды по имени с операндами
    double executeCommand(const std::string& commandName, 
                         const std::vector<double>& operands = {});
    
    // Undo последней команды
    bool undo();
    
    // Redo последней отмененной команды
    bool redo();
    
    // Получение истории
    const std::vector<std::shared_ptr<Command>>& getHistory() const;
    
    // Очистка истории
    void clearHistory();
    
    // Получение текущего результата
    double getCurrentResult() const;
    
    // Установка текущего результата
    void setCurrentResult(double result);
    
    // Получение списка доступных команд
    std::vector<std::string> getAvailableCommands() const;
};

#endif // CALCULATOR_HPP