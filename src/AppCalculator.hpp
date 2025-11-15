//#include <iostream>
#include <string>
#include <vector>
//#include "Menu.h" // предполагаем, что класс Menu вынесен в отдельный файл

class AppCalculator
{
private:
    static AppCalculator *instance; // статический указатель на единственный объект

    // приватный ctor
    AppCalculator();

public:

    // запрет копирования и присваивания
    AppCalculator(const AppCalculator &) = delete;
    AppCalculator &operator=(const AppCalculator &) = delete;

    ~AppCalculator();

    // метод доступа к единственному объекту
    static AppCalculator *getInstance();

    // метод run — принимает аргументы командной строки
    void run(int argc, char *argv[]);
  
};
