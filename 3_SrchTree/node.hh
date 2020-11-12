#ifndef MAP_NODE2_H
#define MAP_NODE2_H

#include <cstdio>
#include <iostream>
#include "my_pair/pair.h"

using std::cout;
using std::endl;
using std::abs;

template <typename DataT>
class Tree;

template <typename DataT>
class NodeIt;




template <typename DataT>
class Node
{
    friend class Tree<DataT>;
    friend class NodeIt<DataT>;

private:
    DataT data_;

    Node * prnt_{nullptr};
    Node * left_{nullptr};
    Node * rght_{nullptr};

public:
    
    Node();
    explicit Node( DataT & data );
    
    const DataT & get_data( ) const;

private:

    void set( const DataT & data, Node * prnt = nullptr );

    NodeIt<DataT> add( const DataT & data );

    template <typename FindT>
    NodeIt<DataT> find( FindT & data );
    Node * next( );
    Node * prev( );

    int depth( );
    bool is_balanced( );
    
    void del( DataT to_del );
    void clear( );

    void print( );
    void print_leafs( );
    void print_lvl( int lvl );
};




template <typename DataT>
class NodeIt
{
    friend class Node<DataT>;

private:
    Node<DataT> * ptr_;

    Node<DataT> * operator -> ( ); // for author's comfort

    explicit NodeIt( Node<DataT> * ptr );

public:

    NodeIt( const NodeIt & it );

    bool operator == ( const NodeIt & it ) const;
    bool operator != ( const NodeIt & it ) const;

    DataT & operator * ( );
    const DataT & operator * ( ) const;

    NodeIt & operator ++ ();
    NodeIt & operator -- ();


};




template <typename DataT>
std::ostream & operator << ( std::ostream & ost, const Node<DataT> & node );

#include "node.ii"

#endif //MAP_NODE2_H
