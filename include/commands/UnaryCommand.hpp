#ifndef UNARY_COMMAND_HPP
#define UNARY_COMMAND_HPP

#include "Command.hpp"

// Команда с одним операндом
class UnaryCommand : public Command {
protected:
    double operand;
    
public:
    UnaryCommand(const std::string& n, const std::string& desc, double op)
        : Command(n, desc), operand(op) {}
    
    virtual ~UnaryCommand() = default;
};

#endif // UNARY_COMMAND_HPP