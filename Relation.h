//
// Created by Helaman on 10/25/2021.
//

#ifndef LEXICALANALYZER_RELATION_H
#define LEXICALANALYZER_RELATION_H
#include "Tuple.h"
#include "Header.h"
#include <map>
#include <vector>
#include <set>
#include <string>
#include <iostream>

using namespace std;
class Relation {
private:
    string name;
    set<Tuple> domain;
    Header* header;
public:
    Relation(string theName, Header* theHeader);
    Relation(string theName, Header* theHeader, set<Tuple> newDomain);
    Relation(string theName, Header theHeader);
    Relation select(int index, string value);
    Relation select(int index1, int index2);
    Relation rename(vector<string> newAttributes);
    Relation project(vector<int> columns);
    Relation join(Relation secondRelation, string ruleName);
    Relation unite(Relation otherRelation, string & output);
    bool isJoinable(Tuple & t, Tuple & u, vector <pair<int,int>> & joinMap);
    Tuple tupleJoin(Tuple & t, Tuple & u, vector <pair<int,int>> & joinMap);
    void addTuple(Tuple toAdd);
    string toString();
    bool isEmpty();
    Header* getHeader();
    Header* combineHeaders(Header a, Header b, vector <pair<int,int>> & joinMap);
    string getName();
    set<Tuple> getDomain();
    void setHeader(Header toSet);
    void setName(string newName);
};




#endif //LEXICALANALYZER_RELATION_H
