//
// Created by Helaman on 9/29/2021.
//

#ifndef LEXICALANALYZER_DATALOGPROGRAM_H
#define LEXICALANALYZER_DATALOGPROGRAM_H
#include "Rule.h"
#include "Predicate.h"
#include <vector>

class DatalogProgram {
private:
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Rule> rules;
    vector<Predicate> queries;
public:
    DatalogProgram();
    void addSchemes(Predicate &toAdd);
    void addFacts(Predicate &toAdd);
    void addRules(Rule &toAdd);
    void addQueries(Predicate &toAdd);
};


#endif //LEXICALANALYZER_DATALOGPROGRAM_H
