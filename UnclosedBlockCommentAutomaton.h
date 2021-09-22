#ifndef LEXICALANALYZER_UNCLOSEDBLOCKCOMMENTAUTOMATON_H
#define LEXICALANALYZER_UNCLOSEDBLOCKCOMMENTAUTOMATON_H

#include "Automaton.h"

class UnclosedBlockCommentAutomaton : public Automaton {
private:
    void S1 (const std::string& input);
    void S2 (const std::string& input);
    void S3 (const std::string& input);
public:
    UnclosedBlockCommentAutomaton() : Automaton(TokenType::UNDEFINED) {}
    void S0 (const std::string& input);

};


#endif //LEXICALANALYZER_UNCLOSEDBLOCKCOMMENTAUTOMATON_H
