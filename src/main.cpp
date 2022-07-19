#include <iostream>
#include <string>

#include "characterType.hpp"
#include "LexicalAnalyzer.hpp"
#include "token.hpp"

int main(int argc, char *argv[]) {

    if (argc < 2) {
        std::cout << "usage: you need to pass at least one parameter" << std::endl;
        return EXIT_FAILURE;
        
    }

    std::string input(argv[1]);

    // std::cout << "Input: " << input << std::endl;

    LexicalAnalyzer lexicalAnalyzer;
    std::unique_ptr<std::vector<std::shared_ptr<Token>>> tokens = lexicalAnalyzer.parseToTokens(input);

    std::cout << "[";
    for (auto i = tokens->begin(); i != tokens->end(); ++i) {
        if(i != tokens->begin()) {
            std::cout << ',';
        }
        std::cout << (*i)->toString();
    }
    std::cout << "]" << std::endl;

    return EXIT_SUCCESS;
}
