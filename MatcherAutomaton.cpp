//
// Created by Helaman on 9/19/2021.
//

#include "MatcherAutomaton.h"

void MatcherAutomaton::S0(const std::string& input) {
    if (input[index] == ',') {
        inputRead = 1;
        type = TokenType::COMMA;
    } else if (input [index] == '.') {
        inputRead = 1;
        type = TokenType::PERIOD;
    } else if (input [index] == '?') {
        inputRead = 1;
        type = TokenType::Q_MARK;
    } else if (input [index] == '(') {
        inputRead = 1;
        type = TokenType::LEFT_PAREN;
    } else if (input [index] == ')') {
        inputRead = 1;
        type = TokenType::RIGHT_PAREN;
    } else if (input [index] == '*') {
        inputRead = 1;
        type = TokenType::MULTIPLY;
    } else if (input [index] == '+') {
        inputRead = 1;
        type = TokenType::ADD;
    } else {
        Serr();
    }
}