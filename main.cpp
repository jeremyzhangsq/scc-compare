#include <boost/config.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>
#include "snap/snap-core/Snap.h"
#define SNAP 1
#define BOOST 2
using namespace std;
using namespace boost;
typedef adjacency_list<vecS, vecS, directedS, no_property, property<edge_weight_t, int>> boostGraph;
typedef graph_traits<adjacency_list<vecS, vecS, directedS> >::vertex_descriptor Vertex;

double time_by(double start){
    return (clock()-start)/CLOCKS_PER_SEC;
}

void read_network_Boost(string file_path, boostGraph &G) {
    FILE* fin=fopen(file_path.c_str(),"rb");
    assert(fin != nullptr);
    int n, m;
    int vi, vj;
    printf("file:%s\n",file_path.c_str());
    fscanf(fin, "%d\t%d\n", &n,&m);
    vector<int> node_deg=vector<int>(n);
    printf("nodes:%d  edges:%d\n", n, m);
    for(unsigned int i = 0;i<m;i++)
    {
        fscanf(fin, "%d\t%d\n", &vi,&vj);
        add_edge (vi, vj,  G);
    }

    fclose(fin);
}

void read_network_SNAP(string file_path,const PNGraph G) {
    FILE* fin=fopen(file_path.c_str(),"rb");
    assert(fin != nullptr);
    int n, m;
    int vi, vj;
    printf("file:%s\n",file_path.c_str());
    fscanf(fin, "%d\t%d\n", &n,&m);
    vector<int> node_deg=vector<int>(n);
    printf("nodes:%d  edges:%d\n", n, m);
    for (int i = 0; i < n; i++) {
        G->AddNode(i);
    }
    for(unsigned int i = 0;i<m;i++)
    {
        fscanf(fin, "%d\t%d\n", &vi,&vj);
        G->AddEdge(vi, vj);
    }

    fclose(fin);
}

void sccByboost(boostGraph &G){
    double start = clock();
    std::vector<int> component(num_vertices(G)), discover_time(num_vertices(G));
    std::vector<default_color_type> color(num_vertices(G));
    std::vector<Vertex> root(num_vertices(G));
    int num = strong_components(G, make_iterator_property_map(component.begin(), get(vertex_index, G)),
                                root_map(make_iterator_property_map(root.begin(), get(vertex_index, G))).
                                        color_map(make_iterator_property_map(color.begin(), get(vertex_index, G))).
                                        discover_time_map(make_iterator_property_map(discover_time.begin(), get(vertex_index, G))));
    printf("boost scc:%d\ttime:%.2fs\n",num,time_by(start));
}

void sccBySNAP(const PNGraph G){
    double start = clock();
    TCnComV CnComV;
    TSnap::GetSccs(G, CnComV);
    printf("SNAP scc:%d\ttime:%.2fs\n",CnComV.Len(),time_by(start));
}


int main(int argc, char *argv[]) {

    string filename = argv[1];
    int type = atoi(argv[2]);

    assert(type==SNAP||type==BOOST);
    if(type==BOOST){
        boostGraph G;
        read_network_Boost(filename,G);
        sccByboost(G);
    }else{
        const PNGraph DirectedGraph = TNGraph::New();
        read_network_SNAP(filename,DirectedGraph);
        sccBySNAP(DirectedGraph);
    }

    return 0;
}