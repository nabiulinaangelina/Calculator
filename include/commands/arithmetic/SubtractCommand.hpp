#ifndef SUBTRACT_COMMAND_HPP
#define SUBTRACT_COMMAND_HPP

#include "../BinaryCommand.hpp"

class SubtractCommand : public BinaryCommand {
private:
    double result;
    double previousResult;
    
public:
    SubtractCommand(double left, double right)
        : BinaryCommand("subtract", "Subtraction operation", left, right), 
          result(0.0), previousResult(0.0) {}
    
    double execute() override {
        if (getState()->hasState()) {
            previousResult = getState()->restore<double>();
        }
        
        result = leftOperand - rightOperand;
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
        return std::to_string(leftOperand) + " - " + 
               std::to_string(rightOperand) + " = " + 
               std::to_string(result);
    }
};

#endif // SUBTRACT_COMMAND_HPP