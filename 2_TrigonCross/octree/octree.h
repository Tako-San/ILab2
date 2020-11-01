#ifndef ILAB2_OCTREE_H
#define ILAB2_OCTREE_H

#include <vector>
#include "octnode.h"

using std::vector;
using std::pair;

template <typename Data_t>
class OctTree
{
private:

    OctNode<Data_t> * root_;
    vector<Data_t> data_;

public:

    OctTree( ) : root_{new OctNode<Data_t>}, data_{}
    {}

    OctTree( const vector<Data_t> data ) : data_{data}
    {}

    ~OctTree( )
    {
        root_->clear_sub();
    }

    bool fill( const vector<Data_t> data )
    {
        vector<Data_t> out{};

        for (auto elem : data)
            if (!root_->insert(elem))
                out.push_back(elem);

        if (out.empty())
            std::cout << "\nout:" << out << "\n";

        return !out.empty();
    }

    bool insert( const Data_t & data )
    {
        return root_->insert(data);
    }
};


#endif //ILAB2_OCTREE_H
