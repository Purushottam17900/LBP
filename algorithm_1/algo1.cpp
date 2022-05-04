#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;

vector<set<int>> graph;
int n, m, q;
vector<bool> mis;
vector<int> count_of_MIS_neighbors;

void inputGraph(){
    //cout << "Enter no of vertices : ";
    cin >> n;
    cout << "Number of vertices : " << n << endl;
    //cout << "Enter no of edges : ";
    cin >> m;
    cout << "Number of edges : " << m << endl;
    //cin >> q;
    graph.resize(n, set<int>());
    mis.resize(n, 0);
    //cout << "Enter the edges as vertices pair : " << endl;
    int u, v;
    for(int i=0;i<m;i++){
        cin >> u >> v;
        graph[u].insert(v);
        graph[v].insert(u);
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
            //mis.insert(i);
            mis[i] = 1;
            for(auto v : graph[i]){
                vis[v] = true;
                count_of_MIS_neighbors[v]++;
            }
        }
    }
}

void edgeDeletion(int u, int v){
    if(mis[u]){
        count_of_MIS_neighbors[v]--;
        if(count_of_MIS_neighbors[v]==0){
            //mis.insert(v);
            mis[v] = 1;
        }
    }
    else if(mis[v]){
        count_of_MIS_neighbors[u]--;
        if(count_of_MIS_neighbors[u]==0){
            //mis.insert(u);
            mis[u] = 1;
        }
    }
    graph[u].erase(v);
    graph[v].erase(u);
}

void edgeInsertion(int u, int v){
    if(mis[u] && mis[v]){
        mis[u] = 0;
        for(auto i : graph[u]){
            count_of_MIS_neighbors[i]--;
            if(count_of_MIS_neighbors[i] == 0){
                mis[i] = 1;
            }
        }
    }
    else if(mis[u]){
        count_of_MIS_neighbors[v]++;
    }
    else if(mis[v]){
        count_of_MIS_neighbors[u]++;
    }
    graph[u].insert(v);
    graph[v].insert(u);
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

int main(){
     #ifndef ONLINE_JUDGE
		freopen("testcase_sample.txt","r", stdin);
		freopen("algo1_output_sample.txt","w", stdout);
	#endif
    inputGraph();
    //displayGraph();
    constructMIS();
    //printMIS();

    auto start = high_resolution_clock::now();

    int c, u, v;
    int ins, del;
    ins = del = 0;
    
    while(true){
        //cout << "\tEnter \"0\" for edge deletion \n\tEnter \"1\" for edge insertion \n\tEnter \"other number\" to exit:  ";
        
        cin >> c; 

        if(u < v){
            swap(u, v);
        }
        if(c == 0){
            //cout << "Enter vertices : ";
            cin  >> u >> v;
            if(graph[u].find(v) == graph[u].end()){
                //cout << "No such edge exists \n" ;
            }
            else{
                //cout << "\nEdge Deletion between " << u << " and " << v << ". ";
                del++;
                edgeDeletion(u, v);
                m--;
            }
        }
        else if(c == 1){
            //cout << "Enter vertices : ";
            cin >> u >> v;
            if(graph[u].find(v) != graph[u].end()){
                //cout << "This edge already exists \n" ;
            }
            else{
                //cout << "\nEdge Insertion between " << u << " and " << v << ". ";
                ins++;
                edgeInsertion(u, v);
                m++;
            }
        }
        else{
            break;
        }
        //printMIS();
    }
    //printMIS();

    cout << "\nNumber of insertions : " << ins << endl;
    cout << "Number of deletions : " << del << endl;

    auto stop = high_resolution_clock::now();
    
    auto duration = duration_cast<microseconds>(stop - start);
 
    cout << "Time taken by program: "
         << duration.count() << " microseconds" << endl;
 

}