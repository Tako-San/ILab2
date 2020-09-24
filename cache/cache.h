#ifndef ILAB2_CACHE_H
#define ILAB2_CACHE_H

#include <list>
#include <unordered_map>
#include <iostream>

#include <string>
#include <cstdlib>

template <typename T, typename KeyT = long long int>
class Cache_t
{
private:

    struct Page;
    struct Node;
    struct FreqEl;

    using NodeLst = typename std::list<Node>;
    using Freqlst = typename std::list<FreqEl>;

    using NodeIt = typename NodeLst::iterator;
    using FreqIt = typename Freqlst::iterator;

    using Map = typename std::unordered_map<KeyT, NodeIt>;
    using MapIt = typename Map::iterator;

    struct Page
    {
        KeyT id;
        T data;

        Page( KeyT id, T data ) : id(id), data(data)
        {}
    };

    struct Node
    {
        Page page;
        FreqIt head;

        Node( Page page, FreqIt head ) : page(page), head(head)
        {}

        Node( KeyT id, T data, FreqIt head ) : page(Page(id, data)),
                                               head(head)
        {}
    };

    struct FreqEl
    {
        size_t hits;
        NodeLst nodes;

        explicit FreqEl( size_t hits ) : hits(hits), nodes()
        {}
    };

    size_t capacity;
    size_t counter;

    Freqlst freq_lst;
    Map hash_tbl;

public:

    explicit Cache_t( size_t capacity ) : capacity(capacity),
                                          counter(0),
                                          freq_lst(),
                                          hash_tbl()
    {}


    T & request( KeyT key )
    {
        MapIt srch = hash_tbl.find(key);

        if (srch != hash_tbl.end())
        {
            increment(srch);
            return srch->second->page.data;
        }

        NodeIt tmp = put_in_cache(key);
        hash_tbl[key] = tmp;

        return tmp->page.data;
    }


    size_t get_counter() const
    {
        return counter;
    }

    template<typename Tp, typename KeyTp>
    friend std::ostream & operator << ( std::ostream &, const Cache_t<Tp, KeyTp> &);

private:

    NodeIt put_in_cache( KeyT key )
    {
        T data = get_from_web(key);

        if (hash_tbl.size() >= capacity)
            del_min();

        if (freq_lst.size() == 0 || freq_lst.front().hits > 0)
            freq_lst.push_front(FreqEl(0));


        NodeLst & nodes = freq_lst.front().nodes;

        nodes.push_front(Node(key, data, freq_lst.begin()));

        return nodes.begin();
    }

    T get_from_web( KeyT key ) const
    {
        return 10 * key;
    }

    void del_min( )
    {
        NodeLst & nodes = freq_lst.front().nodes;
        KeyT key = nodes.front().page.id;

        nodes.erase(nodes.begin());
        hash_tbl.erase(key);
    }

    void increment( MapIt map_it )
    {
        ++counter;

        FreqIt & cur_fr = map_it->second->head;
        FreqIt old_fr = cur_fr;

        size_t cur_hits = old_fr->hits + 1;

        ++cur_fr;

        if (cur_fr == freq_lst.end() || cur_fr->hits != cur_hits)
        {
            freq_lst.insert(cur_fr, FreqEl(cur_hits));
            --cur_fr;
        }

        NodeLst & nodes_new = cur_fr->nodes;
        NodeLst & nodes_old = old_fr->nodes;

        nodes_new.splice(nodes_new.begin(), nodes_old, map_it->second);

        if (nodes_old.empty())
            freq_lst.erase(old_fr);
    }
};


template<typename T, typename KeyT = long long int>
std::ostream & operator << ( std::ostream & ost, const Cache_t<T, KeyT> & cache)
{
    ost << "--------------------------------------------\n";
    for (auto & fl : cache.freq_lst)
    {
        ost << "Hits: " << fl.hits << "\n";
        for (auto & nl : fl.nodes)
        {
            ost << "    Key: " << nl.page.id
                << ", Data: " << nl.page.data << "\n";
        }
        ost << "\n";
    }
    ost << "--------------------------------------------\n";

    return ost;
}

#endif //ILAB2_CACHE_H
