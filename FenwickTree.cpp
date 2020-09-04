//
// Created by LIGHTNING X-TREME on 09.06.2020.
//

#include "Interfaces.h"
#include <iostream>


using namespace std;

namespace Trees{


    template <class T>
    FenwickTree<T>::FenwickTree(int size){

        this->size = size;
        this->ftree = new T[size];

    }

    template <class T>
    int FenwickTree<T>::LSB(int idx) {
        // returns the least significant bit of an bytearray

        int res = 1;
        while(idx % 2 == 0)
        {
            res *= 2;
            idx /= 2;
        }
        return res;
    }

    template <class T>
    int FenwickTree<T>::prefixSum(int idx) {

        int sum = 0;
        do{
            sum = sum + this->ftree[idx];
            idx = idx - this->LSB(idx+1);
        }
        while(idx >= 0);

        return sum;

    }


    template <class T>
    int FenwickTree<T>::LSB_wrapper(int idx) {
        // just to test
        return this->LSB(idx);
    }


    template <class T>
    void FenwickTree<T>::construct(T value_array[])
    {
        // deepcopy
        for (int i=0; i<this->size; i++){
            this->ftree[i] = value_array[i];
        }

        // change array to fenwick tree
        for (int i=0; i<this->size; i++){

            int i_reindexed = i+1; // has to start with 1

            int j = i_reindexed + this->LSB(i_reindexed);
            if (j-1 < this->size){
                this->ftree[j-1] = this->ftree[j-1] + this->ftree[i];
            }
        }
    }



    template <class T>
    void FenwickTree<T>::range_sum(int from_idx, int to_idx) {

        int sum = this->prefixSum(to_idx);

        if (from_idx > 0){
            sum = sum - this->prefixSum(from_idx - 1);
        }

        cout << "Range Sum: " << sum << endl;


    }

    template <class T>
    void FenwickTree<T>::point_update(int idx, T val) {

        T old = this->ftree[idx];
        T diff = val - old;  // all values responsible for "idx" have to be changed by the value "diff"

        while (idx < this->size){

            this->ftree[idx] += diff;
            idx = idx + this->LSB(idx+1);  // LSB(idx+1) because fenwick-tree is typically 1 based array
        }

    }









    template <class T>
    void FenwickTree<T>::print_tree() {

        for (int i=0; i<this->size; i++){
            cout << i << " => " << this->ftree[i] << endl;
        }
    }



}

