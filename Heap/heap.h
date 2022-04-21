//
// Created by OSAMA HAQUE on 4/6/2021.
//
#include<iostream>
#include<vector>
#ifndef HEAPS_OFFLINE_HEAP_H
#define HEAPS_OFFLINE_HEAP_H

#endif
//HEAPS_OFFLINE_HEAP_H

using namespace std;

class Heap{
    int MaxSize;
    int Size;

    int *arr;

public:
    Heap(int maxsize){
        MaxSize = maxsize;
        Size = 0;
        arr = new int [MaxSize];
    }

    void increaseCapacity() {
        int *temp = new int[MaxSize*2];
        for (int i=0; i<Size; i++){
            temp[i] = arr[i];
        }
        arr = temp;
    }

    int leftChildof(int index){
        return 2*index+1;
    }
    int rightChildof(int index){
        return 2*index+2;
    }
    int parentof(int index){
        return (index-1)/2;
    }

    void heapifyUp(int index){
        int i = index;
        while(i!=0 && arr[parentof(i)] < arr[i]){
            swap(parentof(i),i);
            i = parentof(i);
        }

    }

    void heapifyDown(int rootindex){
        int largest = rootindex;
        int left = leftChildof(rootindex);
        int right = rightChildof(rootindex);

        if (left < Size && arr[left] > arr[rootindex])
            largest = left;
        if (right < Size && arr[right] > arr[rootindex])
            largest = right;
        if (largest != rootindex){
            swap(rootindex,largest);
            heapifyDown(largest);
        }

    }

    void swap(int index1, int index2){
        int temp;
        temp = arr [index1];
        arr[index1] = arr[index2];
        arr[index2] = temp;

    }



    void insert(int i) {
        if (Size == MaxSize){
            cout << "oveflow" << endl;
            increaseCapacity();
        }
        arr[Size] = i;
        Size ++;
        heapifyUp(Size-1);
    }
    int size(){
        return  Size;
    }

    int getMax(){
        if(Size == 0)
            exit(0);
        else
        return arr[0];
    }

    void deleteKey() {
        int temp;
        temp = arr[0];
        arr[0] = arr[Size-1];
        Size--;
        heapifyDown(0);


    }
};
void heapify(vector<int> &v, int heapsize, int rootindex){
    int largestElementIndex = rootindex;
    int left = 2*rootindex +1;
    int right = 2*rootindex + 2;

    if (left<heapsize && v[left] > v[largestElementIndex] )
        largestElementIndex = left;
    if (right<heapsize && v[right]> v[largestElementIndex])
        largestElementIndex = right;
    if(largestElementIndex != rootindex){
        int temp;
        temp = v[rootindex];
        v[rootindex] = v[largestElementIndex];
        v[largestElementIndex] = temp;
        heapify(v,heapsize,largestElementIndex);
    }

}
void heapsort(vector<int> &v) {
    int vectorsize = v.size();
    for (int i = (vectorsize/2)-1; i>=0; i--)
        heapify(v,vectorsize,i);

    for (int i = vectorsize - 1; i>=0; i--){
        int temp;
        temp = v[0];
        v[0] = v[i];
        v[i] = temp;
        heapify(v,i,0);
    }

}

