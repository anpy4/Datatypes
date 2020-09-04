//
// Created by schiefer on 17/02/2020.
//


#include <math.h>
#include <iostream>
#include "Interfaces.h"

namespace Arrays{

    template <class T>
    void DynamicArray<T>::init_array(T _array[], int len)
    {

        // get initialization size
        //int const init_len = sizeof(_array) / sizeof(_array[0]);
        int const init_len = len;
        // take only 2^k sized array
        int const init_exponent = log2(double(init_len)) + 1;
        // parse to int
        int const init_size = pow(2.0, init_exponent);

        this->array  = new T[init_size];

        for (int i=0; i<init_size; i++)
        {
            this->array[i] = _array[i];
        }
        this->element_counter = init_len;
        this->size_counter = init_size;

    }

    template <class T>
    void DynamicArray<T>::double_size() {
        int new_size = get_array_size() * 2;
        T *array_tmp;
        array_tmp = new T[new_size];
        for (int i = 0; i < get_array_size(); i++) {
            array_tmp[i] = this->array[i];
        }
        for (int i = get_array_size(); i<new_size; i++)
        {
            array_tmp[i] = 0;
        }
        this->array = array_tmp;
        delete [] array_tmp;
        this->size_counter *= 2;
    }

    template <class T>
    void DynamicArray<T>::rearange(int pos)
    {

        T *array_tmp;
        array_tmp = new T[get_array_size()];
        for (int i=0; i<pos; i++)
        {
            array_tmp[i] = this->array[i];
        }
        for (int i=pos; i<get_array_size(); i++)
        {
            array_tmp[i+1] = this->array[i];
        }
        this->array = array_tmp;
        delete [] array_tmp;
    }



    template <class T>
    DynamicArray<T>::DynamicArray(T _array[], int len)
    {
        init_array(_array, len);
    }


    template <class T>
    void DynamicArray<T>::get_array()
    {
        for (int i=0; i<get_array_size(); i++)
        {
            std::cout << this->array[i] << " ";
        }
        std::cout << "" << std::endl;
    }

    template <class T>
    int DynamicArray<T>::get_array_size()
    {
        return this->size_counter;
    }

    template <class T>
    int DynamicArray<T>::get_num_elements()
    {
        return element_counter;
    }

    template <class T>
    void DynamicArray<T>::append(T element)
    {
        if (get_array_size() == get_num_elements()) {
            double_size();
        }

        this->array[get_num_elements()] = element;
        element_counter++;
    }

    template <class T>
    void DynamicArray<T>::insert(T element, int position)
    {
        while(get_array_size() <= position)
        {
            std::cout << get_array_size() << " <= " << position << std::endl;
            double_size();
        };
        std::cout << get_array_size() << std::endl;

        if (get_array_size() == get_num_elements()) {
            double_size();
        }
        rearange(position);
        this->array[position] = element;
        element_counter++;
    }

}


