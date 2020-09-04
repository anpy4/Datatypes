cmake_minimum_required(VERSION 3.15)
project(Datatypes)

set(CMAKE_CXX_STANDARD 14)

add_executable(Datatypes main.cpp Interfaces.h DynamicArray.cpp LinkedList.cpp Stack.cpp Queue.cpp PriorityQueue.cpp UnionFind.cpp BinarySearchTree.cpp HashTable.cpp FenwickTree.cpp SuffixArray.cpp)