
#include "LexicalAnalyzer.hpp"

#include <memory>

std::unique_ptr<std::vector<std::string>> LexicalAnalyzer::parseToTokens(const std::string &input) {
    auto resultVector = std::make_unique<std::vector<std::string>>();

    resultVector->push_back(input); // this is TODO

    return resultVector;
}