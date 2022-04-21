#include<bits/stdc++.h>
#include<math.h>


using namespace std;

class HeapNode{
    public:
    int key,degree;
    HeapNode *parent;
    HeapNode *leftChild;
    HeapNode *sibling;
    public:

    HeapNode(int newKey){
        key = newKey;
        degree = 0;
        leftChild = nullptr;
        sibling = nullptr;
        parent = nullptr;
        }
    };
    
  
    void printBinomialTree(HeapNode* h,int max){


        while(h){
            cout << "Level " << max - h->degree << " : " << h->key;
            if(h->sibling != nullptr)
            cout << " " << h->sibling ->key ;
            cout<<endl;

            printBinomialTree(h->leftChild,max);
            h=h->sibling;
        }
        // int i = 0;
        // vector<vector<int>> levelOrders;
        // while(h){
        //     //levelOrders[i].push_back(h->key);
        //     //HeapNode* h2 = h;
        //     // while(h2->sibling!=nullptr){
        //     //     levelOrders[i].push_back(h2->sibling->key);
        //     //     h2=h2->sibling;
        //     // }
        //     //cout << "Level " << max - h->degree << " : " << h->key;
        //     // if(h->sibling != nullptr)
        //     // cout << " sibling is " << h->sibling ->key ;
        //     // cout<<endl;
        //     printBinomialTree(h->leftChild,max+1);
        //     h = h->sibling;
        //     //printBinomialTree(h->leftChild->sibling,max);
        //     i++;
        // }
        // //cout<<"yes";
        // for(int i=0; i<levelOrders.size();i++){
        //     for(int j=0;j<levelOrders[i].size();j++){
        //         cout << "Level " << i << " : " << levelOrders[i].size() <<" ";
        //     }
        //     cout<<endl;
        // }
        // int i =0;
        // int maxL =0;
        // queue<pair< int,HeapNode*>> q;
        // vector<int>  adj[100];
        
        // q.push({0,h});
        // while(!q.empty()){
        //     auto popped = q.front();
            

        //     q.pop();
        //     HeapNode* popNode = popped.second;
        //     int level = popped.first;
        //     maxL = std::max(maxL,level);
        //     adj[level].push_back(popNode->key);


        //     //cout << "Level " << level << " : " << popNode->key;
        //     // if(h->sibling != nullptr)
        //     // cout << " sibling is " << h->sibling ->key ;
        //     // cout<<endl;
        //     if(popNode->leftChild!=nullptr)
        //         q.push({level+1,popNode->leftChild});
        //     if(popNode->leftChild->sibling!=nullptr)
        //         q.push({level+1,popNode->leftChild->sibling});
            
            
        // }
        // for(int i =0; i<maxL; i++){
        //     cout<< "Level " << i <<  " : ";
        //     for(auto j:adj[i])
        //         cout<< j << " ";
        //     cout << "\n";
        // }

    }

    void Print(list<HeapNode*> heap){
        cout << "Printing Binomial Heap...\n" <<
        "--------------------------" <<endl;

        list<HeapNode*> ::iterator i = heap.begin();
        int j = 1;
        while(i != heap.end()){
            cout << "Binomial Tree, B" << j << endl;
            printBinomialTree(*i, (*i)->degree);
            i++;
            j++;
        }
        cout<<"---------------------------" <<endl;
    }



    void printTree(HeapNode *h)
    {
    while (h)
    {
        cout << h->key << " ";
        printTree(h->leftChild);
        h = h->sibling;
    }
    cout << ",";
}
  
    // print function for binomial heap
    void printHeap(list<HeapNode*> _heap)
    {
    list<HeapNode*> ::iterator it;
    it = _heap.begin();
    while (it != _heap.end())
    {
        printTree(*it);
        it++;
    }

    cout<<"\n";
    }


    list<HeapNode*> unionHeaps(list<HeapNode*> h1, list<HeapNode*> h2){
        list<HeapNode*> temp;
     
        list<HeapNode*>::iterator i1 = h1.begin();
        list<HeapNode*>::iterator i2 = h2.begin();
        while(i1!=h1.end() && i2!=h2.end()){
            if((*i1)->degree <= (*i2)->degree){
                temp.push_back(*i1);
                i1++;
            }
            else{
                temp.push_back(*i2);
                i2++;
            }
            
        }

        while(i1!=h1.end()){
            temp.push_back(*i1);
            i1++;
        }
        while(i2!=h2.end()){
            temp.push_back(*i2);
            i2++;
        }
        
        //cout << "after union :";
        //printHeap(temp);
        return temp;
    }

    HeapNode* merge(HeapNode* n1, HeapNode* n2){
        if(n1->key < n2->key)
            swap(n1,n2);
        n2->parent = n1;
        n2 -> sibling = n1-> leftChild;
        n1-> leftChild = n2;
        n1->degree++;

        return n1;
    }
    list<HeapNode*> maintainProperty(list<HeapNode*> temp){
        list<HeapNode*> finalHeap;
        if(temp.size()<=1)
            return temp;
        list<HeapNode*>::iterator j1,j2,j3;
        j1 = j2 = j3 = temp.begin();
        //j2++;
        if(temp.size() == 2){
            j2 = j1;
            j2++;
            j3 = temp.end();
        }
            
        else{
            j2++;
            j3 = j2;
            j3++;
        }
        //cout << "list size is " << temp.size() << endl;
        int count = 0;
        while(j1 != temp.end()){
            // count++;
            // if(count == 50)
            // break;
            // cout << "now iterating for " << (*j1) ->key <<endl;
            if(j2 == temp.end()){
                finalHeap.push_back(*j1);
                j1++;
            }

            else if((*j1)->degree < (*j2)->degree){
                finalHeap.push_back(*j1);
                j1++;
                j2++;
                if(j3 != temp.end())
                    j3++;
            }
            else{
                if(j3 != temp.end()&& (*j1) -> degree == (*j2)->degree && (*j1) -> degree == (*j3)->degree){
                    finalHeap.push_back(*j1);
                    j1++;
                    j2++;
                    j3++;
                }
                else if((*j1) -> degree == (*j2)->degree){
                    //cout << "same degree found " << (*j1)->key << " and " << (*j2)->key <<endl;
                    *j1 = merge(*j1,*j2);
                    j2 = temp.erase(j2);
                    if(j3 != temp.end())
                        j3++;
                }


            }
            //cout << "after adjust :";
            //printHeap(temp);
            
        }
        return temp;
    }

    list<HeapNode*> insertKey(list<HeapNode*> existingHeap , int newKey){
        list<HeapNode*> temp;
        HeapNode *newNode= new HeapNode(newKey);
        //cout<< "new node added " << newNode->key << endl;
        temp.push_back(newNode);
        temp = unionHeaps(existingHeap, temp);
        temp = maintainProperty(temp);
        cout << "Inserted " << newKey << endl;
        return temp;
    }
    list<HeapNode*> RemoveMax(HeapNode *h){
        list<HeapNode*> heap;
        HeapNode *temp = h->leftChild;
        HeapNode *n;
  
        while (temp) {
        n = temp;
        temp = temp->sibling;
        n->sibling = NULL;
        heap.push_front(n);
        }
        return heap;
    }

    HeapNode* findMax(list<HeapNode*> h){
    list<HeapNode*>::iterator i = h.begin();
    HeapNode *temp = *i;
    while (i!=h.end())
    {
        if ((*i)->key > temp->key)
            temp = *i;
        i++;
    }
    return temp;
}
  
    list<HeapNode*> extractMax(list<HeapNode*> h){
    list<HeapNode*> finalHeap,n;
    HeapNode *temp;
    temp = findMax(h);
    cout << "ExtractMax returned " << temp->key <<endl;
    list<HeapNode*>::iterator i = h.begin();
    while (i != h.end())
    {
        if (*i!= temp){
            finalHeap.push_back(*i);
        }
        i++;
    }
    n = RemoveMax(temp);
    finalHeap = unionHeaps(finalHeap,n);
    finalHeap = maintainProperty(finalHeap);
    return finalHeap;
}

    HeapNode* findKey(HeapNode* h,int key, int newKey){
        while(h){
            if(h->key == key){
            h->key = newKey;
            cout<< "Increased " << key <<".The updated value is "<< newKey <<"."<<endl;
            return h;
        }
            
        
        else return findKey(h->leftChild,key,newKey);
            h = h->sibling;
        }
        return nullptr;
        }
    list<HeapNode*> findRoot(list<HeapNode*> heap, int key, int newKey){
        list<HeapNode*> ::iterator i = heap.begin();
        int j = 1;
        HeapNode* temp;
        while(i != heap.end()){
            if(temp = findKey(*i,key,newKey))
                //return temp;
                break;
            i++;
            j++;
        }
        //cout << "temp is " << temp->key << endl;
        HeapNode* current;
        current = temp;
        while(current->parent!= nullptr){
            if(current->parent->key < current->key){
                int temp2 = current->parent->key;
                current->parent->key = current ->key;
                current->key = temp2;
                
            }
            current = current->parent;

        }

    return heap;   
    }
    

    // list<HeapNode*> removeMax(HeapNode* h){
    //     list<HeapNode*> finalHeap;
    //     HeapNode *temp = h->leftChild;
    //     HeapNode *n;

    //     while(temp){
    //         n = temp;
    //         temp = temp->sibling;
    //         n->sibling = nullptr;
    //         finalHeap.push_back(n);
    //     }
    //     return finalHeap;

    // }
    // HeapNode* findMax(list<HeapNode*> h){
    //     list<HeapNode*>::iterator i = h.begin();
    //     HeapNode* temp = *i;
    //     while(i != h.end()){
    //         if((*i)->key > temp->key)
    //             temp = *i;
    //         i++;
    //     }
    //     return temp;
    // }



    // list<HeapNode*> extractMax(list<HeapNode*> h){
    //     list<HeapNode*> finalHeap;
    //     list<HeapNode*> n;
    //     HeapNode* temp;
    //     temp = findMax(h);
    //     list<HeapNode*>:: iterator i = h.begin();
    //     while(i != h.end()){
    //         if(*i != temp){
    //             finalHeap.push_back(*i);
    //         }
    //         i++;
    //     }

    //     n = removeMax(temp);
    //     finalHeap = unionHeaps(finalHeap,n);
    //     finalHeap = maintainProperty(finalHeap);
    //     return finalHeap;

    // }

    // vector<HeapNode*> saving(list<HeapNode*> h){
    //     list<HeapNode*> finalHeap;
    //     list<HeapNode*> n;
    //     HeapNode* temp;
    //     temp = findMax(h);

    // }

   





