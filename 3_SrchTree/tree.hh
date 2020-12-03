#ifndef TREE_HH
#define TREE_HH

#include <cstdio>
#include <iostream>
#include <fstream>

#include "node.hh"

namespace F
{
    template <typename DataT>
    class Node;

    template <typename DataT>
    class NodeIt;
    
    template <typename DataT>
    class Tree final
    {
    private:

        Node<DataT> * root_;
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
        NodeIt<DataT> find( const FindT & data );

        template <typename FindT>
        NodeIt<DataT> lower_bound( const FindT & data );

        NodeIt<DataT> begin( ) const;
        NodeIt<DataT> end( ) const;

        void insert( const DataT & data );

        [[nodiscard]] int depth( ) const;
        [[nodiscard]] bool is_balanced( ) const;

        void remove( DataT & to_del );

        void print( ) const;
        void print_leafs( ) const;
        void print_lvl( int lvl ) const;
        void dump( const std::string &dotname,
                   const std::string &pngname ) const;
    };














    template <typename DataT>
    Tree<DataT>::Tree( ) : root_(nullptr),
                           el_num_(0)
    {}

    template <typename DataT>
    Tree<DataT>::Tree( const DataT & data ) : root_(new Node<DataT>(data)),
                                              el_num_(1)
    {}

    template <typename DataT>
    Tree<DataT>::~Tree( )
    {
        auto cur = root_->findmin();

        while (cur != nullptr)
        {
            auto tmp = cur;
            cur = cur->next_ptr();
            delete tmp;
        }
    }

    template <typename DataT>
    template <typename FindT>
    NodeIt<DataT> Tree<DataT>::find( const FindT & data )
    {
        return NodeIt<DataT> {root_->find(data)};
    }

    template <typename DataT>
    template <typename FindT>
    NodeIt<DataT> Tree<DataT>::lower_bound( const FindT & data )
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
                cur_p = cur_p->next_ptr();

            if (cur_p->data() < data)
            {
                beg_p = cur_p = cur_p->next_ptr();
                count -= step + 1;
            }
            else
                count = step;
        }

        return NodeIt{cur_p};
    }

    template <typename DataT>
    NodeIt<DataT> Tree<DataT>::begin( ) const
    {
        return NodeIt<DataT> {root_->findmin()};
    }

    template <typename DataT>
    NodeIt<DataT> Tree<DataT>::end( ) const
    {
        return NodeIt<DataT> {nullptr};
    }

    template <typename DataT>
    void Tree<DataT>::insert( const DataT & data )
    {
        if (el_num_ == 0)
            root_ = new Node<DataT>{data};
        else
            root_ = root_->insert(data);
        ++el_num_;
    }

    template <typename DataT>
    int Tree<DataT>::depth( ) const
    {
        return root_->depth();
    }

    template <typename DataT>
    bool Tree<DataT>::is_balanced( ) const
    {
        return abs(root_->diff()) <= 1;
    }

    template <typename DataT>
    void Tree<DataT>::remove( DataT & to_del )
    {
        --el_num_;
        root_ = root_->remove(to_del);
    }

    template <typename DataT>
    void Tree<DataT>::print( ) const
    {
        for (auto cur_p = root_->findmin(); cur_p != nullptr; cur_p = cur_p->next_ptr())
            cout << cur_p->data() << endl;
    }

    template <typename DataT>
    void Tree<DataT>::print_leafs( ) const
    {
        for (auto cur_p = root_->findmin(); cur_p != nullptr; cur_p = cur_p->next_ptr())
            if (!cur_p->has_children())
                cout << cur_p->data() << endl;
    }

    template <typename DataT>
    void Tree<DataT>::print_lvl( int lvl ) const
    {
        auto max_dpth = root_->depth();
        for (auto cur_p = root_->findmin(); cur_p != nullptr; cur_p = cur_p->next_ptr())
            if (cur_p->depth() == (max_dpth - lvl))
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
}

#endif //TREE_HH