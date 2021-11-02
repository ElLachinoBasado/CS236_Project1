//
// Created by Helaman on 9/29/2021.
//

#include "Predicate.h"

Predicate::Predicate(string id, vector<Parameter*> list) {
    name = id;
    parameterList = list;
}

string Predicate::toString() {
    string result = name + "(";
    for (unsigned int i = 0; i < parameterList.size(); i++) {
        result = result + parameterList.at(i)->getValue();
        if (i != parameterList.size()-1) result = result + ",";
    }
    result = result + ')';
    return result;
}

string Predicate::getName() {
    return name;
}
vector<Parameter*> Predicate::getParameterPointerList() {
    return parameterList;
}
vector<Parameter> Predicate::getParameterList() {
    vector<Parameter> tempList;
    for (unsigned int i = 0; i < parameterList.size(); i++) {
        tempList.push_back(*parameterList.at(i));
    }
    return tempList;
}