#ifndef TREE_HH
#define TREE_HH

#include <cstdio>
#include <iostream>
#include <fstream>

namespace F
{
    template <typename DataT>
    class Tree final
    {
    private:
        class Node;

    public:
        class iterator;

    private:

        Node * root_;
        int el_num_;

    public:

        Tree( );
        explicit Tree( const DataT & data );

        Tree( const Tree & ) = delete;
        Tree( Tree && ) = delete;

        ~Tree( );

        Tree & operator = ( const Tree & ) = delete;
        Tree operator = ( Tree && ) = delete;

        template <typename FindT>
        iterator find( const FindT & data ) const;

        template <typename FindT>
        iterator lower_bound( const FindT & data ) const;

        iterator begin( ) const;
        iterator end( ) const;

        void insert( const DataT & data );

        [[nodiscard]] int depth( ) const;
        [[nodiscard]] bool is_balanced( ) const;

        void remove( const DataT & to_del );

        void print( ) const;
        void print_leafs( ) const;
        void print_lvl( int lvl ) const;
        void dump( const std::string &dotname,
                   const std::string &pngname ) const;

    private:

        Node * remove( Node * node, const DataT & to_del );

    private:

        struct Node final
        {
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

            [[nodiscard]] int diff( ) const;
            [[nodiscard]] bool has_children( ) const;

            const DataT & data( ) const;

            Node * remove( const DataT & data );

            Node * findmin( ) const;
            Node * findmax( ) const;

            void dump( std::ofstream &oft ) const;

            void set_depth( );

            Node * balance( );
            Node * removemin( );

        private:

            Node * rot_rt( );
            Node * rot_lt( );

            void set_parent( Node * prnt );
            void set_right( Node * rght );
            void set_left( Node * left );
        };

    public:

        class iterator final
        {
        private:

            Node * ptr_;

        public:

            explicit iterator( Node * ptr );
            iterator( const iterator & it );

            iterator & operator=( const iterator & it );

            bool operator==( const iterator & it ) const;
            bool operator!=( const iterator & it ) const;

            const DataT & operator*( ) const;

            iterator & operator++( );
            iterator & operator--( );
        };
    };


    /*
     *
     *
     * Tree methods realisations
     *
     *
     */


    template <typename DataT>
    Tree<DataT>::Tree( ) : root_(nullptr),
                           el_num_(0)
    {}

    template <typename DataT>
    Tree<DataT>::Tree( const DataT & data ) : root_(new Node(data)),
                                              el_num_(1)
    {}

    template <typename DataT>
    Tree<DataT>::~Tree( )
    {
        auto cur = root_->findmin();

        while (cur != nullptr)
        {
            auto tmp = cur;
            cur = cur->next_;
            delete tmp;
        }
    }

    template <typename DataT>
    template <typename FindT>
    typename Tree<DataT>::iterator Tree<DataT>::find( const FindT & data ) const
    {
        auto cur = root_;

        while (cur != nullptr)
        {
            if (data == cur->data_)
                iterator{cur};

            if (data > cur->data_)
                cur = cur->rght_;
            else if (data < cur->data_)
                cur = cur->left_;
            else
                cur = nullptr;
        }

        return iterator{cur};
    }

    template <typename DataT>
    template <typename FindT>
    typename Tree<DataT>::iterator Tree<DataT>::lower_bound( const FindT & data ) const
    {
        auto beg_p = root_->findmin(),
             cur_p = beg_p;

        int count = el_num_;
        int step;

        while (count > 0 && cur_p)
        {
            cur_p = beg_p;
            step = count / 2;

            for (int i = 0; i < step; ++i)
                cur_p = cur_p->next_;

            if (cur_p->data() < data)
            {
                beg_p = cur_p = cur_p->next_;
                count -= step + 1;
            }
            else
                count = step;
        }

        return iterator{cur_p};
    }

    template <typename DataT>
    typename Tree<DataT>::iterator Tree<DataT>::begin( ) const
    {
        return iterator{root_->findmin()};
    }

    template <typename DataT>
    typename Tree<DataT>::iterator Tree<DataT>::end( ) const
    {
        return iterator{nullptr};
    }

    template <typename DataT>
    void Tree<DataT>::insert( const DataT & data )
    {
        if (el_num_ == 0)
        {
            root_ = new Node{data};
            ++el_num_;
            return;
        }

        auto cur = root_;

        while(data != cur->data_)
            if (data > cur->data_)
            {
                if (cur->rght_ == nullptr)
                {
                    auto & new_node = cur->rght_;
                    new_node = new Node{data, cur, cur->next_, cur};

                    if (cur->next_)
                        cur->next_->prev_ = new_node;

                    cur->next_ = new_node;
                    cur->set_depth();
                    ++el_num_;
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
                    new_node = new Node{data, cur, cur, cur->prev_};

                    if (cur->prev_)
                        cur->prev_->next_ = new_node;

                    cur->prev_ = new_node;
                    cur->set_depth();
                    ++el_num_;
                    break;
                }
                else
                    cur = cur->left_;
            }

        while (cur != root_)
        {
            cur = cur->balance();
            cur = cur->prnt_;
        }

        root_ =  root_->balance();
    }

    template <typename DataT>
    int Tree<DataT>::depth( ) const
    {
        return root_->dpth_;
    }

    template <typename DataT>
    bool Tree<DataT>::is_balanced( ) const
    {
        return abs(root_->diff()) <= 1;
    }

    template <typename DataT>
    void Tree<DataT>::remove( const DataT & to_del )
    {
        root_ = remove(root_, to_del);
    }

    template <typename DataT>
    void Tree<DataT>::print( ) const
    {
        for (auto cur_p = root_->findmin(); cur_p != nullptr; cur_p = cur_p->next_)
            cout << cur_p->data() << endl;
    }

    template <typename DataT>
    void Tree<DataT>::print_leafs( ) const
    {
        for (auto cur_p = root_->findmin(); cur_p != nullptr; cur_p = cur_p->next_)
            if (!cur_p->has_children())
                cout << cur_p->data() << endl;
    }

    template <typename DataT>
    void Tree<DataT>::print_lvl( int lvl ) const
    {
        auto max_dpth = root_->dpth_;
        for (auto cur_p = root_->findmin(); cur_p != nullptr; cur_p = cur_p->next_)
            if (cur_p->dpth_ == (max_dpth - lvl))
                cout << cur_p->data() << endl;
    }

    template <typename DataT>
    void Tree<DataT>::dump( const std::string &dotname,
                            const std::string &pngname ) const
    {
        std::ofstream fout;
        fout.open(dotname, std::ios::out);

        if (!fout.is_open())
        {
            std::cout << "Cannot open dump file: " << dotname << "\n";
            return;
        }
        fout << "digraph D {\n";
        if (root_ != nullptr)
            root_->dump(fout);

        fout << "}\n";
        fout.close();

        std::string promt = "dot " + dotname + " -Tpng > " + pngname;
        system(promt.c_str());
    }

    template <typename DataT>
    typename Tree<DataT>::Node * Tree<DataT>::remove( Node * node, const DataT & to_del )
    {
        if (node == nullptr)
            return nullptr;
        else if ( to_del < node->data_ )
            node->left_ = node->left_->remove(to_del);
        else if ( to_del > node->data_ )
            node->rght_ = node->rght_->remove(to_del);
        else
        {
            auto * q = node->left_;
            auto * r = node->rght_;

            if (node->prev_)
                node->prev_->next_ = node->next_;
            if (node->next_)
                node->next_->prev_ = node->prev_;

            auto parent = node->prnt_;

            --el_num_;
            delete node;

            if( r == nullptr )
                return q;

            auto * min = r->findmin();
            min->rght_ = r->removemin();
            min->left_ = q;

            if (parent)
            {
                if (min->data_ > parent->data_)
                    parent->rght_ = min;
                else
                    parent->left_ = min;
            }

            return min->balance();
        }

        return node->balance();
    }


    /*
     *
     *
     * Tree::iterator methods realisations
     *
     *
     */


    template <typename DataT>
    Tree<DataT>::Node::Node( const DataT & data,
                             Node * prnt,
                             Node * next,
                             Node * prev) : data_{data},
                                            prnt_{prnt},
                                            next_{next},
                                            prev_{prev}
    {
        set_depth();
    }

    template <typename DataT>
    int Tree<DataT>::Node::diff( ) const
    {
        int dl = (left_ == nullptr) ? 0 : left_->dpth_,
            dr = (rght_ == nullptr) ? 0 : rght_->dpth_;

        return dr - dl;
    }

    template <typename DataT>
    bool Tree<DataT>::Node::has_children( ) const
    {
        return (rght_ != nullptr) || (left_ != nullptr);
    }

    template <typename DataT>
    void Tree<DataT>::Node::set_depth( )
    {
        int dl = (left_ == nullptr) ? 0 : left_->dpth_,
            dr = (rght_ == nullptr) ? 0 : rght_->dpth_;

        dpth_ = std::max(dl, dr) + 1;
    }

    template <typename DataT>
    void Tree<DataT>::Node::set_parent( Node * prnt )
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
    void Tree<DataT>::Node::set_right( Node * rght )
    {
        rght_ = rght;

        if (rght_ != nullptr)
            rght_->prnt_ = this;

        set_depth();
    }

    template <typename DataT>
    void Tree<DataT>::Node::set_left( Node * left )
    {
        left_ = left;

        if (left_ != nullptr)
            left_->prnt_ = this;

        set_depth();
    }

    template <typename DataT>
    const DataT & Tree<DataT>::Node::data( ) const
    {
        return data_;
    }

    template <typename DataT>
    typename Tree<DataT>::Node * Tree<DataT>::Node::rot_rt( ) // правый поворот вокруг this
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
    typename Tree<DataT>::Node * Tree<DataT>::Node::rot_lt( ) // левый поворот вокруг this
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
    typename Tree<DataT>::Node * Tree<DataT>::Node::balance( ) // балансировка узла this
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
    typename Tree<DataT>::Node * Tree<DataT>::Node::findmin( ) const
    {
        auto cur = const_cast<Node *>(this);
        for (; cur->left_ != nullptr; cur = cur->left_);
        return cur;
    }

    template <typename DataT>
    typename Tree<DataT>::Node * Tree<DataT>::Node::findmax( ) const
    {
        auto cur = const_cast<Node *>(this);
        for (; cur->rght_ != nullptr; cur = cur->rght_);
        return cur;
    }

    template <typename DataT>
    typename Tree<DataT>::Node * Tree<DataT>::Node::removemin( ) // удаление узла с минимальным ключом из дерева p
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
    typename Tree<DataT>::Node * Tree<DataT>::Node::remove( const DataT & data ) // удаление ключа k из дерева p
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
    void Tree<DataT>::Node::dump( std::ofstream & oft ) const
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

    /*
     *
     *
     * Tree::iterator methods realisations
     *
     *
     */


    template <typename DataT>
    Tree<DataT>::iterator::iterator( const iterator & it ) : ptr_(it.ptr_)
    {}

    template <typename DataT>
    Tree<DataT>::iterator::iterator( Node * ptr ) : ptr_(ptr)
    {}

    template <typename DataT>
    typename Tree<DataT>::iterator & Tree<DataT>::iterator::operator=( const iterator & it )
    {
        if (ptr_ != it.ptr_)
            ptr_ = it.ptr_;
        return *this;
    }

    template <typename DataT>
    bool Tree<DataT>::iterator::operator==( const iterator & it ) const
    {
        return (ptr_ == it.ptr_);
    }

    template <typename DataT>
    bool Tree<DataT>::iterator::operator!=( const iterator & it ) const
    {
        return (ptr_ != it.ptr_);
    }

    template <typename DataT>
    const DataT & Tree<DataT>::iterator::operator*( ) const
    {
        return ptr_->data();
    }

    template <typename DataT>
    typename Tree<DataT>::iterator & Tree<DataT>::iterator::operator++( )
    {
        ptr_ = ptr_->next_;
        return *this;
    }

    template <typename DataT>
    typename Tree<DataT>::iterator & Tree<DataT>::iterator::operator--( )
    {
        ptr_ = ptr_->prev_;
        return *this;
    }
}

#endif //TREE_HH