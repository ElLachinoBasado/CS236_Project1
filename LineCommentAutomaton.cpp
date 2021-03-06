#include "LineCommentAutomaton.h"

void LineCommentAutomaton::S0 (const std::string& input) {
    if (input[index] == '#') {
        inputRead++;
        index++;
        if (index < input.size()) {
            if (input[index] == '|') {
                Serr();
            } else {
                S1(input);
            }
        }
    } else {
        Serr();
    }
}

void LineCommentAutomaton::S1 (const std::string& input) {
    if (index < input.size()) {
        if (input[index] != '\n') {
            inputRead++;
            index++;
            S1(input);
        }
    }
}