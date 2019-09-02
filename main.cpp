#include "lib.h"

using namespace std;
using namespace boost;


double time_by(double start){
    return (clock()-start)/CLOCKS_PER_SEC;
}

void read_network_Boost(string file_path, boostGraph &G) {
    FILE* fin=fopen(file_path.c_str(),"rb");
    assert(fin != nullptr);
    int n, m;
    int vi, vj;
    printf("file:%s\n",file_path.c_str());
    fscanf(fin, "%d%d\n", &n,&m);
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
    fscanf(fin, "%d%d\n", &n,&m);
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

void read_network(string file_path, Graph &graph) {
    FILE* fin=fopen(file_path.c_str(),"r");
    assert(fin != nullptr);
    int vi, vj;
    printf("file:%s\n",file_path.c_str());
    int i = fscanf(fin,"%d%d", &vi,&vj);
    assert(i==2);
    graph = Graph(vi,vj);
    printf("nodes:%d  edges:%d\n", vi, vj);
    while (fscanf(fin,"%d\t%d\n", &vi,&vj)==2)
    {
        graph.addEdge(vi, vj);
    }
    fclose(fin);
}


void output(string name, vector<vector<int>> &G){
    FILE* fin=fopen(name.c_str(),"w");
    for(vector<int> &vec:G){
        for(int i:vec){
            fprintf(fin,"%d\t",i);
        }
        fprintf(fin,"\n");
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
    const TStr OutFNm = Env.GetIfArgPrefixStr("-o:", "graph", "Output file prefix");
    TSnap::GetSccs(G, CnComV);
    printf("SNAP scc:%d\ttime:%.2fs\n",CnComV.Len(),time_by(start));
    TCnCom::SaveTxt(CnComV, TStr::Fmt("%s.scc.txt", OutFNm.CStr()), "Strongly connected components");
    CnComV.Clr();
}


void tarjan(int u, Graph &G,vector<int> &DFN,vector<int> &LOW,vector<int> &viter,vector<int> &st,vector<int> &id,int &top,int &Tindex,int &stop, int &snum){
    int v;
    DFN[u] = LOW[u] = ++Tindex;
    G.visit[u] = true;
    G.q[++top] = u;
    st[++stop] =u;
    while (stop!=-1){
        u = st[stop];
        for(auto &iter = viter[u];iter < G.neighbour[u].size();iter++) {
            v = G.neighbour[u][iter];
            if (!DFN[v]) {
                DFN[v] = LOW[v] = ++Tindex;
                G.visit[v] = true;
                G.q[++top] = v;
                st[++stop] = v;
                break;
            } else if (DFN[v] > DFN[u] && LOW[v] < LOW[u]) {
                LOW[u] = LOW[v];
            } else if (G.visit[v] && DFN[v] < LOW[u])
                LOW[u] = DFN[v];
        }
        if(u == st[stop]) {
            if (DFN[u] == LOW[u]) {
                do {
                    v = G.q[top--];
                    G.visit[v] = false;
                    id[v] = snum;
                } while (v != u);
                snum++;
            }
            stop--;
        }
    }

}


vector<vector<int>> scc(Graph &G){
    double start = clock();
    int vnums = G.vnums;
    static vector<int> DFN, LOW, st, viter, id;
    static int top, Tindex, stop, snum;
    DFN.resize(vnums); LOW.resize(vnums); viter.resize(vnums);st.resize(vnums);id.resize(vnums);
    top=-1; Tindex=0;stop=-1;
    for(int u=0;u<vnums;u++){
        if(!DFN[u]){
            int v;
            DFN[u] = LOW[u] = ++Tindex;
            G.visit[u] = true;
            G.q[++top] = u;
            st[++stop] =u;
            while (stop!=-1){
                u = st[stop];
                for(auto &iter = viter[u];iter < G.neighbour[u].size();iter++) {
                    v = G.neighbour[u][iter];
                    if (!DFN[v]) {
                        DFN[v] = LOW[v] = ++Tindex;
                        G.visit[v] = true;
                        G.q[++top] = v;
                        st[++stop] = v;
                        break;
                    } else if (DFN[v] > DFN[u] && LOW[v] < LOW[u]) {
                        LOW[u] = LOW[v];
                    } else if (G.visit[v] && DFN[v] < LOW[u])
                        LOW[u] = DFN[v];
                }
                if(u == st[stop]) {
                    if (DFN[u] == LOW[u]) {
                        do {
                            v = G.q[top--];
                            G.visit[v] = false;
                            id[v] = snum;
                        } while (v != u);
                        snum++;
                    }
                    stop--;
                }
            }
        }
    }
    vector<vector<int>> SCCG;
    SCCG.resize(snum);
    DFN.assign(vnums,0);
    for(int i=0;i<vnums;i++){
        SCCG[id[i]].emplace_back(i);
    }
    printf("my scc:%d\ttime:%.2fs\n",SCCG.size(),time_by(start));
    vector<int>().swap(DFN);
    vector<int>().swap(LOW);
    vector<int>().swap(viter);
    vector<int>().swap(st);
    return SCCG;
}


int main(int argc, char *argv[]) {

    string filename = argv[1];
    int type = atoi(argv[2]);
    string ofile = argv[3];
    if(type==BOOST){
        boostGraph G;
        read_network_Boost(filename,G);
        sccByboost(G);
    }else if(type==SNAP){
        const PNGraph DirectedGraph = TNGraph::New();
        read_network_SNAP(filename,DirectedGraph);
        sccBySNAP(DirectedGraph);
    }else{
        Graph G;
        read_network(filename,G);
        vector<vector<int>> SCC = scc(G);
        output(ofile,SCC);
    }

    return 0;
}
