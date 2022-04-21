#include <bits/stdc++.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include "random.h"
#include "hashTable.h"
using namespace std;

int main()
{
    //string Str = getRandomStr();
    int n;
    cin >> n;

    myHashTable h1(n);
    map<string, int> exists;

    string str[10000];
    srand(time(0));
    int k = 0;
    while(1){
        string s;     
		for(int j = 0; j < 7; j++) {
			char ch = (rand() % 26 + 'a');
			s += ch;
		}
        
		if(exists[s]) 
            continue;
        str[k] = s;
		k++;    
        h1.insertValue(s,k);
        if(k == 10000) break;
    }


    float doubleProbe1=0;
    float doubleProbe2 = 0;
    float chainProbe = 0;
    float chainProbe2 = 0;
    float customProbe1 = 0;
    float customProbe2 = 0;

    for(int i = 0; i<1000; i++) {
        int idx = rand() % 10000;
        //cout << str[idx] << endl;
        chainProbe += h1.searchChain1(str[idx]);
        chainProbe2 += h1.searchChain2(str[idx]);
        doubleProbe1 += h1.searchDouble1(str[idx]);
        doubleProbe2 += h1.searchDouble2(str[idx]);
        customProbe1 += h1.searchCustom1(str[idx]);
        customProbe2 += h1.searchCustom2(str[idx]);
	}
    chainProbe = (float)(chainProbe/1000);
    chainProbe2 = (float)(chainProbe2/1000);
    doubleProbe1 = (float)(doubleProbe1/1000);
    doubleProbe2 = (float)(doubleProbe2/1000);
    customProbe1 = (float)(customProbe1/1000);
    customProbe2 = (float)(customProbe2/1000);

    // h1.insertValue("ancient",1);
    // h1.insertValue("puzzled",2);
    // h1.insertValue("benefit",3);
    // h1.insertValue("ancient",4);
    // h1.insertValue("zigzags",5);

    //cout << "yes" <<endl;
    //h1.printTable();
    cout<< left<< setw(36)<< ""<< left<< setw(38)<< "Hash1"<< left<< setw(38)<< "Hash2"<<endl;
    cout<< left<< setw(18)<< ""<< left << setw(22)<< "Number of Collisions"<< left<< setw(18)<< "Average probes"<< left<< setw(22)<< "Number of Collisions"<< left<< setw(16)<< "Average probes"<< left<< endl;
    cout<< left<< setw(18)<< "Chaining Method"<< left<< setw(22)<< h1.getChainCollisions1()<< left<< setw(18)<< chainProbe<< left<< setw(22)<< h1.getChainCollisions2()<< left<< setw(16)<< chainProbe2<< left<< endl;
    cout<< left<< setw(18)<< "Double Hashing"<< left<< setw(22)<< h1.getDoubleCollisions1()<< left<< setw(18)<< doubleProbe1<< left<< setw(22)<< h1.getDoubleCollisions2()<< left<< setw(16)<< doubleProbe2<< left<< endl;
    cout<< left<< setw(18)<< "Custom Probing"<< left<< setw(22)<< h1.getCustomCollisions1()<< left<< setw(18)<< customProbe1<< left<< setw(22)<< h1.getCustomCollisions2()<< left<< setw(16)<< customProbe2<< left<< endl;

    return 0;
}