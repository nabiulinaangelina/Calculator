#include "Calculator.hpp"
#include "commands/arithmetic/AddCommand.hpp"
#include "commands/arithmetic/SubtractCommand.hpp"
#include "commands/arithmetic/SqrtCommand.hpp"
#include <spdlog/spdlog.h>
#include <stdexcept>
#include <functional>

// Инициализация статического указателя
Calculator* Calculator::instance = nullptr;

Calculator::Calculator() : currentResult(0.0) {
    initializeCommandRegistry();
    spdlog::debug("Calculator instance created");
}

Calculator::~Calculator() {
    spdlog::debug("Calculator instance destroyed");
}

Calculator* Calculator::getInstance() {
    if (instance == nullptr) {
        instance = new Calculator();
    }
    return instance;
}

void Calculator::initializeCommandRegistry() {
    // Регистрация команд по умолчанию
    commandRegistry["add"] = []() -> std::shared_ptr<Command> {
        return std::make_shared<AddCommand>(0, 0);
    };
    
    commandRegistry["subtract"] = []() -> std::shared_ptr<Command> {
        return std::make_shared<SubtractCommand>(0, 0);
    };
    
    commandRegistry["sqrt"] = []() -> std::shared_ptr<Command> {
        return std::make_shared<SqrtCommand>(0);
    };
    
    spdlog::debug("Command registry initialized with {} commands", commandRegistry.size());
}

double Calculator::executeCommand(std::shared_ptr<Command> cmd) {
    if (!cmd) {
        throw std::invalid_argument("Command cannot be null");
    }
    
    try {
        double result = cmd->execute();
        commandHistory.push_back(cmd);
        undoStack.push(cmd);
        
        // Очищаем стек redo при новом действии
        while (!redoStack.empty()) {
            redoStack.pop();
        }
        
        currentResult = result;
        spdlog::info("Command executed: {}", cmd->toString());
        return result;
        
    } catch (const std::exception& e) {
        spdlog::error("Failed to execute command {}: {}", cmd->getName(), e.what());
        throw;
    }
}

double Calculator::executeCommand(const std::string& commandName, 
                                 const std::vector<double>& operands) {
    auto it = commandRegistry.find(commandName);
    if (it == commandRegistry.end()) {
        throw std::invalid_argument("Unknown command: " + commandName);
    }
    
    std::shared_ptr<Command> cmd = it->second();
    
    // Устанавливаем операнды в зависимости от типа команды
    if (auto addCmd = std::dynamic_pointer_cast<AddCommand>(cmd)) {
        if (operands.size() < 2) {
            throw std::invalid_argument("Add command requires 2 operands");
        }
        *addCmd = AddCommand(operands[0], operands[1]);
        return executeCommand(addCmd);
    }
    else if (auto subCmd = std::dynamic_pointer_cast<SubtractCommand>(cmd)) {
        if (operands.size() < 2) {
            throw std::invalid_argument("Subtract command requires 2 operands");
        }
        *subCmd = SubtractCommand(operands[0], operands[1]);
        return executeCommand(subCmd);
    }
    else if (auto sqrtCmd = std::dynamic_pointer_cast<SqrtCommand>(cmd)) {
        if (operands.size() < 1) {
            throw std::invalid_argument("Sqrt command requires 1 operand");
        }
        *sqrtCmd = SqrtCommand(operands[0]);
        return executeCommand(sqrtCmd);
    }
    
    throw std::invalid_argument("Unsupported command type: " + commandName);
}

bool Calculator::undo() {
    if (undoStack.empty()) {
        spdlog::warn("Nothing to undo");
        return false;
    }
    
    auto cmd = undoStack.top();
    undoStack.pop();
    cmd->undo();
    redoStack.push(cmd);
    
    spdlog::info("Command undone: {}", cmd->getName());
    return true;
}

bool Calculator::redo() {
    if (redoStack.empty()) {
        spdlog::warn("Nothing to redo");
        return false;
    }
    
    auto cmd = redoStack.top();
    redoStack.pop();
    cmd->execute();  // Повторное выполнение
    undoStack.push(cmd);
    
    spdlog::info("Command redone: {}", cmd->getName());
    return true;
}

void Calculator::clearHistory() {
    commandHistory.clear();
    while (!undoStack.empty()) undoStack.pop();
    while (!redoStack.empty()) redoStack.pop();
    spdlog::info("Command history cleared");
}

std::vector<std::string> Calculator::getAvailableCommands() const {
    std::vector<std::string> commands;
    for (const auto& [name, _] : commandRegistry) {
        commands.push_back(name);
    }
    return commands;
}

const std::vector<std::shared_ptr<Command>>& Calculator::getHistory() const {
    return commandHistory;
}

double Calculator::getCurrentResult() const { 
    return currentResult; 
}

void Calculator::setCurrentResult(double result) { 
    currentResult = result; 
}