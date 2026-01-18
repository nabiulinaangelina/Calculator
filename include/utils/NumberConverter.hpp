#ifndef NUMBER_CONVERTER_HPP
#define NUMBER_CONVERTER_HPP

#include <string>
#include <bitset>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <cmath>
#include <cctype>

class NumberConverter {
public:
    // Преобразование между системами счисления
    
    // Десятичное -> Двоичное
    static std::string decimalToBinary(int decimal, int bits = 32) {
        if (bits < 1 || bits > 64) {
            throw std::invalid_argument("Number of bits must be between 1 and 64");
        }
        
        if (bits <= 32) {
            unsigned int value = static_cast<unsigned int>(decimal);
            return std::bitset<32>(value).to_string().substr(32 - bits);
        } else {
            // Для большего количества битов
            std::string binary;
            unsigned long long value = static_cast<unsigned long long>(decimal);
            
            for (int i = bits - 1; i >= 0; --i) {
                binary += ((value >> i) & 1) ? '1' : '0';
                if (i % 4 == 0 && i != 0) {
                    binary += ' '; // Разделитель для читаемости
                }
            }
            return binary;
        }
    }
    
    // Десятичное -> Шестнадцатеричное
    static std::string decimalToHex(int decimal, bool uppercase = true) {
        std::stringstream ss;
        if (uppercase) {
            ss << std::uppercase << std::hex << decimal;
        } else {
            ss << std::hex << decimal;
        }
        return "0x" + ss.str();
    }
    
    // Двоичное -> Десятичное
    static int binaryToDecimal(const std::string& binary) {
        // Удаляем пробелы и префиксы
        std::string cleanBinary;
        for (char c : binary) {
            if (c == '0' || c == '1') {
                cleanBinary += c;
            } else if (c != ' ' && c != 'b' && c != 'B') {
                throw std::invalid_argument("Invalid binary character: " + std::string(1, c));
            }
        }
        
        if (cleanBinary.empty()) {
            throw std::invalid_argument("Empty binary string");
        }
        
        int result = 0;
        for (char c : cleanBinary) {
            result = (result << 1) | (c - '0');
        }
        return result;
    }
    
    // Шестнадцатеричное -> Десятичное
    static int hexToDecimal(const std::string& hex) {
        // Удаляем префиксы и пробелы
        std::string cleanHex;
        for (char c : hex) {
            if (std::isxdigit(c)) {
                cleanHex += std::tolower(c);
            } else if (c != ' ' && c != 'x' && c != 'X' && c != '0') {
                throw std::invalid_argument("Invalid hex character: " + std::string(1, c));
            }
        }
        
        if (cleanHex.empty()) {
            throw std::invalid_argument("Empty hex string");
        }
        
        int result;
        std::stringstream ss;
        ss << std::hex << cleanHex;
        if (!(ss >> result)) {
            throw std::invalid_argument("Invalid hex number: " + hex);
        }
        return result;
    }
    
    // Шестнадцатеричное -> Двоичное
    static std::string hexToBinary(const std::string& hex, int bits = 32) {
        int decimal = hexToDecimal(hex);
        return decimalToBinary(decimal, bits);
    }
    
    // Двоичное -> Шестнадцатеричное
    static std::string binaryToHex(const std::string& binary, bool uppercase = true) {
        int decimal = binaryToDecimal(binary);
        return decimalToHex(decimal, uppercase);
    }
    
    // Форматированный вывод числа во всех системах
    static std::string formatNumber(int number, int bits = 32) {
        std::stringstream ss;
        ss << "Decimal: " << number << "\n"
           << "Binary:  " << decimalToBinary(number, bits) << "\n"
           << "Hex:     " << decimalToHex(number);
        return ss.str();
    }
    
    // Парсинг строки с автоматическим определением системы счисления
    static int parseNumber(const std::string& str) {
        std::string trimmed;
        for (char c : str) {
            if (c != ' ') {
                trimmed += c;
            }
        }
        
        if (trimmed.empty()) {
            throw std::invalid_argument("Empty number string");
        }

        // Проверяем, что строка состоит только из допустимых символов
        for (char c : trimmed) {
            if (!std::isdigit(static_cast<unsigned char>(c)) && 
                c != '-' && c != '+' && 
                !(std::tolower(c) >= 'a' && std::tolower(c) <= 'f') &&
                c != 'x' && c != 'b') {
                throw std::invalid_argument("Invalid character in number: " + std::string(1, c));
            }
        }
        
        // 1. Проверяем явные префиксы
        if (trimmed.size() >= 2 && trimmed[0] == '0') {
            char second = std::tolower(trimmed[1]);
            if (second == 'b') {
                // Двоичное: 0b...
                return binaryToDecimal(trimmed.substr(2));
            } else if (second == 'x') {
                // Шестнадцатеричное: 0x...
                return hexToDecimal(trimmed.substr(2));
            }
            // Иначе: восьмеричное или просто 0
        }
        
        // 2. Проверяем, содержит ли строка шестнадцатеричные символы (A-F)
        bool hasHexChars = false;
        for (char c : trimmed) {
            c = std::tolower(c);
            if (c >= 'a' && c <= 'f') {
                hasHexChars = true;
                break;
            }
        }
        
        if (hasHexChars) {
            return hexToDecimal(trimmed);
        }
        
        // 3. Пробуем как десятичное
        try {
            size_t pos;
            int result = std::stoi(trimmed, &pos);
            if (pos == trimmed.length()) {
                return result;
            }
        } catch (const std::exception&) {
            // Не десятичное
        }
        
        // 4. Пробуем как двоичное без префикса (только 0 и 1)
        bool isBinary = true;
        for (char c : trimmed) {
            if (c != '0' && c != '1') {
                isBinary = false;
                break;
            }
        }
        
        if (isBinary) {
            return binaryToDecimal(trimmed);
        }
        
        throw std::invalid_argument("Cannot parse number: " + str);
    }
    
    // Вспомогательные методы для проверки формата (опционально)
    static bool isBinary(const std::string& str) {
        try {
            parseNumber(str);
            // Проверяем, содержит ли только 0 и 1
            for (char c : str) {
                if (c != '0' && c != '1' && c != ' ' && c != 'b' && c != 'B') {
                    return false;
                }
            }
            return true;
        } catch (...) {
            return false;
        }
    }
    
    static bool isHex(const std::string& str) {
        try {
            parseNumber(str);
            // Проверяем, содержит ли шестнадцатеричные символы
            for (char c : str) {
                c = std::tolower(c);
                if (!std::isxdigit(c) && c != ' ' && c != 'x' && c != '0') {
                    return false;
                }
            }
            return true;
        } catch (...) {
            return false;
        }
    }
    
    static bool isDecimal(const std::string& str) {
        try {
            parseNumber(str);
            // Проверяем, содержит ли только цифры и знаки
            for (char c : str) {
                if (!std::isdigit(c) && c != ' ' && c != '+' && c != '-') {
                    return false;
                }
            }
            return true;
        } catch (...) {
            return false;
        }
    }
};

#endif // NUMBER_CONVERTER_HPP