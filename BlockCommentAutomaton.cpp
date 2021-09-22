#include "BlockCommentAutomaton.h"

void BlockCommentAutomaton::S0 (const std::string& input) {
    if (input[index] == '#') {
        inputRead++;
        index++;
        if (index < input.size()) {
            S1(input);
        }
    } else {
        Serr();
    }
}

void BlockCommentAutomaton::S1 (const std::string& input) {
    if (input[index] == '|') {
        inputRead++;
        index++;
        S2(input);
    } else {
        S4(input);
    }
}

void BlockCommentAutomaton::S2 (const std::string& input) {
    if (index < input.size()) {
        if (input[index] == '\n') {
            inputRead++;
            index++;
            newLines++;
            S2(input);
        } else if (input[index] == '|') {
            inputRead++;
            index++;
            S3(input);
        } else {
            inputRead++;
            index++;
            S2(input);
        }
    } else {
        Serr();
    }
}

void BlockCommentAutomaton::S3 (const std::string& input) {
    if (index < input.size()) {
        if (input[index] != '#') {
            inputRead++;
            index++;
            S2(input);
        } else {
            inputRead++;
            index++;
        }
    } else {
        Serr();
    }
}

void BlockCommentAutomaton::S4 (const std::string& input) {
    if (index < input.size()) {
        if (input[index] != '\n') {
            inputRead++;
            index++;
            S4(input);
        }
    }
}