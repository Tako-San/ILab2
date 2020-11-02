#ifndef ILAB2_OCTNODE_H
#define ILAB2_OCTNODE_H

#include <vector>
#include "../geom/g_obj/vec.h"
#include "../geom/g_obj/box.h"

#include "../geom/geom.h"

const unsigned CHILDREN_NUM = 7;

using std::vector;
using std::list;
using std::pair;

template <typename DataT>
class OctTree;

template <typename DataT>
class OctNode final
{
private:

    OctNode * parent_;

    OctNode * child_[8];
    bool has_children{false};

    Box zone_;

    using PairIt = typename list<pair<DataT, OctNode<DataT> *>>::iterator;
    vector<PairIt> data_;

    void clear_sub( )
    {
        if(this == nullptr)
            return;

        for (auto & ch_it : child_)
            if (ch_it != nullptr)
                ch_it->clear_sub();

        delete this;
    }

    friend class OctTree<DataT>;
    friend bool intersect_octree( typename list<pair<Triangle, OctNode<Triangle> *>>::iterator pair_it );

public:

    OctNode( ) : parent_{nullptr}, child_{}, zone_{}, data_{}
    {}

    explicit OctNode( Box zone, OctNode * parent = nullptr ) : parent_{parent}, child_{}, zone_{zone}
    {}

    OctNode( const OctNode & ) = default;

    OctNode & operator = ( const OctNode & ) = default;

    const vector<PairIt> & get_data( ) const
    {
        return data_;
    }

    const OctNode ** get_children( ) const
    {
        return child_;
    }

    bool is_parent( ) const
    {
        return has_children;
    }

    bool is_in( const DataT & d ) const
    {
        return zone_.is_in(d);
    }

    bool is_in( const DataT * d ) const
    {
        return zone_.is_in(*d);
    }

    bool need_children( ) const
    {
        return data_.size() >= CHILDREN_NUM && zone_.diag() > 1 && !has_children;
    }

    OctNode<DataT> * insert( PairIt data, bool hate_children = false )
    {
        if (!is_in(data->first))
            return nullptr;

        if (!hate_children && need_children())
            divide();

        if (has_children)
            for (auto ch : child_)
                if (ch->is_in(data->first))
                    return ch->insert(data);

        data_.push_back(data);
        return this;
    }

    bool intersect_subtree( DataT obj )
    {
        if (typeid(DataT) != typeid(Triangle))
        {
            std::cout << "\n" << __func__ << " is only for type Triangle\n\n";
            return false;
        }

        for (auto mate : data_)
            if (is_intersect3D(obj, mate->first))
                return true;

        if (has_children)
            for (auto ch : child_)
                if (ch->intersect_subtree(obj))
                    return true;

        return false;
    }


private:

    #define mid(A)                  \
        (min[A] + max[A]) / 2       \

    void div_box( )
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
            child_[i] = new OctNode<DataT> {sub_box[i], this};
    }
    #undef mid

    void divide( )
    {
        div_box();

        has_children = true;

        using VecIt = typename vector<PairIt>::iterator;
        std::vector<PairIt> new_data{};

        for (VecIt cur = data_.begin(), end = data_.end(); cur != end; ++cur)
        {
            bool in_ch{false};

            for (auto ch : child_)
                if (ch->is_in(((*cur)->first)))
                {
                    ch->insert(*cur, true);
                    in_ch = true;
                    break;
                }

            if (!in_ch)
                new_data.push_back(*cur);
        }

        data_.clear();
        data_ = new_data;
    }
};


#endif //ILAB2_OCTNODE_H
