#ifndef ILAB2_CACHE_H
#define ILAB2_CACHE_H

#include <list>
#include <unordered_map>
#include <iostream>

template <typename T, typename KeyT = int>
struct cache_t
{
    size_t size_;
    std::list<T> cache_;

    struct bucket
    {
        typename std::list<T>::iterator lst_it;
        size_t call_num;
    };

    std::unordered_map<KeyT, bucket> hash_table;

    cache_t( size_t size_ ) : size_(size_)
    {}

    ~cache_t( )
    {}

    bool lookup( const T * elem)
    {

    }
};


#endif //ILAB2_CACHE_H
