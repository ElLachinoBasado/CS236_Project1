//
// Created by Helaman on 9/29/2021.
//

#include "DatalogProgram.h"
DatalogProgram::DatalogProgram() {

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
        cout << "  "  << queries.at(i)->toString() << endl;
    }
    cout << "Domain(" << to_string(domain.size()) << "):" << endl;
    for (string s : domain) {
        cout << "  " << s << endl;
    }
}