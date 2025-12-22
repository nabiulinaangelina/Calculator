#ifndef BINARY_COMMAND_HPP
#define BINARY_COMMAND_HPP

#include "Command.hpp"

// Команда с двумя операндами
class BinaryCommand : public Command {
protected:
    double leftOperand;
    double rightOperand;
    
public:
    BinaryCommand(const std::string& n, const std::string& desc, 
                  double left, double right)
        : Command(n, desc), leftOperand(left), rightOperand(right) {}
    
    virtual ~BinaryCommand() = default;
};

#endif // BINARY_COMMAND_HPP