#include <bits/stdc++.h>
#include <math.h>
#include "edmondsKarp.h"
#include "combi.h"
#define INF 1000000000

using namespace std;

int main(){
    
    int n;
    
    cin >> n;
    //Graph g(n);
    int win[n], loss[n], remains[n], games[n][n];
    vector<string> teams;

    vector<int> EliminatedIndex;
    vector<vector<int>> minCutSet;
    vector<int> minCutGames;
    vector<int> minCutTotalWins[n];
    int minCutTotalGames[n];
    minCutSet.assign(n, vector<int>()) ;
    

    for(int i=0; i<n; i++){
        string s;

        cin >> s;
        teams.push_back(s);

        cin >> win[i] >> loss[i] >> remains[i];
        for(int j=0; j<n; j++)
            cin >> games[i][j];
    }


    int combi = combination(n-1);
    vector<pair<int,int>> pairOfTeams;
    
    int totalNodes = 1 + combi + (n-1) + 1;
    

    for(int k=0; k<n; k++){
        if( win[k]+remains[k] < win[0] ){
            EliminatedIndex.push_back(k); 
            minCutSet[k].push_back(0);
            minCutTotalGames[k] = 0;
            continue;
        }
            
        vector<int> sourceEdges(n-1);
        Graph g(totalNodes);
        int index = 1;
        int r1 = 0;
        int r2 = 0;
        int l = 1;
        int totalCapacity = 0;
        for(int i=0; i<n; i++){
            if(i==k)
                r1++;
            //g.addEdge(i+1,i+combi+1,INF);

            for(int j=0; j<n; j++){
                if(j==k)
                    r2++;

                if(i==k || j==k || i>=j)
                    continue;
                //sourceEdges.push_back(games[i][j]);
                g.addEdge(0,index,games[i][j]);
                pairOfTeams.push_back({i,j});
                
                totalCapacity += games[i][j];

                g.addEdge(index,i+combi+1-r1,INF);
                g.addEdge(index,j+combi+1-r2,INF);
                l++;
                
                
                index++;
            }
            int r3 = 0;
            for(int i=1; i<=n-1; i++){
                if(i == k+1){
                    r3++;
                //continue;
                }
               
            //kisu ekta kora lagbe
            g.addEdge(i+combi, combi+n, win[k]+remains[k]-win[i-1+r3]);
            
        }
    }
    
    int ans = g.MaxFlowEdmondKarp(0,totalNodes-1);
    //cout << "maxflow = " << ans << " totalcap = " << totalCapacity << endl;
    
    //If not saturated
    if(ans!= totalCapacity){
        EliminatedIndex.push_back(k);


        // cout << teams[k] << " is eliminated."<<endl;
        // cout<< "They can win at most " << win[k]<< " + " << remains[k]<< " = " << win[k]+remains[k] << " games." << endl;
        //cout<< endl;


        bool check[n];
        for(int i=0;i<n;i++)
            check[i] = false;

        int totalgames = 0;

        for(int i=1; i<=n-1; i++){
            if(g.resMatrix[0][i]!=0){
                //minCutSet[k].push_back(i);
                auto at = pairOfTeams[i];
                check[at.first-1] = true;
                check[at.second-1] = true;
                totalgames += games[at.first-1][at.second-1];

                //cout<< "mincut element " << at.first << " " << at.second << endl;
                

            }
                
        }
        minCutTotalGames[k] = totalgames;
        for(int i=0;i<n;i++){
                if(check[i]==true)
                    minCutSet[k].push_back(i);
            }
    }
        

    } 

    for(int i =0; i< EliminatedIndex.size();i++){
        int temp = EliminatedIndex[i];
        cout << teams[temp] << " is eliminated."<<endl;
        cout<< "They can win at most " << win[temp]<< " + " << remains[temp]<< " = " << win[temp]+remains[temp] << " games." << endl;
        int TotalGames = 0;
        int totalwins = 0;
        for(int i=0; i<minCutSet[temp].size(); i++){
            cout << teams[minCutSet[temp][i]] << " ";
            totalwins += win[minCutSet[temp][i]];
            
            if(i!=minCutSet[temp].size()-1)
                cout << "and ";
            
        }
        float avg = (float)(totalwins + minCutTotalGames[temp]) / (float)minCutSet[temp].size();
        cout << "have won a total of " << totalwins << " games." << endl;
        cout << "They play each other "  << minCutTotalGames[temp] << " times." <<endl;
        cout << "So on average, each of the teams in this group wins " << totalwins + minCutTotalGames[temp]<< "/" <<minCutSet[temp].size() << " = " << avg << " games." << endl;
        cout<< endl;
    }   
    
   
   //Graph g(6);

   /*
   g.addEdge(0,1,16);
   g.addEdge(0,2,13);
   g.addEdge(1,2,10);
   g.addEdge(2,1,4);
   g.addEdge(3,2,9);
   g.addEdge(1,3,12);
   g.addEdge(2,4,14);
   g.addEdge(4,3,7);
   g.addEdge(3,5,20);
   g.addEdge(4,5,4);
   */

  /*
    g.addEdge(0,1,10);
    g.addEdge(0,2,10);
   g.addEdge(1,2,2);
   g.addEdge(1,3,4);
   g.addEdge(1,4,8);
   g.addEdge(2,4,9);
   g.addEdge(4,3,6);
   g.addEdge(3,5,10);
   g.addEdge(4,5,10);
  */

   //int ans = g.MaxFlowEdmondKarp(0,5);
   //g.printResMAtrix();
   //cout << ans << endl;
   





    return 0;
}
