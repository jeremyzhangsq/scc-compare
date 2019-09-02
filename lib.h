//
// Created by Jeremy Shiqi Zhang on 2019-08-31.
//

#ifndef SCC_LIB_H
#define SCC_LIB_H

#define SNAP 1
#define BOOST 2


#include <boost/config.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include "graph.h"
#include <boost/graph/strong_components.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>
#include "snap/snap-core/Snap.h"


using namespace std;
using namespace boost;
typedef adjacency_list<vecS, vecS, directedS, no_property, property<edge_weight_t, int>> boostGraph;
typedef graph_traits<adjacency_list<vecS, vecS, directedS> >::vertex_descriptor Vertex;

double time_by(double start);
void read_network_Boost(string file_path, boostGraph &G);
void read_network_SNAP(string file_path,const PNGraph G);
void read_network(string file_path, Graph &G);
void sccByboost(boostGraph &G);
void sccBySNAP(const PNGraph G);
vector<vector<int>> scc(Graph &G);
void output(string name, vector<vector<int>> &G);

#endif //SCC_LIB_H
