#ifndef TAN_COMMAND_HPP
#define TAN_COMMAND_HPP

#include "../UnaryCommand.hpp"
#include <cmath>
#include <stdexcept>

class TanCommand : public UnaryCommand {
private:
    double result;
    bool useRadians; // Локальная копия настройки
    
public:
    TanCommand(double angle, bool useRadians = true)
        : UnaryCommand("tan", "Tangent function", angle), 
          result(0.0), useRadians(useRadians) {}
    
    double execute() override {
        // Преобразуем градусы в радианы если нужно
        double angle = useRadians ? operand : operand * M_PI / 180.0;
        
        // Проверяем, что угол не равен π/2 + kπ (где cos = 0)
        double cos_val = std::cos(angle);
        if (std::abs(cos_val) < 1e-10) {
            std::string unit = useRadians ? "рад" : "°";
            throw std::invalid_argument("Tangent undefined for angle = " + 
                                       std::to_string(operand) + unit);
        }
        result = std::tan(angle);
        return result;
    }
    
    void undo() override {
        // Для tan undo - это arctan
    }
    
    std::string toString() const override {
        std::string unit = useRadians ? "рад" : "°";
        return name + "(" + std::to_string(operand) + unit + ") = " + 
               std::to_string(result);
    }
    
    void setUseRadians(bool useRad) { useRadians = useRad; }
};

#endif // TAN_COMMAND_HPP