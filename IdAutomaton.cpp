#include "IdAutomaton.h"
#include <cctype>

void IdAutomaton::S0(const std::string &input) {
    if (isalpha(input[index]) != 0) {
        inputRead++;
        index++;
        S1(input);
    } else {
        Serr();
    }
}

void IdAutomaton::S1(const std::string &input) {
    if (isalnum(input[index])) {
        inputRead++;
        index++;
        S1(input);
    }
}
