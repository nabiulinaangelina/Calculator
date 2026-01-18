#include "Calculator.hpp"
#include "commands/arithmetic/AddCommand.hpp"
#include "commands/arithmetic/SubtractCommand.hpp"
#include "commands/arithmetic/SqrtCommand.hpp"
#include "commands/scientific/SinCommand.hpp"
#include "commands/scientific/CosCommand.hpp"
#include "commands/scientific/TanCommand.hpp"
#include "commands/scientific/PowCommand.hpp"
#include "commands/scientific/LogCommand.hpp"
#include "commands/scientific/ExpCommand.hpp"
#include "commands/programmer/BitwiseAndCommand.hpp"
#include "commands/programmer/BitwiseOrCommand.hpp"
#include "commands/programmer/BitwiseXorCommand.hpp"
#include "commands/programmer/BitwiseNotCommand.hpp"
#include "commands/programmer/ShiftLeftCommand.hpp"
#include "commands/programmer/ShiftRightCommand.hpp"
#include "utils/NumberConverter.hpp"
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

    // Научные команды
    commandRegistry["sin"] = []() -> std::shared_ptr<Command> {
        return std::make_shared<SinCommand>(0);
    };
    
    commandRegistry["cos"] = []() -> std::shared_ptr<Command> {
        return std::make_shared<CosCommand>(0);
    };
    
    commandRegistry["tan"] = []() -> std::shared_ptr<Command> {
        return std::make_shared<TanCommand>(0);
    };
    
    commandRegistry["pow"] = []() -> std::shared_ptr<Command> {
        return std::make_shared<PowCommand>(0, 0);
    };
    
    commandRegistry["log"] = []() -> std::shared_ptr<Command> {
        return std::make_shared<LogCommand>(0);
    };
    
    commandRegistry["exp"] = []() -> std::shared_ptr<Command> {
        return std::make_shared<ExpCommand>(0);
    };

    // Программистские команды
    commandRegistry["bit_and"] = []() -> std::shared_ptr<Command> {
        return std::make_shared<BitwiseAndCommand>(0, 0);
    };
    
    commandRegistry["bit_or"] = []() -> std::shared_ptr<Command> {
        return std::make_shared<BitwiseOrCommand>(0, 0);
    };
    
    commandRegistry["bit_xor"] = []() -> std::shared_ptr<Command> {
        return std::make_shared<BitwiseXorCommand>(0, 0);
    };
    
    commandRegistry["bit_not"] = []() -> std::shared_ptr<Command> {
        return std::make_shared<BitwiseNotCommand>(0);
    };
    
    commandRegistry["shift_left"] = []() -> std::shared_ptr<Command> {
        return std::make_shared<ShiftLeftCommand>(0, 0);
    };
    
    commandRegistry["shift_right"] = []() -> std::shared_ptr<Command> {
        return std::make_shared<ShiftRightCommand>(0, 0);
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
        resultHistory.push_back(result); // Сохраняем результат
        
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
    else if (auto sinCmd = std::dynamic_pointer_cast<SinCommand>(cmd)) {
        if (operands.size() < 1) {
            throw std::invalid_argument("Sin command requires 1 operand");
        }
        *sinCmd = SinCommand(operands[0], true); // по умолчанию радианы
        return executeCommand(sinCmd);
    }
    else if (auto cosCmd = std::dynamic_pointer_cast<CosCommand>(cmd)) {
        if (operands.size() < 1) {
            throw std::invalid_argument("Cos command requires 1 operand");
        }
        *cosCmd = CosCommand(operands[0], true);
        return executeCommand(cosCmd);
    }
    else if (auto tanCmd = std::dynamic_pointer_cast<TanCommand>(cmd)) {
        if (operands.size() < 1) {
            throw std::invalid_argument("Tan command requires 1 operand");
        }
        *tanCmd = TanCommand(operands[0], true);
        return executeCommand(tanCmd);
    }
    else if (auto powCmd = std::dynamic_pointer_cast<PowCommand>(cmd)) {
        if (operands.size() < 2) {
            throw std::invalid_argument("Pow command requires 2 operands");
        }
        *powCmd = PowCommand(operands[0], operands[1]);
        return executeCommand(powCmd);
    }
    else if (auto logCmd = std::dynamic_pointer_cast<LogCommand>(cmd)) {
        if (operands.size() < 1) {
            throw std::invalid_argument("Log command requires 1 operand");
        }
        *logCmd = LogCommand(operands[0]);
        return executeCommand(logCmd);
    }
    else if (auto expCmd = std::dynamic_pointer_cast<ExpCommand>(cmd)) {
        if (operands.size() < 1) {
            throw std::invalid_argument("Exp command requires 1 operand");
        }
        *expCmd = ExpCommand(operands[0]);
        return executeCommand(expCmd);
    }
    else if (auto andCmd = std::dynamic_pointer_cast<BitwiseAndCommand>(cmd)) {
        if (operands.size() < 2) {
            throw std::invalid_argument("Bitwise AND requires 2 operands");
        }
        *andCmd = BitwiseAndCommand(static_cast<int>(operands[0]), 
                                   static_cast<int>(operands[1]));
        return executeCommand(andCmd);
    }
    else if (auto orCmd = std::dynamic_pointer_cast<BitwiseOrCommand>(cmd)) {
        if (operands.size() < 2) {
            throw std::invalid_argument("Bitwise OR requires 2 operands");
        }
        *orCmd = BitwiseOrCommand(static_cast<int>(operands[0]), 
                                 static_cast<int>(operands[1]));
        return executeCommand(orCmd);
    }
    else if (auto xorCmd = std::dynamic_pointer_cast<BitwiseXorCommand>(cmd)) {
        if (operands.size() < 2) {
            throw std::invalid_argument("Bitwise XOR requires 2 operands");
        }
        *xorCmd = BitwiseXorCommand(static_cast<int>(operands[0]), 
                                   static_cast<int>(operands[1]));
        return executeCommand(xorCmd);
    }
    else if (auto notCmd = std::dynamic_pointer_cast<BitwiseNotCommand>(cmd)) {
        if (operands.size() < 1) {
            throw std::invalid_argument("Bitwise NOT requires 1 operand");
        }
        *notCmd = BitwiseNotCommand(static_cast<int>(operands[0]));
        return executeCommand(notCmd);
    }
    else if (auto shiftLCmd = std::dynamic_pointer_cast<ShiftLeftCommand>(cmd)) {
        if (operands.size() < 2) {
            throw std::invalid_argument("Shift left requires 2 operands");
        }
        *shiftLCmd = ShiftLeftCommand(static_cast<int>(operands[0]), 
                                     static_cast<int>(operands[1]));
        return executeCommand(shiftLCmd);
    }
    else if (auto shiftRCmd = std::dynamic_pointer_cast<ShiftRightCommand>(cmd)) {
        if (operands.size() < 2) {
            throw std::invalid_argument("Shift right requires 2 operands");
        }
        *shiftRCmd = ShiftRightCommand(static_cast<int>(operands[0]), 
                                      static_cast<int>(operands[1]));
        return executeCommand(shiftRCmd);
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
    
    // Обновляем currentResult из истории
    if (!resultHistory.empty()) {
        resultHistory.pop_back(); // Удаляем последний результат
        if (!resultHistory.empty()) {
            currentResult = resultHistory.back(); // Берем предыдущий
        } else {
            currentResult = 0.0;
        }
    }
    
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
    double result = cmd->execute();  // Повторное выполнение
    undoStack.push(cmd);
    resultHistory.push_back(result); // Сохраняем результат
    
    currentResult = result;
    
    spdlog::info("Command redone: {}", cmd->getName());
    return true;
}

void Calculator::clearHistory() {
    commandHistory.clear();
    resultHistory.clear(); // Очищаем историю результатов
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