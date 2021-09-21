#ifndef LEXICALANALYZER_SCHEMESAUTOMATON_H
#define LEXICALANALYZER_SCHEMESAUTOMATON_H

#include "Automaton.h"

class SchemesAutomaton : public Automaton {
public:
    SchemesAutomaton() : Automaton(TokenType::SCHEMES) {}
    void S0(const std::string& input); //s
    void S1(const std::string& input); //c
    void S2(const std::string& input); //h
    void S3(const std::string& input); //e
    void S4(const std::string& input); //m
    void S5(const std::string& input); //e
    void S6(const std::string& input); //s
};


#endif //LEXICALANALYZER_SCHEMESAUTOMATON_H
