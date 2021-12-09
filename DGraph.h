//
// Created by Helaman on 12/7/2021.
//

#ifndef LEXICALANALYZER_DGRAPH_H
#define LEXICALANALYZER_DGRAPH_H
#include <vector>
#include <set>
#include "Rule.h"
#include "DatalogProgram.h"

using namespace std;
class DGraph {
private:
    vector<set<int>> adjList;
    vector<set<int>> reverseAdjList;
    vector<int> reversePostOrder;
    vector<vector<int>> sccList;
    vector<set<int>> finalSCCList;
public:
    DGraph(DatalogProgram datalog);

    vector<set<int>> createAdjacencyList(DatalogProgram datalog);

    vector<set<int>> createReverseAdjacencyList();

    vector<int> createReversePostOrder();
    void processNodes(vector<int> & nodeOrder, set<int> & nodesVisited, vector<set<int>> & copyList, vector<int> & postOrder);
    void clearNodeFromSet(int node, vector<set<int>> & copyList);
    int nextNode(vector<int> nodeOrder, set<int> & nodesVisited);
    void recursion(int node, set<int> & nodesVisited, vector<set<int>> & copyList, vector<int> & postOrder);
    //vector<vector<int>> dfsForest();
    //vector<int> createTree(vector<int> & nodes, vector<set<int>> & copyList);
    //bool pathExists(int & nodeToCheck, vector<int> & nodesLeft, vector<set<int>> & copyList);
    //vector<int> processForest(vector<vector<int>> forest);

    vector<vector<int>>  generateSCCList();
    vector<int> sccCreate(vector<int> & postOrder);
    vector<set<int>> generateFinalSCCList();

    void printDGraph();
    vector<vector<int>> getSCC();
    vector<set<int>> getFinalSCC();
};


#endif //LEXICALANALYZER_DGRAPH_H
