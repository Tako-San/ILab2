#ifndef ILAB2_OCTNODE_H
#define ILAB2_OCTNODE_H

#include <vector>
#include "../geom/g_obj/vec.h"
#include "../geom/g_obj/box.h"

using std::vector;
using std::list;

template <typename DataT>
class OctTree;

template <typename DataT>
class OctNode final
{
public:

    OctNode * parent_;

    OctNode * child_[8];
    bool has_children{false};

    Box zone_;

    using DataIt = typename list<DataT>::iterator;
    vector<DataIt> data_;

    void clear_sub( )
    {
        if(this == nullptr)
            return;

        // std::cout << std::endl << "box: " << zone_ << std::endl;
        // for (auto elem : data_)
        //     std::cout << "      >>>  " << *elem << "\n";

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


    friend class OctTree<DataT>;


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
        return data_.size() >= 2 && zone_.diag() > 1 && !has_children;
    }

    bool insert( DataIt data/*MapIt data*/, bool hate_children = false )
    {
        /*std::cout << "HELLO, I AM HERE TO INSERT\n";
        std::cout << "box: " << zone_ << std::endl;

        for (DataIt item : data_)
            std::cout << "    item: " << *item << std::endl;

        std::cout << "    new item: " << *data << std::endl;*/

        if (!is_in(*data/*data->first*/))
            return false;

        if (!hate_children && need_children())
            divide();

        if (has_children)
            for (auto ch : child_)
                if (ch->is_in(*data/*data->first*/))
                    return ch->insert(data);

        data_.push_back(data);
        // data->second = this;
        return true;
    }

    OctNode<DataT> * find_box( const DataT & data )
    {
        if (!is_in(data))
            return nullptr;

        if (has_children)
            for (auto ch : child_)
                if (ch->is_in(data))
                    return find_box(data);

        return this;
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
        // std::cout << "\nHELLO, I AM HERE TO DIVIDE\n\n";

        div_box();

        has_children = true;

        using VecIt = typename vector<DataIt>::iterator;
        std::vector<DataIt> new_data{};

        for (VecIt cur = data_.begin(), end = data_.end(); cur != end; ++cur)
        {
            bool in_ch{false};

            for (auto ch : child_)
                if (ch->is_in(**cur))
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
