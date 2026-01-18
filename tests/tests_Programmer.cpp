#include <gtest/gtest.h>
#include <bitset>
#include "Calculator.hpp"
#include "utils/NumberConverter.hpp"
#include "commands/programmer/BitwiseAndCommand.hpp"
#include "commands/programmer/BitwiseOrCommand.hpp"
#include "commands/programmer/BitwiseXorCommand.hpp"
#include "commands/programmer/BitwiseNotCommand.hpp"
#include "commands/programmer/ShiftLeftCommand.hpp"
#include "commands/programmer/ShiftRightCommand.hpp"

TEST(ProgrammerTests, BitwiseAndCommand) {
    BitwiseAndCommand andCmd(0b1100, 0b1010); // 12 AND 10
    EXPECT_EQ(static_cast<int>(andCmd.execute()), 0b1000); // 8
    
    BitwiseAndCommand andCmd2(0xFF, 0xF0); // 255 AND 240
    EXPECT_EQ(static_cast<int>(andCmd2.execute()), 0xF0); // 240
}

TEST(ProgrammerTests, BitwiseOrCommand) {
    BitwiseOrCommand orCmd(0b1100, 0b1010); // 12 OR 10
    EXPECT_EQ(static_cast<int>(orCmd.execute()), 0b1110); // 14
    
    BitwiseOrCommand orCmd2(0x0F, 0xF0); // 15 OR 240
    EXPECT_EQ(static_cast<int>(orCmd2.execute()), 0xFF); // 255
}

TEST(ProgrammerTests, BitwiseXorCommand) {
    BitwiseXorCommand xorCmd(0b1100, 0b1010); // 12 XOR 10
    EXPECT_EQ(static_cast<int>(xorCmd.execute()), 0b0110); // 6
    
    BitwiseXorCommand xorCmd2(0xFF, 0xFF); // 255 XOR 255
    EXPECT_EQ(static_cast<int>(xorCmd2.execute()), 0); // 0
}

TEST(ProgrammerTests, BitwiseNotCommand) {
    BitwiseNotCommand notCmd(0); // NOT 0
    EXPECT_EQ(static_cast<int>(notCmd.execute()), -1); // Все биты установлены
    
    BitwiseNotCommand notCmd2(0xFF); // NOT 255
    EXPECT_EQ(static_cast<int>(notCmd2.execute()), -256); // Для 32-битного int
}

TEST(ProgrammerTests, ShiftLeftCommand) {
    ShiftLeftCommand shiftLCmd(1, 3); // 1 << 3
    EXPECT_EQ(static_cast<int>(shiftLCmd.execute()), 8);
    
    ShiftLeftCommand shiftLCmd2(0xFF, 4); // 255 << 4
    EXPECT_EQ(static_cast<int>(shiftLCmd2.execute()), 0xFF0); // 4080
}

TEST(ProgrammerTests, ShiftLeftCommandEdgeCases) {
    // Сдвиг больше 31 бита
    ShiftLeftCommand shiftLCmd(1, 32);
    EXPECT_THROW(shiftLCmd.execute(), std::invalid_argument);
    
    // Отрицательный сдвиг
    ShiftLeftCommand shiftLCmd2(1, -1);
    EXPECT_THROW(shiftLCmd2.execute(), std::invalid_argument);
}

TEST(ProgrammerTests, ShiftRightCommand) {
    ShiftRightCommand shiftRCmd(8, 3); // 8 >> 3
    EXPECT_EQ(static_cast<int>(shiftRCmd.execute()), 1);
    
    ShiftRightCommand shiftRCmd2(0xFF00, 8); // 65280 >> 8
    EXPECT_EQ(static_cast<int>(shiftRCmd2.execute()), 0xFF); // 255
}

TEST(ProgrammerTests, ShiftRightCommandEdgeCases) {
    // Сдвиг больше 31 бита
    ShiftRightCommand shiftRCmd(1, 32);
    EXPECT_THROW(shiftRCmd.execute(), std::invalid_argument);
    
    // Отрицательный сдвиг
    ShiftRightCommand shiftRCmd2(1, -1);
    EXPECT_THROW(shiftRCmd2.execute(), std::invalid_argument);
}

TEST(NumberConverterTests, DecimalToBinary) {
    EXPECT_EQ(NumberConverter::decimalToBinary(10, 8), "00001010");
    EXPECT_EQ(NumberConverter::decimalToBinary(255, 8), "11111111");
    EXPECT_EQ(NumberConverter::decimalToBinary(0, 8), "00000000");
    EXPECT_EQ(NumberConverter::decimalToBinary(-1, 8), "11111111"); // Дополнительный код
}

TEST(NumberConverterTests, DecimalToHex) {
    EXPECT_EQ(NumberConverter::decimalToHex(10, false), "0xa");
    EXPECT_EQ(NumberConverter::decimalToHex(255), "0xFF");
    EXPECT_EQ(NumberConverter::decimalToHex(4095), "0xFFF");
    EXPECT_EQ(NumberConverter::decimalToHex(0), "0x0");
}

TEST(NumberConverterTests, BinaryToDecimal) {
    EXPECT_EQ(NumberConverter::binaryToDecimal("1010"), 10);
    EXPECT_EQ(NumberConverter::binaryToDecimal("11111111"), 255);
    EXPECT_EQ(NumberConverter::binaryToDecimal("0000"), 0);
    EXPECT_EQ(NumberConverter::binaryToDecimal("1"), 1);
}

TEST(NumberConverterTests, HexToDecimal) {
    EXPECT_EQ(NumberConverter::hexToDecimal("A"), 10);
    EXPECT_EQ(NumberConverter::hexToDecimal("FF"), 255);
    EXPECT_EQ(NumberConverter::hexToDecimal("FFF"), 4095);
    EXPECT_EQ(NumberConverter::hexToDecimal("0"), 0);
}

TEST(NumberConverterTests, ParseNumber) {
    // Явные двоичные с префиксом
    EXPECT_EQ(NumberConverter::parseNumber("0b1010"), 10);
    EXPECT_EQ(NumberConverter::parseNumber("0B1111"), 15);
    EXPECT_EQ(NumberConverter::parseNumber("0b0"), 0);
    EXPECT_EQ(NumberConverter::parseNumber("0b1"), 1);
    
    // Явные шестнадцатеричные с префиксом
    EXPECT_EQ(NumberConverter::parseNumber("0xA"), 10);
    EXPECT_EQ(NumberConverter::parseNumber("0xFF"), 255);
    EXPECT_EQ(NumberConverter::parseNumber("0xFFF"), 4095);
    EXPECT_EQ(NumberConverter::parseNumber("0x0"), 0);
    
    // Шестнадцатеричные без префикса
    EXPECT_EQ(NumberConverter::parseNumber("A"), 10);
    EXPECT_EQ(NumberConverter::parseNumber("FF"), 255);
    EXPECT_EQ(NumberConverter::parseNumber("a"), 10);
    EXPECT_EQ(NumberConverter::parseNumber("ff"), 255);
    EXPECT_EQ(NumberConverter::parseNumber("10FF"), 4351); // Шестнадцатеричное
    
    // Десятичные
    EXPECT_EQ(NumberConverter::parseNumber("10"), 10);
    EXPECT_EQ(NumberConverter::parseNumber("255"), 255);
    EXPECT_EQ(NumberConverter::parseNumber("-5"), -5);
    EXPECT_EQ(NumberConverter::parseNumber("0"), 0);
    EXPECT_EQ(NumberConverter::parseNumber("1010"), 1010); // Десятичное
    EXPECT_EQ(NumberConverter::parseNumber("1111"), 1111); // Десятичное
    
    // Двоичные без префикса
    EXPECT_EQ(NumberConverter::parseNumber("0"), 0); // И двоичное, и десятичное
    EXPECT_EQ(NumberConverter::parseNumber("1"), 1); // И двоичное, и десятичное
    EXPECT_EQ(NumberConverter::parseNumber("10"), 10); // Десятичное, не двоичное!
    EXPECT_EQ(NumberConverter::parseNumber("11"), 11); // Десятичное, не двоичное!
    
    // С пробелами
    EXPECT_EQ(NumberConverter::parseNumber(" 0b1010 "), 10);
    EXPECT_EQ(NumberConverter::parseNumber(" 0xFF "), 255);
    EXPECT_EQ(NumberConverter::parseNumber(" 10 "), 10);
}

TEST(NumberConverterTests, ParseNumberInvalid) {
    // Пустая строка
    EXPECT_THROW(NumberConverter::parseNumber(""), std::invalid_argument);
    
    // Недопустимые символы в двоичных (с префиксом)
    EXPECT_THROW(NumberConverter::parseNumber("0b102"), std::invalid_argument);
    EXPECT_THROW(NumberConverter::parseNumber("0b12a"), std::invalid_argument);
    
    // Недопустимые символы в шестнадцатеричных
    EXPECT_THROW(NumberConverter::parseNumber("0xGG"), std::invalid_argument);
    EXPECT_THROW(NumberConverter::parseNumber("GG"), std::invalid_argument);
    
    // Строки без цифр
    EXPECT_THROW(NumberConverter::parseNumber("xyz"), std::invalid_argument);
    
    // Смешанные невалидные
    EXPECT_THROW(NumberConverter::parseNumber("12.3"), std::invalid_argument);
}

TEST(ProgrammerTests, CalculatorIntegration) {
    Calculator* calc = Calculator::getInstance();
    calc->clearHistory();
    
    // Тест через Calculator
    double andResult = calc->executeCommand("bit_and", {12.0, 10.0});
    EXPECT_EQ(static_cast<int>(andResult), 8);
    
    double orResult = calc->executeCommand("bit_or", {12.0, 10.0});
    EXPECT_EQ(static_cast<int>(orResult), 14);
    
    double shiftResult = calc->executeCommand("shift_left", {1.0, 3.0});
    EXPECT_EQ(static_cast<int>(shiftResult), 8);
}

TEST(ProgrammerTests, UndoRedoProgrammer) {
    Calculator* calc = Calculator::getInstance();
    calc->clearHistory();
    
    double result1 = calc->executeCommand("bit_and", {12.0, 10.0});
    EXPECT_EQ(static_cast<int>(result1), 8);
    
    double result2 = calc->executeCommand("bit_or", {12.0, 10.0});
    EXPECT_EQ(static_cast<int>(result2), 14);
    
    // Undo - должна отменить последнюю команду (bit_or)
    EXPECT_TRUE(calc->undo());
    // После undo текущий результат должен быть от bit_and = 8
    EXPECT_EQ(static_cast<int>(calc->getCurrentResult()), 8);
    
    // Redo - должен повторить bit_or
    EXPECT_TRUE(calc->redo());
    // После redo текущий результат должен быть от bit_or = 14
    EXPECT_EQ(static_cast<int>(calc->getCurrentResult()), 14);
}