#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> graph;
int n, m;
int m_c;
set<int> mis;
vector<int> lowCount;
vector<int> degreeV;
set<int> lowV, highV, lowMIS, highMIS;
int deltaC;

void inputGraph(){
    cout << "Enter no of vertices : ";
    cin >> n;
    cout << "Enter no of edges : ";
    cin >> m;
    graph.resize(n, vector<int>());
    degreeV.resize(n, 0);
    cout << "Enter the edges as vertices pair \"(u v)\" : " << endl;
    int u, v;
    for(int i=0;i<m;i++){
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
        degreeV[u]++;
        degreeV[v]++;
    }
}


void partitionGraph(){
    lowV.clear();
    highV.clear();
    for(int i=0;i<n;i++){
        if(degreeV[i] <= deltaC){
            lowV.insert(i);
        }
        else{
            highV.insert(i);
        }
    }
}

set<int> staticMIS(set<int> &Vs){
    vector<bool> vis(n, false);
    set<int> res;
    for(auto u : Vs){
        if(vis[u] == false){
            res.insert(u);
            for(auto v : graph[u]){
                vis[v] = true;
            }
        }
    }
    return res;
}

void heavyMIS(){
    highMIS.clear();
    set<int> Vs;
    for(auto v : highV){
        if(lowCount[v] == 0){
            Vs.insert(v);
        }
    }
    highMIS = staticMIS(Vs);
}

void initialize(){
    deltaC = (int)(pow(m, (2/3)));
    m_c = m;
    partitionGraph();
    lowCount.resize(n, 0);
    lowMIS = staticMIS(lowV);
    for(auto u : lowMIS){
        for(auto v : graph[u]){
            lowCount[v]++;
        }
    }
    heavyMIS();
}

void edgeDeletion(int u, int v){
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

    if(lowMIS.find(u) != lowMIS.end()){
        lowCount[v]--;
        if(lowCount[v]==0){
            if(lowV.find(v) != lowV.end()){
                lowMIS.insert(v);
                for(auto w : graph[v]){
                    lowCount[w]++;
                }
            }
        }
    }
    else if(lowMIS.find(v) != lowMIS.end()){
        lowCount[u]--;
        if(lowCount[u]==0){
            if(lowV.find(u) != lowV.end()){
                lowMIS.insert(u);
                for(auto w : graph[u]){
                    lowCount[w]++;
                }
            }
        }
    }
    heavyMIS();
    
}

void edgeInsertion(int u, int v){
    if((lowMIS.find(u) != lowMIS.end()) && (lowMIS.find(v) != lowMIS.end())){
        lowMIS.erase(u);
        for(auto w : graph[u]){
            lowCount[w]--;
            if(lowCount[w]==0){
                if(lowV.find(w) != lowV.end()){
                    lowMIS.insert(w);
                    for(auto x : graph[w]){
                        lowCount[x]++;
                    }
                }
            }
        }
    }
    else if(lowMIS.find(u) != lowMIS.end()){
        lowCount[v]++;
    }
    else if(lowMIS.find(v) != lowMIS.end()){
        lowCount[u]++;
    }
    graph[u].push_back(v);
    graph[v].push_back(u);

    heavyMIS();
}

void printMIS(){
    cout << "lowMIS : ";
    for(auto i : lowMIS){
        cout << i << " ";
    }
    cout << endl;
    cout << "highMIS : ";
    for(auto i : highMIS){
        cout << i << " ";
    }
    cout << endl;
}

int main(){
    inputGraph();
    initialize();
    printMIS();
    int c, u, v;
    while(true){
        cout << "\tEnter \"0\" for edge deletion \n\tEnter \"1\" for edge insertion \n\tEnter \"other number\" to exit:  ";
        cin >> c;
        
        if(c == 0){
            cout << "Enter vertices : ";
            cin >> u >> v;
            edgeDeletion(u, v);
            degreeV[u]--;
            degreeV[v]--;
            m--;
        }
        else if(c == 1){
            cout << "Enter vertices : ";
            cin >> u >> v;
            edgeInsertion(u, v);
            degreeV[u]++;
            degreeV[v]++;
            m++;
        }
        else{
            break;
        }
        if((m == m_c/2) || (m == 2*m_c)){
            initialize();
        }
    }
    printMIS();
}