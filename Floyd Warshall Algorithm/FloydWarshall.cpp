#include <bits/stdc++.h>
#include <math.h>
#define INF 1000000000

using namespace std;

void floyd_warshall(vector<vector<int>> adjMatrix, int V){

    for(int k=0; k<V; k++){
        for(int i=0;i<V;i++){
            for(int j=0; j<V; j++){
                if(adjMatrix[i][j]> (adjMatrix[i][k] + adjMatrix[k][j])){
                    adjMatrix[i][j] = adjMatrix[i][k] + adjMatrix[k][j];
                }
            }
        }
    }

    cout << "Shortest distance matrix" <<endl;
    for (int i=0; i<V; i++){
        for(int j=0; j<V;j++){
            if(adjMatrix[i][j] == INF)
                cout << "INF ";
            else 
            cout<< adjMatrix[i][j] << "   ";
        }
        cout << endl;
    }
}

int main(){
int n, m, s, d;
    //cin >> n >> m;   
    ifstream myfile;
    myfile.open("input.txt");
    myfile >> n >> m;

    vector<vector<int>> adjMatrix(n, vector<int> (n,INF));
    
    for (int i=0; i<n; i++){
        for(int j=0; j<n;j++){
            if(i == j)
                adjMatrix[i][j] = 0;
        }
    }

    for (int i=0; i<m; i++){
        int a,b,w;
        //cin >> a >> b >> w;
        myfile >> a >> b >> w;
        adjMatrix[a-1][b-1] = w;
    }

    floyd_warshall(adjMatrix,n);
    
    return 0;
}