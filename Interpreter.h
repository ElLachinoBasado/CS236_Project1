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

    vector<Relation> getIntermediateRelations(vector<Rule> allRules);
};
#endif //LEXICALANALYZER_INTERPRETER_H
