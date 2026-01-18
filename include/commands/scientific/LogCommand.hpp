#ifndef LOG_COMMAND_HPP
#define LOG_COMMAND_HPP

#include "../UnaryCommand.hpp"
#include <cmath>
#include <stdexcept>

class LogCommand : public UnaryCommand {
private:
    double result;
    
public:
    LogCommand(double value)
        : UnaryCommand("log", "Natural logarithm", value), 
          result(0.0) {}
    
    double execute() override {
        if (operand <= 0) {
            throw std::invalid_argument("Logarithm undefined for value <= 0");
        }
        result = std::log(operand);
        return result;
    }
    
    void undo() override {
        // Для log undo - это exp
    }
    
    std::string toString() const override {
        return name + "(" + std::to_string(operand) + ") = " + std::to_string(result);
    }
};

#endif // LOG_COMMAND_HPP