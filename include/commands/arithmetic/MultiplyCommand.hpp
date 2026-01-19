#ifndef MULTIPLY_COMMAND_HPP
#define MULTIPLY_COMMAND_HPP

#include "../BinaryCommand.hpp"

class MultiplyCommand : public BinaryCommand {
private:
    double result;
    double previousResult;
    
public:
    MultiplyCommand(double left, double right)
        : BinaryCommand("multiply", "Multiplication operation", left, right), 
          result(0.0), previousResult(0.0) {}
    
    double execute() override {
        if (getState()->hasState()) {
            previousResult = getState()->restore<double>();
        }
        
        result = leftOperand * rightOperand;
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
        return std::to_string(leftOperand) + " * " + 
               std::to_string(rightOperand) + " = " + 
               std::to_string(result);
    }
};

#endif // MULTIPLY_COMMAND_HPP