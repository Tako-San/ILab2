#ifndef MAP_NODE2_H
#define MAP_NODE2_H

#include <cstdio>
#include <iostream>
#include "map.h"

#define Data_t Map_t

class Node
{
public:

    Data_t data;

    Node * parent;
    Node * left;
    Node * right;

public:

    Node();
    Node(Data_t &n_data);
    Node(key_t key, val_t val); //Only with map_t

    void set(Data_t &n_data, Node * parent = 0);
    void set(key_t key, val_t val = 0, Node * parent = 0);  //Only with map_t

    Node * add(Data_t &n_data);
    Node * add(key_t key, val_t val = 0);  //Only with map_t

    Node * find(Data_t &n_data); //tree
    Node * find(key_t key); //tree

    int depth(); //tree
    bool is_balanced(); //tree

    void del(Data_t &to_del); //tree
    void del(key_t key); //Only with map_t

    void clear(); //tree
    void print(); //tree
    void print_leafs(); //tree
    void print_lvl(int lvl); //tree

    friend std::ostream& operator << (std::ostream &out, const Node &node);
    friend class Tree;
};

#endif //MAP_NODE2_H
