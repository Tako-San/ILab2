#include "map.h"


/**
 * Map_t no args constructor.
 */
Map_t::Map_t() : key(-1),
                 val{0}
{
    std::cout<<"Map_t constructor without arguments. "<<this<<"\n";
}

/**
 * Map_t copy constructor.
 * @param map_data
 */
Map_t::Map_t(Map_t &map_data) : key(map_data.key),
                                val(map_data.val)
{
    std::cout<<"Map_t copy constructor. "<<this<<"\n";
}

/**
 * Map_t constructor with arguments.
 * @param n_key
 * @param n_val
 */
Map_t::Map_t(key_t n_key, val_t n_val) : key(n_key),
                                         val(n_val)
{
    std::cout<<"Map_t constructor with arguments. "<<this<<"\n";
}

/**
 * Map_t destructor.
 */
Map_t::~Map_t()
{
    cout << "Map_t destructor. " << this << endl;
}



#include "map_operators.h"



/**
 * Comparing 2 Map_t elements.
 * @param map_data1
 * @param map_data2
 * @return
 */
key_t map_cmp (const key_t * key1, const key_t * key2)
{
    return *key1 - *key2;
}
