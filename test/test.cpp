
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include "characterType.cpp"
#include "LexicalAnalyzer.hpp"

TEST_CASE("testing functions") {
    CHECK(isBracket('(') == true);
    CHECK(isBracket('a') == false);
}

TEST_CASE("testing LexicalAnalyzer - simple number") {
    LexicalAnalyzer lexicalAnalyzer;
    auto tokensToTest = lexicalAnalyzer.parseToTokens("2");
    CHECK(tokensToTest->at(0) == "2");
    CHECK(tokensToTest->size() == 1);
}

TEST_CASE("testing LexicalAnalyzer - simple addition") {
    LexicalAnalyzer lexicalAnalyzer;
    auto tokensToTest = lexicalAnalyzer.parseToTokens("2+3");
    CHECK(tokensToTest->at(0) == "2");
    CHECK(tokensToTest->at(0) == "+");
    CHECK(tokensToTest->at(0) == "3");
    CHECK(tokensToTest->size() == 3);
}

TEST_CASE("testing LexicalAnalyzer - addition with large numbers") {
    LexicalAnalyzer lexicalAnalyzer;
    auto tokensToTest = lexicalAnalyzer.parseToTokens("258+37375");
    CHECK(tokensToTest->at(0) == "258");
    CHECK(tokensToTest->at(0) == "+");
    CHECK(tokensToTest->at(0) == "37375");
    CHECK(tokensToTest->size() == 3);
}
