#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <memory>

#include "characterType.hpp"

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
        std::string token;
    public:
        Transition(std::shared_ptr<State> targetState, std::string token);
        std::shared_ptr<State> getTargetState();
        std::string getToken();
};


class State : public std::enable_shared_from_this<State> {
    
    public:
        virtual void validate(char readCharacter, char nextCharacter) = 0;

        virtual std::shared_ptr<Transition> transition(char readCharacter, char nextCharacter) = 0;
    
        virtual std::string getToken() = 0;
        
        std::shared_ptr<Transition> getTransition();
};


class DigitReadingState : public State {
    private:
        std::stringstream numberBuffer;
    public:
        DigitReadingState(char initialDigit);
        
        void validate(char readCharacter, char nextCharacter);

        std::shared_ptr<Transition> transition(char readCharacter, char nextCharacter);
        
        std::string getToken();

};

class DigitCompleteState : public State {
    private:
        std::string number;
    public:
        DigitCompleteState(std::string number);
        void validate(char readCharacter, char nextCharacter);

        std::shared_ptr<Transition> transition(char readCharacter, char nextCharacter);
        
        std::string getToken();

};

class OperatorState : public State {
    private:
        char symbol;
    public:
        OperatorState(char symbol);
        
        void validate(char readCharacter, char nextCharacter);

        std::shared_ptr<Transition> transition(char readCharacter, char nextCharacter);
        
        std::string getToken();

};

class EmptyState : public State {
    public:
        void validate(char readCharacter, char nextCharacter);

        std::shared_ptr<Transition> transition(char readCharacter, char nextCharacter);
        
        std::string getToken();
};



class FSM {
    private:
        std::shared_ptr<State> state;
    public:
        FSM();
        std::string transition(char readCharacter, char nextCharacter);
};

class LexicalAnalyzer {

public:
    std::unique_ptr<std::vector<std::string>> parseToTokens(const std::string &input);

};

