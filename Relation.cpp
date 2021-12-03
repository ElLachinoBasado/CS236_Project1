//
// Created by Helaman on 10/25/2021.
//

#include "Relation.h"

Relation::Relation(string theName, Header* theHeader) {
    name = theName;
    header = theHeader;
}

Relation::Relation() {

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

bool Relation::isJoinable(Tuple t, Tuple u, map <int,int> joinMap) {
    for (auto i : joinMap) {
        if (t.getValue(i.first) != u.getValue(i.second)) return false;
    }
    return true;
}

Relation Relation::join(Relation b, string ruleName){ //, Header * combinedHeaders, vector <pair<int,int>> joinVector) {
    Header * newHeader = new Header(header->getAttributes());
    map <int,int> joinMap;
    for (unsigned int i = 0; i < (b.getHeader()->getAttributes().size()); i++) {
        bool exists = false;
        for (unsigned int j = 0; j < newHeader->getAttributes().size(); j++) {
            if (b.getHeader()->getAttributes().at(i) == newHeader->getAttributes().at(j)) {
                exists = true;
                joinMap.emplace(j,i);
                break;
            }
        }
        if (!exists) newHeader->addAttribute(b.getHeader()->getAttributes().at(i));
    }

    Relation newRelation(ruleName,newHeader);
    for (Tuple t : domain) {
        for (Tuple u : b.getDomain()) {
            if (isJoinable(t,u,joinMap)) newRelation.addTuple(combineTuples(t,u,joinMap));
        }
    }
    return newRelation;
}

string Relation::getName() {
    return name;
}

set<Tuple> Relation::getDomain() {
    return domain;
}

void Relation::setHeader(Header * newHeader) {
    header = newHeader;
}

Tuple Relation::combineTuples(Tuple t, Tuple u, map<int,int> joinMap) {
    Tuple joinedTuple(t.getValues());
    vector<int> ignoredValues;
    for (auto i : joinMap) ignoredValues.push_back(i.second);

    bool shouldSkip;
    for (unsigned int i = 0; i < u.getValues().size(); i++) {
        shouldSkip = false;
        for (unsigned int j = 0; j < ignoredValues.size(); j++) if (i == ignoredValues.at(j)) shouldSkip = true;
        if (!shouldSkip) joinedTuple.addValue(u.getValue(i));
    }
    return joinedTuple;
}

Relation Relation::unite(Relation r, bool & addTuple, string & output) {
    for (Tuple t : domain) {
        if (r.domain.insert(t).second) {
            output += convertTuple(t) + "\n";
            addTuple = true;
        }
    }
    return r;
}

string Relation::convertTuple(Tuple t) {
    string result = "";
    for (unsigned int i = 0; i < header->getAttributes().size()-1; i++) {
        result += header->getAttributes().at(i) + "=" + t.getValue(i) + ", ";
    }
    result += header->getAttributes().at(header->getAttributes().size()-1) + "=" + t.getValue(header->getAttributes().size()-1);
    return result;
}

void Relation::setDomain(set<Tuple> newDomain) {
    domain = newDomain;
}