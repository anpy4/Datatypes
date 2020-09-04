//
// Created by schiefer on 12/03/2020.
//

#include <iostream>
#include <vector>
#include "Interfaces.h"
#include <cmath>


namespace PriorityQueues
{


    template <class T>
    BinaryPQ<T>::BinaryPQ()
    {
        this->size = 0;
    }

    template <class T>
    void BinaryPQ<T>::swap_nodes(int idx_1, int idx_2)
    {

        if (idx_1 < 0 || idx_1 >= this->size)
        {
            std::cout << "Index 1 out of range!";
        }
        if (idx_2 < 0 || idx_2 >= this->size)
        {
            std::cout << "Index 2 out of range!";
        }


        T& a = this->heap[idx_1];
        T& b = this->heap[idx_2];

        T tmp = a;
        a = b;
        b = tmp;
    }

    template <class T>
    int BinaryPQ<T>::bubble_up(int idx)
    {
        // return idx and compare if it has changed to check for further bubble_up calls
        if (idx == 0)
        {
            return idx;  // already root node
        }

        int parent_idx = (idx - 1) * 0.5;
        if (this->heap[parent_idx] <= this->heap[idx])
        {
            return idx;  // heap invariant satisfied
        } else
        {
            this->swap_nodes(parent_idx, idx);
            return parent_idx;
        }
    }

    template <class T>
    int BinaryPQ<T>::bubble_down(int idx)
   {
       int left_child_idx = idx * 2 + 1;
       int right_child_idx = idx * 2 + 2;

       if (left_child_idx >= this->size)
       {
           return idx;  // idx is already leaf node
       }

       T curr = this->heap[idx];
       T left = this->heap[left_child_idx];
       T right = this->heap[right_child_idx];

       if (curr <= left && curr <= right)
       {
           return idx;  // heap invariant satisfied
       }
       else if (curr > left && curr <= right)
       {
           this->swap_nodes(idx, left_child_idx);
           return left_child_idx;
       }
       else if (curr <= left && curr > right)
       {
           this->swap_nodes(idx, right_child_idx);
           return right_child_idx;
       }
       else
       {
           // swap with smaller child
           if (left <= right)
           {
               swap_nodes(idx, left_child_idx);
               return left_child_idx;
           } else{
               swap_nodes(idx, right_child_idx);
               return right_child_idx;
           };
       }



   }

    template <class T>
    void BinaryPQ<T>::rearange(int idx)
    {
        // restore heap invariant
        int tmp = -1;
        while (tmp != idx)
        {
            tmp = idx;
            idx = bubble_up(idx);  // did it change?
        }

        // same for bubbling down
        tmp = -1;
        while (tmp != idx)
        {
            tmp = idx;
            idx = bubble_down(idx);  // did it change?
        }



    }



    template <class T>
    void BinaryPQ<T>::peek()
    {
        std::cout << "Smallest Element is: " << this->heap[0] << std::endl;
    }

    template <class T>
    void BinaryPQ<T>::contains(T val)
    {
        int idx = -1;
        for (int i=0; i<this->size; i++)
        {
            if (this->heap[i] == val)
            {
                idx = i;
            }
        }

        if (idx == -1)
        {
            std::cout << "PQ does not contain the value:  " << val << std::endl;
        }
        else{
            std::cout << "PQ contains the value:  " << val << " (idx: " << idx << ")" << std::endl;
        }

    }

    template <class T>
    void BinaryPQ<T>::add(T val)
    {
        this->size++;
        this->heap.push_back(val);

        int idx = this->size -1 ;
        this->rearange(idx);

    }

    template <class T>
    void BinaryPQ<T>::poll()
    {
        this->swap_nodes(0, this->size-1);
        this->heap.pop_back();
        this->size--;
        this->rearange(0);
    }

    template <class T>
    void BinaryPQ<T>::remove(T val)
    {
        // find last element with val
        int idx = -1;
        for (int i=0; i<this->size-1; i++)
        {
            if (this->heap[i] == val)
            {
                idx = i;
            }
        }

        if (idx == -1)
        {
            std::cout << "Passed value not found!" << std::endl;
        }
        else
        {
            this->swap_nodes(idx, this->size-1);
            this->heap.pop_back();
            this->size--;
            this->rearange(idx);

            std::cout << "Value found and removed at index: " << idx << std::endl;
        }

    }

    template <class T>
    void BinaryPQ<T>::print_tree()
    {
        int level = 0;
        int level_end_idx = 0;

        for (int i=0; i < this->size; i++){
            std::cout << this->heap[i] << "  ";

            if (i == level_end_idx)
            {
                std::cout << "" << std::endl;
                level++;
                level_end_idx = level_end_idx + std::pow(2, level);
            }

        }
    }

}