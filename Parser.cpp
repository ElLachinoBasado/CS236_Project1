//
// Created by Helaman on 9/29/2021.
//

#include "Parser.h"
#include <iostream>
using namespace std;
Parser::Parser(vector<Token*> input) {
    succeeded = false; //sets boolean
    i = 0;
    program = new DatalogProgram();
    for (unsigned int i = 0; i < input.size(); i++) { //clears comment tokens
        if (input.at(i)->getType() == "COMMENT") {
            input.erase(input.begin()+i);
        }
    }
    tokens = input;
}

void Parser::parse() {
    if (tokens.at(i)->getType() == "SCHEMES" && tokens.at(i+1)->getType() == "COLON") i += 2;
    else throw tokens.at(i);
    scheme();
    schemeList();

    if (tokens.at(i)->getType() == "FACTS" && tokens.at(i+1)->getType() == "COLON") i += 2;
    else throw tokens.at(i);
    factList();

    if (tokens.at(i)->getType() == "RULES" && tokens.at(i+1)->getType() == "COLON") i += 2;
    else throw tokens.at(i);
    ruleList();

    if (tokens.at(i)->getType() == "QUERIES" && tokens.at(i+1)->getType() == "COLON") i += 2;
    else throw tokens.at(i);
    query();
    queryList();

    if (tokens.at(i)->getType() == "EOF") i++;
    else throw tokens.at(i);

    program->print();
}

void Parser::schemeList() {
    if (tokens.at(i)->getType() == "ID") {
        scheme();
        schemeList();
    }
}

void Parser::factList() {
    if (tokens.at(i)->getType() == "ID") {
        fact();
        factList();
    }
}

void Parser::ruleList() {
    if (tokens.at(i)->getType() == "ID") {
        rule();
        ruleList();
    }
}

void Parser::queryList() {
    if (tokens.at(i)->getType() == "ID") {
        query();
        queryList();
    }
}

void Parser::scheme() {
    string name;
    vector<Parameter*> list;
    if (tokens.at(i)->getType() == "ID") {
        name = tokens.at(i)->getValue();
        i++;
    } else throw tokens.at(i);

    if (tokens.at(i)->getType() == "LEFT_PAREN") i++;
    else throw tokens.at(i);

    if (tokens.at(i)->getType() == "ID") {
        Parameter* newParameter = new Parameter(false, tokens.at(i)->getValue());
        list.push_back(newParameter);
        i++;
    } else throw tokens.at(i);

    idList(list);

    if (tokens.at(i)->getType() == "RIGHT_PAREN") i++;
    else throw tokens.at(i);

    Predicate* newPredicate = new Predicate(name,list);
    program->addSchemes(newPredicate);
}

void Parser::fact() {
    string name;
    vector<Parameter*> list;
    if (tokens.at(i)->getType() == "ID") {
        name = tokens.at(i)->getValue();
        i++;
    } else throw tokens.at(i);

    if (tokens.at(i)->getType() == "LEFT_PAREN") i++;
    else throw tokens.at(i);

    if (tokens.at(i)->getType() == "STRING") {
        Parameter* newParameter = new Parameter(false, tokens.at(i)->getValue());
        list.push_back(newParameter);
        program->addDomain(newParameter);
        i++;
    } else throw tokens.at(i);

    stringList(list);

    if (tokens.at(i)->getType() == "RIGHT_PAREN") i++;
    else throw tokens.at(i);

    if (tokens.at(i)->getType() == "PERIOD") i++;
    else throw tokens.at(i);

    Predicate* newPredicate = new Predicate(name,list);
    program->addFacts(newPredicate);
}

void Parser::rule() {
    vector<Predicate*> list;
    Predicate* newHeadPredicate = headPredicate();

    if (tokens.at(i)->getType() == "COLON_DASH") i++;
    else throw tokens.at(i);

    if (tokens.at(i)->getType() == "ID") {
        list.push_back(predicate());
        predicateList(list);
    } else throw tokens.at(i);

    if (tokens.at(i)->getType() == "PERIOD") i++;
    else throw tokens.at(i);

    Rule* newRule = new Rule(newHeadPredicate, list);
    program->addRules(newRule);
}

void Parser::query() {
    Predicate* newPredicate = predicate();
    if (tokens.at(i)->getType() == "Q_MARK") i++;
    else throw tokens.at(i);
    program->addQueries(newPredicate);
}

Predicate* Parser::headPredicate() {
    string headPredicateName;
    vector<Parameter*> list;
    if (tokens.at(i)->getType() == "ID") {
        headPredicateName = tokens.at(i)->getValue();
        i++;
    } else throw tokens.at(i);

    if (tokens.at(i)->getType() == "LEFT_PAREN") i++;
    else throw tokens.at(i);

    if (tokens.at(i)->getType() == "ID") {
        Parameter* newParameter = new Parameter(false, tokens.at(i)->getValue());
        list.push_back(newParameter);
        i++;
    } else throw tokens.at(i);

    idList(list);

    if (tokens.at(i)->getType() == "RIGHT_PAREN") i++;
    else throw tokens.at(i);

    Predicate* newPredicate = new Predicate(headPredicateName, list);
    return newPredicate;
}

Predicate* Parser::predicate() {
    string name;
    vector<Parameter*> list;
    if (tokens.at(i)->getType() == "ID") {
        name = tokens.at(i)->getValue();
        i++;
    } else throw tokens.at(i);

    if (tokens.at(i)->getType() == "LEFT_PAREN") i++;
    else throw tokens.at(i);

    list.push_back(parameter());
    parameterList(list);

    if (tokens.at(i)->getType() == "RIGHT_PAREN") i++;
    else throw tokens.at(i);
    return new Predicate(name, list);
}

void Parser::predicateList(vector<Predicate*> &list) {
    if (tokens.at(i)->getType() == "COMMA") {
        i++;
        list.push_back(predicate());
        predicateList(list);
    }
}

void Parser::parameterList(vector<Parameter*> &list) {
    if (tokens.at(i)->getType() == "COMMA") {
        i++;
        list.push_back(parameter());
        parameterList(list);
    }
}

void Parser::stringList(vector<Parameter*> &list) {
    if (tokens.at(i)->getType() == "COMMA") {
        i++;
        if (tokens.at(i)->getType() == "STRING") {
            Parameter* newParameter = new Parameter(false, tokens.at(i)->getValue());
            list.push_back(newParameter);
            program->addDomain(newParameter);
            i++;
            stringList(list);
        } else throw tokens.at(i);
    }
}

void Parser::idList(vector<Parameter*> &list) {
    if (tokens.at(i)->getType() == "COMMA") {
        i++;
        if (tokens.at(i)->getType() == "ID") {
            Parameter* newParameter = new Parameter(false, tokens.at(i)->getValue());
            list.push_back(newParameter);
            i++;
            idList(list);
        } else throw tokens.at(i);
    }
}

Parameter* Parser::parameter() {
    if (tokens.at(i)->getType() == "ID") {
        Parameter* newParameter = new Parameter(false,tokens.at(i)->getValue());
        i++;
        return newParameter;
    } else if (tokens.at(i)->getType() == "STRING") {
        Parameter* newParameter = new Parameter(true,tokens.at(i)->getValue());
        i++;
        return newParameter;
    } else throw tokens.at(i);
}

