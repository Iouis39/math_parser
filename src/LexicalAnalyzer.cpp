#include "LexicalAnalyzer.hpp"

#include <iostream>
#include <memory>


InvalidFormulaException::InvalidFormulaException(const std::string &message) : message_(message) {
}

/* ***************************************************************** */

Transition::Transition(std::shared_ptr<State> targetState, std::shared_ptr<Token> token) : token(token), targetState(targetState) {} 
std::shared_ptr<State> Transition::getTargetState() {
    return targetState;
}
std::shared_ptr<Token> Transition::getToken() {
    return this->token;
}

/* ***************************************************************** */

std::shared_ptr<Transition> State::getTransition() {
    return std::make_shared<Transition>(shared_from_this(), getToken());
}

/* ***************************************************************** */

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

std::shared_ptr<Token> DigitReadingState::getToken() {
    return nullptr;
}

/* ***************************************************************** */

DigitCompleteState::DigitCompleteState(std::string number) : number(number) {}
void DigitCompleteState::validate(char readCharacter, char nextCharacter) {
   if(!isOperator(readCharacter)) {
       throw InvalidFormulaException("Invalid character found " + std::string(1, readCharacter));
   }
}

std::shared_ptr<Transition> DigitCompleteState::transition(char readCharacter, char nextCharacter) {
    return std::make_shared<OperatorState>(readCharacter)->getTransition();
}

std::shared_ptr<Token> DigitCompleteState::getToken() {
    return std::make_shared<Token>(number, TokenType::NUMBER);
}

/* ***************************************************************** */

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

std::shared_ptr<Token> OperatorState::getToken() {
    return std::make_shared<Token>(std::string(1, symbol), TokenType::OPERATOR);
}

/* ***************************************************************** */


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

std::shared_ptr<Token> EmptyState::getToken() {
    return nullptr;
}

/* ***************************************************************** */

FSM::FSM() : state(std::make_shared<EmptyState>()) {
    
}

std::shared_ptr<Token> FSM::transition(char readCharacter, char nextCharacter) {
    state->validate(readCharacter, nextCharacter);
    auto transition = state->transition(readCharacter, nextCharacter);
    state = transition->getTargetState();
    return transition->getToken();
}

/* ***************************************************************** */

std::unique_ptr<std::vector<std::shared_ptr<Token>>> LexicalAnalyzer::parseToTokens(const std::string &input) {
    
    auto resultVector = std::make_unique<std::vector<std::shared_ptr<Token>>>();
    
   FSM fsm;
   
    for(auto i = 0; i < input.length(); i++) {
        
        char readCharacter = input[i];
        char nextCharacter = input[i+1];
    
        auto token = fsm.transition(readCharacter, nextCharacter);
        if( token != nullptr ) {
            resultVector->push_back(token);
        }   
        
    }

    return resultVector;
}
