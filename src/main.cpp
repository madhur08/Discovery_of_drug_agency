#include <iostream>
#include <cstdlib>
#include <Graph.h>
using namespace std;

int main(int argc, char** argv){
    if (argc < 3)
    {
        cout << "Missing arguments\n";
        cout << "Correct format : ./code <graph_filename> {1 | 2}";
    }
    else if(atoi(argv[2]) == 1){
        std::cerr<<"Building SAT input\n";
        Graph graph(string(argv[1])+".graph",1);
        graph.convertToCNF(string(argv[1])+".satinput");
    }
    else if(atoi(argv[2]) == 2){
        std::cerr<<"Building subgraphs\n";
        Graph graph(string(argv[1])+".graph",0);
        graph.convertToSubgraphs(string(argv[1])+".satoutput", string(argv[1])+".subgraphs");
    }

}