#include <bits/stdc++.h>
#define INF 1000000

using namespace std;

class kruskalDSU{
    int *rank;
    int *parent;
    public:
    kruskalDSU(int n){
        rank = new int[n];
        parent = new int[n];
        for(int i=0;i<n;i++){
            rank[i] = 1 ;
            parent[i] = -1;
        }
    }
    int findParent(int v){
        if(parent[v] == -1)
            return v;
        else{
            return findParent(parent[v]);
        }
    }

    void merge(int u, int v){
        int p1 = findParent(u);
        int p2 = findParent(v);
        if(p1 !=p2){
            if(rank[p1]<rank[p2]){
                parent[p1] = p2;
                rank[p2] += rank[p1];
            }
            else{
                 parent[p2] = p1;
                 rank[p1] += rank[p2];
            }
           
        }
    }   
    
};

class mstGraph{
    int V;
    vector <pair<float,int>> *adj;
    vector <pair<float, pair<int,int>>> edges;
    vector <pair<int,int>> KruskalSerialpair;
    vector <int> PrimSerial;
    vector <int> KruskalSerial;

    int *key;
    int *parentPrim;
    int intermediateNode;

    public:
    mstGraph(int v){
        V = v;
        adj = new vector<pair<float, int>>[v];
        key = new int[v];
        parentPrim = new int[v];
        for(int i=0; i<v;i++){
            key[i] = INF;
            parentPrim[i] = -1;
        }
    }
    void addEdge(float weight, int source, int destination){
        adj[source].push_back({weight,destination});
        adj[destination].push_back({weight,source});
        edges.push_back({weight,{source,destination}});
        }

    float minSpanWeightKruskal(){
        sort(edges.begin(),edges.end());
        float totalWeight = 0;
        kruskalDSU S(V);

        for(auto i:edges){
            float w = i.first;
            int u = i.second.first;
            int v = i.second.second;

            if(S.findParent(u)!=S.findParent(v)){
                S.merge(u,v);
                KruskalSerialpair.push_back({u,v});
                totalWeight += w;
            }

        }
    return totalWeight;

    }
    float minSpanWeightPrim(){
        float totalWeight = 0.0;
        bool *visited = new bool[V]{0};
        priority_queue<pair<float,int>, vector<pair<float,int>>, greater<pair<float,int>>> Q;
        Q.push({0,0});
        //PrimSerial.push_back(0);
        //KruskalSerial.push_back(0);
        
        while (!(Q.empty()))
        {
            auto popped = Q.top();
            Q.pop();
            

            if(visited[popped.second])
                continue;
            visited[popped.second] = 1;
            PrimSerial.push_back(popped.second);
            //cout << popped.second << endl;
            totalWeight += popped.first;

            for (auto i : adj[popped.second]){
                int w = i.first;
                int destination = i.second;
                if(visited[destination]==0 && key[destination]>w){
                    Q.push({w, destination});
                    key[destination] = w;
                    parentPrim[destination] = popped.second;

                }
            }
        }
        return totalWeight;
    }
    void printEdgesPrim(){
        cout<<"{";
        for(int i=1; i<V; i++){
            if(i!=1)
                cout<< ",";
            cout<< "(" << parentPrim[PrimSerial[i]] << "," << PrimSerial[i] <<")";
        }
        cout<<"}" <<endl;

        // for(int i=0;i<V;i++){
        //     cout<< PrimSerial[i] <<endl;
        // }
    }
    void printEdgesKruskal(){
        cout<<"{";
        for(int i=0;i< KruskalSerialpair.size();i++){
            if(i!=0)
                cout<< ",";
            cout<< "(" << KruskalSerialpair[i].first << "," << KruskalSerialpair[i].second <<")";
        }
        cout<<"}" <<endl;
    }

};

int main(){
    int n,m;
    //cin >> n >> m;
    ifstream myfile;
    myfile.open("mst.txt");

    myfile >> n >> m;
    mstGraph g(n);
    for (int i=0; i<m; i++){
        int s,d;
        float w;
        myfile >>s >>d >> w;
        g.addEdge(w,s,d);
    }

    float ansPrim = g.minSpanWeightPrim();
    float ansKruskal = g.minSpanWeightKruskal();
    cout << "Cost of the minimum spanning tree :" << fixed << setprecision(1) << ansPrim << endl;
    cout << "List of edges selected by Prim’s:";
    g.printEdgesPrim();
    cout << "List of edges selected by Kruskal’s:";
    g.printEdgesKruskal();
     
return 0;

}



