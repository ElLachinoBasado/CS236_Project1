//
// Created by Helaman on 12/7/2021.
//

#include "DGraph.h"

DGraph::DGraph(DatalogProgram datalog) {
    adjList = createAdjacencyList(datalog); //creates adjacency list
    reverseAdjList = createReverseAdjacencyList();
    reversePostOrder = createReversePostOrder();
    finalSCCList = generateSCCList();
    printDGraph();
}

vector<set<int>> DGraph::createAdjacencyList(DatalogProgram datalog) {
    vector<Rule> allRules = datalog.getRules();
    vector<set<int>> adjacencyList;

    for (unsigned int row = 0; row < allRules.size(); row++) {
        set<int> newRow;
        vector<Predicate> currentRulePredicates = allRules.at(row).getPredicateList(); //retrieves the current rule's predicates
        for (Predicate currentPredicate : currentRulePredicates) {
            for (unsigned int i = 0; i < allRules.size(); i++) {
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
    for (unsigned int row = 0; row < adjList.size(); row++) { // initializes set of empty rows
        set<int> newRow;
        reverseAdjacencyList.push_back(newRow);
    }

    for (unsigned int currentNode = 0; currentNode < adjList.size(); currentNode++) {
        for (int i : adjList.at(currentNode)) {
            reverseAdjacencyList.at(i).insert(currentNode);
        }
    }

    return reverseAdjacencyList;
}

vector<int> DGraph::createReversePostOrder() {
    vector<int> nodeOrder;
    set<int> nodesVisited;
    for (unsigned int i = 0; i < reverseAdjList.size(); i++) { // populates nodes to have R0...RN, where N is the # of nodes
        nodeOrder.push_back(i);
    }
    vector<set<int>> copyList = reverseAdjList;
    vector<int> postOrder;

    while (nodesVisited.size() < reverseAdjList.size()) {
        processNodes(nodeOrder,nodesVisited,copyList,postOrder);
    }

    return postOrder;
}

void DGraph::processNodes(vector<int> & nodeOrder, set<int> & nodesVisited, vector<set<int>> & copyList, vector<int> & postOrder) {
    int frontNode = nextNode(nodeOrder,nodesVisited);
    recursion(frontNode,nodesVisited,copyList,postOrder);
}

void DGraph::recursion(int node, set<int> & nodesVisited, vector<set<int>> & copyList, vector<int> & postOrder) {
    clearNodeFromSet(node,copyList);
    while (!copyList.at(node).empty()) {
        recursion(*copyList.at(node).begin(),nodesVisited,copyList,postOrder);
    }
    nodesVisited.emplace(node);
    postOrder.push_back(node);
}

int DGraph::nextNode(vector<int> nodeOrder, set<int> & nodesVisited) {
    int nodeToUse;
    bool found = false;
    int i = 0;
    while (!found) {
        if (nodesVisited.count(nodeOrder.at(i)) == 0) {
            found = true;
            nodeToUse = nodeOrder.at(i);
        } else {
            i++;
        }
    }
    nodesVisited.emplace(nodeToUse);
    return nodeToUse;
}



/**
 *
 */

/** vector<vector<int>> DGraph::dfsForest() {
    vector<set<int>> copyList = reverseAdjList;
    vector<int> nodes;
    for (unsigned int i = 0; i < reverseAdjList.size(); i++) { // populates nodes to have R0...RN, where N is the # of nodes
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
        for (unsigned int node = 0; node < nodesLeft.size(); node++) {
            if (currTerminal == nodesLeft.at(node)) {
                nodeToCheck = currTerminal;
                nodesLeft.erase(nodesLeft.begin() + node);
                return true;
            }
        }
    }

    return false;
}
**/
/** vector<int> DGraph::processForest(vector<vector<int>> forest) {
    vector<int> postOrder;

    //for (unsigned int i = 0; i < forest.size(); i++) {
    for (vector<int> currentVector : forest) {
        for (unsigned int j = currentVector.size() - 1; j != static_cast<unsigned>(-1); j--) {
            postOrder.push_back(currentVector.at(j));
        }
    }

    return postOrder;
} **/

vector<set<int>>  DGraph::generateSCCList() {
    /**    vector<int> nodes;
    for (unsigned int i = reversePostOrder.size() - 1; i != static_cast<unsigned>(-1); i--) {
        nodes.push_back(reversePostOrder.at(i));
    }

    vector<vector<int>> sccOrder;
    while (!nodes.empty()) {
        vector<int> newScc = sccCreate(nodes);
        sccOrder.push_back(newScc);
    }

    return sccOrder;
    **/

    vector<int> nodeOrder;
    for (unsigned int i = reversePostOrder.size() - 1; i != static_cast<unsigned>(-1); i--) {
        nodeOrder.push_back(reversePostOrder.at(i));
    }
    vector<set<int>> sccOrder;
    vector<set<int>> copyList = adjList;

    while (nodeOrder.size() > 0) {
        fillSCCOrder(sccOrder, nodeOrder, copyList);
    }

    return sccOrder;
}

void DGraph::fillSCCOrder(vector<set<int>> & sccOrder, vector<int> & nodeOrder, vector<set<int>> & copyList) {
    int frontNode = 0;
    set<int> currentSCC;
    sccRecursion(frontNode,currentSCC,nodeOrder,copyList);
    sccOrder.push_back(currentSCC);
}

void DGraph::sccRecursion(int node,set<int> & currentSCC, vector<int> & nodeOrder, vector<set<int>> & copyList) {
    int nodeValue = nodeOrder.at(node);
    clearNodeFromSet(nodeValue,copyList);
    currentSCC.emplace(nodeValue);
    nodeOrder.erase(nodeOrder.begin()+node);
    while (!copyList.at(nodeValue).empty()) {
        int nextNodeToPass = *copyList.at(nodeValue).begin();
        nextNodeToPass = findPosition(nodeOrder,nextNodeToPass);
        sccRecursion(nextNodeToPass,currentSCC,nodeOrder,copyList);
    }

}

int DGraph::findPosition(vector<int> nodeOrder,int nextNodeToPass) {
    int position;
    for (unsigned int i = 0; i < nodeOrder.size(); i++) {
        if (nodeOrder.at(i) == nextNodeToPass) {
            position = i;
        }
    }
    return position;
}

void DGraph::clearNodeFromSet(int node, vector<set<int>> & copyList) {
    for (unsigned int i = 0; i < copyList.size(); i++) {
        copyList.at(i).erase(node);
    }
}
/**
vector<int> DGraph::sccCreate(vector<int> & postOrder) {
    vector <int> sccValues;

    sccValues.push_back(postOrder.front());
    postOrder.erase(postOrder.begin());


    set<int> tempSet = adjList.at(sccValues.front());
    for (int i : tempSet) {
        for (unsigned int j = 0; j < postOrder.size(); j++) {
            if (i == postOrder.at(j)) {
                sccValues.push_back(postOrder.at(j));
                postOrder.erase(postOrder.begin() + j);
            }
        }
    }


    return sccValues;
} **/

/**vector<set<int>> DGraph::generateFinalSCCList() {
    vector<set<int>> finalList;

    for (vector<int> currentVector : sccList) {
        set<int> tempSet;
        for (int i : currentVector) {
            tempSet.emplace(i);
        }
        finalList.push_back(tempSet);
    }

    return finalList;
} **/

void DGraph::printDGraph() {
    string output = "Dependency Graph\n";
    int i = 0;
    for (set<int> currRule : adjList) {
        output += "R" + to_string(i) + ":";
        unsigned int j = 0;
        for (int currNode : currRule) {
            j++;
            output += "R" + to_string(currNode);
            if (j != currRule.size()) output += ",";
        }
        output += "\n";
        i++;
    }
    cout << output << endl;
}

/**
vector<vector<int>> DGraph::getSCC() {
    return sccList;
} **/

vector<set<int>> DGraph::getFinalSCC() {
    return finalSCCList;
}