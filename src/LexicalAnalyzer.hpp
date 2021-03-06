#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <memory>

#include "characterType.hpp"
#include "token.hpp"

class InvalidFormulaException : public std::exception {
private:
    std::string message_;
public:
    explicit InvalidFormulaException(const std::string &message);

    const char *what() const noexcept override {
        return message_.c_str();
    }
};

class State;

class Transition {
    private:
        std::shared_ptr<State> targetState;
        std::shared_ptr<Token> token;
    public:
        Transition(std::shared_ptr<State> targetState, std::shared_ptr<Token> token);
        std::shared_ptr<State> getTargetState();
        std::shared_ptr<Token> getToken();
};


class State : public std::enable_shared_from_this<State> {
    
    public:
        virtual void validate(char readCharacter, char nextCharacter) = 0;

        virtual std::shared_ptr<Transition> transition(char readCharacter, char nextCharacter) = 0;
    
        virtual std::shared_ptr<Token> getToken() = 0;
        
        std::shared_ptr<Transition> getTransition();
};


class DigitReadingState : public State {
    private:
        std::stringstream numberBuffer;
    public:
        DigitReadingState(char initialDigit);
        
        void validate(char readCharacter, char nextCharacter) override;

        std::shared_ptr<Transition> transition(char readCharacter, char nextCharacter) override;
        
        std::shared_ptr<Token> getToken() override;

};

class DigitCompleteState : public State {
    private:
        std::string number;
    public:
        DigitCompleteState(std::string number);
        void validate(char readCharacter, char nextCharacter) override;

        std::shared_ptr<Transition> transition(char readCharacter, char nextCharacter) override;
        
        std::shared_ptr<Token> getToken() override;

};

class OperatorState : public State {
    private:
        char symbol;
    public:
        OperatorState(char symbol);
        
        void validate(char readCharacter, char nextCharacter) override;

        std::shared_ptr<Transition> transition(char readCharacter, char nextCharacter) override;
        
        std::shared_ptr<Token> getToken() override;

};

class EmptyState : public State {
    public:
        void validate(char readCharacter, char nextCharacter) override;

        std::shared_ptr<Transition> transition(char readCharacter, char nextCharacter) override;
        
        std::shared_ptr<Token> getToken() override;
};



class FSM {
    private:
        std::shared_ptr<State> state;
    public:
        FSM();
        std::shared_ptr<Token> transition(char readCharacter, char nextCharacter);
};

class LexicalAnalyzer {

public:
    std::unique_ptr<std::vector<std::shared_ptr<Token>>> parseToTokens(const std::string &input);

};

