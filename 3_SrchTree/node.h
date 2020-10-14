#ifndef MAP_NODE2_H
#define MAP_NODE2_H

#include <cstdio>
#include <iostream>
#include "pair.h"

using std::cout;
using std::endl;
using std::abs;

// using Data_t = typename Map_t;

template <typename Data_t>
class Node
{
public:
    Data_t data_;

    Node * prnt_;
    Node * left_;
    Node * rght_;

public:
    Node(): data_(), prnt_(nullptr),
            left_(nullptr), rght_(nullptr)
    {};

    Node( Data_t & data ) : data_(data), prnt_(nullptr),
                            left_(nullptr), rght_(nullptr)
    {};

    void set( Data_t &n_data, Node * prnt = nullptr )
    {
        data_ = n_data;
        prnt_ = prnt;
    }

    Node * add(Data_t & data)
    {
#define DIRTY_JOB(side)                        \
    if(side != nullptr)                        \
        return side->add(data);                \
    else                                       \
    {                                          \
        side = new Node;                       \
        side->set(data, this);                 \
        return side;                           \
    }                                          \

        if(data < data_)
        {
            DIRTY_JOB(left_)
        }
        else if(data > data_)
        {
            DIRTY_JOB(rght_)
        }
        else
            std::cout << "\nWARNING: idk what should i do, my king\n";

        return nullptr;
#undef DIRTY_JOB
    }

    Node * find( Data_t & n_data ) //tree
    {
        if((n_data > data_) && (rght_ != nullptr))
            return rght_->find(n_data);
        else if((n_data < data_) && (left_ != nullptr))
            return left_->find(n_data);
        else if(n_data == data_)
            return this;
        return nullptr;
    }

    int depth( ) //tree
    {
        if(this == nullptr)
            return 0;

        int depth = 1;

        int depth_l = left_->depth();
        int depth_r = rght_->depth();

        int subtr_max = (depth_l > depth_r)? depth_l : depth_r;

        depth += subtr_max;

        return depth;
    }
    
    bool is_balanced() //tree
    {
        int res = abs(left_->depth() - rght_->depth()) <= 1 ? 1 : 0;
        return res;
    }

    void del(Data_t &to_del) //tree
    {
        del(to_del.key);
    }
    
    void del(key_t key)
    {
        if (this == nullptr)
            return;
        if (key < data_)
            left_->del(key);
        else if (key > data_)
            rght_->del(key);
        else if (left_ != nullptr && rght_ != nullptr)
        {
            Node *tmp;
            for(tmp = rght_; tmp->left_!= nullptr; tmp = tmp->left);
            data_ = tmp->data_;
            rght_->del(data_.key);
        }
        else if (left_ != nullptr)
        {
            Node * tmp = left_;

            if (left_->left_ != nullptr)
                left_->left_->prnt_ = this;
            if (left_->rght_ != nullptr)
                left_->rght_->prnt_ = this;

            data_ = left_->data;

            rght_ = left_->rght_;
            left_= left_->left_;

            delete tmp;
        }
        else if (rght_ != nullptr)
        {
            Node * tmp = rght_;

            if (rght_->rght_ != nullptr)
                rght_->rght_->prnt_ = this;
            if (rght_->left_!= nullptr)
                rght_->left_->prnt_ = this;

            data_ = rght_->data_;

            left_= rght_->left_;
            rght_ = rght_->rght_;

            delete tmp;
        }
        else
        {
            if(prnt_->left_== this)
                prnt_->left_= nullptr;
            else
                prnt_->rght_ = nullptr;
            delete this;
        }
    }

    void clear() //tree
    {
        if(this == nullptr)
            return;

        if(left_!= nullptr)
            left_->clear();
        if(rght_ != nullptr)
            rght_->clear();

        delete this;
    }
    
    void print() //tree
    {
        if(left_!= nullptr)
            left_->print();

        if(prnt_ == nullptr)
            cout << *this << " - ROOT" << endl;
        else if(left_== nullptr && rght_ == nullptr)
            cout << *this << " - leaf" << endl;
        else
            cout << *this << endl;

        if(rght_ != nullptr)
            rght_->print();
    }
    
    void print_leafs() //tree
    {
        if(this == nullptr)
            return;

        if(left_== nullptr && rght_ == nullptr)
            std::cout << data_ <<"\n";
        else
        {
            left_->print_leafs();
            rght_->print_leafs();
        }
    }


    void print_lvl(int lvl) //tree
    {
        if(this == nullptr)
            return;
        else if(lvl == 0)
            std::cout << *this;
        else if(lvl > 0)
        {
            left_->print_lvl(lvl - 1);
            rght_->print_lvl(lvl - 1);
        }
    }

    friend std::ostream & operator << (std::ostream & ost, const Node &node)
    {
        //out<<"Data: ("<<node.data<<"), this: "<<&node<<", prnt_: "<<node.prnt_<<", lt: "<<node.left<<", rt: "<<node.rght_<<endl;
        ost << node.data_;

        return ost;
    }
    
    // friend class Tree;
};

#endif //MAP_NODE2_H
