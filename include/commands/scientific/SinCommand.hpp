#ifndef SIN_COMMAND_HPP
#define SIN_COMMAND_HPP

#include "../UnaryCommand.hpp"
#include <cmath>

class SinCommand : public UnaryCommand {
private:
    double result;
    bool useRadians; // Локальная копия настройки
    
public:
    SinCommand(double angle, bool useRadians = true)
        : UnaryCommand("sin", "Sine function", angle), 
          result(0.0), useRadians(useRadians) {}
    
    double execute() override {
        // Преобразуем градусы в радианы если нужно
        double angle = useRadians ? operand : operand * M_PI / 180.0;
        result = std::sin(angle);
        return result;
    }
    
    void undo() override {
        // Для sin undo - это arcsin
    }
    
    std::string toString() const override {
        std::string unit = useRadians ? "рад" : "°";
        return name + "(" + std::to_string(operand) + unit + ") = " + 
               std::to_string(result);
    }
    
    void setUseRadians(bool useRad) { useRadians = useRad; }
};

#endif // SIN_COMMAND_HPP