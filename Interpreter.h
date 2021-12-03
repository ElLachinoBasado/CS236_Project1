#ifndef LEXICALANALYZER_INTERPRETER_H
#define LEXICALANALYZER_INTERPRETER_H
#include "DatalogProgram.h"
#include "Database.h"

class Interpreter {
private:
    DatalogProgram datalogProgram;
    Database database;
public:
    Interpreter(DatalogProgram *dpReference);

    Relation evaluatePredicate(Predicate p);

    void evaluateAllQueries();
    void evaluateAllRules();

    bool evaluateRule(Rule evaluatedRule, string & output);
    vector<Relation> getIntermediateRelations(Rule ruleToCheck);
    Relation joinRelations(vector<Relation> relations, string ruleName);
};
#endif //LEXICALANALYZER_INTERPRETER_H
