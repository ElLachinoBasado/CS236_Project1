#ifndef LEXICALANALYZER_RULESAUTOMATON_H
#define LEXICALANALYZER_RULESAUTOMATON_H

#include "Automaton.h"

class RulesAutomaton : public Automaton {
public:
    RulesAutomaton() : Automaton(TokenType::RULES) {}
    void S0(const std::string& input); //R
    void S1(const std::string& input); //u
    void S2(const std::string& input); //l
    void S3(const std::string& input); //e
    void S4(const std::string& input); //s
};


#endif //LEXICALANALYZER_RULESAUTOMATON_H
