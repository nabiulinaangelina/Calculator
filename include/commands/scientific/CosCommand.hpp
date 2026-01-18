#ifndef COS_COMMAND_HPP
#define COS_COMMAND_HPP

#include "../UnaryCommand.hpp"
#include <cmath>

class CosCommand : public UnaryCommand {
private:
    double result;
    
public:
    CosCommand(double angle, bool useRadians = true)
        : UnaryCommand("cos", "Cosine function", 
                      useRadians ? angle : angle * M_PI / 180.0), 
          result(0.0) {}
    
    double execute() override {
        result = std::cos(operand);
        return result;
    }
    
    void undo() override {
        // Для cos undo - это arccos
    }
    
    std::string toString() const override {
        return name + "(" + std::to_string(operand) + ") = " + std::to_string(result);
    }
};

#endif // COS_COMMAND_HPP