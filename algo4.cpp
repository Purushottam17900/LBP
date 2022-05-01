#include<bits/stdc++.h>
using namespace std;

int n, m;
set<int> mis;
vector<int> dominator;
int X; // no. of induced subgraphs

class Graph{
public:
    set<int> vertices;
    map<int, set<int>> neighbor_vertices;
};

Graph graph;
vector<Graph> induced_subgraphs;

set<int> greedyMIS(Graph &graph){
    set<int> vis;
    set<int> res;
    for(auto i : graph.vertices){
        if(vis.find(i) == vis.end()){
            res.insert(i);
            //dominator[i] = i;
            for(auto v : graph.neighbor_vertices[i]){
                if(vis.find(v) == vis.end()){
                    vis.insert(v);
                    //dominator[v] = i;
                }
            }
        }
    }
    return res;
}

int find_k(int z){
    int ans = log2(z);
    return ans;
}

set<int> findInfluencedSet(int u, int v, int b, string type_of_update){  
    set<int> S,T;
    if(mis.find(u) == mis.end()){
        return {};
    }
    else{
        if(mis.find(v) == mis.end()){
            if(type_of_update == "insertion"){
                return {};
            }
            else if(type_of_update == "deletion"){
                if(dominator[v] != u){
                    return {};
                }
                else{
                    T = {v};
                }
            }
        }
        else{
            if(type_of_update == "insertion"){
                T = {v};
            }
        }
    }

    while(!(T.empty())){
        int z = *(T.begin());
        T.erase(z);
        if(mis.find(z) != mis.end()){
            S.insert(z);
            int k = find_k(z);
            //assert(induced_subgraphs[k].vertices.find(z) != induced_subgraphs[k].vertices.end());
            for(auto w : induced_subgraphs[k].vertices){
                if(w > z){
                    T.insert(w);
                }
            }
        }
        else{
            bool flag = true;
            for(auto w : induced_subgraphs[b].vertices){
                if((w < z) && (mis.find(w) != mis.end())){
                    if(S.find(w) == S.end()){
                        flag = false;
                        break;
                    }
                }
            }
            if(flag){
                S.insert(z);
                for(auto w : induced_subgraphs[b].vertices){
                    if((w > z) && (mis.find(w) != mis.end())){
                        T.insert(w);
                    }
                }
            }
        }
    }
    return S;
}

void fixSubgraphs(set<int> S, int b){
    for(auto z : S){
        int k = find_k(z);
        if(mis.find(z) != mis.end()){//z has joined mis after update
            for(auto w : graph.neighbor_vertices[z]){
                if(induced_subgraphs[k].vertices.find(w) != induced_subgraphs[k].vertices.end()){
                    for(int i=k+1;i<X;i++){
                        induced_subgraphs[i].vertices.erase(w);
                    }
                }
            }
        }
        else{//z has left mis after update
            //for neighbor w of z in OLD VERSION of Vk before update
            //compute w's memberships in Gk ....
        }
    }
}

void update(int u, int v, string type_of_update){
    int a, b;
    a = find_k(u);
    b = find_k(v);

    set<int> S = findInfluencedSet(u, v, b, type_of_update);

    if(S.empty()){
        //recompute v's memberships among induced subgraphs for k>a
        if(type_of_update == "insertion" && dominator[v] > u){
            for(int i=a+1;i<X;i++){
                induced_subgraphs[i].vertices.erase(v);
            }
        }
    }
    else{
        if(type_of_update == "insertion"){
            for(int i=a+1;i<X;i++){
                induced_subgraphs[i].vertices.erase(v);
            }
            //greedyMIS(); // greedy MIS on influenced set.
        }
        else{
            for(int i=a+1;i<=b;i++){
                induced_subgraphs[i].vertices.insert(v);
            }
            //greedyMIS(); // greedy MIS on influenced set.
        }

        fixSubgraphs(S, b);

    }
}

void initialize(){
    X = log2(n);
    induced_subgraphs.resize(X);
    //map<int, Graph> induced_subgraphs;
    greedyMIS(graph);
    for(int i=0;i<X;i++){
        //induced_subgraphs[i] = new Graph();
        int k = (int)(pow(2, i));
        // vector<bool> v(n, true);
        for(int j=k;j<n;j++){
            if(dominator[j] > k){
                induced_subgraphs[i].vertices.insert(j);
            }
        }
    }
}

int main(){

}