//
// Created by Helaman on 10/25/2021.
//

#ifndef LEXICALANALYZER_RELATION_H
#define LEXICALANALYZER_RELATION_H
#include "Tuple.h"
#include "Header.h"
#include <vector>
#include <set>
#include <string>

using namespace std;
class Relation {
private:
    string name;
    set<Tuple> domain;
    Header* header;
public:
    Relation(string theName, Header* theHeader);
    Relation select(int index, string value);
    void addTuple(Tuple toAdd);
    string toString();

    Header* getHeader();
};




#endif //LEXICALANALYZER_RELATION_H
