#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;

vector<set<int>> graph;
int n, m;
int m_c;
set<int> mis;
vector<int> lowCount;
vector<int> degreeV;
set<int> lowV, highV, lowMIS, highMIS;
int deltaC;

void inputGraph(){
    //cout << "Enter no of vertices : ";
    cin >> n;
    cout << "Number of vertices : " << n << endl;
    //cout << "Enter no of edges : ";
    cin >> m;
    cout << "Number of edges : " << m << endl;
    graph.resize(n, set<int>());
    degreeV.resize(n, 0);
    //cout << "Enter the edges as vertices pair \"(u v)\" : " << endl;
    int u, v;
    for(int i=0;i<m;i++){
        cin >> u >> v;
        graph[u].insert(v);
        graph[v].insert(u);
        degreeV[u]++;
        degreeV[v]++;
    }
}

void displayGraph(){
    for(int i=0;i<n;i++){
        cout << i << ": ";
        for(auto v : graph[i]){
            cout << v << " ";
        }
        cout << endl;
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
    cout << "number of light vertices : " << lowV.size() << endl;
    cout << "number of heavy vertices : " << highV.size() << endl;
    
}

set<int> staticMIS(set<int> &Vs){
    set<int> vis;
    set<int> res;
    for(auto u : Vs){
        if(vis.find(u) == vis.end()){
            res.insert(u);
            for(auto v : graph[u]){
                vis.insert(v);
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
    deltaC = (int)(pow(m, (0.6666667)));
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
    graph[u].erase(v);
    graph[v].erase(u);

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
    graph[u].insert(v);
    graph[v].insert(u);

    heavyMIS();
}

void printMIS(){
    cout << "MIS vertices are : ";
    //cout << "lowMIS : ";
    for(auto i : lowMIS){
        cout << i << " ";
    }
    //cout << endl;
    //cout << "highMIS : ";
    for(auto i : highMIS){
        cout << i << " ";
    }
    cout << endl;
}

int main(){
    #ifndef ONLINE_JUDGE
		freopen("testcase_sample.txt","r", stdin); //input file
		freopen("algo3_output_sample.txt","w", stdout); // output file
	#endif

    inputGraph();
    initialize();
    //displayGraph();
    //printMIS();

    auto start = high_resolution_clock::now();

    int c, u, v;
    
    int ins, del;
    ins = del = 0;
    
    while(true){
        //cout << "\tEnter \"0\" for edge deletion \n\tEnter \"1\" for edge insertion \n\tEnter \"other number\" to exit:  ";
        cin >> c;
        
        if(c == 0){
            //cout << "Enter vertices : ";
            cin >> u >> v;
            if(graph[u].find(v) == graph[u].end()){
                //cout << "No such edge exists \n" ;
            }
            else{
                //cout << "\nEdge Deletion between " << u << " and " << v << ". ";
                del++;
                edgeDeletion(u, v);
                degreeV[u]--;
                degreeV[v]--;
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
                degreeV[u]++;
                degreeV[v]++;
                m++;
            }
        }
        else{
            break;
        }
        if((m == m_c/2) || (m == 2*m_c)){
            initialize();
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