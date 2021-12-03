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
#include <map>

using namespace std;
class Relation {
private:
    string name;
    set<Tuple> domain;
    Header* header;
public:
    Relation();
    Relation(string theName, Header* theHeader);
    Relation select(int index, string value);
    Relation select(int index1, int index2);
    Relation rename(vector<string> newAttributes);
    Relation project(vector<int> columns);
    Relation join(Relation b, string ruleName);//, Header * combinedHeaders, vector <pair<int,int>> joinVector);
    Relation unite(Relation r, bool & addTuple, string & output);
    void addTuple(Tuple toAdd);
    string toString();
    bool isEmpty();
    bool isJoinable(Tuple t, Tuple u, map <int,int> joinMap);

    string getName();
    set<Tuple> getDomain();
    Header* getHeader();
    void setHeader(Header * newHeader);
    Tuple combineTuples(Tuple t, Tuple u, map<int,int> joinMap);
    string convertTuple(Tuple t);

    void setDomain(set<Tuple> newDomain);

};




#endif //LEXICALANALYZER_RELATION_H
