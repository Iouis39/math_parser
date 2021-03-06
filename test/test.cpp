
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
    CHECK(tokensToTest->at(0)->getData() == "2");
    CHECK(tokensToTest->size() == 1);
}

TEST_CASE("testing LexicalAnalyzer - floating point number") {
    LexicalAnalyzer lexicalAnalyzer;
    auto tokensToTest = lexicalAnalyzer.parseToTokens("2.1");
    CHECK(tokensToTest->at(0)->getData() == "2.1");
    CHECK(tokensToTest->size() == 1);
}

TEST_CASE("testing LexicalAnalyzer - large floating point number") {
    LexicalAnalyzer lexicalAnalyzer;
    auto tokensToTest = lexicalAnalyzer.parseToTokens("234.354"); 
    CHECK(tokensToTest->at(0)->getData() == "234.354");
    CHECK(tokensToTest->size() == 1);
}

TEST_CASE("testing LexicalAnalyer - addition with two floating point numbers") {
    LexicalAnalyzer lexicalAnalyzer;
    auto tokensToTest = lexicalAnalyzer.parseToTokens("23.4+435.1");
    CHECK(tokensToTest->at(0)->getData() == "23.4");
    CHECK(tokensToTest->at(1)->getData() == "+");
    CHECK(tokensToTest->at(2)->getData() == "435.1");
    CHECK(tokensToTest->size() == 3);
}

TEST_CASE("testing LexicalAnalyer - addition with three floating point numbers") {
    LexicalAnalyzer lexicalAnalyzer;
    auto tokensToTest = lexicalAnalyzer.parseToTokens("345.1+2.1+3456.56");
    CHECK(tokensToTest->at(0)->getData() == "345.1");
    CHECK(tokensToTest->at(1)->getData() == "+");
    CHECK(tokensToTest->at(2)->getData() == "2.1");
    CHECK(tokensToTest->at(3)->getData() == "+");
    CHECK(tokensToTest->at(4)->getData() == "3456.56");
    CHECK(tokensToTest->size() == 5);
}



TEST_CASE("testing LexicalAnalyzer - simple addition") {
    LexicalAnalyzer lexicalAnalyzer;
    auto tokensToTest = lexicalAnalyzer.parseToTokens("2+3");
    CHECK(tokensToTest->at(0)->getData() == "2");
    CHECK(tokensToTest->at(1)->getData() == "+");
    CHECK(tokensToTest->at(2)->getData() == "3");
    CHECK(tokensToTest->size() == 3);
}

TEST_CASE("testing LexicalAnalyzer - addition with large numbers") {
    LexicalAnalyzer lexicalAnalyzer;
    auto tokensToTest = lexicalAnalyzer.parseToTokens("258+37375");
    CHECK(tokensToTest->at(0)->getData() == "258");
    CHECK(tokensToTest->at(1)->getData() == "+");
    CHECK(tokensToTest->at(2)->getData() == "37375");
    CHECK(tokensToTest->size() == 3);
}

TEST_CASE("testing LexicalAnalyzer - addition with multiple numbers") {
    LexicalAnalyzer lexicalAnalyzer;
    auto tokensToTest = lexicalAnalyzer.parseToTokens("258+37375+433");
    CHECK(tokensToTest->at(0)->getData() == "258");
    CHECK(tokensToTest->at(1)->getData() == "+");
    CHECK(tokensToTest->at(2)->getData() == "37375");
    CHECK(tokensToTest->at(3)->getData() == "+");
    CHECK(tokensToTest->at(4)->getData() == "433");
    CHECK(tokensToTest->size() == 5);
}
