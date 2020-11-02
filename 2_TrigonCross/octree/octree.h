#ifndef ILAB2_OCTREE_H
#define ILAB2_OCTREE_H

#include <map>
#include <list>
#include "octnode.h"

using std::map;
using std::list;

template <typename DataT>
class OctTree
{
public:

    OctNode<DataT> * root_;

    list<pair<DataT, OctNode<DataT> *>> data_;

public:

    OctTree( ) : root_{}, data_{}
    {
        root_ = new OctNode<DataT>;
    }

    OctTree( const Box & zone ) : data_{}
    {
        root_ = new OctNode<DataT>{zone};
    }

    OctTree( const Box & zone, const list<DataT> & data ) : data_{}
    {
        root_ = new OctNode<DataT>{zone};
        
        for (DataT dat : data)
            insert(dat);
    }

    OctTree( const Box & zone, const vector<DataT> & data ) : data_{}
    {
        root_ = new OctNode<DataT>{zone};

        for (DataT dat : data)
            insert(dat);
    }

    ~OctTree( )
    {
        root_->clear_sub();
    }

    bool insert( const DataT & data )
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
};


#endif //ILAB2_OCTREE_H
