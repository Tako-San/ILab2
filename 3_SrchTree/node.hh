#ifndef NODE_HH
#define NODE_HH

#include <cstdio>
#include <iostream>


namespace F
{
    template <typename DataT>
    class Tree;

    template <typename DataT>
    class NodeIt;

    template <typename DataT>
    class Node final
    {
        friend class Tree<DataT>;
        friend class NodeIt<DataT>;

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
        int diff( );

        void set_depth( );

        void set_parent( Node * prnt );
        void set_right( Node * rght );
        void set_left( Node * left );

        Node * rot_rt( );
        Node * rot_lt( );
        Node * balance( );

        bool is_balanced( );

        Node * next( );
        Node * prev( );
        Node * findmin( );
        Node * findmax( );
        Node * removemin( );
        Node * remove( const DataT & data );

        template <typename FindT>
        Node * find( const FindT & data );
        template <typename FindT>
        Node * lower_bound( const FindT & data );

        Node * insert( const DataT & data );

        void clear_subtree( );

        void print( );
        void print_leafs( );
        void print_lvl( int lvl );
    };

    template <typename DataT>
    class NodeIt final
    {
        friend class Tree<DataT>;

    private:

        Node<DataT> * ptr_;

    public:

        NodeIt( const NodeIt & it );
        explicit NodeIt( Node<DataT> * ptr );

        NodeIt & operator = ( const NodeIt & iter );

        bool operator == ( const NodeIt & it ) const;
        bool operator != ( const NodeIt & it ) const;

        DataT & operator * ( );
        const DataT & operator * ( ) const;

        NodeIt & operator ++ ();
        NodeIt & operator -- ();
    };

    #include "node.ii"

}
#endif //NODE_HH
