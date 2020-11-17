#ifndef TREE_HH
#define TREE_HH

#include <cstdio>
#include <iostream>

#include "node.hh"

namespace F
{
    template <typename DataT>
    class Node;

    template <typename DataT>
    class NodeIt;
    
    template <typename DataT>
    class Tree final
    {
        using NodeT = Node<DataT>;

    private:

        NodeT * root_;
        bool is_empty_{true};
        int el_num_{0};

    public:

        Tree( );
        explicit Tree( const DataT & data );

        Tree( const Tree & ) = delete;
        Tree( Tree && ) = delete;

        ~Tree( );

        Tree & operator = ( const Tree & ) = delete;
        Tree operator = ( Tree && ) = delete;

        template <typename FindT>
        NodeIt<DataT> find( const FindT & data );

        template <typename FindT>
        NodeIt<DataT> lower_bound( const FindT & data );

        NodeIt<DataT> begin( );
        NodeIt<DataT> end( );

        void insert( const DataT & data );

        int depth( );
        bool is_balanced( );

        void remove( DataT & to_del );

        void print( );
        void print_leafs( );
        void print_lvl( int lvl );
    };

    #include "tree.ii"
}

#endif //TREE_HH