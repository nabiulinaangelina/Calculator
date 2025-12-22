#ifndef SUBTRACT_COMMAND_HPP
#define SUBTRACT_COMMAND_HPP

#include "../BinaryCommand.hpp"

class SubtractCommand : public BinaryCommand {
private:
    double result;
    
public:
    SubtractCommand(double left, double right)
        : BinaryCommand("subtract", "Subtraction operation", left, right), result(0.0) {}
    
    double execute() override {
        result = leftOperand - rightOperand;
        return result;
    }
    
    void undo() override {
        // Для вычитания undo - это сложение
    }
    
    std::string toString() const override {
        return name + "(" + std::to_string(leftOperand) + ", " + 
               std::to_string(rightOperand) + ") = " + std::to_string(result);
    }
};

#endif // SUBTRACT_COMMAND_HPP