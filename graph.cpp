//
// Created by Jeremy Shiqi Zhang on 2019-08-31.
//

#include "lib.h"

Graph::Graph(unsigned int v, unsigned int e) {
    vnums = v;
    enums = e;
    if(e == 0)
        uneighbour.resize(v);
    else
    {
        neighbour.resize(v);
        //    last_neighbour.resize(v);
        visit.resize(v, false);
        visit_mark.resize(v, 0);
        q.resize(v);
    }
}

void Graph::addEdge(int vi, int vj) {
    neighbour[vi].emplace_back(vj);
}

void Graph::adduEdge(int vi, int vj) {
    uneighbour[vi].insert(vj);
}

