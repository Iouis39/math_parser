#include "token.hpp"
#include <string>

Token::Token(const std::string &data, TokenType tokenType) : data(data), tokenType(tokenType) {};

const std::string& Token::getData() {
    return data;
}

std::string Token::toString() const {
    std::string tokenTypeLabel;
 
    switch(tokenType) {
        case NUMBER : 
        tokenTypeLabel = "NUMBER";
        break;
        
        case OPERATOR :
        tokenTypeLabel = "OPERATOR";
        break;
    }
    return "{\"type\": \"" + tokenTypeLabel + "\", \"data\": \"" + data + "\"}";
}
