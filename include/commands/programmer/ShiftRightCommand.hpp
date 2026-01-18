#ifndef SHIFT_RIGHT_COMMAND_HPP
#define SHIFT_RIGHT_COMMAND_HPP

#include "../BinaryCommand.hpp"
#include <bitset>
#include <string>
#include <stdexcept>

class ShiftRightCommand : public BinaryCommand {
private:
    int result;
    
public:
    ShiftRightCommand(int value, int shift)
        : BinaryCommand("shift_right", "Bitwise right shift", value, shift), 
          result(0) {}
    
    double execute() override {
        int value = static_cast<int>(leftOperand);
        int shift = static_cast<int>(rightOperand);
        
        if (shift < 0) {
            throw std::invalid_argument("Shift amount cannot be negative");
        }
        if (shift > 31) {
            throw std::invalid_argument("Shift amount cannot exceed 31 bits");
        }
        
        result = value >> shift;
        return static_cast<double>(result);
    }
    
    void undo() override {
        // Для right shift undo - это left shift (но теряются биты!)
        int shift = static_cast<int>(rightOperand);
        result = result << shift;
    }
    
    std::string toString() const override {
        int value = static_cast<int>(leftOperand);
        int shift = static_cast<int>(rightOperand);
        return name + "(" + std::to_string(value) + " >> " + 
               std::to_string(shift) + ") = " + std::to_string(result);
    }
    
    std::string toBinaryString() const {
        int value = static_cast<int>(leftOperand);
        int shift = static_cast<int>(rightOperand);
        int res = result;
        
        std::string binaryStr = "RIGHT SHIFT " + std::to_string(shift) + " bits:\n";
        binaryStr += "Original: " + std::bitset<32>(value).to_string() + "\n";
        binaryStr += "Result:   " + std::bitset<32>(res).to_string();
        return binaryStr;
    }
};

#endif // SHIFT_RIGHT_COMMAND_HPP