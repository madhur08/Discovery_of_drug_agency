#include <Graph.h>
#include <cmath>
#include <iostream>

int Graph::toIndex(int i, int k)
{
    return (k * V + i + 1);
}
void Graph::printClauses(Clause clause, ofstream &fout)
{
    switch (clause)
    {
    case NO_DIRECT_EDGE:
        for (int i = 0, z = V * K * K + 1; i < V; ++i)
            for (int j = i + 1; j < V; ++j)
                if (adjacencyMatrix[i][j] == 1)
                {
                    for (int k = 0; k < K; ++k)
                    {
                        fout << toIndex(i, k) << " -" << z + k << " 0\n";
                        fout << toIndex(j, k) << " -" << z + k << " 0\n";
                    }
                    z += K;
                }
        for (int i = V * K * K + 1; i < V * K * K + K * E; i += K, fout << "0\n")
            for (int k = 0; k < K; ++k)
                fout << i + k << " ";
        break;

    case SUBGRAPH_FULLY_CONNECTED:
        for (int k = 0; k < K; ++k)
            for (int i = 0; i < V; ++i)
                for (int j = i + 1; j < V; ++j)
                    if (adjacencyMatrix[i][j] == 0)
                        fout << "-" << toIndex(i, k) << " -" << toIndex(j, k) << " 0\n";
        break;
    case SUBGRAPH_NOT_SUBSET:
        for (int k = 0, z = V * K + 1; k < K; ++k)
            for (int l = k + 1; l < K; ++l, z += (2 * V))
                for (int i = 0; i < V; ++i)
                {
                    fout << "-" << toIndex(i, k) << " -" << z + i << " 0\n";
                    fout << toIndex(i, l) << " -" << z + i << " 0\n";
                    fout << "-" << toIndex(i, l) << " -" << z + i + V << " 0\n";
                    fout << toIndex(i, k) << " -" << z + i + V << " 0\n";
                }
        for (int i = V * K + 1; i < V * K * K; i += V, fout << "0\n")
            for (int j = 0; j < V; ++j)
                fout << i + j << " ";
        break;
    case NO_VERTEX_UNUSED:
        for (int i = 0; i < V; ++i, fout << "0\n")
            for (int k = 0; k < K; ++k)
                fout << toIndex(i, k) << " ";
        break;
    }
}
Graph::Graph(string file_name, bool make_graph)
{
    ifstream fin(file_name.c_str(), fstream::in);
    if (fin.is_open())
    {
        fin >> V >> E >> K;
        number_of_clauses = K * K * (2 * V + 1) + K * (0.5 * V * V - 2.5 * V - 1 + E) + V + E;
        number_of_variables = V * K * K + K * E;
        if (make_graph)
        {
            adjacencyMatrix.resize(V);
            for (auto &v : adjacencyMatrix)
                v.resize(V);
            int a, b;
            while (fin >> a >> b)
            {
                adjacencyMatrix[a - 1][b - 1] = 1;
                adjacencyMatrix[b - 1][a - 1] = 1;
            }
        }
    }
    else
        cerr << "File does not exit\n";
    fin.close();
}
void Graph::convertToCNF(string file_name)
{
    ofstream fout(file_name.c_str(), fstream::out);
    fout << "p cnf " << number_of_variables << " " << number_of_clauses << endl;
    printClauses(NO_DIRECT_EDGE, fout);
    printClauses(SUBGRAPH_FULLY_CONNECTED, fout);
    printClauses(SUBGRAPH_NOT_SUBSET, fout);
    printClauses(NO_VERTEX_UNUSED, fout);
    fout.close();
}
void Graph::convertToSubgraphs(string sat_file, string subgraphs_file)
{
    ofstream fout(subgraphs_file.c_str(), fstream::out);
    ifstream fin(sat_file.c_str(), fstream::in);
    if (fin.is_open())
    {
        string RESULT;
        fin >> RESULT;
        if (RESULT == "SAT")
        {
            int a;
            vector<vector<int>> subgraphs;
            subgraphs.resize(K);
            while (fin >> a && std::abs(a) <= V * K)
                if (a > 0)
                    subgraphs[(a - 1) / V].push_back((a - 1) % V);
            for (int i = 0; i < K; ++i)
            {
                fout << "#" << (i + 1) << " " << subgraphs[i].size() << endl;
                fout << (subgraphs[i][0] + 1);
                for (size_t v = 1; v < subgraphs[i].size(); ++v)
                    fout << " " << (subgraphs[i][v] + 1);
                fout << endl;
            }
        }
        else
            fout << 0 << endl;
        fin.close();
    }
    else
        cerr << "File does not exit\n";
    fout.close();
}