#ifndef BITWISE_XOR_COMMAND_HPP
#define BITWISE_XOR_COMMAND_HPP

#include "../BinaryCommand.hpp"
#include <bitset>
#include <string>

class BitwiseXorCommand : public BinaryCommand {
private:
    int result;
    
public:
    BitwiseXorCommand(int left, int right)
        : BinaryCommand("bit_xor", "Bitwise XOR operation", left, right), 
          result(0) {}
    
    double execute() override {
        result = static_cast<int>(leftOperand) ^ static_cast<int>(rightOperand);
        return static_cast<double>(result);
    }
    
    void undo() override {
        // Для bitwise XOR undo проще - повторный XOR отменяет операцию
    }
    
    void undoSpecific() {
        result = result ^ static_cast<int>(rightOperand); // Отмена XOR
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
        
        std::string binaryStr = "XOR:  ";
        binaryStr += std::bitset<32>(left).to_string() + "\n      " +
                     std::bitset<32>(right).to_string() + "\n      " +
                     std::string(32, '-') + "\n      " +
                     std::bitset<32>(res).to_string();
        return binaryStr;
    }
};

#endif // BITWISE_XOR_COMMAND_HPP