#ifndef ILAB2_OCTREE_H
#define ILAB2_OCTREE_H

#include <vector>
#include "octnode.h"

using std::vector;
using std::pair;

template <typename Data_t>
class OctTree
{
public:

    OctNode<Data_t> * root_;
    vector<Data_t> data_;

public:

    OctTree( ) : root_{}, data_{}
    {
        root_ = new OctNode<Data_t>;
    }

    OctTree( const Box & zone, const vector<Data_t> data = vector<Data_t>{0} ) : root_{},  data_{data}
    {
        root_ = new OctNode<Data_t>{zone};
    }

    ~OctTree( )
    {
        root_->clear_sub();
    }

    bool fill( const vector<Data_t> data )
    {
        vector<Data_t> out{};

        for (auto & elem : data)
            if (!root_->insert(elem))
                out.push_back(elem);

        if (out.empty())
            std::cout << "\nout:" << out << "\n";

        return !out.empty();
    }

    bool insert( const Data_t & data )
    {
        if (!root_->zone_.is_in(data))
            return false;

        Data_t tmp{data};
        data_.push_back(tmp);
        return root_->insert(tmp);
    }
};


#endif //ILAB2_OCTREE_H
