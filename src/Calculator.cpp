#include "Calculator.hpp"
#include "commands/arithmetic/AddCommand.hpp"
#include "commands/arithmetic/MultiplyCommand.hpp"
#include "commands/arithmetic/DivideCommand.hpp"
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

// Инициализация статического указателя
Calculator* Calculator::instance = nullptr;

Calculator::Calculator() : currentResult(0.0), useRadians(true) {
    initializeCommandRegistry();
    spdlog::debug("Calculator instance created. Angle mode: {}", 
                  useRadians ? "radians" : "degrees");
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

    commandRegistry["multiply"] = []() -> std::shared_ptr<Command> {
        return std::make_shared<MultiplyCommand>(0, 0);
    };
    
    commandRegistry["divide"] = []() -> std::shared_ptr<Command> {
        return std::make_shared<DivideCommand>(0, 0);
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
    
    // Создаем команду через фабричный метод
    std::shared_ptr<Command> cmd;
    
    if (commandName == "add") {
        if (operands.size() < 2) {
            throw std::invalid_argument("Add command requires 2 operands");
        }
        cmd = std::make_shared<AddCommand>(operands[0], operands[1]);
    }
    else if (commandName == "multiply") {
        if (operands.size() < 2) {
            throw std::invalid_argument("Multiply command requires 2 operands");
        }
        cmd = std::make_shared<MultiplyCommand>(operands[0], operands[1]);
    }
    else if (commandName == "divide") {
        if (operands.size() < 2) {
            throw std::invalid_argument("Divide command requires 2 operands");
        }
        cmd = std::make_shared<DivideCommand>(operands[0], operands[1]);
    }
    else if (commandName == "subtract") {
        if (operands.size() < 2) {
            throw std::invalid_argument("Subtract command requires 2 operands");
        }
        cmd = std::make_shared<SubtractCommand>(operands[0], operands[1]);
    }
    else if (commandName == "sqrt") {
        if (operands.size() < 1) {
            throw std::invalid_argument("Sqrt command requires 1 operand");
        }
        cmd = std::make_shared<SqrtCommand>(operands[0]);
    }
    else if (commandName == "sin") {
        if (operands.size() < 1) {
            throw std::invalid_argument("Sin command requires 1 operand");
        }
        cmd = std::make_shared<SinCommand>(operands[0], useRadians);
    }
    else if (commandName == "cos") {
        if (operands.size() < 1) {
            throw std::invalid_argument("Cos command requires 1 operand");
        }
        cmd = std::make_shared<CosCommand>(operands[0], useRadians);
    }
    else if (commandName == "tan") {
        if (operands.size() < 1) {
            throw std::invalid_argument("Tan command requires 1 operand");
        }
        cmd = std::make_shared<TanCommand>(operands[0], useRadians);
    }
    else if (commandName == "pow") {
        if (operands.size() < 2) {
            throw std::invalid_argument("Pow command requires 2 operands");
        }
        cmd = std::make_shared<PowCommand>(operands[0], operands[1]);
    }
    else if (commandName == "log") {
        if (operands.size() < 1) {
            throw std::invalid_argument("Log command requires 1 operand");
        }
        cmd = std::make_shared<LogCommand>(operands[0]);
    }
    else if (commandName == "exp") {
        if (operands.size() < 1) {
            throw std::invalid_argument("Exp command requires 1 operand");
        }
        cmd = std::make_shared<ExpCommand>(operands[0]);
    }
    else if (commandName == "bit_and") {
        if (operands.size() < 2) {
            throw std::invalid_argument("Bitwise AND requires 2 operands");
        }
        cmd = std::make_shared<BitwiseAndCommand>(
            static_cast<int>(operands[0]), 
            static_cast<int>(operands[1])
        );
    }
    else if (commandName == "bit_or") {
        if (operands.size() < 2) {
            throw std::invalid_argument("Bitwise OR requires 2 operands");
        }
        cmd = std::make_shared<BitwiseOrCommand>(
            static_cast<int>(operands[0]), 
            static_cast<int>(operands[1])
        );
    }
    else if (commandName == "bit_xor") {
        if (operands.size() < 2) {
            throw std::invalid_argument("Bitwise XOR requires 2 operands");
        }
        cmd = std::make_shared<BitwiseXorCommand>(
            static_cast<int>(operands[0]), 
            static_cast<int>(operands[1])
        );
    }
    else if (commandName == "bit_not") {
        if (operands.size() < 1) {
            throw std::invalid_argument("Bitwise NOT requires 1 operand");
        }
        cmd = std::make_shared<BitwiseNotCommand>(
            static_cast<int>(operands[0])
        );
    }
    else if (commandName == "shift_left") {
        if (operands.size() < 2) {
            throw std::invalid_argument("Shift left requires 2 operands");
        }
        cmd = std::make_shared<ShiftLeftCommand>(
            static_cast<int>(operands[0]), 
            static_cast<int>(operands[1])
        );
    }
    else if (commandName == "shift_right") {
        if (operands.size() < 2) {
            throw std::invalid_argument("Shift right requires 2 operands");
        }
        cmd = std::make_shared<ShiftRightCommand>(
            static_cast<int>(operands[0]), 
            static_cast<int>(operands[1])
        );
    }
    else {
        throw std::invalid_argument("Unsupported command: " + commandName);
    }
    
    return executeCommand(cmd);
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