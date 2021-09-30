//
// Created by Helaman on 9/29/2021.
//

#include "Predicate.h"

Predicate::Predicate(string id, vector<Parameter> list) {
    name = id;
    parameterList = list;
}

string Predicate::toString() {
    string result = name + "(";
    for (int i = 0; i < parameterList.size(); i++) {
        result += parameterList.at(i).getValue();
    }
    result += ')';
    return result;
}