#ifndef ILAB2_OCTREE_H
#define ILAB2_OCTREE_H

#include <map>
#include <list>
#include "octnode.hh"


namespace Geom
{
    using namespace Geom;

    using std::map;
    using std::list;

    template <typename DataT>
    class OctTree
    {

    private:

        OctNode<DataT> * root_;

    public:

        OctTree( );
        explicit OctTree( const Box & zone );

        template <typename IterT>
        OctTree( const Box & zone, const IterT & begin, const IterT & end );

        ~OctTree( );

        bool insert( const DataT & obj );
        bool is_intersect( const DataT & obj, bool not_in_tree = false );

        void print( );
    };

    template <typename DataT>
    OctTree<DataT>::OctTree( ) : root_(new OctNode<DataT>)
    {}

    template <typename DataT>
    OctTree<DataT>::OctTree( const Box & zone ) : root_(new OctNode<DataT>{zone})
    {}

    template <typename DataT>
    template <typename IterT>
    OctTree<DataT>::OctTree( const Box & zone,
                             const IterT & beg,
                             const IterT & end ) : root_(new OctNode<DataT>{zone})
    {
        for (auto cur = beg; cur != end; ++cur)
            insert(*cur);
    }

    template <typename DataT>
    OctTree<DataT>::~OctTree( )
    {
        root_->clear_sub();
    }

    template <typename DataT>
    bool OctTree<DataT>::insert( const DataT & obj )
    {
        return (root_->insert(obj) != nullptr);
    }

    template <typename DataT>
    bool OctTree<DataT>::is_intersect( const DataT & obj, bool not_in_tree )
    {
        return root_->is_intersect(obj, not_in_tree);
    }

    template <typename DataT>
    void OctTree<DataT>::print( )
    {
        root_->print();
    }

}
#endif //ILAB2_OCTREE_H
