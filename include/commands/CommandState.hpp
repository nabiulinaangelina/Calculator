#ifndef COMMAND_STATE_HPP
#define COMMAND_STATE_HPP

#include <memory>
#include <any>

// Состояние для отмены операций
class CommandState {
private:
    std::any savedState;
    
public:
    template<typename T>
    void save(const T& state) {
        savedState = state;
    }
    
    template<typename T>
    T restore() const {
        try {
            return std::any_cast<T>(savedState);
        } catch (const std::bad_any_cast&) {
            throw std::runtime_error("Invalid state type");
        }
    }
    
    bool hasState() const {
        return savedState.has_value();
    }
};

#endif // COMMAND_STATE_HPP