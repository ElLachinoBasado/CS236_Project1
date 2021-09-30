//
// Created by Helaman on 9/29/2021.
//

#include "Rule.h"

Rule::Rule(Predicate head, vector<Predicate> list) {
    headPredicate = head;
    predicateList = list;
}

string Rule::toString() {
    string result = headPredicate.toString() + " :- ";
    for (int i = 0; i < predicateList.size(); i++) {
        result += predicateList.at(i).toString();
        if (i != predicateList.size()-1) {
            result += ",";
        }
    }
    result += ".";
}
