#ifndef ILAB2_OCTNODE_H
#define ILAB2_OCTNODE_H

#include <vector>
#include "../geom/g_obj/vec.h"
#include "../geom/g_obj/box.h"

using std::vector;

template <typename Data_t>
class OctTree;

template <typename Data_t>
class OctNode final
{
public:
    
    OctNode * parent_;

    OctNode * child_[8];
    bool has_children{false};

    Box zone_;
    vector<Data_t *> data_;

    using Data_it = typename vector<Data_t *>::iterator;

    void clear_sub( )
    {
        if(this == nullptr)
            return;

        for (auto & ch_it : child_)
            if (ch_it != nullptr)
                ch_it->clear_sub();

        delete this;
    }

public:

    OctNode( ) : parent_{nullptr}, child_{}, zone_{}, data_{}
    {}

    explicit OctNode( Box zone, OctNode * parent = nullptr ) : parent_{parent}, child_{}, zone_{zone}
    {}

    OctNode( const OctNode & ) = default;

    OctNode & operator = ( const OctNode & ) = default;


    friend class OctTree<Data_t>;


    bool is_in( const Data_t & d )
    {
        return zone_.is_in(d);
    }

    bool is_in( const Data_t * d )
    {
        return zone_.is_in(*d);
    }

    bool need_children( )
    {
        /*if (data_.size() >= 2)
            return true;
        return false;*/
        return data_.size() >= 2 && zone_.diag() > 1;
    }

    bool insert( Data_t & data, bool hate_children = false )
    {
        if (!zone_.is_in(data))
            return false;

        if (!hate_children && !has_children && need_children())
            divide();

        if (has_children)
            for (auto & ch_it : child_)
                if (ch_it->zone_.is_in(data))
                    return ch_it->insert(data);

        data_.push_back(&data);
        return true;
    }

    #define mid(A)                  \
        (min[A] + max[A]) / 2       \

    void divide( )
    {
        std::cout << "HELLO, I AM HERE TO DIVIDE\n";
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
            child_[i] = new OctNode<Data_t> {sub_box[i], this};

        has_children = true;

        for (Data_it cur = data_.begin(), end = data_.end(); cur != end; ++cur)
        {
            bool in_ch{false};
            for (int i = 0; i < 8; ++i)
                if (child_[i]->insert(**cur, true))
                {
                    in_ch = true;
                    break;
                }
            if (in_ch)
                std::cout << "doin stuff\n";
                // data_.erase(cur);
        }
    }
    #undef mid
};


#endif //ILAB2_OCTNODE_H
