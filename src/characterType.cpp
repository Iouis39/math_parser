#include "characterType.hpp"
#include <cctype>

bool isAlphabetic(char c) {
    return std::isalpha(c);
}

bool isNumber(char c) {
    return std::isalnum(c) || c == '.';
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '/' || c == '*';
}

bool isAlgebraicSign(char c) {
    return c == '+' || c == '-';
}

bool isBracket(char c) {
    return c == '(' || c == ')';
}

