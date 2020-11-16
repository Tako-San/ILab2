#ifndef NODE_HH
#define NODE_HH

#include <cstdio>
#include <iostream>


namespace F
{
    template <typename DataT>
    class Tree;


    template <typename DataT>
    class Node final
    {
        friend class Tree<DataT>;

    private:

        DataT  data_;
        int    dpth_{1};

        Node * prnt_{nullptr};
        Node * left_{nullptr};
        Node * rght_{nullptr};

    private:

        Node( );
        explicit Node( const DataT & data, Node * prnt = nullptr );

        int depth( );
        int cdepth( );
        int diff( );

        void set_depth( );

        void set_parent( Node * prnt );
        void set_right( Node * rght );
        void set_left( Node * left );

        Node * rot_rt( );
        Node * rot_lt( );
        Node * balance( );

        bool is_balanced( );

        Node * findmin( );
        Node * removemin( );
        Node * remove( const DataT & data );

        template <typename FindT>
        Node * find( const DataT & data );
        Node * insert( const DataT & data );

        void clear_subtree( );

        void print( );
        void print_leafs( );
        void print_lvl( int lvl );
    };

    #include "node.ii"

}
#endif //NODE_HH
