#include<bits/stdc++.h>
using namespace std;

vector<set<int>> graph;
int n, m;
set<int> mis;
vector<int> dominator;
vector<set<int>> dominated_by;

void inputGraph(){
    cout << "Enter no of vertices : ";
    cin >> n;
    cout << "Enter no of edges : ";
    cin >> m;
    graph.resize(n, set<int>());
    cout << "Enter the edges as vertices pair : " << endl;
    int u, v;
    for(int i=0;i<m;i++){
        cin >> u >> v;
        graph[u].insert(v);
        graph[v].insert(u);
    }
}

void greedyMIS(){
    vector<bool> vis(n, false);
    dominator.resize(n, -1);
    dominated_by.resize(n, set<int>());
    for(int i=0;i<n;i++){
        if(!vis[i]){
            mis.insert(i);
            dominator[i] = i;
            dominated_by[i].insert(i);
            for(auto v : graph[i]){
                if(!vis[v]){
                    vis[v] = true;
                    dominator[v] = i;
                    dominated_by[i].insert(v);
                }
            }
        }
    }
}

void edgeDeletion(int u, int v){ // (u < v)
    if(mis.find(u) != mis.end()){ 
        if(dominated_by[u].find(v) != dominated_by[u].end()){
            for(auto w : graph[v]){
                if(mis.find(w) != mis.end()){
                    if(w < v){
                        dominated_by[u].erase(v);
                        dominator[v] = w;
                        dominated_by[w].insert(v);
                        return;
                    }
                    else{
                        break;                        
                    }
                }
            }
            mis.insert(v);
            dominated_by[u].erase(v);
            dominator[v] = v;
            dominated_by[v].insert(v);
            for(auto w : graph[v]){
                if(mis.find(w) != mis.end()){
                    for(auto x : dominated_by[w]){
                        edgeDeletion(w, x);  
                    }
                    mis.erase(w);
                }
                else{
                    if(dominator[w] > v){
                        dominated_by[dominator[w]].erase(w);
                        dominator[w] = v;
                        dominated_by[v].insert(w);
                    }
                }
            }
        }
    }
}

void edgeInsertion(int u, int v){
    if((mis.find(u) != mis.end()) && (mis.find(v) != mis.end())){
        for(auto w : dominated_by[v]){
            edgeDeletion(v, w);
        }
        mis.erase(v);
    }
    else if(mis.find(u) != mis.end()){
        if(dominator[v] > u){
            dominated_by[dominator[u]].erase(v);
            dominator[v] = u;
            dominated_by[u].insert(v);
        }
    }
}

void printMIS(){
    cout << "MIS vertices are : ";
    for(auto i: mis){
        cout << i << " ";
    }
    cout << endl;
}

int main(){
    inputGraph();
    greedyMIS();
    printMIS();

    int c, u, v;
    while(true){
        cout << "\tEnter \"0\" for edge deletion \n\tEnter \"1\" for edge insertion \n\tEnter \"other number\" to exit:  ";
        cin >> c;
        
        if(c == 0){
            cout << "Enter vertices : ";
            cin >> u >> v;
            if(u > v){
                swap(u, v);
            }
            graph[u].erase(v);
            graph[v].erase(u);
            edgeDeletion(u, v);
            m--;
        }
        else if(c == 1){
            cout << "Enter vertices : ";
            cin >> u >> v;
            if(u > v){
                swap(u, v);
            }
            graph[u].insert(v);
            graph[v].insert(u);
            edgeInsertion(u, v);
            m++;
        }
        else{
            break;
        }
        printMIS();
    }
    printMIS();
}