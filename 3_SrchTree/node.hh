#ifndef NODE_HH
#define NODE_HH

#include <cstdio>
#include <iostream>
#include <fstream>


namespace F
{
    using std::cout;
    using std::endl;

    template <typename DataT>
    class Tree;

    template <typename DataT>
    class NodeIt;

    template <typename DataT>
    class Node final
    {
    private:

        DataT  data_;
        int    dpth_{1};

        Node * prnt_{nullptr};

        Node * left_{nullptr};
        Node * rght_{nullptr};

        Node * next_{nullptr};
        Node * prev_{nullptr};

    public:

        explicit Node( const DataT & data = nullptr,
                       Node * prnt = nullptr,
                       Node * next = nullptr,
                       Node * prev = nullptr);

        [[nodiscard]] int depth( ) const;
        [[nodiscard]] int diff( ) const;
        [[nodiscard]] bool has_children( ) const;

        const DataT & data( ) const;
        NodeIt<DataT> next( ) const;
        NodeIt<DataT> prev( ) const;

        Node * insert( const DataT & data );
        Node * remove( const DataT & data );

        Node * findmin( ) const;
        Node * findmax( ) const;

        Node * next_ptr( ) const;
        Node * prev_ptr( ) const;

        void print_lvl( int lvl )  const;
        void dump( std::ofstream &oft ) const;

    private:
        Node * rot_rt( );

        Node * rot_lt( );
        Node * balance( );

        Node * removemin( );

        void set_depth( );

        void set_parent( Node * prnt );
        void set_right( Node * rght );
        void set_left( Node * left );
    };

    template <typename DataT>
    class NodeIt final
    {
    private:

        Node<DataT> * ptr_;

    public:

        explicit NodeIt( Node<DataT> * ptr );
        NodeIt( const NodeIt & it );

        NodeIt & operator=( const NodeIt & it );

        bool operator==( const NodeIt & it ) const;
        bool operator!=( const NodeIt & it ) const;

        const DataT & operator*( ) const;

        NodeIt & operator++( );
        NodeIt & operator--( );
    };









/*
 * Classes methods realisations
 */













    template <typename DataT>
    Node<DataT>::Node( const DataT & data,
                       Node<DataT> * prnt,
                       Node<DataT> * next,
                       Node<DataT> * prev) : data_{data},
                                             prnt_{prnt},
                                             next_{next},
                                             prev_{prev}
    {
        set_depth();
    }

    template <typename DataT>
    int Node<DataT>::depth( ) const
    {
        return dpth_;
    }

    template <typename DataT>
    int Node<DataT>::diff( ) const
    {
        int dl = (left_ == nullptr) ? 0 : left_->dpth_,
            dr = (rght_ == nullptr) ? 0 : rght_->dpth_;

        return dr - dl;
    }

    template <typename DataT>
    bool Node<DataT>::has_children( ) const
    {
        return (rght_ != nullptr) || (left_ != nullptr);
    }

    template <typename DataT>
    void Node<DataT>::set_depth( )
    {
        int dl = (left_ == nullptr) ? 0 : left_->dpth_,
            dr = (rght_ == nullptr) ? 0 : rght_->dpth_;

        dpth_ = std::max(dl, dr) + 1;
    }

    template <typename DataT>
    void Node<DataT>::set_parent( Node<DataT> * prnt )
    {
        prnt_ = prnt;

        if (prnt_ == nullptr)
            return;

        if (data_ > prnt->data_)
            prnt_->rght_ = this;
        else if (data_ < prnt->data_)
            prnt_->left_ = this;

        prnt_->set_depth();
    }

    template <typename DataT>
    void Node<DataT>::set_right( Node<DataT> * rght )
    {
        rght_ = rght;

        if (rght_ != nullptr)
            rght_->prnt_ = this;

        set_depth();
    }

    template <typename DataT>
    void Node<DataT>::set_left( Node<DataT> * left )
    {
        left_ = left;

        if (left_ != nullptr)
            left_->prnt_ = this;

        set_depth();
    }

    template <typename DataT>
    const DataT & Node<DataT>::data( ) const
    {
        return data_;
    }

    template <typename DataT>
    NodeIt<DataT> Node<DataT>::next( ) const
    {
        return NodeIt<DataT>{next_};
    }

    template <typename DataT>
    NodeIt<DataT> Node<DataT>::prev( ) const
    {
        return NodeIt<DataT>{prev_};
    }

    template <typename DataT>
    Node<DataT> * Node<DataT>::rot_rt( ) // правый поворот вокруг this
    {
        Node * that = left_;
        that->set_parent(prnt_);

        set_left(that->rght_);
        that->set_right(this);

        set_depth();
        that->set_depth();

        return that;
    }

    template <typename DataT>
    Node<DataT> * Node<DataT>::rot_lt( ) // левый поворот вокруг this
    {
        Node * that = rght_;
        that->set_parent(prnt_);

        set_right(that->left_);
        that->set_left(this);

        set_depth();
        that->set_depth();

        return that;
    }

    template <typename DataT>
    Node<DataT> * Node<DataT>::balance( ) // балансировка узла this
    {
        set_depth();

        int cur_diff = diff();

        if( cur_diff == 2 )
        {
            if( rght_->diff() < 0 )
            {
                rght_ = rght_->rot_rt();
                set_depth();
            }
            return rot_lt();
        }
        else if( cur_diff == -2 )
        {
            if( left_->diff() > 0 )
            {
                left_ = left_->rot_lt();
                set_depth();
            }
            return rot_rt();
        }

        return this; // балансировка не нужна
    }

    template <typename DataT>
    Node<DataT> * Node<DataT>::findmin( ) const
    {
        auto cur = const_cast<Node<DataT> *>(this);
        for (; cur->left_ != nullptr; cur = cur->left_);
        return cur;
    }

    template <typename DataT>
    Node<DataT> * Node<DataT>::findmax( ) const
    {
        auto cur = const_cast<Node<DataT> *>(this);
        for (; cur->rght_ != nullptr; cur = cur->rght_);
        return cur;
    }

    template <typename DataT>
    Node<DataT> * Node<DataT>::removemin( ) // удаление узла с минимальным ключом из дерева p
    {
        if( left_ == nullptr )
        {
            auto * res = rght_;
            delete this;
            return res;
        }

        left_ = left_->removemin();
        return balance();
    }

    template <typename DataT>
    Node<DataT> * Node<DataT>::remove( const DataT & data ) // удаление ключа k из дерева p
    {
        if( data < data_ )
            left_ = left_->remove(data);
        else if( data > data_ )
            rght_ = rght_->remove(data);
        else
        {
            auto * q = left_;
            auto * r = rght_;

            if (prev_)
                prev_->next_ = next_;
            if (next_)
                next_->prev_ = prev_;

            delete this;

            if( r == nullptr )
                return q;

            auto * min = r->findmin();
            min->rght_ = r->removemin();
            min->left_ = q;

            return min->balance();
        }
        return balance();
    }

    template <typename DataT>
    Node<DataT> * Node<DataT>::insert( const DataT & data )
    {
        auto cur = this;

        while(data != cur->data_)
            if (data > cur->data_)
            {
                if (cur->rght_ == nullptr)
                {
                    auto & new_node = cur->rght_;
                    new_node = new Node<DataT>{data, cur, cur->next_, cur};

                    if (cur->next_)
                        cur->next_->prev_ = new_node;

                    cur->next_ = new_node;
                    cur->set_depth();
                    break;
                }
                else
                    cur = cur->rght_;
            }
            else
            {
                if (cur->left_ == nullptr)
                {
                    auto & new_node = cur->left_;
                    new_node = new Node<DataT>{data, cur, cur, cur->prev_};

                    if (cur->prev_)
                        cur->prev_->next_ = new_node;

                    cur->prev_ = new_node;
                    cur->set_depth();
                    break;
                }
                else
                    cur = cur->left_;
            }

        while (cur != this)
        {
            cur = cur->balance();
            cur = cur->prnt_;
        }

        return balance();
    }

    template <typename DataT>
    void Node<DataT>::print_lvl( int lvl ) const
    {
        if(lvl == 0)
            std::cout << data_ << " ";
        else if(lvl > 0)
        {
            left_->print_lvl(lvl - 1);
            rght_->print_lvl(lvl - 1);
        }
    }

    template <typename DataT>
    void Node<DataT>::dump( std::ofstream & oft ) const
    {
        if (left_ != nullptr)
        {
            oft << data_ << " -> " << left_->data_ << ";\n";
            left_->dump(oft);
        }

        if (rght_ != nullptr)
        {
            oft << data_ << " -> " << rght_->data_ << " [style=dashed];\n";
            rght_->dump(oft);
        }

        if (next_ != nullptr)
            oft << data_ << " -> " << next_->data_ << " [color=red];\n";

        oft << data_ << ";\n";
    }

    template <typename DataT>
    Node<DataT> * Node<DataT>::next_ptr( ) const
    {
        return next_;
    }

    template <typename DataT>
    Node<DataT> * Node<DataT>::prev_ptr( ) const
    {
        return prev_;
    }




















    template <typename DataT>
    NodeIt<DataT>::NodeIt( const NodeIt<DataT> & it ) : ptr_(it.ptr_)
    {}

    template <typename DataT>
    NodeIt<DataT>::NodeIt( Node<DataT> * ptr ) : ptr_(ptr)
    {}

    template <typename DataT>
    NodeIt<DataT> & NodeIt<DataT>::operator=( const NodeIt<DataT> & it )
    {
        if (ptr_ != it.ptr_)
            ptr_ = it.ptr_;
        return *this;
    }

    template <typename DataT>
    bool NodeIt<DataT>::operator==( const NodeIt<DataT> & it ) const
    {
        return (ptr_ == it.ptr_);
    }

    template <typename DataT>
    bool NodeIt<DataT>::operator!=( const NodeIt<DataT> & it ) const
    {
        return (ptr_ != it.ptr_);
    }

    template <typename DataT>
    const DataT & NodeIt<DataT>::operator*( ) const
    {
        return ptr_->data();
    }

    template <typename DataT>
    NodeIt<DataT> & NodeIt<DataT>::operator++( )
    {
        return (*this = ptr_->next());
    }

    template <typename DataT>
    NodeIt<DataT> & NodeIt<DataT>::operator--( )
    {
        return (*this = ptr_->prev());
    }

}
#endif //NODE_HH
