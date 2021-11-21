//
// Created by Helaman on 10/25/2021.
//

#include "Relation.h"


Relation::Relation(string theName, Header* theHeader) {
    name = theName;
    header = theHeader;
}

string Relation::getName() {
    return name;
}

set<Tuple> Relation::getDomain() {
    return domain;
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
    //newString = newString + "(" + to_string(domain.size()) + ")" + "\n";
    newString = newString + "\n";
    for (auto thisTuple : domain) {
        for (unsigned int i = 0; i < headerValues.size(); i++) {
            if (i == 0) newString += " ";
            newString += " ";
            newString += headerValues.at(i);
            newString += "=";
            newString += thisTuple.toString(i);
            if (i != headerValues.size() - 1) {
                newString += ",";
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

Header * Relation::combineHeaders(Header a, Header b, map <int,int> &joinMap) {
    vector<string> newAttributes = a.getAttributes();
    int i = 0;
    for (string currBAttribute : b.getAttributes()) {
        int j = 0;
        bool addAttribute = true;
        for (string currAAttribute : a.getAttributes()) {
            if (currAAttribute == currBAttribute) {
                addAttribute = false;
                joinMap.emplace(j,i);
            }
            j++;
        }
        i++;
        if (addAttribute) newAttributes.push_back(currBAttribute);
    }
    Header * newHeader = new Header(newAttributes);
    return newHeader;
}
bool Relation::isJoinable(Tuple & t, Tuple & u, map <int,int> & joinMap) {
    for (auto & i : joinMap) {
        if (t.getValue(i.first) != u.getValue(i.second)) return false;
    }
    return true;
}

Relation Relation::join(Relation secondRelation, string ruleName) {
    map <int,int> joinMap;
    Header * newHeader = combineHeaders(* header, * secondRelation.getHeader(), joinMap);
    Relation newRelation(ruleName, newHeader);

    for (Tuple t : domain) {
        for (Tuple u : secondRelation.domain) {
            if (isJoinable(t,u,joinMap)) {
                newRelation.addTuple(tupleJoin(t,u,joinMap));
            }
        }
    }
    return newRelation;
}

Tuple Relation::tupleJoin(Tuple & t, Tuple & u, map <int,int> & joinMap) {
    vector<string> values = t.getValues();
    for (string toCheckU : u.getValues()) {
        bool add = true;
        for (string toCheckT : t.getValues()) {
            if (toCheckU == toCheckT) add = false;
        }
        if (add) values.push_back(toCheckU);
    }
    Tuple newTuple(values);
    return newTuple;
}

Relation::Relation(string theName, Header theHeader) {
    header = &theHeader;
    name = theName;
}

void Relation::setHeader(Header toSet) {
    header = &toSet;
}

Relation Relation::unite(Relation otherRelation, string & output) {
    for (Tuple currTuple: otherRelation.getDomain()) {
        if (domain.insert(currTuple).second) {
            output += " ";
            for (unsigned int i = 0; i < header->getAttributes().size(); i++) {
                output += " ";
                output += header->getAttributes().at(i);
                output += "=";
                output += currTuple.toString(i);
                if (i != header->getAttributes().size() - 1) {
                    output += ",";
                } else {
                    output += "\n";
                }
            }
        }
    }
    return *this;
}

Relation::Relation(string theName, Header* theHeader, set<Tuple> newDomain) {
   name = theName;
   header = theHeader;
   domain = newDomain;
}

void Relation::setName(string newName) {
    name = newName;
}