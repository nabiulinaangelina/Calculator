#ifndef SIN_COMMAND_HPP
#define SIN_COMMAND_HPP

#include "../UnaryCommand.hpp"
#include <cmath>

class SinCommand : public UnaryCommand {
private:
    double result;
    bool useRadians;
    double originalAngle; // Сохраняем оригинальный угол
    
public:
    SinCommand(double angle, bool useRadians = true)
        : UnaryCommand("sin", "Sine function", angle), 
          result(0.0), useRadians(useRadians), originalAngle(angle) {}
    
    double execute() override {
        // Преобразуем градусы в радианы если нужно
        double angle = useRadians ? operand : operand * M_PI / 180.0;
        
        // Сохраняем оригинальный угол для undo
        getState()->save(operand);
        
        result = std::sin(angle);
        return result;
    }
    
    void undo() override {
        // Для sin undo - восстанавливаем оригинальный угол
        if (getState()->hasState()) {
            operand = getState()->restore<double>();
        } else {
            operand = originalAngle;
        }
        result = operand; // Устанавливаем результат как оригинальный угол
    }
    
    std::string toString() const override {
        std::string unit = useRadians ? "рад" : "°";
        return "sin(" + std::to_string(originalAngle) + unit + ") = " + 
               std::to_string(result);
    }
    
    void setUseRadians(bool useRad) { useRadians = useRad; }
};

#endif // SIN_COMMAND_HPP