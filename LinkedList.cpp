//
// Created by schiefer on 18/02/2020.
//

# include <iostream>
#include "Interfaces.h"


namespace Lists
{

    // Singly Linked List
    template <typename T>
    struct sNode
    {
        T value;
        sNode* successor;  // pointer to the next node
    };


    template <class T>
    SinglyLinkedList<T>::SinglyLinkedList()
    {
        this->head = NULL;
        this->tail = NULL;
        this->len = 0;
    }

    template <class T>
    void SinglyLinkedList<T>::appendNode(T val)
    {
        sNode<T> *node = new sNode<T>;
        node->value = val; // same as (*node).value
        node->successor = NULL;

        if (this->head == NULL)
        {
            this->head = node;
            this->tail = node;
            node = NULL;  // fre memory
            this->len += 1;
        }
        else
        {
            // append to current tailnode
            this->tail->successor = node;
            // set new tailnode
            this->tail = node;
            node = NULL;  // fre memory
            this->len += 1;
        }
    }


    template <class T>
    void SinglyLinkedList<T>::printList()
    {

        sNode<T> *curr = this->head;

        while(curr != NULL)
        {
            std::cout << curr->value << std::endl;
            curr = curr->successor;
        }

        if (this->head == NULL)
        {
            std::cout << "Linked List is empty!" << std::endl;
        }
    }

    template <class T>
    void SinglyLinkedList<T>::insertNode(T val, int pos)
    {
        if (pos > this->len)
        {
            std::cout << "Passed Position out of Bounds" << std::endl;
        }
        else
        {
            sNode<T> *node = new sNode<T>;
            node->value = val;
            this->len += 1;
            if (pos == 0)
            {
                // new head
                node->successor = this->head;
                this->head = node;
            }
            else if (pos == this->len)
            {
                // new tail
                appendNode(val);
            }
            else
            {
                // actual insertion
                int counter = 0;
                sNode<T> *curr = this->head;

                for (int i=0; i<pos-1; i++)
                {
                    curr = curr->successor;
                }
                // e.g. pos=1 :  pre=node0, succ=node1
                node->successor = curr->successor;
                curr->successor = node;

            }
        }
    }


    template <class T>
    void SinglyLinkedList<T>::deleteNode(T val)
    {

        sNode<T> *curr = this->head;
        if (curr->value == val)
        {
            this->head = head->successor;
            delete curr;
            this->len -= 1;
            return;
        }

        while(curr != tail)
        {

            sNode<T> *tmp = curr->successor;
            if (tmp->value == val)
            {
                if (tmp == tail)
                {
                    tail = curr;
                    tail->successor = NULL;
                    delete tmp;
                    return;
                }
                else
                {
                    curr->successor = tmp->successor;
                    delete tmp;
                    return;
                }
            }
            curr = curr->successor;
        }
        this->len -= 1;
        std::cout << "Passed Value not found" << std::endl;
    }

    
    template <class T>
    void SinglyLinkedList<T>::deleteAll()
    {
        sNode<T> *nodes[this->len];
        sNode<T> *curr = this->head;

        for (int i=0; i < this->len; i++)
        {
            nodes[i] = curr;
            curr = curr->successor;
        }

        for (int i = this->len - 1; i>=0; i--)
        {
            delete nodes[i];
        }

        head = NULL;
        tail = NULL;
        this->len = 0;


    }




    // Doubly Linked List
    template <typename T>
    struct dNode
    {
        T value;
        dNode* predecessor;
        dNode* successor;
    };

    template <class T>
    DoublyLinkedList<T>::DoublyLinkedList()
    {
        this->head = NULL;
        this->tail = NULL;
        this->len = 0;
    }

    template <class T>
    void DoublyLinkedList<T>::appendNode(T val)
    {
        dNode<T>* node = new dNode<T>;
        node->value = val;
        node->successor = NULL;

        if (this->len == 0)
        {
            node->predecessor = NULL;
            this->head = node;
            this->tail = node;
        }
        else
        {
            this->tail->successor = node;
            node->predecessor = this->tail;
            this->tail = node;
        }
        node = NULL; // free memory
        this->len += 1;

    }

    template <class T>
    void DoublyLinkedList<T>::printList() {
        std::cout << "Print Doubly Linked List:" << std::endl;

        if (this->len == 0) {
            std::cout << "Linked List is empty!" << std::endl <<std::endl;
            return;
        }

        dNode<T> *node = new dNode<T>;
        node = this->head;

        while (node != NULL) {
            std::cout << "Node: " << node->value << std::endl;
            node = node->successor;
        }
        delete node;
        std::cout << std::endl;

    }

    template <class T>
    void DoublyLinkedList<T>::insertNode(T val, int pos)
    {

        if (pos > this->len)
        {
            std::cout << "Passed Position out of Bounds" << std::endl;
        }
        else
        {
            dNode<T>* node = new dNode<T>;
            node->value = val;

            if (pos == 0)  // head node
            {
                node->predecessor = NULL;
                node->successor = head;
                head->predecessor = node;
                this->head = node;
            }
            else if (pos == this->len)  // tail node
            {
                node->predecessor = tail;
                node->successor = NULL;
                tail->successor = node;
                this->tail = node;
            }
            else  // regular insertion
            {
                dNode<T>* curr = new dNode<T>;
                curr = this->head;

                for (int curr_pos=1; curr_pos <= pos; curr_pos++)
                {
                    curr = curr->successor;
                }
                // "curr" is the current node at index "pos"
                std::cout << "Insert before: " << curr->value << std::endl;
                node->successor = curr;
                node->predecessor = curr->predecessor;
                curr->predecessor->successor = node;
                curr->predecessor = node;

                curr = NULL;

            }
            this->len += 1;
        }

    }

    template <class T>
    void DoublyLinkedList<T>::deleteNode(T val)
    {
        dNode<T>* curr = new dNode<T>;
        curr = head;
        for(int i=0; i<this->len; i++)
        {
            if (curr->value == val)
            {
                if (curr == this->head)  // delete head node
                {
                    this->head = curr->successor;
                    this->head->predecessor = NULL;
                }
                else if (curr == this->tail)
                {
                    this->tail = this->tail->predecessor;
                    this->tail->successor = NULL;
                }
                else
                {
                    curr->predecessor->successor = curr->successor;
                    curr->successor->predecessor = curr->predecessor;
                }
                this->len -= 1;
                delete curr;
                return;
            }
            else
            {
                curr = curr->successor;
            }
        }
        std::cout << "Passed Value not found" << std::endl;

    }

    template <class T>
    void DoublyLinkedList<T>::deleteAll()
    {

        if (this->len == 0)
        {
            std::cout << "List is already empty!" << std::endl;
            return;
        }

        while (this->len > 1)
        {
            this->tail = tail->predecessor;
            delete this->tail->successor;
            this->len -= 1;
        }
        delete this->tail;
        this->head = NULL;
        this->tail = NULL;
        this->len = 0;
    }

}

