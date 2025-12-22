#ifndef ADD_COMMAND_HPP
#define ADD_COMMAND_HPP

#include "../BinaryCommand.hpp"

class AddCommand : public BinaryCommand {
private:
    double result;
    
public:
    AddCommand(double left, double right)
        : BinaryCommand("add", "Addition operation", left, right), result(0.0) {}
    
    double execute() override {
        result = leftOperand + rightOperand;
        return result;
    }
    
    void undo() override {
        // Для сложения undo - это вычитание
        // В реальной реализации нужно будет хранить предыдущее состояние
    }
    
    std::string toString() const override {
        return name + "(" + std::to_string(leftOperand) + ", " + 
               std::to_string(rightOperand) + ") = " + std::to_string(result);
    }
};

#endif // ADD_COMMAND_HPP