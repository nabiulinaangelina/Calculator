#ifndef BITWISE_OR_COMMAND_HPP
#define BITWISE_OR_COMMAND_HPP

#include "../BinaryCommand.hpp"
#include <bitset>
#include <string>

class BitwiseOrCommand : public BinaryCommand {
private:
    int result;
    
public:
    BitwiseOrCommand(int left, int right)
        : BinaryCommand("bit_or", "Bitwise OR operation", left, right), 
          result(0) {}
    
    double execute() override {
        result = static_cast<int>(leftOperand) | static_cast<int>(rightOperand);
        return static_cast<double>(result);
    }
    
    void undo() override {
        // Для bitwise OR undo не тривиально
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
        
        std::string binaryStr = "OR:   ";
        binaryStr += std::bitset<32>(left).to_string() + "\n      " +
                     std::bitset<32>(right).to_string() + "\n      " +
                     std::string(32, '-') + "\n      " +
                     std::bitset<32>(res).to_string();
        return binaryStr;
    }
};

#endif // BITWISE_OR_COMMAND_HPP