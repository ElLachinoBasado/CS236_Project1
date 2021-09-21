#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "MatcherAutomaton.h"
#include "SchemesAutomaton.h"
#include "FactsAutomaton.h"
#include "RulesAutomaton.h"
#include "QueriesAutomaton.h"
#include "IdAutomaton.h"
#include <sstream>
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
    // TODO: Add the other needed automata here
}

void Lexer::Run(std::string& input) {
    int lineNumber = 1;
    //read and iterate through string
    istringstream f(input);
    string line;
    while (getline(f, line)) { //retrieves a line
        if (line == "") {
            lineNumber++;
            continue;
        }
        while(line.size()>0){
            int maxRead = 0;
            Automaton* maxAutomaton = automata.front();
            while (isspace(line[0])) {
                line.erase(line.begin());
            }

            for (int i = 0; i < automata.size(); i++) {
                int inputRead = automata.at(i)->Start(line);
                if (inputRead > maxRead) {
                    maxRead = inputRead;
                    maxAutomaton = automata.at(i);
                }
            }

            if (maxRead > 0) {
                Token* newToken = maxAutomaton->CreateToken(line.substr(0,maxRead),lineNumber);
                tokens.push_back(newToken);
            } else {
                maxRead = 1;
                Token* newToken = new Token(TokenType::UNDEFINED, line.substr(0,maxRead), lineNumber);
                tokens.push_back(newToken);
            }
            line.erase(0, maxRead);
        }
        lineNumber++;
    }
}
