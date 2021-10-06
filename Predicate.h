//
// Created by Helaman on 9/29/2021.
//

#ifndef LEXICALANALYZER_PREDICATE_H
#define LEXICALANALYZER_PREDICATE_H

#include <string>
#include <vector>
#include "Parameter.h"
using namespace std;
class Predicate {
private:
    string name;
    vector<Parameter*> parameterList;
public:
    Predicate() {};
    Predicate(string id, vector<Parameter*> list);
    string toString();
};


#endif //LEXICALANALYZER_PREDICATE_H
