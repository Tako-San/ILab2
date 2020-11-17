#ifndef ILAB2_OCTNODE_H
#define ILAB2_OCTNODE_H

#include <vector>
#include "../geom/g_obj/vec.h"
#include "../geom/g_obj/box.h"

#include "../geom/geom.h"

const unsigned CHILDREN_NUM = 3;
const double MIN_DIAG = 0.03;

using std::vector;
using std::list;
using std::pair;

template <typename DataT>
class OctTree;

template <typename DataT>
class OctNode final
{
    using PairIt = typename list<pair<DataT, OctNode<DataT> *>>::iterator;

private:

    OctNode * parent_;

    OctNode * child_[8];
    bool has_children{false};

    Box zone_;
    vector<PairIt> data_;

public:

    OctNode( );
    explicit OctNode( Box zone, OctNode * parent = nullptr );
    OctNode( const OctNode & ) = default;
    OctNode & operator = ( const OctNode & ) = default;

    const vector<PairIt> & get_data( ) const;
    const OctNode ** get_children( ) const;

    bool is_parent( ) const;
    bool is_in( const DataT & d ) const;
    bool is_in( const DataT * d ) const;
    bool need_children( ) const;

    OctNode * insert( PairIt data, bool hate_children = false );

    bool intersect_subtree( DataT obj );

private:

    void clear_sub( );
    void div_box( );
    void divide( );

    friend class OctTree<DataT>;
    friend bool intersect_octree( typename list<pair<Triangle, OctNode<Triangle> *>>::iterator pair_it );
};

#include "octnode.i"

#endif //ILAB2_OCTNODE_H
