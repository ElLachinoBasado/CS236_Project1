//
// Created by Helaman on 12/7/2021.
//

#include "DGraph.h"

DGraph::DGraph(DatalogProgram datalog) {
    adjList = createAdjacencyList(datalog); //creates adjacency list
    reverseAdjList = createReverseAdjacencyList();
    reversePostOrder = createReversePostOrder();
}

vector<set<int>> DGraph::createAdjacencyList(DatalogProgram datalog) {
    vector<Rule> allRules = datalog.getRules();
    vector<set<int>> adjacencyList;

    for (int row = 0; row < allRules.size(); row++) {
        set<int> newRow;
        vector<Predicate> currentRulePredicates = allRules.at(row).getPredicateList(); //retrieves the current rule's predicates
        for (Predicate currentPredicate : currentRulePredicates) {
            for (int i = 0; i < allRules.size(); i++) {
                if (currentPredicate.getName() == allRules.at(i).getHeadPredicate()->getName()) {
                    newRow.insert(i);
                }
            }
        }
        adjacencyList.push_back(newRow);
    }

    return adjacencyList;
}

vector<set<int>> DGraph::createReverseAdjacencyList() {
    vector<set<int>> reverseAdjacencyList;
    for (int row = 0; row < adjList.size(); row++) { // initializes set of empty rows
        set<int> newRow;
        reverseAdjacencyList.push_back(newRow);
    }

    for (int currentNode = 0; currentNode < adjList.size(); currentNode++) {
        for (int i : adjList.at(currentNode)) {
            reverseAdjacencyList.at(i).insert(currentNode);
        }
    }

    return reverseAdjacencyList;
}

vector<int> DGraph::createReversePostOrder() {
    vector<vector<int>> forest = dfsForest();

    vector<int> postOrder = processForest(forest);
    return postOrder;
}

vector<vector<int>> DGraph::dfsForest() {
    vector<set<int>> copyList = reverseAdjList;
    vector<int> nodes;
    for (int i = 0; i < reverseAdjList.size(); i++) { // populates nodes to have R0...RN, where N is the # of nodes
        nodes.push_back(i);
    }

    vector<vector<int>> dfsForest;
    while (!nodes.empty()) {
        vector<int> tree = createTree(nodes,copyList);
        dfsForest.push_back(tree);
    }

    return dfsForest;
}

vector<int> DGraph::createTree(vector<int> & nodes, vector<set<int>> & copyList) {
    vector<int> tree;
    int nodeToAdd = nodes.front();
    tree.push_back(nodeToAdd);
    nodes.erase(nodes.begin());

    while (pathExists(nodeToAdd,nodes,copyList)) {
        tree.push_back(nodeToAdd);
    }

    return tree;
}

bool DGraph::pathExists(int & nodeToCheck, vector<int> & nodesLeft, vector<set<int>> & copyList) {
    set<int> terminalsToCheck = copyList.at(nodeToCheck);

    for (int currTerminal : terminalsToCheck) {
        for (int node = 0; node < nodesLeft.size(); node++) {
            if (currTerminal == nodesLeft.at(node)) {
                nodeToCheck = currTerminal;
                nodesLeft.erase(nodesLeft.begin() + node);
                return true;
            }
        }
    }

    return false;
}

vector<int> DGraph::processForest(vector<vector<int>> forest) {
    vector<int> postOrder;

    for (int i = 0; i < forest.size(); i++) {
        for (int j = forest.at(i).size() - 1; j >= 0; j--) {
            postOrder.push_back(forest.at(i).at(j));
        }
    }

    return postOrder;
}