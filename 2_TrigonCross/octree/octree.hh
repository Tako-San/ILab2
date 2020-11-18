#ifndef ILAB2_OCTREE_H
#define ILAB2_OCTREE_H

#include <map>
#include <list>
#include "octnode.hh"

using std::map;
using std::list;

template <typename DataT>
class OctTree
{
public:

    OctNode<DataT> * root_;

    list<pair<DataT, OctNode<DataT> *>> data_;

public:

    OctTree( );
    OctTree( const Box & zone );
    OctTree( const Box & zone, const list<DataT> & data );
    OctTree( const Box & zone, const vector<DataT> & data );

    ~OctTree( );

    bool insert( const DataT & data );

    void print( );
};

template <typename DataT>
OctTree<DataT>::OctTree( ) : root_{}, data_{}
{
    root_ = new OctNode<DataT>;
}

template <typename DataT>
OctTree<DataT>::OctTree( const Box & zone ) : data_{}
{
    root_ = new OctNode<DataT>{zone};
}

template <typename DataT>
OctTree<DataT>::OctTree( const Box & zone, const list<DataT> & data ) : data_{}
{
    root_ = new OctNode<DataT>{zone};

    for (DataT dat : data)
        insert(dat);
}

template <typename DataT>
OctTree<DataT>::OctTree( const Box & zone, const vector<DataT> & data ) : data_{}
{
    root_ = new OctNode<DataT>{zone};

    for (DataT dat : data)
        insert(dat);
}

template <typename DataT>
OctTree<DataT>::~OctTree( )
{
    root_->clear_sub();
}

template <typename DataT>
bool OctTree<DataT>::insert( const DataT & data )
{
    if (!root_->is_in(data))
        return false;

    data_.push_back({data, nullptr});
    OctNode<DataT> * srch = root_->insert(--data_.end());

    if (srch == nullptr)
    {
        data_.pop_back();
        return false;
    }

    data_.back().second = srch;
    return true;
}

template <typename DataT>
void OctTree<DataT>::print( )
{
    root_->print();
}

#endif //ILAB2_OCTREE_H
