#ifndef BITWISE_AND_COMMAND_HPP
#define BITWISE_AND_COMMAND_HPP

#include "../BinaryCommand.hpp"
#include <bitset>

class BitwiseAndCommand : public BinaryCommand {
private:
    int result;
    int previousLeft;
    int previousRight;
    
public:
    BitwiseAndCommand(int left, int right)
        : BinaryCommand("bit_and", "Bitwise AND operation", left, right), 
          result(0), previousLeft(left), previousRight(right) {}
    
    double execute() override {
        // Сохраняем предыдущие значения
        std::pair<int, int> prevState = {previousLeft, previousRight};
        if (!getState()->hasState()) {
            getState()->save(prevState);
        }
        
        result = static_cast<int>(leftOperand) & static_cast<int>(rightOperand);
        
        // Обновляем предыдущие значения
        previousLeft = static_cast<int>(leftOperand);
        previousRight = static_cast<int>(rightOperand);
        
        return static_cast<double>(result);
    }
    
    void undo() override {
        // Восстанавливаем предыдущие значения
        if (getState()->hasState()) {
            auto [prevLeft, prevRight] = getState()->restore<std::pair<int, int>>();
            leftOperand = prevLeft;
            rightOperand = prevRight;
        }
        result = static_cast<int>(leftOperand) & static_cast<int>(rightOperand);
    }
    
    std::string toString() const override {
        return name + "(" + std::to_string(static_cast<int>(leftOperand)) + ", " + 
               std::to_string(static_cast<int>(rightOperand)) + ") = " + 
               std::to_string(result);
    }
    
    std::string toBinaryString() const {
        int left = static_cast<int>(leftOperand);
        int right = static_cast<int>(rightOperand);
        int res = result;
        
        std::string binaryStr = "AND:\n      ";
        binaryStr += std::bitset<32>(left).to_string() + "\n      " +
                     std::bitset<32>(right).to_string() + "\n      " +
                     std::string(32, '-') + "\n      " +
                     std::bitset<32>(res).to_string();
        return binaryStr;
    }
};

#endif // BITWISE_AND_COMMAND_HPP