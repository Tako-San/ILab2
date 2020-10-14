#ifndef MAP_TREE_H
#define MAP_TREE_H

#include <cstdio>
#include <iostream>
#include "node.h"

class Tree
{
    Node * root;

public:

    Tree();
    Tree(Data_t &n_data);
    Tree(key_t key, val_t val); //Only with map_t

    void add(Data_t &n_data);
    void add(key_t key, val_t val);  //Only with map_t

    Data_t& find(Data_t &n_data);
    Data_t& find(key_t key);

    int depth();
    bool is_balanced();

    void del(Data_t &to_del);
    void del(key_t key); //Only with map_t

    void clear();
    void print();
    void print_leafs();
    void print_lvl(int lvl);

    val_t& operator[] (key_t key);
};

#endif //MAP_TREE_H
