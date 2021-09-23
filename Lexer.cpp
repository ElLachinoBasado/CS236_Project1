#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "MatcherAutomaton.h"
#include "SchemesAutomaton.h"
#include "FactsAutomaton.h"
#include "RulesAutomaton.h"
#include "QueriesAutomaton.h"
#include "IdAutomaton.h"
#include "StringAutomaton.h"
#include "BlockCommentAutomaton.h"
#include "UnclosedStringAutomaton.h"
#include "UnclosedBlockCommentAutomaton.h"
#include <iostream>
#include <cctype>

using namespace std;
Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    // TODO: need to clean up the memory in `automata` and `tokens`
}
vector<Token*> Lexer::getTokens() {
    return tokens;
}
void Lexer::CreateAutomata() {
    automata.push_back(new SchemesAutomaton());
    automata.push_back(new FactsAutomaton());
    automata.push_back(new RulesAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new MatcherAutomaton());
    automata.push_back(new IdAutomaton());
    automata.push_back(new UnclosedStringAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new UnclosedBlockCommentAutomaton());
    automata.push_back(new BlockCommentAutomaton());

    // TODO: Add the other needed automata here
}

void Lexer::Run(std::string& input) {
    int lineNumber = 1;
    //read and iterate through string
    string line = input;
    while (line.size() > 0) {
        int maxRead = 0;
        Automaton* maxAutomaton = automata.front();
        while (isspace(line[0])) { //deletes whitespace at front of string
            if (line[0] == '\n') {
                line.erase(line.begin());
                lineNumber++;
                continue;
            } else {
                line.erase(line.begin());
            }
        }

        for (long unsigned int i = 0; i < automata.size(); i++) {
            int inputRead = automata.at(i)->Start(line);
            if (inputRead > maxRead) {
                maxRead = inputRead;
                maxAutomaton = automata.at(i);
            }
        }

        if (maxRead > 0) {
            Token* newToken = maxAutomaton->CreateToken(line.substr(0,maxRead),lineNumber);
            tokens.push_back(newToken);
            if (maxAutomaton->NewLinesRead() > 0) {
                lineNumber += maxAutomaton->NewLinesRead();
            }
        } else {
            if (line.size() < 1) {
                continue;
            }
            maxRead = 1;
            Token* newToken = new Token(TokenType::UNDEFINED, line.substr(0,maxRead), lineNumber);
            tokens.push_back(newToken);
        }
        line.erase(0, maxRead);
    }
    Token* newToken = new Token(TokenType::EOF_TYPE,"",lineNumber);
    tokens.push_back(newToken);
}
