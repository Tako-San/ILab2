#ifndef ILAB2_OCTNODE_H
#define ILAB2_OCTNODE_H

#include <vector>
#include "../geom/g_obj/vec.h"
#include "../geom/g_obj/box.h"

template <typename Data_t>
class OctNode final
{
private:
    
    OctNode * parent_;
    OctNode * child_[8];

    Box zone_;

    std::vector<Data_t*> data_;

    void clear_sub( )
    {
        if(this == nullptr)
            return;

        for (int i = 0; i < 8; ++i)
            if (child_[i] != nullptr)
                child_[i]->clear_sub();

        delete this;
    }

public:

    OctNode( ) : parent_{nullptr}, child_{}, zone_{}, data_{}
    {}

    OctNode( Box zone, OctNode * parent = nullptr ) : parent_{parent}, child_{}, zone_{zone}
    {}

    OctNode( const OctNode & ) = default;

    OctNode & operator = ( const OctNode & ) = default;

    bool is_in( const Data_t & d )
    {
        return zone_.is_in(d);
    }

    bool is_in( const Data_t * d )
    {
        return zone_.is_in(*d);
    }

#define mid(A)                  \
    (min[A] + max[A]) / 2       \

    void divide( )
    {
        Box sub_box[8] = {};

        Vec min{zone_.get_min()};
        Vec max{zone_.get_max()};

        double minx = min[X], miny = min[Y], minz = min[Z],
               maxx = max[X], maxy = max[Y], maxz = max[Z],
               midx = mid(X), midy = mid(Y), midz = mid(Z);

        sub_box[0] = Box{{minx, miny, minz}, {midx, midy, midz}};
        sub_box[1] = Box{{minx, midy, minz}, {midx, maxy, midz}};
        sub_box[2] = Box{{midx, midy, minz}, {maxx, maxy, midz}};
        sub_box[3] = Box{{midx, miny, minz}, {maxx, midy, midz}};
        sub_box[4] = Box{{minx, miny, midz}, {midx, midy, maxz}};
        sub_box[5] = Box{{minx, midy, midz}, {midx, maxy, maxz}};
        sub_box[6] = Box{{midx, midy, midz}, {maxx, maxy, maxz}};
        sub_box[7] = Box{{midx, miny, midz}, {maxx, midy, maxz}};

        for (int i = 0; i < 8; ++i)
            child_ = new OctNode<Data_t> {sub_box[i], this};

        for (auto dat : data_)
        {
            bool in_child = false;

            for (int i = 0; i < 8; ++i)
                if (child_[i]->is_in(dat))
                {
                    child_->data_.push_back(dat);
                    in_child = true;
                    break;
                }

            if (in_child)
                data_.erase(dat);
        }
    }

#undef mid

    bool insert( Data_t & data )
    {
        if (!zone_.is_in(data))
            return false;

        for (int i = 0; i < 8; ++i)
            if (child_[i] != nullptr)
                if (child_[i]->zone_.is_in(data))
                    return child_[i].insert(data);

        data_.push_back(&data);
        return true;
    }
};


#endif //ILAB2_OCTNODE_H
