#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <fstream>
#include <string>
using namespace std;

enum Clause
{
    NO_DIRECT_EDGE,
    NO_SUBGRAPH_EMPTY,
    SUBGRAPH_FULLY_CONNECTED,
    SUBGRAPH_NOT_SUBSET,
    NO_VERTEX_UNUSED
};

class Graph
{
  private:
    int V, E, K;
    int number_of_clauses, number_of_variables;
    vector<vector<bool>> adjacencyMatrix;
    void printClauses(Clause, ofstream &);
    int toIndex(int, int);

  public:
    Graph(string, bool);
    void convertToCNF(string);
    void convertToSubgraphs(string,string);
};

#endif