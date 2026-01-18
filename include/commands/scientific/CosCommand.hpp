#ifndef COS_COMMAND_HPP
#define COS_COMMAND_HPP

#include "../UnaryCommand.hpp"
#include <cmath>

class CosCommand : public UnaryCommand {
private:
    double result;
    bool useRadians; // Локальная копия настройки
    
public:
    CosCommand(double angle, bool useRadians = true)
        : UnaryCommand("cos", "Cosine function", angle), 
          result(0.0), useRadians(useRadians) {}
    
    double execute() override {
        // Преобразуем градусы в радианы если нужно
        double angle = useRadians ? operand : operand * M_PI / 180.0;
        result = std::cos(angle);
        return result;
    }
    
    void undo() override {
        // Для cos undo - это arccos
    }
    
    std::string toString() const override {
        std::string unit = useRadians ? "рад" : "°";
        return name + "(" + std::to_string(operand) + unit + ") = " + 
               std::to_string(result);
    }
    
    void setUseRadians(bool useRad) { useRadians = useRad; }
};

#endif // COS_COMMAND_HPP