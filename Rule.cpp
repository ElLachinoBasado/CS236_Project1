//
// Created by Helaman on 9/29/2021.
//

#include "Rule.h"

Rule::Rule(Predicate* head, vector<Predicate*> list) {
    headPredicate = head;
    predicateList = list;
}

string Rule::toString() {
    string result = headPredicate->toString() + " :- ";
    for (unsigned int i = 0; i < predicateList.size(); i++) {
        result += predicateList.at(i)->toString();
        if (i != predicateList.size()-1) {
            result = result + ",";
        }
    }
    result = result + ".";
    return result;
}

Predicate Rule::getHeadPredicate() {
    return * headPredicate;
}

vector<Predicate> Rule::getPredicateList() {
    vector<Predicate> tempPredList;
    for (Predicate * currPredicate : predicateList) {
        tempPredList.push_back(* currPredicate);
    }
    return tempPredList;
}