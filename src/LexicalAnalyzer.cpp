#include "LexicalAnalyzer.hpp"

#include <iostream>
#include <memory>


InvalidFormulaException::InvalidFormulaException(const std::string &message) : message_(message) {
}


Transition::Transition(std::shared_ptr<State> targetState, std::string token) : token(token), targetState(targetState) {} 
std::shared_ptr<State> Transition::getTargetState() {
    return targetState;
}
std::string Transition::getToken() {
    return token;
}



std::shared_ptr<Transition> State::getTransition() {
    return std::make_shared<Transition>(shared_from_this(), getToken());
}

DigitReadingState::DigitReadingState(char initialDigit) {
    numberBuffer << initialDigit;
}

void DigitReadingState::validate(char readCharacter, char nextCharacter) {
    if(isOperator(readCharacter)) {
        throw InvalidFormulaException("Invalid character found " + std::string(1, readCharacter));
    }
}

std::shared_ptr<Transition> DigitReadingState::transition(char readCharacter, char nextCharacter) {
    numberBuffer << readCharacter;

    if(isOperator(nextCharacter) || nextCharacter == 0) {
        return std::make_shared<DigitCompleteState>(numberBuffer.str())->getTransition();
    }

    return getTransition();
}

std::string DigitReadingState::getToken() {
    return std::string();
}


DigitCompleteState::DigitCompleteState(std::string number) : number(number) {}
void DigitCompleteState::validate(char readCharacter, char nextCharacter) {
   if(!isOperator(readCharacter)) {
       throw InvalidFormulaException("Invalid character found " + std::string(1, readCharacter));
   }
}

std::shared_ptr<Transition> DigitCompleteState::transition(char readCharacter, char nextCharacter) {
    return std::make_shared<OperatorState>(readCharacter)->getTransition();
}

std::string DigitCompleteState::getToken() {
    return number;
}


OperatorState::OperatorState(char symbol) : symbol(symbol) {}

void OperatorState::validate(char readCharacter, char nextCharacter) {
    if(isOperator(readCharacter)) {
        throw InvalidFormulaException("Invalid character found " + std::string(1, readCharacter));
    }
}

std::shared_ptr<Transition> OperatorState::transition(char readCharacter, char nextCharacter) {
    if(isNumber(nextCharacter)) {
        return std::make_shared<DigitReadingState>(readCharacter)->getTransition();
    } else {
        return std::make_shared<DigitCompleteState>(std::string(1, readCharacter))->getTransition();
    }
}

std::string OperatorState::getToken() {
    return std::string(1, symbol);
}


void EmptyState::validate(char readCharacter, char nextCharacter) {
    if(isOperator(readCharacter)) {
        throw InvalidFormulaException("Invalid character found " + std::string(1, readCharacter));
    }
}

std::shared_ptr<Transition> EmptyState::transition(char readCharacter, char nextCharacter) {
    
    if(isNumber(nextCharacter)) {
        return std::make_shared<DigitReadingState>(readCharacter)->getTransition();
    } else {
        return std::make_shared<DigitCompleteState>(std::string(1, readCharacter))->getTransition();
    }
}

std::string EmptyState::getToken() {
    return std::string();
}


FSM::FSM() : state(std::make_shared<EmptyState>()) {
    
}

std::string FSM::transition(char readCharacter, char nextCharacter) {
    state->validate(readCharacter, nextCharacter);
    auto transition = state->transition(readCharacter, nextCharacter);
    state = transition->getTargetState();
    return transition->getToken();
}

std::unique_ptr<std::vector<std::string>> LexicalAnalyzer::parseToTokens(const std::string &input) {
    std::cout << "LexicalAnalyzer::parseToTokens IN" << "\n";
    auto resultVector = std::make_unique<std::vector<std::string>>();
    
   FSM fsm;
   
    std::cout << "input.length() = " << input.length() << "\n";
    for(auto i = 0; i < input.length(); i++) {
        
        char readCharacter = input[i];
        char nextCharacter = input[i+1];
        
        std::cout << "INPUT: " << readCharacter << "\n";
        std::cout << "INPUT-next: " << nextCharacter << "\n";
    
        
        auto token = fsm.transition(readCharacter, nextCharacter);
        std::cout << "TOKEN: " << token << "\n";
        
        if(!token.empty()) {
            resultVector->push_back(token);
        }   
        
    }
    
    std::cout << "LexicalAnalyzer::parseToTokens OUT" << "\n";
    return resultVector;
}
