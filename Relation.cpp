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
    for (auto thisTuple : domain) {
        for (int i = 0; i < headerValues.size(); i++) {
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
