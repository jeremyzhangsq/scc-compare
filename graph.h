//
// Created by Jeremy Shiqi Zhang on 2019-08-31.
//
#include "lib.h"
#ifndef SCC_GRAPH_H
#define SCC_GRAPH_H
using namespace std;



class Graph {
public:
    unsigned int vnums, enums;
    vector<Vint> neighbour;
    vector<unordered_set<int>> uneighbour;
    vector<Vint> last_neighbour;
    Vbool visit;
    Vint visit_mark;
    Vint vertices;
    Vint q;
    Graph() = default;
    Graph(unsigned int v, unsigned int e);
    void addEdge(int vi, int vj);
    void adduEdge(int vi, int vj);
    void cleaning();
};

#endif //SCC_GRAPH_H
