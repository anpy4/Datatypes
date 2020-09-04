//
// Created by schiefer on 14/02/2020.
//

#ifndef DATATYPES_INTERFACES_H
#define DATATYPES_INTERFACES_H

#include <array>  // for HT
#include <forward_list>  // for HT
#include <vector>  // for PQ
#include <string> // for SA



namespace Arrays
{

    // Class should work independently of datatype
    template <class T>
    class DynamicArray
    {
        private:

            T *array;
            int element_counter;
            int size_counter;
            void init_array(T _array[], int len);
            void double_size();
            void rearange(int position);

        public:
            // constructor
            DynamicArray(T _array[], int len);
            void get_array();
            int get_array_size();
            int get_num_elements();
            void append(T element);
            void insert(T element, int position);
    };
}


namespace Lists
{

    template <typename T>
    struct sNode;

    template <class T>
    class SinglyLinkedList
    {
        private:
            sNode<T> *head;
            sNode<T> *tail;
            int len;


        public:
            SinglyLinkedList();
            void appendNode(T val);
            void printList();
            void insertNode(T val, int pos);
            void deleteNode(T val);
            void deleteAll();

    };

    template <typename T>
    struct dNode;

    template <class T>
    class DoublyLinkedList
    {
        private:
            dNode<T> *head;
            dNode<T> *tail;
            int len;

        public:
            DoublyLinkedList();
            void appendNode(T val);
            void printList();
            void insertNode(T val, int pos);
            void deleteNode(T val);
            void deleteAll();

    };



}


namespace Stacks
{

    template <typename T>
    struct Node;

    template <class T>
    class Stack
    {
        private:
            int size;
            Node<T>* top;

        public:
            Stack();
            void push(T value);
            T pop();
            void peek();
            void get_size();
    };

}


namespace Queues
{

    template <typename T>
    struct Node;

    template <class T>
    class Queue
    {
        private:
            int size;
            Node<T>* head;
            Node<T>* tail;

        public:
            Queue();
            void enqueue(T val);
            int* dequeue();
            void peek();
            bool contains(T val);
            void remove(T val);
            bool is_empty();
            void print_size();
    };



}


namespace PriorityQueues
{


    template <class T>
    class BinaryPQ
    {

        private:
            std::vector<T> heap;
            int size;
            void swap_nodes(int idx_1, int idx_2);
            int bubble_up(int idx);
            int bubble_down(int idx);
            void rearange(int idx);  // calls bubble_up and bubble_down

        public:
            BinaryPQ();
            void peek();
            void contains(T val);
            void add(T val);
            void poll();
            void remove(T val);
            void print_tree();


    };

}

/*
namespace UnionFinds
{

    template <class T>
    class UnionFind
    {


        private:
            int size;
            int num_components = size;
            // std::vector<T> nodes(size);
            // std::vector<int> component_size(size);


        public:
            UnionFind<T>(int sz);
            void unify(int idx1, int idx2);
            int find(int idx);
            int get_component_size(int idx);
            bool check_if_connected(int idx1, int idx2);
            void count_components();

    };

}
*/


namespace Trees
{

    template <typename T>
    struct Node;


    template <class T>
    class BinarySearchTree
    {
        private:
            Node<T>* root;
            int size;

        public:
            BinarySearchTree<T>();
            void insert(T val);
            void remove(T val);
            std::pair<Node<T>*,Node<T>*> search(T val);
            int get_size();
            Node<T>* get_root();

            void preorder(Node<T>*);
            void inorder(Node<T>*);
            void postorder(Node<T>*);
            void levelorder(Node<T>*);

    };


    template <class T>
    class FenwickTree{

    private:
        int* ftree;
        int size;
        int LSB(int idx);
        int prefixSum(int idx);

    public:
        FenwickTree<T>(int size);
        void construct(T value_array[]);
        void point_update(int idx, T val);
        void range_sum(int from_idx, int to_idx);
        int LSB_wrapper(int idx);
        void print_tree();

    };




}


namespace HashTables
{

    template <typename T>
    struct pair;

    template<class T>
    class SC {
    // SC = Separate Chaining using LinkedLists
    private:
        int size;
        int num_elements;
        double thres_load_factor;
        // std::array<std::forward_list<pair<T>>, 3> table;  // <key,value> where key hashes to index
        int hash(int key);
        void rehash();
        double get_current_load_factor();
        bool equal_pairs(pair<T> p1, pair<T> p2);

    public:
        SC<T>(double thres_load_factor);
        void insert(pair<T> p);
        void remove(pair<T> p);
        std::pair<int, int> find(pair<T> p);
        void get_info();
        void print_table();
    };

    template<class T>
    class OA{
    // OA = Open Addressing using Probing Functions
    private:
        int size;
        int num_elements;
        double thres_load_factor;
        // std::array<pair<T>, 7> table;  // <key,value> where key hashes to index
        int hash(int key);
        void rehash();
        int get_current_load_factor();

    public:
        OA<T>(double load_factor_threshold, int size);
        void insert(pair<T> p);
        void remove(pair<T> p);
        int find(pair<T> p);
        void get_info();
        void print_table();


    };


}



namespace SuffixArrays{

    // Both "Longest Common Substring" (LCS) and "Longest Repeated Substring" (LRS) utilize "Longest Common Prefix" (LCP) arrays

    struct myComparator;

    class LongestCommonPrefix{
        protected:
            std::string s;
            std::vector<int> suffixArray;
            std::vector<int> lcpArray;
            std::string getSuffixFromSuffixArray(int idx);


        public:

            LongestCommonPrefix(std::string str);
            std::string getString();
            std::vector<int> getSuffixArray();
            void buildSuffixArray();
            std::vector<int> getLcpArray();
            void buildLcpArray();

            void printResult();



    };

    class LongestCommonSubstring : public LongestCommonPrefix{

    private:
        std::vector<int> stringAssignmentArray;

    public:

        LongestCommonSubstring(std::string str, std::vector <std::string> stringArray);
        std::vector<int> getStringAssignmentArray();
        void assignStringCategory();

        void printResult();
    };



}

#endif //DATATYPES_INTERFACES_H


