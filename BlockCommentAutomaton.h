#ifndef LEXICALANALYZER_BLOCKCOMMENTAUTOMATON_H
#define LEXICALANALYZER_BLOCKCOMMENTAUTOMATON_H

#include "Automaton.h"

class BlockCommentAutomaton : public Automaton {
private:
    void S1 (const std::string& input);
    void S2 (const std::string& input);
    void S3 (const std::string& input);
    void S4 (const std::string& input);
public:
    BlockCommentAutomaton() : Automaton(TokenType::COMMENT) {}
    void S0 (const std::string& input);
};


#endif //LEXICALANALYZER_BLOCKCOMMENTAUTOMATON_H
