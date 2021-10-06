#ifndef LEXICALANALYZER_DATALOGPROGRAM_H
#define LEXICALANALYZER_DATALOGPROGRAM_H
#include "Rule.h"
#include "Predicate.h"
#include <vector>
#include <iostream>
#include <set>

using namespace std;

class DatalogProgram {
private:
    vector<Predicate*> schemes;
    vector<Predicate*> facts;
    vector<Rule*> rules;
    vector<Predicate*> queries;
    set<string> domain;
public:
    DatalogProgram();
    void addSchemes(Predicate* &toAdd);
    void addFacts(Predicate* &toAdd);
    void addRules(Rule* &toAdd);
    void addQueries(Predicate* &toAdd);
    void addDomain(Parameter* &toAdd);
    void print();
};


#endif //LEXICALANALYZER_DATALOGPROGRAM_H
