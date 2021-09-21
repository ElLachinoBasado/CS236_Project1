#ifndef LEXICALANALYZER_QUERIESAUTOMATON_H
#define LEXICALANALYZER_QUERIESAUTOMATON_H

#include "Automaton.h"

class QueriesAutomaton : public Automaton {
public:
    QueriesAutomaton() : Automaton(TokenType::QUERIES) {}
    void S0(const std::string& input); //Q
    void S1(const std::string& input); //u
    void S2(const std::string& input); //e
    void S3(const std::string& input); //r
    void S4(const std::string& input); //i
    void S5(const std::string& input); //e
    void S6(const std::string& input); //s
};


#endif //LEXICALANALYZER_QUERIESAUTOMATON_H
