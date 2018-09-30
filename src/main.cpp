#include <iostream>
#include <cstdlib>
#include <Graph.h>
using namespace std;

int main(int argc, char** argv){
    if (argc < 2)
    {
        cout << "Missing arguments\n";
        cout << "Correct format : ./code <graph_filename> {1 | 2}";
        exit(0);
    }
    else if(atoi(argv[1]) == 1){
        Graph graph(string(argv[0])+".graph",1);
        graph.convertToCNF(string(argv[0])+".satinput");
    }
    else if(atoi(argv[1]) == 1){
        Graph graph(string(argv[0])+".graph",0);
        graph.convertToSubgraphs(string(argv[0])+".satoutput", string(argv[0])+".subgraphs");
    }

}