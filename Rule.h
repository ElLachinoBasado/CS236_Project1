//
// Created by Helaman on 9/29/2021.
//

#ifndef LEXICALANALYZER_RULE_H
#define LEXICALANALYZER_RULE_H

#include <string>
#include <vector>
#include "Predicate.h"
class Rule {
private:
    Predicate* headPredicate;
    vector<Predicate*> predicateList;
public:
    Rule(Predicate* head, vector<Predicate*> list);
    string toString();
};


#endif //LEXICALANALYZER_RULE_H
