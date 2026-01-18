#ifndef POW_COMMAND_HPP
#define POW_COMMAND_HPP

#include "../BinaryCommand.hpp"
#include <cmath>
#include <stdexcept>

class PowCommand : public BinaryCommand {
private:
    double result;
    
public:
    PowCommand(double base, double exponent)
        : BinaryCommand("pow", "Power function", base, exponent), 
          result(0.0) {}
    
    double execute() override {
        if (leftOperand < 0 && std::floor(rightOperand) != rightOperand) {
            throw std::invalid_argument("Negative base with non-integer exponent");
        }
        if (leftOperand == 0 && rightOperand < 0) {
            throw std::invalid_argument("Zero to negative power");
        }
        result = std::pow(leftOperand, rightOperand);
        return result;
    }
    
    void undo() override {
        // Для pow undo - это root
    }
    
    std::string toString() const override {
        return name + "(" + std::to_string(leftOperand) + ", " + 
               std::to_string(rightOperand) + ") = " + std::to_string(result);
    }
};

#endif // POW_COMMAND_HPP