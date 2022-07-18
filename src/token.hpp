#pragma once

#include <iostream>

enum TokenType {
    NUMBER,
    OPERATOR
};

class Token {
private:
    std::string data;
    TokenType tokenType;
public:
    Token(const std::string &data, TokenType tokenType);

    const std::string &getData();

    std::string toString() const;
};
