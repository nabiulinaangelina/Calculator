#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <memory>
#include <vector>
#include "CommandState.hpp"

// Базовый абстрактный класс Command
class Command {
protected:
    std::string name;
    std::string description;
    std::unique_ptr<CommandState> state;
    
public:
    Command(const std::string& n, const std::string& desc = "")
        : name(n), description(desc), state(std::make_unique<CommandState>()) {}
    
    virtual ~Command() = default;
    
    virtual double execute() = 0;
    virtual void undo() = 0;
    virtual std::string toString() const = 0;
    
    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
    
    // Фабричный метод для создания команд
    static std::shared_ptr<Command> createCommand(const std::string& commandName);
    
protected:
    CommandState* getState() { return state.get(); }
};

#endif // COMMAND_HPP