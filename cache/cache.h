#ifndef ILAB2_CACHE_H
#define ILAB2_CACHE_H

#include <list>
#include <unordered_map>
#include <iostream>

// TODO: подумать нужно ли делать тип ключа шаблонным
template <typename T, typename KeyT = int>
struct Cache_t
{
    size_t cap;
    std::list<T> cache;

    using lst_it = typename std::list<T>::iterator;

    struct bucket_el
    {
        lst_it data;
        size_t call_num;
    };

    using u_map = typename std::unordered_map<KeyT, std::list<bucket_el>>;
    using u_map_it = typename u_map::iterator;

    u_map hash_tbl;

    Cache_t( size_t cap ) : cap(cap),
                            cache(cap)
    {}

    ~Cache_t( )
    {}

    T & request( const T & data )
    {
        KeyT key = hash(data) % cap;
        auto search = hash_tbl.find(key);

        if (search != hash_tbl.end())
        {
            //создаем новый элемент мапа
            //  put_in_cache();
        }
        else
        {
            //сравниваем данные в листе элементов бакетов с входными
            //  если нашли совпадение:
            //    возвращаем итератор на найденный элемент листа
            //    КОНЕЦ
            //
            //  если не нашли:
            //    put_in_cache();
        }
    }

    KeyT hash( const T & data)
    {
        return data;
    }
};

/*template <typename T, typename KeyT = int>
struct cache_t
{
    size_t sz_;
    std::list<T> cache_;

    typedef typename std::list<T>::iterator ListIt;
    std::unordered_map<int, ListIt> hash_;

    cache_t(size_t sz) : sz_(sz) {}

    bool full() const;
    bool lookup(const T *elem)
    {
        auto hit = hash_.find(elem->id);
        if (hit == hash_.end())
        {
            if (full())
            {
                hash_.erase(cache_.back().id);
                cache_.pop_back();
            }
            cache_.push_front(*elem);
            hash_[elem->id] = cache_.begin();
            return false;
        }

        auto eltit = hit->second;

        if (eltit != cache_.begin())
            cache_.splice(cache_.begin(), cache_, eltit, std::next(eltit));

        return true;
    }
};

struct page_t
{
    int id;   // page index: 1, 2, ... n
    int sz;      // page size
    char *data;  // page data
};*/



#endif //ILAB2_CACHE_H
