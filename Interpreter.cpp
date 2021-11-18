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
    for (Rule currRule : datalogProgram.getRules()) {
        vector<Relation> intermediateRelations;
        for (Predicate currPredicate: currRule.getPredicateList()) {
            Relation tempRelation = evaluatePredicate(currPredicate);
            intermediateRelations.push_back(tempRelation);
            //cout << tempRelation.toString() << endl;
        }

        Relation newRelation = intermediateRelations.front();

        while (intermediateRelations.size() > 1) {
            Relation firstRelation = intermediateRelations.front(); //gets first element
            Relation secondRelation = intermediateRelations.at(1); //gets second element
            newRelation = firstRelation.join(secondRelation, currRule.getHeadPredicate().getName());

            intermediateRelations.at(0) = newRelation;
            intermediateRelations.erase(intermediateRelations.begin()+1); // removes second element
        }
        cout << newRelation.toString() << endl;
    }
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
    for (Predicate currQuery : datalogProgram.getQueries()) {
        cout << currQuery.toString() << "?";
        Relation newRelation = evaluatePredicate(currQuery);
        if (newRelation.isEmpty()) {
            cout << " No" << endl;
        } else {
            cout << " Yes" << newRelation.toString();
        }
    }
}