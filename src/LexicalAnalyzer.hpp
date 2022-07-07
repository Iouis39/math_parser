#pragma once

#include <vector>
#include <string>

class LexicalAnalyzer {

public:
    std::unique_ptr<std::vector<std::string>> parseToTokens(const std::string &input);

};

