//
// Created by Helaman on 9/29/2021.
//

#include "DatalogProgram.h"
DatalogProgram::DatalogProgram() {
    database = new Database();
}

void DatalogProgram::addSchemes(Predicate* &toAdd) {
    schemes.push_back(toAdd);
}

void DatalogProgram::addFacts(Predicate* &toAdd) {
    facts.push_back(toAdd);
}

void DatalogProgram::addRules(Rule* &toAdd) {
    rules.push_back(toAdd);
}

void DatalogProgram::addQueries(Predicate* &toAdd) {
    queries.push_back(toAdd);
}

void DatalogProgram::addDomain(Parameter* &toAdd) {
    domain.insert(toAdd->getValue());
}

void DatalogProgram::print() {
    cout << "Success!" << endl;
    cout << "Schemes(" << to_string(schemes.size()) << "):" << endl;
    for (unsigned int i = 0; i < schemes.size(); i++) {
        cout << "  " << schemes.at(i)->toString() << endl;
    }
    cout << "Facts(" << to_string(facts.size()) << "):" << endl;
    for (unsigned int i = 0; i < facts.size(); i++) {
        cout << "  "  << facts.at(i)->toString() << "." << endl;
    }
    cout << "Rules(" << to_string(rules.size()) << "):" << endl;
    for (unsigned int i = 0; i < rules.size(); i++) {
        cout << "  "  << rules.at(i)->toString() << endl;
    }
    cout << "Queries(" << to_string(queries.size()) << "):" << endl;
    for (unsigned int i = 0; i < queries.size(); i++) {
        cout << "  "  << queries.at(i)->toString() << "?" << endl;
    }
    cout << "Domain(" << to_string(domain.size()) << "):" << endl;
    for (string s : domain) {
        cout << "  " << s << endl;
    }
}

Database * DatalogProgram::getDatabase() {
    return database;
}

void DatalogProgram::createDatabase() {

    for (unsigned int i = 0; i < schemes.size(); i++) {
        //get relation name
        string relationName = schemes.at(i)->getName();

        //get header
        vector<Parameter*> parameterHeaderList = schemes.at(i)->getParameterPointerList();
        vector<string> stringHeaderList;
        for (unsigned int j = 0; j < parameterHeaderList.size(); j++) {
            stringHeaderList.push_back(parameterHeaderList.at(j)->getValue());
        }
        Header * relationHeader = new Header(stringHeaderList);

        //construct relation
        Relation * newRelation = new Relation(relationName, relationHeader);

        //get tuples
        for (unsigned int j = 0; j < facts.size(); j++) {
            if (facts.at(j)->getName() == relationName) {
                vector<Parameter*> parameterTupleList = facts.at(j)->getParameterPointerList();
                vector<string> stringTupleList;
                for (unsigned int k = 0; k < parameterTupleList.size(); k++) {
                    stringTupleList.push_back(parameterTupleList.at(k)->getValue());
                }
                Tuple newTuple = Tuple(stringTupleList);
                newRelation->addTuple(newTuple);
            }
        }
        database->addRelation(relationName, newRelation);
    }
}

vector<Predicate> DatalogProgram::getQueries() {
    vector<Predicate> queryCopy;
    for (unsigned int i = 0; i < queries.size(); i++) {
        queryCopy.push_back(*queries.at(i));
    }
    return queryCopy;
}

vector<Rule> DatalogProgram::getRules() {
    vector<Rule> ruleCopy;
    for (unsigned int i = 0; i < rules.size(); i++) {
        ruleCopy.push_back(*rules.at(i));
    }
    return ruleCopy;
}

Predicate DatalogProgram::getScheme(string name) {
    for (Predicate* currPredicate : schemes) {
        if (currPredicate->getName() == name) {
            return *currPredicate;
        }
    }
    Predicate nullPredicate;
    return nullPredicate;
}