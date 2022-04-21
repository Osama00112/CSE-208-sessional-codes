//
// Created by Osama Haque on 1/11/2022.
//

#ifndef EDMONDSKARP_H
#define EDMONDSKARP_H
#include<bits/stdc++.h>
#include<vector>

#define INF 1000000000

using namespace std;
class Graph{

public:
    int teams;
    vector <vector<int>> adjMatrix;
    vector<vector<int>> resMatrix;
    //vector<vector<int>> flowMatrix;
    vector<vector<int>> edges;

public:
    Graph(int t){
        teams = t;
        adjMatrix.assign(t, vector<int>()) ;
        resMatrix.assign(t, vector<int>(t)) ;
    }
    void addEdge(int source, int destination, int capacity){
        adjMatrix[source].push_back(destination);
        //cout << "hehe" <<endl;
        resMatrix[source][destination] = capacity;
    }
    int bfsFlow(int source, int sink, vector<int> & parent ){
        fill(parent.begin(),parent.end(), -1);

        parent[source] = -2;
        queue<pair<int,int>> qOfTeams;
        qOfTeams.push({source,INF});
        //cout << "hehe" <<endl;

        while(!qOfTeams.empty()){
            //cout << "hehe" <<endl;
            int currentNode = qOfTeams.front().first;
            int flowToTheNode = qOfTeams.front().second;

            qOfTeams.pop();
            for(int child: adjMatrix[currentNode]){

                if(parent[child] == -1  &&  resMatrix[currentNode][child]){

                    parent[child] = currentNode;
                    int currentFlow = min(flowToTheNode, resMatrix[currentNode][child]);
                    if(child == sink){
                        //cout << currentFlow<<endl;
                        return currentFlow;
                    }

                    qOfTeams.push({child,currentFlow});
                }
            }
            //cout << "hehe " <<currentNode << endl;
        }
        //cout << "hehe" <<endl;
        return 0;
    }
    int MaxFlowEdmondKarp(int source, int sink){
        int maxflow = 0;
        int flow;
        vector<int> parents(teams);
        //printResMAtrix();

        while(flow = bfsFlow(source,sink, parents)){

            maxflow += flow;
            int currentNode = sink;
            //while(parents[currentNode]){
                while(currentNode!=source){
                //cout << "hehe" <<endl;
                int parentOfCurrent = parents[currentNode];
                resMatrix[parentOfCurrent][currentNode] -= flow;
                resMatrix[currentNode][parentOfCurrent] += flow;
                currentNode = parentOfCurrent;
            }

        //printResMAtrix();
        }

        return maxflow;
    }
    void printResMAtrix(){
        for(int i =0; i<teams; i++){
            for(int j=0;j<teams; j++){
                if(resMatrix[i][j]==INF)
                    cout << "-1  ";
                else
                cout << resMatrix[i][j] <<"   ";
            }
            cout<< endl;
        }
        cout<<endl;
    }

};

#endif //HEAPS_OFFLINE_EDMONDSKARP_H
