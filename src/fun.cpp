// Copyright 2024 UNN-IASR
#include "fun.h"
#include <cstring>
#include <cctype>
unsigned int faStr1(const char* str) {
    unsigned int count = 0;
    bool inWord = false;
    bool containsDigit = false;

    while (*str != '\0') {
        if (std::isspace(*str)) {
            if (inWord && !containsDigit) {
                ++count;
            }
            inWord = false;
            containsDigit = false;
        } else {
            if (std::isdigit(*str)) {
                containsDigit = true;
            }
            inWord = true;
        }
        ++str;
    }

    // Проверка последнего слова, если оно было допустимым словом без цифр
    if (inWord && !containsDigit) {
        ++count;
    }

    return count;
}

unsigned int faStr2(const char* str) {
    return 0;
}

unsigned int faStr3(const char* str) {
    return 0;
}
