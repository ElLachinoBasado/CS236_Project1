#ifndef LEXICALANALYZER_UNCLOSEDSTRINGAUTOMATON_H
#define LEXICALANALYZER_UNCLOSEDSTRINGAUTOMATON_H

#include "Automaton.h"

class UnclosedStringAutomaton : public Automaton {
private:
    void S1(const std::string &input);
    void S2(const std::string &input);
public:
    UnclosedStringAutomaton() : Automaton(TokenType::UNDEFINED) {}
    void S0 (const std::string& input);
};


#endif //LEXICALANALYZER_UNCLOSEDSTRINGAUTOMATON_H
