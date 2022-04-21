#include<bits/stdc++.h>
#include "avlTree.h"

using namespace std;

int main (){
    avlTreeNode *root = nullptr;
    ifstream myfile;
    myfile.open("avlInput.txt");
    
    while(true){
        //cout << "inside loop"<< endl;
        char command;
        int insertedKey;
        myfile >> command >> insertedKey;
        if(command == 'I'){
            root = insertKey(root,insertedKey);
            printTree(root);
            cout<< "\n";
            // cout<<"heights:";
            // printTreeHeights(root);
            // cout << "\n";
        }
        else if(command == 'D'){
            root = deleteKey(root,insertedKey);
            cout << "after delete" <<endl;
            printTree(root);
            cout<< "\n";
        }
        else if(command == 'F'){
            avlTreeNode *temp = root;
            temp = findKey(temp,insertedKey);
            if(temp == nullptr)
                cout<< "False\n";
            else
                cout<< "True\n";
        }

        if(myfile.eof())
            break;

    }
    
    // root = insertKey(root, 10);
    // printTree(root); cout << endl;
    // root = insertKey(root, 20);
    // printTree(root);cout << endl;
    // root = insertKey(root, 30);
    // printTree(root);cout << endl;
    // root = insertKey(root, 40);
    // printTree(root);cout << endl;
    // root = insertKey(root, 50);
    // printTree(root);cout << endl;
    // root = insertKey(root, 25);

    // printTree(root);cout << endl;

    // cout << "balance is" << balanceStatus(root) << endl;

    return 0;
}