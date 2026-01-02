#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include <vector>
#include <functional>

// Структура для пункта меню
struct MenuItem {
    std::string title;
    std::function<void()> action;
    
    MenuItem(const std::string& t, std::function<void()> a) 
        : title(t), action(a) {}
};

class Menu {
private:
    std::string title;
    std::vector<MenuItem> items;
    bool isRunning;
    
public:
    Menu(const std::string& menuTitle);
    
    // Добавить пункт меню
    void addItem(const std::string& title, std::function<void()> action);
    
    // Запустить меню
    void run();
    
    // Остановить меню
    void stop();
    
    // Очистить экран (кросс-платформенный способ)
    static void clearScreen();
};

#endif // MENU_HPP