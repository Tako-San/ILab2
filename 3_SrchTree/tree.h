#ifndef MAP_TREE_H
#define MAP_TREE_H

#include <cstdio>
#include <iostream>
#include "node.h"

template <typename Data_t>
class Tree
{
    using NodeT = Node<Data_t>;

    NodeT * root;

public:

    Tree( ) : root(new NodeT)
    {}

    Tree( const Data_t & data ) : root(new NodeT{data})
    {}

    Tree( const Tree & ) = delete;
    Tree & operator = ( const Tree & ) = delete;


    void add( const Data_t & data )
    { root->add(data); }

    Data_t & find( const Data_t & data )
    {
        NodeT * res = root->find(data);
        return res->data_;
    }

    int depth( )
    { return root->depth(); }

    bool is_balanced( )
    { return root->is_balanced(); }

    void del( Data_t & to_del )
    { root->del(to_del); }

    void clear( )
    {
        if(root == nullptr)
            return;
        root->clear();
    }

    void print( )
    { root->print(); }

    void print_leafs( )
    {
        if(root == nullptr)
            return;
        root->print_leafs();
    }

    void print_lvl( int lvl )
    {
        if(root == nullptr)
            return;
        root->print_lvl(lvl);
    }

    Data_t & operator[] ( Data_t data )
    {
        NodeT * tmp = root->find(data);

        if(tmp != nullptr)
            return tmp->data_;
        else
            tmp = root->add(data);
        return tmp->data_;
    }

};

#endif //MAP_TREE_H
