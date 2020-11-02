#ifndef ILAB2_OCTREE_H
#define ILAB2_OCTREE_H

#include <list>
#include "octnode.h"

using std::list;

template <typename DataT>
class OctTree
{
public:

    OctNode<DataT> * root_;
    list<DataT> data_;

public:

    OctTree( ) : root_{}, data_{}
    {
        root_ = new OctNode<DataT>;
    }

    OctTree( const Box & zone, const list<DataT> & data ) : root_{},  data_{}
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

        data_.push_front(data);
        return root_->insert(data_.begin());
    }

    bool fill( const list<DataT> & data )
    {
        vector<DataT> out{};

        for (auto & elem : data)
            if (!root_->insert(elem))
                out.push_back(elem);

        if (out.empty())
            std::cout << "\nout:" << out << "\n";

        return !out.empty();
    }
};


#endif //ILAB2_OCTREE_H
