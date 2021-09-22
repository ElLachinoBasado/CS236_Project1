#include "UnclosedStringAutomaton.h"
void UnclosedStringAutomaton::S0(const std::string &input) {
    if (input[index] == '\'') {
        inputRead++;
        index++;
        S1(input);
    } else {
        Serr();
    }
}

void UnclosedStringAutomaton::S1(const std::string &input) {
    if (index > input.size()) {

    } else if (input[index] == '\n') {
        newLines++;
        inputRead++;
        index++;
        S1(input);
    } else if (input[index] == '\'') {
        inputRead++;
        index++;
        S2(input);
    } else {
        inputRead++;
        index++;
        S1(input);
    }
}

void UnclosedStringAutomaton::S2(const std::string &input) {
    if (input[index] == '\'') {
        inputRead++;
        index++;
        S1(input);
    } else {
        Serr();
    }
}