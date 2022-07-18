#include "token.hpp"
#include <string>

Token::Token(const std::string &data, TokenType tokenType) : data(data), tokenType(tokenType) {};

const std::string& Token::getData() {
    return data;
}

std::string Token::toString() const {
    return "{type: " + std::to_string(tokenType) + ", data: " + data + "}";
}
