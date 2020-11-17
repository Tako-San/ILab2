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
        bool is_empty{true};

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




    template <typename DataT>
    Tree<DataT>::Tree( ) : root_{new NodeT}
    {}

    template <typename DataT>
    Tree<DataT>::Tree( const DataT & data ) : root_{new NodeT{data}},
                                              is_empty{false}
    {}

    template <typename DataT>
    Tree<DataT>::~Tree( )
    {
        root_->clear_subtree();
        is_empty = true;
    }

    template <typename DataT>
    template <typename FindT>
    NodeIt<DataT> Tree<DataT>::find( const FindT & data )
    {
        return NodeIt<DataT> {root_->find(data)};
    }

    template <typename DataT>
    template <typename FindT>
    NodeIt<DataT> Tree<DataT>::lower_bound( const FindT & data )
    {
        return NodeIt<DataT> {root_->lower_bound(data)};
    }

    template <typename DataT>
    NodeIt<DataT> Tree<DataT>::begin( )
    {
        return NodeIt<DataT> {root_->findmin()};
    }

    template <typename DataT>
    NodeIt<DataT> Tree<DataT>::end( )
    {
        return NodeIt<DataT> {nullptr};
    }

    template <typename DataT>
    void Tree<DataT>::insert( const DataT & data )
    {
        if (is_empty)
        {
            root_->data_ = data;
            is_empty = false;
        }
        else
            root_ = root_->insert(data);
    }

    template <typename DataT>
    int Tree<DataT>::depth( )
    {
        return root_->depth();
    }

    template <typename DataT>
    bool Tree<DataT>::is_balanced( )
    {
        return root_->is_balanced();
    }

    template <typename DataT>
    void Tree<DataT>::remove( DataT & to_del )
    {
        root_ = root_->remove(to_del);
    }

    template <typename DataT>
    void Tree<DataT>::print( )
    {
        root_->print();
    }

    template <typename DataT>
    void Tree<DataT>::print_leafs( )
    {
        if(root_ == nullptr)
            return;
        root_->print_leafs();
    }

    template <typename DataT>
    void Tree<DataT>::print_lvl( int lvl )
    {
        if(root_ == nullptr)
            return;
        root_->print_lvl(lvl);
    }
}

#endif //TREE_HH