//
// Created by schiefer on 06/03/2020.
//

#include <iostream>
#include "Interfaces.h"

namespace Stacks
{

    template <typename T>
    struct Node
    {
        T value;
        Node* predecessor;
    };



    // Constructor
    template <class T>
    Stack<T>::Stack()
    {
        this->size = 0;
        this->top = NULL;
    }



    template <class T>
    void Stack<T>::push(T value)
    {
        Node<T>* node = new Node<T>();
        node->value = value;
        node->predecessor = this->top;
        this->top = node;
        this->size += 1;
    }


    template <class T>
    T Stack<T>::pop()
    {
        Node<T>* node = this->top;
        this->top = node->predecessor;
        this->size += 1;
        node->predecessor = NULL; // not relevant any more
        return node->value;


    }


    template <class T>
    void Stack<T>::peek()
    {
        if (this->size == 0)
        {
            std::cout << "Stack is still empty!" << std::endl;
        }
        else
        {
            std::cout << "Node: " << this->top << "   , Value: " << this->top->value << std::endl;
        }
    }


    template <class T>
    void Stack<T>::get_size()
    {
        std::cout << "Current size: " << this->size << std::endl;
    }



}