#include "Menu.hpp"
#include <iostream>
#include <limits>
#include <cstdlib>

#ifdef _WIN32
    #define CLEAR_COMMAND "cls"
#else
    #define CLEAR_COMMAND "clear"
#endif

Menu::Menu(const std::string& menuTitle) 
    : title(menuTitle), isRunning(false) {}

void Menu::addItem(const std::string& title, std::function<void()> action) {
    items.push_back(MenuItem(title, action));
}

void Menu::clearScreen() {
    int result = std::system(CLEAR_COMMAND);
    (void)result;
}

void Menu::run() {
    isRunning = true;
    
    while (isRunning) {
        clearScreen();
        std::cout << "\n=== " << title << " ===\n\n";
        
        // Вывод пунктов меню
        for (size_t i = 0; i < items.size(); ++i) {
            std::cout << i + 1 << ". " << items[i].title << "\n";
        }
        
        if (title == "Главное меню") {
            std::cout << "0. Выход\n";
        } else {
            std::cout << "0. Назад\n";
        }
        
        std::cout << "\nВыберите пункт: ";
        
        // Обработка ввода
        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка: введите число!\n";
            continue;
        }
        
        if (choice == 0) {
            stop();
            break;
        }
        
        if (choice < 1 || choice > static_cast<int>(items.size())) {
            std::cout << "Неверный выбор. Попробуйте снова.\n";
            std::cout << "Нажмите Enter для продолжения...";
            std::cin.ignore();
            std::cin.get();
            continue;
        }
        
        // Выполнение выбранного действия
        clearScreen();
        items[choice - 1].action();
        
        if (isRunning && title != "Главное меню") {
            std::cout << "\nНажмите Enter для возврата в меню...";
            std::cin.ignore();
            std::cin.get();
        }
    }
}

void Menu::stop() {
    isRunning = false;
}