#ifndef MAP_MAP_H
#define MAP_MAP_H

#include <cstdio>
#include <iostream>
#include <string>

#define val_t string
#define key_t long long int

using namespace std;

class Map_t
{
    key_t key;
    val_t val;

public:

    Map_t();
    Map_t(Map_t &map_data);
    Map_t(key_t n_key, val_t n_val);

    ~Map_t();

    Map_t& operator= (const Map_t &map_data);

    bool operator< (Map_t &map_data);
    bool operator<= (Map_t &map_data);
    bool operator> (Map_t &map_data);
    bool operator>= (Map_t &map_data);
    bool operator== (Map_t &map_data);

    friend std::ostream& operator<< (std::ostream &out, const Map_t &map_data);
    friend std::istream& operator>> (std::istream &in, Map_t &map_data);

    friend bool operator< (Map_t &map_data, key_t &key);
    friend bool operator< (key_t &key, Map_t &map_data);

    friend bool operator<= (Map_t &map_data, key_t &key);
    friend bool operator<= (key_t &key, Map_t &map_data);

    friend bool operator> (Map_t &map_data, key_t &key);
    friend bool operator> (key_t &key, Map_t &map_data);

    friend bool operator>= (Map_t &map_data, key_t &key);
    friend bool operator>= (key_t &key, Map_t &map_data);

    friend bool operator== (Map_t &map_data, key_t &key);
    friend bool operator== (key_t &key, Map_t &map_data);

    friend class Node;
    friend class Tree;
};

key_t map_cmp (const key_t * key1, const key_t * key2);

#endif //MAP_MAP_H
