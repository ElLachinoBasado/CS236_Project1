//
// Created by Helaman on 9/29/2021.
//

#ifndef LEXICALANALYZER_PARSER_H
#define LEXICALANALYZER_PARSER_H
#include "Token.h"
#include "DatalogProgram.h"
#include "Parser.h"
#include "Parameter.h"
#include "Predicate.h"
#include "Rule.h"
#include <vector>

class Parser {
private:
    unsigned int i;
    bool succeeded;
    vector<Token*> tokens;
    DatalogProgram* program;
public:
    Parser(vector<Token*> input);
    void parse();
    DatalogProgram* getProgram();

    void predicateList(vector<Predicate*> &list);
    void parameterList(vector<Parameter*> &list);
    void stringList(vector<Parameter*> &list);
    void idList(vector<Parameter*> &list);
    Parameter* parameter();

    Predicate* headPredicate();
    Predicate* predicate();

    void scheme();
    void fact();
    void rule();
    void query();

    void schemeList();
    void factList();
    void ruleList();
    void queryList();

};


#endif //LEXICALANALYZER_PARSER_H
//headPredicate (predicate), predicate (predicate)
// lowercase = function, caps = if statement