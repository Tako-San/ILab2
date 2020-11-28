#ifndef NODE_HH
#define NODE_HH

#include <cstdio>
#include <iostream>
#include <fstream>


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
        Node * next_{nullptr};
        Node * prev_{nullptr};

    private:

        Node( );
        explicit Node( const DataT & data,
                       Node * prnt = nullptr,
                       Node * next = nullptr,
                       Node * prev = nullptr);

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

        Node * findmin( );
        Node * findmax( );
        Node * removemin( );
        Node * remove( const DataT & data );

        template <typename FindT>
        Node * find( const FindT & data );

        Node * insert( const DataT & data );

        void clear_subtree( );

        void print( );
        void print_leafs( );
        void print_lvl( int lvl );
        void dump( std::ofstream &oft );
    };

    template <typename DataT>
    class NodeIt final // TODO: наследоваться от std::iterator?
    {
        friend class Node<DataT>;
        friend class Tree<DataT>;

    private:

        Node<DataT> * ptr_;
        explicit NodeIt( Node<DataT> * ptr );

    public:

        NodeIt( const NodeIt & it );

        NodeIt & operator = ( const NodeIt & it );

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
