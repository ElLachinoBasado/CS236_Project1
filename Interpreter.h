#ifndef LEXICALANALYZER_INTERPRETER_H
#define LEXICALANALYZER_INTERPRETER_H
#include "DatalogProgram.h"
#include "Database.h"

class Interpreter {
private:
    DatalogProgram datalogProgram;
    Database database;
public:
    Interpreter(DatalogProgram * dpReference);
    Relation evaluatePredicate(Predicate p);
    Relation evaluateRule(Rule mainRule, Relation newRelation);
    void evaluateAllQueries();
    void evaluateAllRules();

};


#endif //LEXICALANALYZER_INTERPRETER_H
