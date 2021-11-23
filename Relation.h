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
    Relation select(int index1, int index2);
    Relation rename(vector<string> newAttributes);
    Relation project(vector<int> columns);
    void addTuple(Tuple toAdd);
    string toString();
    bool isEmpty();
    Header* getHeader();
};




#endif //LEXICALANALYZER_RELATION_H
