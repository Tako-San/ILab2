#include "tree.h"

#include "node.h"

Tree::Tree()
{
    root = new Node;
    //std::cout<<"Tree constructor without arguments. "<<this<<"\n\n";
}

Tree::Tree(Data_t &n_data)
{
    root = new Node(n_data);
    //std::cout<<"Tree constructor with n_data. "<<this<<"\n\n";
}

Tree::Tree(key_t key, val_t val)
{
    root = new Node(key, val);
    //*root = Node(key, val);
    //std::cout<<"Node constructor with key, val. "<<this<<"\n\n";
}

void Tree::print()
{
    root->print();
}

void Tree::print_leafs()
{
    if(root == nullptr)
        return;

    root->print_leafs();
}

void Tree::print_lvl(int lvl)
{
    if(root == nullptr)
        return;

    root->print_lvl(lvl);
}

void Tree::clear()
{
    if(root == nullptr)
        return;

    root->clear();
}


void Tree::add(Data_t &n_data)
{
    root->add(n_data);
}

void Tree::add(key_t key, val_t val)
{
    root->add(key, val);
}



Data_t& Tree::find(Data_t &n_data)
{
    Node * res = root->find(n_data);
    return res->data;
}

Data_t& Tree::find(key_t key)
{
    Node * res = root->find(key);
    return res->data;
}


int Tree::depth()
{
    return root->depth();
}

bool Tree::is_balanced()
{
    return root->is_balanced();
}

void Tree::del(key_t key)
{
    root->del(key);
}

void Tree::del(Data_t &to_del)
{
    root->del(to_del);
}

val_t &Tree::operator[](key_t key)
{
    Node * tmp = root->find(key);
    if(tmp != nullptr)
        return tmp->data.val;
    else
        tmp = root->add(key);
    return tmp->data.val;
}
