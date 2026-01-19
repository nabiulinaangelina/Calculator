#ifndef SQRT_COMMAND_HPP
#define SQRT_COMMAND_HPP

#include "../UnaryCommand.hpp"
#include <cmath>
#include <stdexcept>

class SqrtCommand : public UnaryCommand {
private:
    double result;
    double originalValue; // Сохраняем оригинальное значение
    
public:
    SqrtCommand(double op)
        : UnaryCommand("sqrt", "Square root operation", op), 
          result(0.0), originalValue(op) {}
    
    double execute() override {
        if (operand < 0) {
            throw std::invalid_argument("Cannot calculate square root of negative number");
        }
        
        // Сохраняем оригинальное значение для undo
        getState()->save(operand);
        
        result = std::sqrt(operand);
        return result;
    }
    
    void undo() override {
        // Для sqrt undo - возвращаем квадрат результата
        if (getState()->hasState()) {
            operand = getState()->restore<double>();
        } else {
            // Если нет сохраненного состояния, используем квадрат результата
            operand = result * result;
        }
        result = operand; // Восстанавливаем исходное значение
    }
    
    std::string toString() const override {
        return "sqrt(" + std::to_string(originalValue) + ") = " + 
               std::to_string(result);
    }
};

#endif // SQRT_COMMAND_HPP