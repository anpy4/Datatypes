//
// Created by LIGHTNING X-TREME on 22.04.2020.
//
#include <iostream>
#include <queue>
#include <vector>
#include "Interfaces.h"


namespace Trees
{
    template <typename T>
    struct Node
    {
        T value;
        Node* left;
        Node* right;

        Node<T>(T val): value(val), left(NULL), right(NULL){};
    };

    template <class T>
    BinarySearchTree<T>::BinarySearchTree()
    {
        this->root = NULL;
        this->size = 0;
    }

    template <class T>
    int BinarySearchTree<T>::get_size()
    {
        return size;
    }

    template <class T>
    Node<T>* BinarySearchTree<T>::get_root()
    {
        return this->root;
    }

    template <class T>
    std::pair<Node<T>*,Node<T>*> BinarySearchTree<T>::search(T val)
    {
        if (get_size() == 0)
        {
            Node<T>* nullnode = NULL;
            return std::make_pair(nullnode, nullnode);

        }
        
        Node<T>* curr = get_root();
        Node<T>* parent = NULL;
        while (curr != NULL)
        {
            if (curr->value == val)
            {
                std::cout << "Node " << curr << " :  " << curr->value << std::endl;
                if (parent != NULL)
                    std::cout << "Parent " << parent << " :  " << parent->value << std::endl;
                return std::make_pair(curr, parent);
            }
            parent = curr;

            if (val < curr->value)
                curr = curr->left;
            else
                curr = curr->right;
        }
        // Return NULL if element not found
        Node<T>* nullnode = NULL;
        return std::make_pair(nullnode, nullnode);
    }

    template <class T>
    void BinarySearchTree<T>::insert(T val)
    {

        Node<T>* node = new Node<T>(val);
        this->size++;

        if (get_size() == 1)
        {
            this->root = node;
            return;
        }


        Node<T>* curr = get_root();
        Node<T>* parent; // needed to decide which node is parent and whether left or right child
        while (curr != NULL)
        {
            parent = curr;
            if (val < curr->value)
                    curr = curr->left;

            else if (val > curr->value)
                curr = curr->right;

            else
            {
                // equal value case -> insert between equal node and its left child
                node->left = curr->left;
                curr->left = node;
                return;
            }
        }

        if (val < parent->value)
            parent->left = node;
        else
            parent->right = node;

    }

    template <class T>
    void BinarySearchTree<T>::remove(T val)
    {
        std::pair<Node<T>*,Node<T>*> tup = search(val);  // <node,parent>
        if (tup.first == NULL){
            std::cout << "Passed value not found!" << std::endl;
            return;
        }

        this->size--;

        // Case 1: Leaf Node
        if (tup.first->left == NULL && tup.first->right == NULL)
        {
            // is root?
            if (tup.first == get_root())
                this->root = NULL;

            // not root but left child
            else if (tup.first->value <= tup.second->value )
                tup.second->left = NULL;
            else  // right child
                tup.second->right = NULL;
            delete tup.first;
        }



        // Case 4: Both left and right child
        else if (tup.first->left != NULL && tup.first->right != NULL)
        {
            // biggest node of left subtree
            Node<T>* curr = tup.first->left;
            Node<T>* parent = tup.first;
            while (curr->right != NULL)
            {
                parent = curr;
                curr = curr->right;
            }


            // swap nodes an delete
            tup.first->value = curr->value;
            if (curr->value <= parent->value)
                parent->left = NULL;
            else
                parent->right = NULL;
        }

        // Case 2: Only left child
        else if (tup.first->left != NULL)
        {
            // node is root?
            if (tup.first == get_root())
                this->root = tup.first->left;

            // not root nur left child
            else if (tup.first->value <= tup.second->value )
                tup.second->left = tup.first->left;
            else // right child
                tup.second->right = tup.first->left;
            delete tup.first;
        }


        // Case 3: Only right child
        else if (tup.first->right != NULL)
        {
            // node is root?
            if (tup.first == get_root())
                this->root = tup.first->right;

            // not root but left child
            else if (tup.first->value <= tup.second->value )
                tup.second->left = tup.first->right;
            else // right child
                tup.second->right = tup.first->right;
            delete tup.first;
        }


        std::cout << "Node successfully deleted!" << std::endl;
    }



    template <class T>
    void BinarySearchTree<T>::preorder(Node<T>* root)
    {
        if (root == NULL)
            return;

        std::cout << root->value << "  ";
        preorder(root->left);
        preorder(root->right);
    }

    template <class T>
    void BinarySearchTree<T>::postorder(Node<T> * root)
    {
        if (root == NULL)
            return;

        postorder(root->left);
        postorder(root->right);
        std::cout << root->value << "  ";
    }

    template <class T>
    void BinarySearchTree<T>::inorder(Node<T> * root)
    {
        if (root == NULL)
            return;

        inorder(root->left);
        std::cout << root->value << "  ";
        inorder(root->right);
    }

    template <class T>
    void BinarySearchTree<T>::levelorder(Trees::Node<T> * root)
    {
        std::queue<std::vector<Node<T>*>> q;
        std::vector<Node<T>*> level;
        level.push_back(root);
        q.push(level);

        while (!q.empty())
        {
            std::vector<Node<T>*> lvl = q.front();
            q.pop();
            std::vector<Node<T>*> next_lvl;

            bool anynode = false;
            std::cout << "\n" << "[";
            for (Node<T>* n: lvl)
            {
                if (n != NULL)
                {
                    std::cout << " " << n->value;
                    next_lvl.push_back(n->left);
                    next_lvl.push_back(n->right);
                    anynode = true;
                }
                else {
                    std::cout << " " << "*";
                    Node<T> *nullnode = NULL;
                    next_lvl.push_back(nullnode);
                    next_lvl.push_back(nullnode);
                }
            }
            std::cout << " ]" << std::endl;
            if (anynode)
                q.push(next_lvl);
        }

        std::cout << "\n";

    }







}
