//
// Created by Helaman on 10/25/2021.
//

#include "Relation.h"

Relation::Relation(string theName, Header* theHeader) {
    name = theName;
    header = theHeader;
}

Header* Relation::getHeader() {
    return header;
}

void Relation::addTuple(Tuple toAdd) {
    domain.insert(toAdd);
}

string Relation::toString() {
    string newString = "";
    vector<string> headerValues = header->getAttributes();
    newString = newString + "(" + to_string(domain.size()) + ")" + "\n";
    for (auto thisTuple : domain) {
        for (unsigned int i = 0; i < headerValues.size(); i++) {
            newString += "  ";
            newString += headerValues.at(i);
            newString += "=";
            newString += thisTuple.toString(i);
            if (i != headerValues.size() - 1) {
                newString += ", ";
            } else {
                newString += "\n";
            }
        }
    }
    return newString;
}

Relation Relation::select(int index, string value) {
    Relation selectedRelation(name,header);
    for (auto thisTuple : domain) {
        if (thisTuple.toString(index) == value) {
            selectedRelation.addTuple(thisTuple);
        }
    }
    return selectedRelation;
}

Relation Relation::select(int index1, int index2) {
    Relation selectedRelation(name,header);
    for (auto thisTuple : domain) {
        if (thisTuple.toString(index1) == thisTuple.toString(index2)) {
            selectedRelation.addTuple(thisTuple);
        }
    }
    return selectedRelation;
}

Relation Relation::rename(vector<string> newAttributes) {
    Header * newHeader = new Header(newAttributes);
    Relation renamedRelation(name,newHeader);
    renamedRelation.domain = domain;
    return renamedRelation;
}

Relation Relation::project(vector<int> columns) {
    vector<string> newAttributes;
    Header * newHeader;
    for (unsigned int i = 0; i < columns.size(); i++) {
        newAttributes.push_back(header->getAttributes().at(columns.at(i)));
    }
    newHeader = new Header(newAttributes);
    Relation projectedRelation(name, newHeader);
    for (auto thisTuple : domain) {
        vector<string> newColumns;
        for (unsigned int i = 0; i < columns.size(); i++) {
            newColumns.push_back(thisTuple.toString(columns.at(i)));
        }
        Tuple newTuple(newColumns);
        projectedRelation.addTuple(newTuple);
    }
    return projectedRelation;
}

bool Relation::isEmpty() {
    return domain.empty();
}