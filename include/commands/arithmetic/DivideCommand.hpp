#ifndef DIVIDE_COMMAND_HPP
#define DIVIDE_COMMAND_HPP

#include "../BinaryCommand.hpp"
#include <stdexcept>

class DivideCommand : public BinaryCommand {
private:
    double result;
    double previousResult;
    
public:
    DivideCommand(double left, double right)
        : BinaryCommand("divide", "Division operation", left, right), 
          result(0.0), previousResult(0.0) {}
    
    double execute() override {
        if (rightOperand == 0) {
            throw std::invalid_argument("Division by zero");
        }
        
        if (getState()->hasState()) {
            previousResult = getState()->restore<double>();
        }
        
        result = leftOperand / rightOperand;
        getState()->save(result);
        return result;
    }
    
    void undo() override {
        if (getState()->hasState()) {
            result = getState()->restore<double>();
        } else {
            result = previousResult;
        }
    }
    
    std::string toString() const override {
        return std::to_string(leftOperand) + " / " + 
               std::to_string(rightOperand) + " = " + 
               std::to_string(result);
    }
};

#endif // DIVIDE_COMMAND_HPP