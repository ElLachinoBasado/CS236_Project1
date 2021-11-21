//
// Created by Helaman on 10/25/2021.
//
#include <iostream>
#include "Database.h"
using namespace std;
void Database::addRelation(string theKey, Relation * toAdd) {
    database.emplace(theKey, toAdd);
}

bool Database::updateRelation(string toChange, Relation * theRelation, int & numIterations) {
    Relation * ogRelation = database[toChange];
    database[toChange] = theRelation;

    if (ogRelation->toString() != database[toChange]->toString()) {
        //numIterations++;
        return true;
    } else {
        return false;
    }
}
void Database::addTuple(Tuple toAdd, string theRelation) {
    //database.at(theRelation).addTuple(toAdd);
}
Relation Database::getRelation(string theRelation) {
    return *database.at(theRelation);
}

void Database::print() {
    for (const auto& elem : database) {
        cout << elem.first << endl;
        cout << elem.second->toString() << endl;
    }
}