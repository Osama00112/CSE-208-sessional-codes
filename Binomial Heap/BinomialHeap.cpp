#include<bits/stdc++.h>
#include "BHeap.h"

using namespace std;


int main(){
    list<HeapNode*> binomialHeap;
    ifstream myfile;
    myfile.open("input.txt");

    
    string str;
    while(1){
        int a,b;
        myfile >> str;
        if(str == "INS"){
            myfile >> a;
            binomialHeap = insertKey(binomialHeap,a);
        }
        else if(str == "PRI")
            Print(binomialHeap);
        else if(str == "INC"){
            myfile >> a >> b;
            binomialHeap = findRoot(binomialHeap,a,b);
        }
        else if(str == "FIN"){
            HeapNode *temp = findMax(binomialHeap);
            cout << "FindMax returned "<< temp->key << "\n";
        }
        else if(str == "EXT"){
            binomialHeap = extractMax(binomialHeap);
        }
        else
            return 0;
    }
    // int ch,key;
    
  
    // // Insert data in the heap
    // binomialHeap = insertKey(binomialHeap,7);
    // binomialHeap = insertKey(binomialHeap,12);
    // binomialHeap = insertKey(binomialHeap,19);
    // binomialHeap = insertKey(binomialHeap,5);
    // binomialHeap = insertKey(binomialHeap,16);
    // binomialHeap = insertKey(binomialHeap,6);
  
    // //cout << "Heap elements after insertion:\n";
    // Print(binomialHeap);
    // //printHeap(_heap);
  
    // HeapNode *temp = findMax(binomialHeap);
    // cout << "FindMax returned "
    //      << temp->key << "\n";
    // HeapNode* temp1;
    // binomialHeap = findRoot(binomialHeap,7,27);
    // //cout << temp->key << " is found" << endl;
    // Print(binomialHeap);
    // // Delete minimum element of heap
    // binomialHeap = extractMax(binomialHeap);
    // //cout << "Heap after deletion of maximum element\n";
    // Print(binomialHeap);
    
    // //printHeap(binomialHeap);
    
  
    // return 0;


}