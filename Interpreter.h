#ifndef LEXICALANALYZER_INTERPRETER_H
#define LEXICALANALYZER_INTERPRETER_H
#include "DatalogProgram.h"
#include "Database.h"
#include "DGraph.h"

class Interpreter {
private:
    DatalogProgram datalogProgram;
    Database database;
    DGraph * dGraph;
public:
    Interpreter(DatalogProgram *dpReference);
    Relation evaluatePredicate(Predicate p);

    void evaluateAllQueries();
    void evaluateAllRules();
    void evaluateAllSCCRules();

    bool evaluateRule(Rule evaluatedRule, string & output);
    vector<Relation> getIntermediateRelations(Rule ruleToCheck);
    Relation joinRelations(vector<Relation> relations, string ruleName);

    string sccToString(set<int> currentSCC);
    bool isSelfDependent(set<int> currentSCC);
};
#endif //LEXICALANALYZER_INTERPRETER_H
