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

vector<Predicate> Rule::getPredicateList() {
    vector<Predicate> newPredicateList;
    for (Predicate * currPredicatePointer : predicateList) {
        newPredicateList.push_back(*currPredicatePointer);
    }
    return newPredicateList;
}

string Rule::getName() {
    return headPredicate->getName();
}

Predicate* Rule::getHeadPredicate() {
    return headPredicate;
}