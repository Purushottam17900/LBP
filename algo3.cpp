#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;

vector<set<int>> graph;
int n, m;
//set<int> mis;
vector<bool> mis;
vector<int> dominator;

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
    mis.resize(n, 0);
    for(int i=0;i<n;i++){
        if(!vis[i]){
            mis[i] = 1;
            dominator[i] = i;
            for(auto v : graph[i]){
                if(!vis[v]){
                    vis[v] = true;
                    dominator[v] = i;
                }
            }
        }
    }
}

void edgeDeletion(int u, int v){ // (u < v)
    if(mis[u]){ 
        if(dominator[v] == u){
            for(auto w : graph[v]){
                if(mis[w]){
                    if((w < v) && (w > u)){
                        dominator[v] = w;
                        return;
                    }
                    else{
                        break;                        
                    }
                }
            }
            mis[v] = 1;
            dominator[v] = v;
            for(auto w : graph[v]){
                if(mis[w]){
                    for(auto x : graph[w]){
                        if(dominator[x] == w){
                            edgeDeletion(w, x);
                        }
                    }
                    mis[w] = 0;
                    dominator[w] = v;
                }
                else{
                    if(dominator[w] > v){
                        dominator[w] = v;
                    }
                }
            }
        }
    }
}

void edgeInsertion(int u, int v){
    if(mis[u] && mis[v]){
        for(auto w : graph[v]){
            if(dominator[w] == v){
                edgeDeletion(v, w);
            }
        }
        mis[v] = 0;
        dominator[v] = u;
    }
    else if(mis[u]){
        if(dominator[v] > u){
            dominator[v] = u;
        }
    }
}

void printMIS(){
    cout << "MIS vertices are : ";
    for(int i=0;i<n;i++){
        if(mis[i]){
            cout << i << " ";
        }
    }
    cout << endl;
}

void printDominators(){
    for(int i=0;i<n;i++){
        cout << i << " dominated by : " << dominator[i] << endl;
    }
}

int main(){
    // #ifndef ONLINE_JUDGE
	// 	freopen("output_3.txt","r", stdin);
	// 	freopen("answer_3.txt","w", stdout);
	// #endif
    inputGraph();
    greedyMIS();
    printMIS();
    //printDominators();

    int c, u, q, v;
    //cin >> q;
    while(q--){
        cout << "\tEnter \"0\" for edge deletion \n\tEnter \"1\" for edge insertion \n\tEnter \"other number\" to exit:  ";
        cin >> c;
        
        if(c == 0){
            cout << "Enter vertices : ";
            cin >> u >> v;
            if(u > v){
                int t = u;
                u = v;
                v = t;
            }
            if(graph[u].find(v) == graph[u].end()){
                //cout << "No such edge exists \n" ;
            }
            else{
                graph[u].erase(v);
                graph[v].erase(u);
                edgeDeletion(u, v);
                m--;
            }
        }
        else if(c == 1){
            cout << "Enter vertices : ";
            cin >> u >> v;
            if(u > v){
                swap(u, v);
            }
            if(graph[u].find(v) != graph[u].end()){
                //cout << "This edge already exists \n" ;
            }
            else{
                graph[u].insert(v);
                graph[v].insert(u);
                edgeInsertion(u, v);
                m++;    
            }
        }
        else{
            break;
        }
        printMIS();
        //printDominators();
    }
    printMIS();
}