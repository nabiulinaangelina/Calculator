#ifndef SIN_COMMAND_HPP
#define SIN_COMMAND_HPP

#include "../UnaryCommand.hpp"
#include <cmath>

class SinCommand : public UnaryCommand {
private:
    double result;
    
public:
    SinCommand(double angle, bool useRadians = true)
        : UnaryCommand("sin", "Sine function", 
                      useRadians ? angle : angle * M_PI / 180.0), 
          result(0.0) {}
    
    double execute() override {
        result = std::sin(operand);
        return result;
    }
    
    void undo() override {
        // Для sin undo - это arcsin
    }
    
    std::string toString() const override {
        return name + "(" + std::to_string(operand) + ") = " + std::to_string(result);
    }
};

#endif // SIN_COMMAND_HPP