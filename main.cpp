#include <boost/config.hpp>
#include <iostream>
#include <vector>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>
#include "snap/snap-core/Snap.h"

using namespace std;
using namespace boost;
typedef adjacency_list<vecS, vecS, directedS, no_property, property<edge_weight_t, int>> boostGraph;
typedef graph_traits<adjacency_list<vecS, vecS, directedS> >::vertex_descriptor Vertex;


int sccByboost(boostGraph &G){

//    const char* name = "abcdefghij";
//    std::cout << "A directed graph:" << std::endl;
//    print_graph(G, name);
//    std::cout << std::endl;

    std::vector<int> component(num_vertices(G)), discover_time(num_vertices(G));
    std::vector<default_color_type> color(num_vertices(G));
    std::vector<Vertex> root(num_vertices(G));
    int num = strong_components(G, make_iterator_property_map(component.begin(), get(vertex_index, G)),
                                root_map(make_iterator_property_map(root.begin(), get(vertex_index, G))).
                                        color_map(make_iterator_property_map(color.begin(), get(vertex_index, G))).
                                        discover_time_map(make_iterator_property_map(discover_time.begin(), get(vertex_index, G))));

//    std::cout << "Total number of components: " << num << std::endl;
//    std::vector<int>::size_type i;
//    for (i = 0; i != component.size(); ++i)
//        std::cout << "Vertex " << name[i]
//                  <<" is in component " << component[i] << std::endl;
    return num;
}

int main() {

    boostGraph G;

    add_edge (0, 1,  G);
    add_edge (0, 3,  G);
    add_edge (1, 2,  G);
    add_edge (2, 3,  G);
    add_edge (3, 1,  G);
    add_edge (1, 3,  G);
    add_edge (1, 4,  G);
    add_edge (4, 5,  G);
    add_edge (2, 5,  G);

    int num = sccByboost(G);
    printf("boost scc:%d\n",num);

    const PNGraph DirectedGraph = TNGraph::New();
    for (int i = 0; i < 6; i++) {
        DirectedGraph->AddNode(i);
    }
    DirectedGraph->AddEdge(0, 1);
    DirectedGraph->AddEdge(0, 3);
    DirectedGraph->AddEdge(1, 2);
    DirectedGraph->AddEdge(2, 3);
    DirectedGraph->AddEdge(3, 1);
    DirectedGraph->AddEdge(1, 3);
    DirectedGraph->AddEdge(1, 4);
    DirectedGraph->AddEdge(4, 5);
    DirectedGraph->AddEdge(2, 5);

    TCnComV CnComV;
    // strongly connected components
    TSnap::GetSccs(DirectedGraph, CnComV);
    printf("SNAP scc:%d\n",CnComV.Len());
//    printf("SNAP scc:%d\n",SccSzCntV1.Len());
    return 0;
}