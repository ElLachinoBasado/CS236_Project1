//
// Created by Helaman on 9/29/2021.
//

#ifndef LEXICALANALYZER_PARSER_H
#define LEXICALANALYZER_PARSER_H
#include "Token.h"
#include "DatalogProgram.h"

class Parser {
private:
    unsigned int i;
public:
    Parser( );

    DatalogProgram parse();

    void datalogProgram();

    void schemeList();
    void factList();
    void ruleList();
    void queryList();

    void scheme();

//headPredicate (predicate), predicate (predicate)
// lowercase = function, caps = if statement
};


#endif //LEXICALANALYZER_PARSER_H
