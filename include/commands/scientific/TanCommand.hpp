#ifndef TAN_COMMAND_HPP
#define TAN_COMMAND_HPP

#include "../UnaryCommand.hpp"
#include <cmath>
#include <stdexcept>

class TanCommand : public UnaryCommand {
private:
    double result;
    
public:
    TanCommand(double angle, bool useRadians = true)
        : UnaryCommand("tan", "Tangent function", 
                      useRadians ? angle : angle * M_PI / 180.0), 
          result(0.0) {}
    
    double execute() override {
        double cos_val = std::cos(operand);
        if (std::abs(cos_val) < 1e-10) {
            throw std::invalid_argument("Tangent undefined for angle = " + 
                                       std::to_string(operand) + " radians");
        }
        result = std::tan(operand);
        return result;
    }
    
    void undo() override {
        // Для tan undo - это arctan
    }
    
    std::string toString() const override {
        return name + "(" + std::to_string(operand) + ") = " + std::to_string(result);
    }
};

#endif // TAN_COMMAND_HPP