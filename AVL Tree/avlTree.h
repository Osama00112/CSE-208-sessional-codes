#include<bits/stdc++.h>
using namespace std;

class avlTreeNode{

    public:
    int key;
    int height;
    avlTreeNode *leftChild;
    avlTreeNode *rightChild;
    
};
avlTreeNode* newNode(int k){
    avlTreeNode *tempNode = new avlTreeNode();
    tempNode->key = k;
    tempNode->height = 1;
    tempNode->leftChild = nullptr;
    tempNode->rightChild = nullptr;
    return tempNode;
}

void printTree(avlTreeNode *root){
    if(root == nullptr)
        return;
    cout<< root->key;
    //cout << "afsd" << " sdfa" << endl;
    if(root->leftChild != nullptr || root->rightChild != nullptr){
    cout<< "(";
    printTree(root->leftChild);
    cout << ")(" ;
    printTree(root->rightChild);
    cout << ")";
    }
}
void printTreeHeights(avlTreeNode *root){
    if(root == nullptr)
        cout<< "0";
    cout<< root->height;
    //cout << "afsd" << " sdfa" << endl;
    if(root->leftChild != nullptr || root->rightChild != nullptr){
        cout<< "(";
        printTreeHeights(root->leftChild);
        cout << ")(" ;
        printTreeHeights(root->rightChild);
        cout << ")";
    }
    
}


int getMax(int a, int b){ return (a>b)?a:b;}

int getHeight(avlTreeNode *root){
    if(root == nullptr)
        return 0;
    return root->height;
}

int balanceStatus(avlTreeNode *root){
    if(root == nullptr)
       return 0;
    else return getHeight(root->leftChild) - getHeight(root->rightChild);
}

avlTreeNode* singleRotateLeft(avlTreeNode* z){
    avlTreeNode *y = z->rightChild;
    avlTreeNode *x = y->leftChild;
    //cout<< y->key << " and " << y->height <<endl;
    y->leftChild = z;
    z->rightChild = x;

    z->height = 1 + getMax(getHeight(z->leftChild),getHeight(z->rightChild));
    y->height = 1 + getMax(getHeight(y->leftChild),getHeight(y->rightChild));
    
    //cout<< y->key << " and " << y->height <<endl;
    return y;

}

avlTreeNode* singleRotateRight(avlTreeNode* z){
    avlTreeNode *y = z->leftChild;
    avlTreeNode *x = y->rightChild;
    //cout<< "before rotating z,y,x: " << z->key<< "ht:" <<z->height << "," <<y->key<< "ht:" <<y->height <<"," <<x->key<< "ht:" <<x->height << endl ;

    y->rightChild = z;
    z->leftChild = x;

    z->height = 1 + getMax(getHeight(z->leftChild),getHeight(z->rightChild));
    y->height = 1 + getMax(getHeight(y->leftChild),getHeight(y->rightChild));
    
    //cout<< "after rotating y,z,x: " << y->key<< "ht:" <<y->height << "," <<z->key<< "ht:" <<z->height <<"," <<x->key<< "ht:" <<x->height << endl ;
    return y;

}

avlTreeNode* insertKey(avlTreeNode *root,int k){

    

    if(root == nullptr)
        return newNode(k);
    else if (k > root->key){
        root->rightChild =  insertKey(root->rightChild,k);
    }
    else {
        root->leftChild =  insertKey(root->leftChild,k);
    }

    root->height = 1 + getMax(getHeight(root->leftChild),getHeight(root->rightChild));
    int heightDiff = balanceStatus(root);
    //printTree(root); cout<< " = current, heightdiff:" << heightDiff << " root: "<< root->key << " height: "<< root->height <<endl;

    if(heightDiff > 1){
        
        cout << "Height invariant violated.\nAfter rebalancing:";
        if(k < root->leftChild->key){
            //cout << "case:1"<<endl;
            return singleRotateRight(root);
        }
        else{
            //cout << "case:2"<<endl;
            //double rotation
            root->leftChild = singleRotateLeft(root->leftChild);
            return singleRotateRight(root);
        }
    }
    else if (heightDiff < -1){
        cout << "Height invariant violated.\nAfter rebalancing:";
        if(k > root->rightChild->key){
            //cout << "case:3"<<endl;
            return singleRotateLeft(root);
        }
        else{
            //double rotation
            //cout << "case:4"<<endl;
            root->rightChild = singleRotateRight(root->rightChild);
            return singleRotateLeft(root);

        }
    }


    return root;
        
}

avlTreeNode* inOrderPred(avlTreeNode* root){

}

avlTreeNode* findKey(avlTreeNode* root, int key){
    avlTreeNode* temp = root;
    if(temp == nullptr)
        return nullptr;
    if (temp->key == key){
        return temp;
    }
    else if(key < temp->key){
        return findKey(temp->leftChild,key);
    }
    else if(key > temp->key){
        return findKey(temp->rightChild,key);
    }
    else
        return nullptr;
}

avlTreeNode* deleteKey(avlTreeNode* root, int key){
   avlTreeNode* temp;
    if(root == nullptr)
        return nullptr;
    else if(key > root->key){
        root->rightChild = deleteKey(root->rightChild,key);
        //root->height = 1 + getMax(getHeight(root->leftChild),getHeight(root->rightChild));
        
        int heightDiff = balanceStatus(root);
        //printTree(root); cout<< " = current, heightdiff:" << heightDiff << " root: "<< root->key << " height: "<< root->height <<endl;

        if(heightDiff > 1){
            cout << "Height invariant violated.\nAfter rebalancing:";
            //cout << "Height invariant violated.After rebalancing:";
            //double rotation
            //root = singleRotateRight(root);
            //root->leftChild = singleRotateLeft(root->leftChild);
            root = singleRotateRight(root);
        }
        else if (heightDiff < -1){
            cout << "Height invariant violated.\nAfter rebalancing:";
            //cout << "Height invariant violated.After rebalancing:";
            //root = singleRotateLeft(root);
            root->rightChild = singleRotateRight(root->rightChild);
            root = singleRotateLeft(root);
        }
    }
    else if(key < root->key){
        root->leftChild = deleteKey(root->leftChild,key);
        //root->height = 1 + getMax(getHeight(root->leftChild),getHeight(root->rightChild));
        int heightDiff = balanceStatus(root);
        //printTree(root); cout<< " = current, heightdiff:" << heightDiff << " root: "<< root->key << " height: "<< root->height <<endl;

        if(heightDiff > 1){
            cout << "Height invariant violated.\nAfter rebalancing:";
            //root = singleRotateRight(root);
            root->leftChild = singleRotateLeft(root->leftChild);
            root = singleRotateRight(root);
        }
        else if (heightDiff < -1){
            cout << "Height invariant violated.\nAfter rebalancing:";
            //double rotation
            //root->rightChild = singleRotateRight(root->rightChild);
            root = singleRotateLeft(root);
            //root = singleRotateLeft(root);
        }
    }
    else{
        if(root->rightChild != nullptr){
            //printTree(root); cout<< " = current before deleting when rightchild!=null, heightdiff:" << balanceStatus(root) << " root: "<< root->key << " height: "<< root->height <<endl;
            temp = root->rightChild;
            while(temp->leftChild != nullptr)
                temp = temp->leftChild;
            root->key = temp->key;
            root->rightChild = deleteKey(root->rightChild,temp->key);
            root->height = 1 + getMax(getHeight(root->leftChild),getHeight(root->rightChild));
            int heightDiff = balanceStatus(root);
            //printTree(root); cout<< " = current when rightchild!=null, heightdiff:" << heightDiff << " root: "<< root->key << " height: "<< root->height <<endl;
            if(heightDiff > 1){
                if(balanceStatus(root->leftChild)>=0)
                    root = singleRotateRight(root);
                else{
                    root->leftChild = singleRotateLeft(root->leftChild);
                    root = singleRotateRight(root);
                }
            }
            
        }
        else
            return root->leftChild;
    }
    root->height = 1 + getMax(getHeight(root->leftChild),getHeight(root->rightChild));
    return root;
}


    



