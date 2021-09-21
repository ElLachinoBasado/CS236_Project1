#ifndef LEXICALANALYZER_FACTSAUTOMATON_H
#define LEXICALANALYZER_FACTSAUTOMATON_H

#include "Automaton.h"

class FactsAutomaton : public Automaton {
public:
    FactsAutomaton() : Automaton(TokenType::FACTS) {}
    void S0(const std::string& input); //F
    void S1(const std::string& input); //a
    void S2(const std::string& input); //c
    void S3(const std::string& input); //t
    void S4(const std::string& input); //s
};


#endif //LEXICALANALYZER_FACTSAUTOMATON_H
