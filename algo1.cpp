#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> graph;
int n, m;
set<int> mis;
vector<int> count_of_MIS_neighbors;

void inputGraph(){
    cout << "Enter no of vertices : ";
    cin >> n;
    cout << "Enter no of edges : ";
    cin >> m;
    graph.resize(n, vector<int>());
    cout << "Enter the edges as vertices pair : " << endl;
    int u, v;
    for(int i=0;i<m;i++){
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
}

void displayGraph(){
    cout << "\nThe adjacency list of the graph is : " << endl;
    for(int i=0;i<n;i++){
        cout << i << ": ";
        for(auto j : graph[i]){
            cout << j << " " ;
        }
        cout << endl;
    }
}

void constructMIS(){
    vector<bool> vis(n, false);
    count_of_MIS_neighbors.resize(n, 0);
    for(int i=0;i<n;i++){
        if(vis[i] == false){
            mis.insert(i);
            for(auto v : graph[i]){
                vis[v] = true;
                count_of_MIS_neighbors[v]++;
            }
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

void edgeDeletion(int u, int v){
    if(mis.find(u) != mis.end()){
        count_of_MIS_neighbors[v]--;
        if(count_of_MIS_neighbors[v]==0){
            mis.insert(v);
        }
    }
    else if(mis.find(v) != mis.end()){
        count_of_MIS_neighbors[u]--;
        if(count_of_MIS_neighbors[u]==0){
            mis.insert(u);
        }
    }
    
    int p;
    for(int i=0;i<graph[u].size();i++){
        if(graph[u][i] == v){
            p = i;
            break;
        }
    }
    graph[u].erase(graph[u].begin()+p);

    for(int i=0;i<graph[v].size();i++){
        if(graph[v][i] == u){
            p = i;
            break;
        }
    }
    graph[v].erase(graph[v].begin()+p);
}

void edgeInsertion(int u, int v){
    if((mis.find(u) != mis.end()) && (mis.find(v) != mis.end())){
        mis.erase(u);
        for(auto i : graph[u]){
            count_of_MIS_neighbors[i]--;
            if(count_of_MIS_neighbors[i] == 0){
                mis.insert(i);
            }
        }
    }
    else if((mis.find(u) != mis.end())){
        count_of_MIS_neighbors[v]++;
    }
    else if((mis.find(v) != mis.end())){
        count_of_MIS_neighbors[u]++;
    }
    graph[u].push_back(v);
    graph[v].push_back(u);
}


int main(){
    inputGraph();
    displayGraph();
    constructMIS();
    printMIS();

    int c=0, u, v;
    while(true){
        cout << "\tEnter \"0\" for edge deletion \n\tEnter \"1\" for edge insertion \n\tEnter \"other number\" to exit:  ";
        cin >> c;
        
        if(c == 0){
            cout << "Enter vertices : ";
            cin >> u >> v;
            edgeDeletion(u, v);
            m--;
        }
        else if(c == 1){
            cout << "Enter vertices : ";
            cin >> u >> v;
            edgeInsertion(u, v);
            m++;
        }
        else{
            break;
        }
    }
    displayGraph();
    printMIS();
}