#ifndef BITWISE_NOT_COMMAND_HPP
#define BITWISE_NOT_COMMAND_HPP

#include "../UnaryCommand.hpp"
#include <bitset>
#include <string>

class BitwiseNotCommand : public UnaryCommand {
private:
    int result;
    
public:
    BitwiseNotCommand(int value)
        : UnaryCommand("bit_not", "Bitwise NOT operation", value), 
          result(0) {}
    
    double execute() override {
        result = ~static_cast<int>(operand);
        return static_cast<double>(result);
    }
    
    void undo() override {
        // NOT является самодостаточной операцией - повторный NOT отменяет
        result = ~result;
    }
    
    std::string toString() const override {
        return name + "(" + std::to_string(static_cast<int>(operand)) + ") = " + 
               std::to_string(result);
    }
    
    std::string toBinaryString() const {
        int val = static_cast<int>(operand);
        int res = result;
        
        std::string binaryStr = "NOT:  ";
        binaryStr += std::bitset<32>(val).to_string() + "\n      " +
                     std::string(32, '-') + "\n      " +
                     std::bitset<32>(res).to_string();
        return binaryStr;
    }
};

#endif // BITWISE_NOT_COMMAND_HPP