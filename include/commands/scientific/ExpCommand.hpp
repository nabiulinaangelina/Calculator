#ifndef EXP_COMMAND_HPP
#define EXP_COMMAND_HPP

#include "../UnaryCommand.hpp"
#include <cmath>

class ExpCommand : public UnaryCommand {
private:
    double result;
    
public:
    ExpCommand(double exponent)
        : UnaryCommand("exp", "Exponential function", exponent), 
          result(0.0) {}
    
    double execute() override {
        result = std::exp(operand);
        return result;
    }
    
    void undo() override {
        // Для exp undo - это log
    }
    
    std::string toString() const override {
        return name + "(" + std::to_string(operand) + ") = " + std::to_string(result);
    }
};

#endif // EXP_COMMAND_HPP