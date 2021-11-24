//
// Created by Helaman on 10/27/2021.
//

#include "Interpreter.h"

Interpreter::Interpreter(DatalogProgram * dpReference) {
    datalogProgram = * dpReference;
    datalogProgram.createDatabase();
    database = *datalogProgram.getDatabase();
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

void Interpreter::evaluateAllRules() {
    string output = "Rule Evaluation";

    bool databaseUpdated = true;
    do {
         vector<Rule> allRules = datalogProgram.getRules();    //1. retrieve rules from DatalogProgram
         vector<Relation> intermediateRelations = getIntermediateRelations (allRules); //2. iterate through them + 3. evaluate predicates on right-hand side of the rule todo - getIntermediateRelations()
         //4. If there are multiple relations, join them todo - create join function in relation
         // todo - create function for 5-6
         //5. Project columns that appear in the head predicate
         //6. Rename the relation to make it union-compatible
         //7. Unite the relation with the database
        databaseUpdated = false; //todo - end the while loop after the database stops updating
    } while (databaseUpdated);

    cout << output << endl;//print output
}

/**
 *
 * @param allRules - every rule found in the datalog program
 * @return all of the intermediate relations, as described in step 1 of the evaluating rules write up
 */
vector<Relation> Interpreter::getIntermediateRelations(vector<Rule> allRules) {
    vector<Relation> intermediateRelations;
    return intermediateRelations;
}