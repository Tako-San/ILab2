#ifndef ILAB2_OCTNODE_H
#define ILAB2_OCTNODE_H

#include "../geom.h"

namespace Geom
{
    const unsigned CHILDREN_NUM = 3;
    const double MIN_DIAG = 0.3;

    using std::list;

    template <typename DataT>
    class OctTree;

    template <typename DataT>
    class OctNode final
    {
        friend class OctTree<DataT>;

    private:

        OctNode * parent_;
        OctNode * child_[8];

        bool has_ch_{false};

        list<DataT> data_{};
        Box zone_;

        int lvl_;

    private:

        OctNode();
        explicit OctNode( Box zone, OctNode * parent = nullptr );

        [[nodiscard]] bool is_parent( ) const;
        [[nodiscard]] bool is_in( const DataT & obj ) const;
        [[nodiscard]] bool need_children( ) const;

        OctNode * insert( const DataT & obj, bool hate_children = false );

        bool is_intersect( const DataT & obj, bool not_in_tree = false ) const;

        void print( ) const;

        void clear_sub( );
        void div_box( );
        void divide( );
    };


    /*
     *
     *
     *
     * OctNode class methods realisations
     *
     *
     *
     */


    template <typename DataT>
    OctNode<DataT>::OctNode( ) : parent_(nullptr),
                                 child_(),
                                 zone_(),
                                 lvl_(1)
    {}

    template <typename DataT>
    OctNode<DataT>::OctNode( Box zone, OctNode * parent) : parent_(parent),
                                                           child_(),
                                                           zone_(zone)
    {
        if (parent == nullptr)
            lvl_ = 1;
        else
            lvl_ = parent->lvl_ + 1;
    }

    template <typename DataT>
    bool OctNode<DataT>::is_parent( ) const
    {
        return has_ch_;
    }

    template <typename DataT>
    bool OctNode<DataT>::is_in( const DataT & obj ) const
    {
        return zone_.is_in(obj);
    }

    template <typename DataT>
    bool OctNode<DataT>::need_children( ) const
    {
        return (!has_ch_) && (data_.size() >= CHILDREN_NUM) && (zone_.diag() > MIN_DIAG);
    }

    template <typename DataT>
    OctNode<DataT> * OctNode<DataT>::insert( const DataT & obj, bool hate_children )
    {
        if (!is_in(obj))
            return nullptr;

        if (!hate_children && need_children())
            divide();

        if (has_ch_)
            for (auto ch : child_)
            {
                auto res = ch->insert(obj);
                if (res != nullptr)
                    return res;
            }

        data_.push_front(obj);
        return this;
    }

    template <typename DataT>
    bool OctNode<DataT>::is_intersect( const DataT & obj, bool not_in_tree ) const
    {
        if (typeid(DataT) != typeid(Triangle))
        {
            std::cerr << "\n" << __func__ << " is only for type Triangle\n\n";
            return false;
        }

        int credit = not_in_tree ? 0 : 1;

        for (auto cur = data_.begin(), end = data_.end(); cur != end; ++cur)
        {
            if (*cur == obj)
            {
                if (credit < 1)
                    return true;
                --credit;
                continue;
            }

            if (trian_intr3D(obj, *cur))
                return true;
        }

        if (has_ch_)
            for (auto ch : child_)
                if (ch->is_intersect(obj, not_in_tree))
                    return true;

        return false;
    }

    template <typename DataT>
    void OctNode<DataT>::print( ) const
    {
        if (has_ch_)
            for (auto child : child_)
                child->print();

        std::string indent{""};

        for (int i = 0; i < lvl_; ++i)
            indent += "  ";

        std::cout << indent << "BOX_MIN: " << zone_.get_min() << std::endl;
        std::cout << indent << "BOX_MAX: " << zone_.get_max() << std::endl;
        std::cout << indent << "data: " << std::endl;

        for (auto & obj : data_)
        {
            std::cout << indent;
            std::cout << obj << std::endl;
        }

        std::cout << std::endl;
    }

#define mid(A)                    \
    ((min[A] + max[A]) / 2)       \

    template <typename DataT>
    void OctNode<DataT>::div_box( )
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

    template <typename DataT>
    void OctNode<DataT>::divide( )
    {
        div_box();

        has_ch_ = true;

        for (auto cur = data_.begin(), end = data_.end(); cur != end; )
        {
            for (auto ch : child_)
                if (ch->is_in(*cur))
                {
                    auto & lst = ch->data_;
                    auto tmp = cur;
                    ++cur;
                    lst.splice(lst.begin(), data_, tmp);
                    break;
                }
            ++cur;
        }
    }

    template <typename DataT>
    void OctNode<DataT>::clear_sub( )
    {
        for (auto & ch_it : child_)
            if (ch_it != nullptr)
                ch_it->clear_sub();

        delete this;
    }


}
#endif //ILAB2_OCTNODE_H
