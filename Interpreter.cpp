//
// Created by Helaman on 10/27/2021.
//

#include "Interpreter.h"

Interpreter::Interpreter(DatalogProgram * dpReference) {
    datalogProgram = * dpReference;
    datalogProgram.createDatabase();
    database = *datalogProgram.getDatabase();
}

void Interpreter::evaluateAllRules() {
string output = "Rule Evaluation\n";
int numIterations = 0;
bool keepLooping = true;
do {
    for (Rule currRule : datalogProgram.getRules()) {
        vector<Relation> intermediateRelations;
        for (Predicate currPredicate: currRule.getPredicateList()) {
            Relation tempRelation = evaluatePredicate(currPredicate);
            intermediateRelations.push_back(tempRelation);
        }

        Relation newRelation = intermediateRelations.front();

        while (intermediateRelations.size() > 1) {
            Relation firstRelation = intermediateRelations.front(); //gets first element
            Relation secondRelation = intermediateRelations.at(1); //gets second element
            newRelation = firstRelation.join(secondRelation, currRule.getHeadPredicate().getName());

            intermediateRelations.at(0) = newRelation;
            intermediateRelations.erase(intermediateRelations.begin()+1); // removes second element
        }
        output += currRule.toString();
        output += "\n";
        //string currRuleName = intermediateRelations.front().getName();
        newRelation = evaluateRule(currRule,newRelation);
        newRelation = database.getRelation(currRule.getHeadPredicate().getName()).unite(newRelation,output);
        Relation * newRelationPointer = new Relation(newRelation.getName(), newRelation.getHeader(), newRelation.getDomain());
        keepLooping = database.updateRelation(currRule.getHeadPredicate().getName(), newRelationPointer);

        if (keepLooping == true) {
            numIterations++;
        }
        }
    } while (keepLooping);
    output = output + "\nSchemes populated after " + to_string(numIterations) +  " passes through the Rules.\n";
    cout << output;
}

Relation Interpreter::evaluateRule(Rule mainRule, Relation newRelation) {
    Predicate p = mainRule.getHeadPredicate();

    vector<Parameter> parameterList = p.getParameterList();
    vector<int> markedIndices;
    vector<string> seenValues;

    Predicate scheme = datalogProgram.getScheme(mainRule.getHeadPredicate().getName());

    for (unsigned int i = 0; i < parameterList.size(); i++) {
        vector<string> tempHeader = newRelation.getHeader()->getAttributes();
        seenValues.push_back(scheme.getParameterList().at(i).getValue());
        for (unsigned int j = 0; j < tempHeader.size(); j++) {
            if (parameterList.at(i).getValue() == tempHeader.at(j)) {
                markedIndices.push_back(j);
            }
        }
    }

    newRelation = newRelation.project(markedIndices);
    newRelation = newRelation.rename(seenValues);
    newRelation.setName(p.getName());
    return newRelation;
}

Relation Interpreter::evaluatePredicate(Predicate p) {
    //retrieves Relation
    string pName = p.getName();
    Relation retrievedRelation = database.getRelation(pName);

    //loop through every parameter
    vector<Parameter> parameterList = p.getParameterList();
    vector<int> markedIndices;
    vector<string> seenValues;
    for (unsigned int i = 0; i < parameterList.size(); i++) {
        if (parameterList.at(i).getConstant()) { // if it's constant
            retrievedRelation = retrievedRelation.select(i, parameterList.at(i).getValue());
        } else {
            bool isFound = false;
            for (unsigned int j = 0; j < seenValues.size(); j++) {
                if (parameterList.at(i).getValue() == seenValues.at(j)) {
                    retrievedRelation = retrievedRelation.select(i, j);
                    isFound = true;
                    break;
                }
            }
            if (!isFound) {
                markedIndices.push_back(i);
                seenValues.push_back(parameterList.at(i).getValue());
            }
        }
    }
    retrievedRelation = retrievedRelation.project(markedIndices);
    retrievedRelation = retrievedRelation.rename(seenValues);
    return retrievedRelation;
}

void Interpreter::evaluateAllQueries() {
    cout << endl << "Query Evaluation" << endl;
    for (Predicate currQuery : datalogProgram.getQueries()) {
        cout << currQuery.toString() << "?";
        Relation newRelation = evaluatePredicate(currQuery);
        if (newRelation.isEmpty()) {
            cout << " No" << endl;
        } else {
            cout << " Yes(" << to_string(newRelation.getDomain().size()) << ")" << newRelation.toString();
        }
    }
}