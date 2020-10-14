#include "node.h"

Node::Node() : data(),
               parent(nullptr),
               left(nullptr),
               right(nullptr)
{
    //std::cout<<"Node constructor without arguments. "<<this<<"\n\n";
}

Node::Node(Data_t &n_data) : data(n_data),
                             parent(nullptr),
                             left(nullptr),
                             right(nullptr)
{
    //std::cout<<"Node constructor with n_data. "<<this<<"\n\n";
}

Node::Node(key_t key, val_t val) : data(key, val),
                                   parent(nullptr),
                                   left(nullptr),
                                   right(nullptr)
{
    //std::cout<<"Node constructor with key, val. "<<this<<"\n\n";
}



std::ostream& operator<< (std::ostream &out, const Node &node)
{
    //out<<"Data: ("<<node.data<<"), this: "<<&node<<", parent: "<<node.parent<<", lt: "<<node.left<<", rt: "<<node.right<<endl;
    out << node.data;

    return out;
}



void Node::set(key_t key, val_t val, Node * n_parent)
{
    data = Map_t(key, val);
    parent = n_parent;
}

void Node::set(Data_t &n_data, Node * n_parent)
{
    data = n_data;
    parent = n_parent;
}



void Node::print()
{
    if(left != nullptr)
        left->print();

    if(parent == nullptr)
        cout << *this << " - ROOT" << endl;
    else if(left == nullptr && right == nullptr)
        cout << *this << " - leaf" << endl;
    else
        cout << *this << endl;

    if(right != nullptr)
        right->print();
}

void Node::print_leafs()
{
    if(this == nullptr)
        return;

    if(left == nullptr && right == nullptr)
        std::cout << data <<"\n";
    else
    {
        left->print_leafs();
        right->print_leafs();
    }
}

void Node::print_lvl(int lvl)
{
    if(this == nullptr)
        return;
    else if(lvl == 0)
        std::cout << *this;
    else if(lvl > 0)
    {
        left->print_lvl(lvl - 1);
        right->print_lvl(lvl - 1);
    }
    else
        return;
}

void Node::clear()
{
    if(this == nullptr)
        return;

    if(left != nullptr)
        left->clear();
    if(right != nullptr)
        right->clear();

    delete this;
}


Node * Node::add(Data_t &n_data)
{
#define DIRTY_JOB(side)                        \
    if(side != nullptr)                        \
        return side->add(n_data);              \
    else                                       \
    {                                          \
        side = new Node;                       \
        side->set(n_data, this);               \
        return side;                           \
    }                                          \

    std::cout<<"\nADD FUNC\n";

    if(n_data < data)
    {
        DIRTY_JOB(left)
    }
    else if(n_data > data)
    {
        DIRTY_JOB(right)
    }

    return nullptr;

#undef DIRTY_JOB
}

/*Node * Node::add(key_t key, val_t val)
{
    Map_t tmp(key, val);
    return add(tmp);
}*/

Node * Node::add(key_t key, val_t val)
{
#define DIRTY_JOB(side)                            \
    if(side != nullptr)                            \
        return side->add(key, val);                \
    else                                           \
    {                                              \
        std::cout << "\nDYNAMYC MEMORY: NEW\n";    \
        side = new Node;                           \
        side->set(key, val, this);                 \
        return side;                               \
    }                                              \

    //std::cout<<"\nADD FUNC\n";

    if(key < data)
    {
        DIRTY_JOB(left)
    }
    else if(key > data)
    {
        DIRTY_JOB(right)
    }

    return nullptr;

#undef DIRTY_JOB
}



Node * Node::find(Data_t &n_data)
{
    if((n_data > data) && (right != nullptr))
        return right->find(n_data);
    else if((n_data < data) && (left != nullptr))
        return left->find(n_data);
    else if(n_data == data)
        return this;
    return nullptr;
}

Node * Node::find(key_t key)
{
    if((key > data) && (right != nullptr))
        return right->find(key);
    else if((key < data) && (left != nullptr))
        return left->find(key);
    else if(key == data)
        return this;
    return nullptr;
}


int Node::depth()
{
    if(this == nullptr)
        return 0;

    int depth = 1;

    int depth_l = left->depth();
    int depth_r = right->depth();

    int subtr_max = (depth_l > depth_r)? depth_l : depth_r;

    depth += subtr_max;

    return depth;
}

bool Node::is_balanced()
{
    int res = abs(left->depth() - right->depth()) <= 1 ? 1 : 0;
    return res;
}

void Node::del(key_t key)
{
    if (this == nullptr)
        return;
    if (key < data)
        left->del(key);
    else if (key > data)
        right->del(key);
    else if (left != nullptr && right != nullptr)
    {
        Node *tmp;
        for(tmp = right; tmp->left != nullptr; tmp = tmp->left);
        data = tmp->data;
        right->del(data.key);
    }
    else if (left != nullptr)
    {
        Node * tmp = left;

        if (left->left != nullptr)
            left->left->parent = this;
        if (left->right != nullptr)
            left->right->parent = this;

        data = left->data;

        right = left->right;
        left = left->left;

        delete tmp;
    }
    else if (right != nullptr)
    {
        Node * tmp = right;

        if (right->right != nullptr)
            right->right->parent = this;
        if (right->left != nullptr)
            right->left->parent = this;

        data = right->data;

        left = right->left;
        right = right->right;

        delete tmp;
    }
    else
    {
        if(parent->left == this)
            parent->left = nullptr;
        else
            parent->right = nullptr;
        delete this;
    }
}

void Node::del(Data_t &to_del)
{
    del(to_del.key);
}