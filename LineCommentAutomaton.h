#ifndef LEXICALANALYZER_LINECOMMENTAUTOMATON_H
#define LEXICALANALYZER_LINECOMMENTAUTOMATON_H

#include "Automaton.h"

class LineCommentAutomaton : public Automaton {
private:
    void S1 (const std::string& input);
public:
    LineCommentAutomaton() : Automaton(TokenType::COMMENT) {}
    void S0 (const std::string& input);
};


#endif //LEXICALANALYZER_LINECOMMENTAUTOMATON_H
