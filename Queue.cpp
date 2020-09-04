//
// Created by schiefer on 09/03/2020.
//
#include <iostream>
#include "Interfaces.h"

namespace Queues
{

    template <typename T>
    struct Node
    {
        T value;
        Node<T>* successor;
    };


    template <class T>
    Queue<T>::Queue()
    {
        this->size = 0;
        this->head = NULL;
        this->tail = NULL;
    }

    template <class T>
    void Queue<T>::enqueue(T val)
    {
        Node<T>* node = new Node<T>;
        node->value = val;
        node->successor = NULL;

        if (this->size == 0)
        {
            this->head = node;
            this->tail = node;
            this->size += 1;
        }
        else
        {
            this->tail->successor = node;
            this->tail = node;
            this->size += 1;
        }
    }

    template <class T>
    int* Queue<T>::dequeue()
    {

        if (this->size == 0)
        {
            std::cout << "Queue is already empty!" << std::endl;
            return nullptr;
        }
        else
        {
            T* val = new T(this->head->value);
            Node<T>* tmp = this->head;
            this->head = this->head->successor;
            delete tmp;
            this->size -= 1;
            return val;
        }
    }

    template <class T>
    void Queue<T>::peek()
    {
        if (this->size == 0)
        {
            std::cout << "Queue is empty!" << std::endl;
        }
        else
        {
            std::cout << "Head of Queue: " << this->head->value << std::endl;
        }
    }

    template <class T>
    bool Queue<T>::contains(T val)
    {
        Node<T>* curr = this->head;
        int idx = 0;

        while(curr != this->tail)
        {
            if (curr->value == val)
            {
                std::cout << "Element can be found at position: " << idx << std::endl;
                return true;
            }
            curr = curr->successor;
            idx += 1;
        }
        if (this->tail->value == val)
        {
            std::cout << "Element can be found at position: " << this->size - 1 << std::endl;
            return true;
        }

        return false;
    }


    template <class T>
    void Queue<T>::remove(T val)
    {
        if (this->head->value == val)
        {
            std::cout << "HEAD IS VAL" << std::endl;
            T* tmp = dequeue();
            delete tmp;
        }
        else
        {
            // during iteration, track previous node
            Node<T>* prev = this->head;
            Node<T>* curr = this->head->successor;

            while(prev != this->tail)
            {

                if (curr->value == val)
                {
                    prev->successor = curr->successor;
                    delete curr;
                    this->size --;
                    std::cout << "Successfully removed value: " << val << std::endl;
                    return;
                }
                else
                {
                    prev = curr;
                    curr = curr->successor;
                }
            }
        }
    }

    template <class T>
    bool Queue<T>::is_empty()
    {
        if (this->size == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    template <class T>
    void Queue<T>::print_size()
    {
        std::cout << "Queue currently has size: " << this->size << std::endl;
    }

}