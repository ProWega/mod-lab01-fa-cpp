// Copyright 2024 UNN-IASR
#include "fun.h"
#include <math.h>
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
    // Состояния: начальное, слово с заглавной,
    // обнаружен неправ. символ, пробел
    enum State { Initial, InWordUpper, InWordInvalid, Space };
    State state = Initial;
    unsigned int count = 0;

    while (*str != '\0') {
        switch (state) {
        case Initial:
            if (std::isupper(*str) && std::isalpha(*str)) {
                state = InWordUpper;
            } else if (std::isspace(*str)) {
                state = Space;
            } else {
                state = InWordInvalid;
            }
            break;
        case InWordUpper:
            if (std::islower(*str) && std::isalpha(*str)) {
                // остаться в InWordUpper
            } else if (std::isspace(*str)) {
                state = Space;
                ++count; // слово соответствует условиям
            } else {
                state = InWordInvalid;
            }
            break;
        case InWordInvalid:
            if (std::isspace(*str)) {
                state = Space;
            }
            // остаться в InWordInvalid
            break;
        case Space:
            if (std::isupper(*str) && std::isalpha(*str)) {
                state = InWordUpper;
            } else if (!std::isspace(*str)) {
                state = InWordInvalid;
            }
            // остаться в Space если это не другой пробел
            break;
        }
        ++str;
    }

    // Проверка последнего слова, если оно было допустимым словом
    if (state == InWordUpper) {
        ++count;
    }

    return count;
}

unsigned int faStr3(const char *str) {
    enum State { Initial, InWord, Space };
    State state = Initial;
    unsigned int wordCount = 0;
    unsigned int totalLength = 0;
    unsigned int currentLength = 0;

    while (*str != '\0') {
        switch (state) {
            case Initial:
                if (std::isspace(*str)) {
                    state = Space;
                } else {
                    state = InWord;
                    currentLength = 1;
                }
                break;
            case InWord:
                if (std::isspace(*str)) {
                    state = Space;
                    ++wordCount;
                    totalLength += currentLength;
                    currentLength = 0;
                } else {
                    ++currentLength;
                }
                break;
            case Space:
                if (!std::isspace(*str)) {
                    state = InWord;
                    currentLength = 1;
                }
                // Если пробел, остаемся в Space
                break;
        }
        ++str;
    }

    // Проверка последнего слова, если строка не заканчивается пробелом
    if (state == InWord) {
        ++wordCount;
        totalLength += currentLength;
    }

    if (wordCount == 0) {
        return 0; // Нет слов в строке
    }

    return round(static_cast<double>(totalLength) / wordCount);
}
