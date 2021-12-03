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
    cout << "\nQuery Evaluation\n";
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

    int numberOfIterations = 0;
    bool keepRepeating = true;
    string output = "Rule Evaluation\n";
    do {
        keepRepeating = false;
        for (Rule currentRule : datalogProgram.getRules()) {
            output += currentRule.toString() + "\n";
            if (evaluateRule(currentRule,output)) keepRepeating = true;
        }
        numberOfIterations++;
    } while (keepRepeating);
    cout << output << endl << "Schemes populated after " << numberOfIterations << " passes through the Rules." << endl;
}

bool Interpreter::evaluateRule(Rule evaluatedRule, string & output) {
    vector<Relation> relations = getIntermediateRelations(evaluatedRule); //gets intermediate relations

    Relation combinedRelation = joinRelations(relations, evaluatedRule.getName());

    vector<int> valuesToKeep;
    vector<string> vectorRename;
    for (unsigned int i = 0; i < evaluatedRule.getHeadPredicate()->getParameterList().size(); i++) {
        for (unsigned int j = 0; j < combinedRelation.getHeader()->getAttributes().size(); j++) {
            if (evaluatedRule.getHeadPredicate()->getParameterList().at(i).getValue() == combinedRelation.getHeader()->getAttributes().at(j)) {
                valuesToKeep.push_back(j);
                vectorRename.push_back(evaluatedRule.getHeadPredicate()->getParameterList().at(i).getValue());
            }
        }
    }

    combinedRelation = combinedRelation.project(valuesToKeep);
    combinedRelation = combinedRelation.rename(vectorRename);
    bool tuplesAdded = false;
    Relation newRelation = database.getRelation(evaluatedRule.getHeadPredicate()->getName());
    newRelation = combinedRelation.unite(newRelation,tuplesAdded, output);
    Relation * finalRelation = new Relation(newRelation.getName(),newRelation.getHeader());
    finalRelation->setDomain(newRelation.getDomain());
    database.updateRelation(newRelation.getName(), finalRelation);
    return tuplesAdded;
}

Relation Interpreter::joinRelations(vector<Relation> relations, string ruleName) {
    Relation combinedRelation = relations.at(0);
    if (relations.size() > 1) {
        for (unsigned int i = 1; i < relations.size(); i++) {
            combinedRelation = combinedRelation.join(relations.at(i),ruleName);
        }
    }
    return combinedRelation;
}

/**
 *
 * @param allRules - every rule found in the datalog program
 * @return all of the intermediate relations, as described in step 1 of the evaluating rules write up
 */
vector<Relation> Interpreter::getIntermediateRelations(Rule ruleToCheck) {
    vector<Relation> intermediateRelations;
    for (Predicate currPredicate : ruleToCheck.getPredicateList()) {
        intermediateRelations.push_back(evaluatePredicate(currPredicate));
    }

    return intermediateRelations;
}