//
// Created by Helaman on 10/25/2021.
//

#ifndef LEXICALANALYZER_DATABASE_H
#define LEXICALANALYZER_DATABASE_H
#include <string>
#include "Relation.h"
#include "Tuple.h"
#include <map>

using namespace std;
class Database {
private:
    map<string, Relation *> database;
public:
    Database() = default;
    void addRelation(string theKey, Relation * toAdd); //emplace
    void updateRelation(string toChange, Relation theRelation); //database[toChange] = theRelation
    void addTuple(Tuple toAdd, string theRelation); //database.at(theRelation).addTuple(toAdd)
    Relation * getRelation(string theRelation); //database.at(theRelation)
    void print();
};


#endif //LEXICALANALYZER_DATABASE_H
