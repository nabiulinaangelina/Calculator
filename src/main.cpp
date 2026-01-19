#include "AppCalculator.hpp"
#include <iostream>

int main(int argc, char* argv[]){
    AppCalculator::getInstance()->run(argc, argv);
    return 0;
}