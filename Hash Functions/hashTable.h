#include <bits/stdc++.h>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

class myHashTable{
    public:
    int tableSize;
    int order;
    int chainCollision1,chainCollision2, doubleCollision1,doubleCollision2,customCollision1, customCollision2;
    vector<pair<string,int>> *tableList1; 
    vector<pair<string,int>> *tableList2; 
    vector<pair<string,int>> *doubleHashTable1; 
    vector<pair<string,int>> *doubleHashTable2; 
    vector<pair<string,int>> *customHashTable1;
    vector<pair<string,int>> *customHashTable2;
    //vector<unsigned char *> *table;

    public:
    myHashTable(int size){
        tableSize = size;
        order = 0;
        chainCollision1 = 0;
        chainCollision2 = 0;
        doubleCollision1 = 0;
        doubleCollision2 = 0;
        customCollision1 = 0;
        customCollision2 = 0;

        tableList1 = new vector<pair<string,int>>[size];
        tableList2 = new vector<pair<string,int>>[size];
        doubleHashTable1 = new vector<pair<string,int>>[size];
        doubleHashTable2 = new vector<pair<string,int>>[size];
        customHashTable1 = new vector<pair<string,int>>[size];
        customHashTable2 = new vector<pair<string,int>>[size];
        
    }

    void insertValue(string str, int key){
        order ++;
        int hashIndex1 = hash1(str) % tableSize;
        int hashIndex2 = hash2(str) % tableSize;

        //cout << str << " ->" <<  hashIndex <<endl;
        if(tableList1[hashIndex1].size() > 0){
            
            seperateChain1(hashIndex1,str,order);            
        } else
            tableList1[hashIndex1].push_back({str,order});


        if(tableList2[hashIndex2].size() > 0 ){
            
            seperateChain2(hashIndex2,str,order);
        }else
            tableList2[hashIndex2].push_back({str,order});

        //cout<< "done chain" <<endl;

        if(doubleHashTable1[hashIndex1].size() > 0){
            
            doubleHashing1(hashIndex1,str,order);            
        }else
            doubleHashTable1[hashIndex1].push_back({str,order});
        
        if(doubleHashTable2[hashIndex2].size() > 0){
            
            doubleHashing2(hashIndex2,str,order);
        }else           
            doubleHashTable2[hashIndex2].push_back({str,order});

        //cout<< "done double" <<endl;

        if(customHashTable1[hashIndex1].size() > 0){
            
            customHashing1(hashIndex1,str,order);            
        }else
            customHashTable1[hashIndex1].push_back({str,order});
        
        if(customHashTable2[hashIndex2].size() > 0){
            
            customHashing2(hashIndex2,str,order);
        }else           
            customHashTable2[hashIndex2].push_back({str,order});
        //table[hashIndex].push_back(str);
        //cout << "done custom " << endl;

    }
    void customHashing1(int hashIndex, string str, int order){
        customCollision1 ++;
        int hashIndex1 = hashIndex;
        int auxhashIndex = auxhash(str) % tableSize;
        int i = 1;
        int c1 = 5;
        int c2 = 7;
        while (1) {
            int customHashIndex = (hashIndex1 + ((i*auxhashIndex*c1)%tableSize) + ((i*i*c2)%tableSize)) % tableSize;
            if (customHashTable1[customHashIndex].size() == 0) {
                customHashTable1[customHashIndex].push_back({str,order});
                break;
            }
            customCollision1 ++;
            i++;
        }

    }
    void customHashing2(int hashIndex, string str, int order){
        customCollision2 ++;
        int hashIndex1 = hashIndex;
        int auxhashIndex = auxhash(str) % tableSize;
        int i = 1;
        int c1 = 5;
        int c2 = 7;
        while (1) {
            int customHashIndex = (hashIndex1 + ((i*auxhashIndex*c1)%tableSize) + ((i*i*c2)%tableSize)) % tableSize;
            if (customHashTable2[customHashIndex].size() == 0) {
                customHashTable2[customHashIndex].push_back({str,order});
                break;
            }
            customCollision2 ++;
            i++;
        }
    }

    void doubleHashing1(int hashIndex, string str, int order){
        doubleCollision1 ++;
        int hashIndex1 = hashIndex;
        int auxhashIndex = auxhash(str) % tableSize;
        int i = 1;
        while (1) {
            int doubleHashIndex = (hashIndex1 + ((i * auxhashIndex)%tableSize)) % tableSize;
            if (doubleHashTable1[doubleHashIndex].size() == 0) {
                doubleHashTable1[doubleHashIndex].push_back({str,order});
                break;
            }
            doubleCollision1 ++;
            i++;
        }
        //int doubleHashIndex = (hashIndex1 + i*hashIndex2); 
    }
    void doubleHashing2(int hashIndex, string str, int order){
        doubleCollision2 ++;
        int hashIndex1 = hashIndex;
        int auxhashIndex = auxhash(str) % tableSize;
        int i = 1;
        while (1) {
            int doubleHashIndex = (hashIndex1 + ((i * auxhashIndex)%tableSize)) % tableSize;
            if (doubleHashTable2[doubleHashIndex].size() == 0) {
                doubleHashTable2[doubleHashIndex].push_back({str,order});
                break;
            }
            doubleCollision2 ++;
            i++;
        }
        //int doubleHashIndex = (hashIndex1 + i*hashIndex2); 
    }

    void seperateChain1(int hashIndex, string str, int order){
        chainCollision1 ++;
            //order --;
        //auto k = tableList1[hashIndex].front();
        // if(k.first == str)
        //     tableList1[hashIndex].push_back({str,k.second});
        // else
            tableList1[hashIndex].push_back({str,order});

    }
    void seperateChain2(int hashIndex, string str, int order){
        chainCollision2 ++;
            //order --;
        //auto k = tableList2[hashIndex].front();
        // if(k.first == str)
        //     tableList2[hashIndex].push_back({str,k.second});
        // else
            tableList2[hashIndex].push_back({str,order});

    }
    
    void deleteValue(int key){

    }

    int searchDouble1(string const & str){
        int index1 = hash1(str) %tableSize;
        int index2 = auxhash(str) % tableSize;
        int i = 0;
        while (doubleHashTable1[(index1 + i * index2) % tableSize].front().first != str) {
            // if (doubleHashTable1[(index1 + i * index2) % tableSize].size() == 0) {
            //     cout << str << " does not exist" << endl;
            //     return;
            // }
            i++;
        }
        //cout << str << " found" << endl;
        return i+1;
    }
    int searchDouble2(string const & str){
        int index1 = hash2(str) %tableSize;
        int index2 = auxhash(str) % tableSize;
        int i = 0;
        while (doubleHashTable2[(index1 + i * index2) % tableSize].front().first != str) {
            // if (doubleHashTable1[(index1 + i * index2) % tableSize].size() == 0) {
            //     cout << str << " does not exist" << endl;
            //     return;
            // }
            i++;
        }
        //cout << str << " found" << endl;
        return i+1;
    }
    int searchChain1(string const & str){
        int index1 = hash1(str) %tableSize;
        int count = 1;
        for(auto it = begin (tableList1[index1]); it != end (tableList1[index1]); ++it){
            if(it->first == str)
                break;
            count ++;
        }

        return count;
        //auto k = tableList1[index1];
        
    }
    int searchChain2(string const & str){
        int index1 = hash2(str) %tableSize;
        int count = 1;
        for(auto it = begin (tableList1[index1]); it != end (tableList1[index1]); ++it){
            if(it->first == str)
                break;
            count ++;
        }

        return count;
        //auto k = tableList1[index1];
        
    }
    int searchCustom1(string const & str){
        int index1 = hash1(str) %tableSize;
        int index2 = auxhash(str) % tableSize;
        int i = 0;
        int c1 = 5;
        int c2 = 7;
        while (customHashTable1[(index1 + ((i*index2*c1)%tableSize) + ((i*i*c2)%tableSize)) % tableSize].front().first != str) {
            i++;
        }
        //cout << str << " found" << endl;
        return i+1;

    }
    int searchCustom2(string const & str){
        int index1 = hash2(str) %tableSize;
        int index2 = auxhash(str) % tableSize;
        int i = 0;
        int c1 = 5;
        int c2 = 7;
        while (customHashTable2[(index1 + ((i*index2*c1)%tableSize) + ((i*i*c2)%tableSize)) % tableSize].front().first != str) {
            // if (doubleHashTable1[(index1 + i * index2) % tableSize].size() == 0) {
            //     cout << str << " does not exist" << endl;
            //     return;
            // }
            i++;
        }
        //cout << str << " found" << endl;
        return i+1;

    }

    unsigned int auxhash(string const & str){
        unsigned int hash = 0;
	    int c;
        int i =0;
	    while (c = str[i++])
	        hash += c;

	    return hash;
    }
    unsigned long hash2(string const & str){
        unsigned long hash = 0;
        int c;

        int i = 0;

        while (c = str[i++])
            hash = c + (hash << 6) + (hash << 16) - hash;

        return hash;

    }
    unsigned long hash1(string const & str)
    {
        unsigned long hash = 5381;
        int c;
        int i = 0;

        while (c =  str[i++])
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

        return hash;
    }

    void printTable(){
       for (int i = 0; i < tableSize; i++) {
        cout << i;
        for (auto x : tableList1[i])
            cout << "(" <<  x.first << " , " << x.second << ")";
        cout << endl;
        }
    }
    int getChainCollisions1(){
        return chainCollision1;
    }
    int getChainCollisions2(){
        return chainCollision2;
    }
    int getDoubleCollisions1(){
        return doubleCollision1;
    }
    int getDoubleCollisions2(){
        return doubleCollision2;
    }
    int getCustomCollisions1(){
        return customCollision1;
    }
    int getCustomCollisions2(){
        return customCollision2;
    }

    int avgDoubleProbe1(){
        
    }
};