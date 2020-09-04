//
// Created by LIGHTNING X-TREME on 29.04.2020.
//

#include <iostream>
#include <array>
#include <forward_list>
#include "Interfaces.h"


using namespace std;

namespace HashTables
{

    template <typename T>
    struct pair{
        int key;
        T value;

        pair<T>(int k, T v): key(k), value(v){};
    };



    // Separate Chaining

    // Constructor
    template <class T>
    SC<T>::SC(double thres_load_factor)
    {
        this->size = 3;  // prime number
        this->num_elements = 0;
        this->thres_load_factor = thres_load_factor;
        array<forward_list<pair<T>>, 3>* table = new array<forward_list<pair<T>>, 3>;

    }

    // private
    template <class T>
    int SC<T>::hash(int key)
    {
        return key % this->size;
    }

    template <class T>
    void SC<T>::rehash()
    {
        // rehash not really necessary here
    }

    template <class T>
    double SC<T>::get_current_load_factor()
    {
        return this->num_elements / (this->size + 0.0);
    }

    template <class T>
    bool SC<T>::equal_pairs(HashTables::pair<T> p1, HashTables::pair<T> p2)
    {
        if (p1.key == p2.key && p1.value == p2.value)
            return true;
        else
            return false;
    }



    // public
    template <class T>
    void SC<T>::insert(HashTables::pair<T> p)
    {
        int hash = this->hash(p.key);
        this->num_elements++;

        if (this->table[hash].empty())
        {
            // Create new singly linked list
            forward_list<pair<T>> chain {p};
            this->table[hash] = chain;
        } else
        {
            // Insert into existing singly linked list
            this->table[hash].push_front(p);
        }

        /*
        if (this->get_current_load_factor() > this->thres_load_factor)
            this->rehash();
        */
    }

    template <class T>
    void SC<T>::remove(HashTables::pair<T> p)
    {
        std::pair<int, int> found = find(p);
        if (found.first == -1 || found.second == -1)
        {
            cout << "Passed key-value pair not found, hence not deleted" << endl;
        } else {

            if (found.second == 0) {
                // remove head of the list
                this->table[found.first].pop_front();
            } else {

                int cnt = 0;
                for (auto it = this->table[found.first].cbegin(); it != this->table[found.first].cend(); it++) {

                    if (cnt == found.second - 1) {
                        this->table[found.first].erase_after(it);
                        break;
                    }
                    cnt++;
                }
            }
            cout << "Erased key-value pair from Hashtable at hash '"<< found.first << "' and its position '" <<
                found.second << "'" << endl;

        }

    }

    template <class T>
    std::pair<int, int> SC<T>::find(HashTables::pair<T> p)
    {
        int hash = this->hash(p.key);
        if (this->table[hash].empty())
            return {-1, -1};

        int idx = -1;
        for (auto it = this->table[hash].cbegin(); it != this->table[hash].cend(); it++){
            idx++;
            if (this->equal_pairs(*it, p))
                return {hash, idx};

        }
        return {hash, -1};
    }


    template <class T>
    void SC<T>::get_info()
    {
        cout << "\n" << "Information on HashTable: " << endl;
        cout << "Size: " << this->size << endl;
        cout << "Load Factor: " << this->get_current_load_factor() << " < " << this->thres_load_factor << "\n" << endl;
    }

    template <class T>
    void SC<T>::print_table()
    {
        cout << "\n" << "HashTable Elements:" << endl;
        for (int hash=0; hash < this->table.size(); hash++)
        {
            cout << "\nHash -> " << hash << endl;
            for (auto it = this->table[hash].cbegin(); it != this->table[hash].cend(); it++)
            {

                cout << "    (k, v) -> (" << (*it).key << ", " << (*it).value << ")" << endl;
            }
        }

    }




    // Open Addressing

    template <class T>
    OA<T>::OA(double load_factor_threshold, int size)
    {

        pair<T>* table;
        table = new pair<T>[size];
        this->thres_load_factor = load_factor_threshold;
        this->size = size;

        cout << size << endl;
        cout << table << endl;

        // cout << (*table)[0].key << " " <<  (*table)[1].key << " " << (*table)[2].key << endl;

    }





}

