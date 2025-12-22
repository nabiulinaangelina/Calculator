#ifndef SQRT_COMMAND_HPP
#define SQRT_COMMAND_HPP

#include "../UnaryCommand.hpp"
#include <cmath>
#include <stdexcept>

class SqrtCommand : public UnaryCommand {
private:
    double result;
    
public:
    SqrtCommand(double op)
        : UnaryCommand("sqrt", "Square root operation", op), result(0.0) {}
    
    double execute() override {
        if (operand < 0) {
            throw std::invalid_argument("Cannot calculate square root of negative number");
        }
        result = std::sqrt(operand);
        return result;
    }
    
    void undo() override {
        // Для sqrt undo - это возведение в квадрат
    }
    
    std::string toString() const override {
        return name + "(" + std::to_string(operand) + ") = " + std::to_string(result);
    }
};

#endif // SQRT_COMMAND_HPP