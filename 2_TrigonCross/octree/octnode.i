

template <typename DataT>
OctNode<DataT>::OctNode( ) : parent_{nullptr}, child_{}, zone_{}, data_{}
{}

template <typename DataT>
OctNode<DataT>::OctNode( Box zone, OctNode * parent) : parent_{parent}, child_{}, zone_{zone}
{}


template <typename DataT>
const vector<typename OctNode<DataT>::PairIt> & OctNode<DataT>::get_data( ) const
{
    return data_;
}

template <typename DataT>
const OctNode<DataT> ** OctNode<DataT>::get_children( ) const
{
    return child_;
}

template <typename DataT>
bool OctNode<DataT>::is_parent( ) const
{
    return has_children;
}

template <typename DataT>
bool OctNode<DataT>::is_in( const DataT & d ) const
{
    return zone_.is_in(d);
}

template <typename DataT>
bool OctNode<DataT>::is_in( const DataT * d ) const
{
    return zone_.is_in(*d);
}

template <typename DataT>
bool OctNode<DataT>::need_children( ) const
{
    return !has_children && data_.size() >= CHILDREN_NUM && zone_.diag() > MIN_DIAG;
}

template <typename DataT>
OctNode<DataT> * OctNode<DataT>::insert( PairIt data, bool hate_children )
{
    if (!is_in(data->first))
        return nullptr;

    if (!hate_children && need_children())
        divide();

    if (has_children)
    {
        for (auto ch : child_)
        {
            auto res = ch->insert(data);
            if (res != nullptr)
                return res;
        }
    }

    data_.push_back(data);
    data->second = this;
    return this;
}

template <typename DataT>
bool OctNode<DataT>::intersect_subtree( DataT obj )
{
    if (typeid(DataT) != typeid(Triangle))
    {
        std::cerr << "\n" << __func__ << " is only for type Triangle\n\n";
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



#define mid(A)                   \
     (min[A] + max[A]) / 2       \


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

    has_children = true;

    using VecIt = typename vector<PairIt>::iterator;
    std::vector<PairIt> new_data{};

    for (VecIt cur = data_.begin(), end = data_.end(); cur != end; ++cur)
    {
        bool in_ch{false};

        for (auto ch : child_)
            if (ch->is_in((*cur)->first))
            {
                (*cur)->second = ch->insert(*cur, true);
                in_ch = true;
                break;
            }

        if (!in_ch)
            new_data.push_back(*cur);
    }

    data_.clear();
    data_ = new_data;
}

template <typename DataT>
void OctNode<DataT>::clear_sub( )
{
    for (auto & ch_it : child_)
        if (ch_it != nullptr)
            ch_it->clear_sub();

    delete this;
}