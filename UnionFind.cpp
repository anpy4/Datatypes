//
// Created by schiefer on 16/03/2020.
//

#include <iostream>
#include "Interfaces.h"

/*
 *
namespace UnionFinds
{

    template <class T>
    UnionFind<T>::UnionFind(int sz)
    {
        this->size = sz;
        for (int i=0; i<sz ; i++)
        {
            this->component_size[i] = 1;
            this->nodes[i] = i;
        }
    }

    template <class T>
    void UnionFind<T>::unify(int idx1, int idx2)
    {

        int root1 = find(idx1);
        int root2 = find(idx2);
        if (root1 == root2)
        {
            std::cout << "Passed Nodes are already connected!" << std::endl;
        }
        else
        {
            int component_size1 = this->component_size[root1];
            int component_size2 = this->component_size[root2];

            if (component_size1 >= component_size2) {
                this->nodes[root2] = root1;
                this->component_size[root1] += this->component_size[root2];
            }
            else
            {
                this->nodes[root1] = root2;
                this->component_size[root2] += this->component_size[root1];
            }
            this->num_components--;
        }

    }

    template <class T>
    int UnionFind<T>::find(int idx)
    {
        // works for both, with or without path compression
        while(idx != this->nodes[idx])
        {
            idx = nodes[idx];
        }
        return idx;
    }


    template <class T>
    int UnionFind<T>::get_component_size(int idx)
    {
        return this->component_size[this->find(idx)];
    }


    template <class T>
    bool UnionFind<T>::check_if_connected(int idx1, int idx2)
    {
        return find(idx1) == find(idx2);
    }


    template <class T>
    void UnionFind<T>::count_components()
    {
        std::cout << "Number of distinct components: " << this->num_components << std::endl;
    }


}


*/