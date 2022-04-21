#include <bits/stdc++.h>
#include <math.h>
#define inf 1000000000

using namespace std;

class Graph{
    public:
    int V;
    vector <pair<int,int>> *adj;
    vector <int> path;
    vector<vector<int>> edges;
    int *minDist;
    int *parent;
    bool isCycleNeg;

    public:
    Graph(int v){
        V = v;
        adj = new vector<pair<int, int>>[v];
        minDist = new int[v];
        parent = new int[v];
        isCycleNeg = false;

        for(int i=0;i<v;i++){
            minDist[i] = inf;
            parent[i] = -1;
        }
        
    }
    void addEdge(int weight, int source, int destination){
        adj[source].push_back({weight,destination});
        vector<int> vec;
        vec = {source,destination,weight};
        edges.push_back(vec);
        //adj[destination].push_back({weight,source});
    }

    bool relax(int u, int v, int w){
        if(minDist[v] > minDist[u] + w ){
            minDist[v] = minDist[u] + w;
            parent[v] = u;
            return true;
        }        
        return false;
    }

    void Bellman(int source, int edge){
        minDist[source] = 0;
        parent[source] = -1;
        for(int i=0; i<edge-1; i++){
            for(auto j: edges ){
                int u = j[0];
                int v = j[1];
                int w = j[2];
                relax(u,v,w);
            }
        }
        for(auto j: edges){
            int u = j[0];
            int v = j[1];
            int w = j[2];
            if(minDist[v] > minDist[u] + w ){
                isCycleNeg = true;
            }        
        }
    }
    void Dijkstra(int source){
        int minCost = 0;
        
        minDist[source] = 0;
        parent[source] = -1;
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> Q;
        Q.push({0,source});
        

        while(!Q.empty()){
            auto popped = Q.top();
            Q.pop();
            if(popped.first > minDist[popped.second]) continue;

            for(auto j: adj[popped.second]){  
                //parent[i.second] = popped.second; 
                       
                if(relax(popped.second, j.second, j.first)) 
                    Q.push({minDist[j.second], j.second});
            }

        }
    }

    void printPath(int source, int destination){

        if(destination == source)
            cout<< source ;
        else{
            printPath(source,parent[destination]);
            cout << " -> " << destination;
        }        
    }
};

int main(){
    int n, m, s, d;
    int isNeg = 0;
    cin >> n >> m;

    Graph g(n);
    for (int i=0; i<m; i++){
        int a,b;
        int w;
        cin >>a >>b >> w;
        if(w<0)
            isNeg = 1;
        g.addEdge(w,a,b);
    }
    cin >> s >> d;  
    
    if(isNeg) {
        g.Bellman(s,m);
        if(g.isCycleNeg)
            cout<< "The graph contains a negative cycle" <<endl;
        else{
            cout<< "The graph does not contain a negative cycle" <<endl;
            cout << "Shortest path cost: " <<  g.minDist[d] << "\n";
            g.printPath(s,d);
        }
    }
    else{
        g.Dijkstra(s);
        cout << "Shortest path cost: " <<  g.minDist[d] << "\n";
         g.printPath(s,d);
    }   
    
        
    return 0;
}