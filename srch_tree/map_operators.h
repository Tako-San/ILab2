#ifndef MAP_MAP_OPERATORS_H
#define MAP_MAP_OPERATORS_H

/**
 * Operator = redefenition.
 * @param map_data
 * @return
 */
Map_t& Map_t::operator= (const Map_t &map_data)
{
    if(&map_data == this)
        return *this;
    key = map_data.key;
    val = map_data.val;
    return *this;
}

/**
 * Operator < redefenition.
 * @param map_data
 * @return
 */
bool Map_t::operator< (Map_t &map_data)
{
    return map_cmp(&key, &(map_data.key)) < 0;
}

/**
 * Operator <= redefenition.
 * @param map_data
 * @return
 */
bool Map_t::operator<= (Map_t &map_data)
{
    return map_cmp(&key, &(map_data.key)) <= 0;
}

/**
 * Operator > redefenition.
 * @param map_data
 * @return
 */
bool Map_t::operator> (Map_t &map_data)
{
    return map_cmp(&key, &(map_data.key)) > 0;
}

/**
 * Operator >= redefenition.
 * @param map_data
 * @return
 */
bool Map_t::operator>= (Map_t &map_data)
{
    return map_cmp(&key, &(map_data.key)) >= 0;
}

/**
 * Operator == redefenition.
 * @param map_data
 * @return
 */
bool Map_t::operator== (Map_t &map_data)
{
    return map_cmp(&key, &(map_data.key)) == 0;
}


/**
 * Operator < redefenition.
 * @param map_data
 * @param key
 * @return
 */
bool operator< (Map_t &map_data, key_t &key)
{
    return map_cmp(&(map_data.key), &key) < 0;
}

bool operator< (key_t &key, Map_t &map_data)
{
    return map_cmp(&key, &(map_data.key)) < 0;
}


/**
 * Operator <= redefenition.
 * @param map_data
 * @param key
 * @return
 */
bool operator<= (Map_t &map_data, key_t &key)
{
    return map_cmp(&(map_data.key), &key) <= 0;
}

bool operator<= (key_t &key, Map_t &map_data)
{
    return map_cmp(&key, &(map_data.key)) <= 0;
}


/**
 * Operator > redefenition.
 * @param map_data
 * @param key
 * @return
 */
bool operator> (Map_t &map_data, key_t &key)
{
    return map_cmp(&(map_data.key), &key) > 0;
}

bool operator> (key_t &key, Map_t &map_data)
{
    return map_cmp(&key, &(map_data.key)) > 0;
}


/**
 * Operator >= redefenition.
 * @param map_data
 * @param key
 * @return
 */
bool operator>= (Map_t &map_data, key_t &key)
{
    return map_cmp(&(map_data.key), &key) >= 0;
}

bool operator>= (key_t &key, Map_t &map_data)
{
    return map_cmp(&key, &(map_data.key)) >= 0;
}


/**
 * Operator == redefenition.
 * @param map_data
 * @param key
 * @return
 */
bool operator== (Map_t &map_data, key_t &key)
{
    return map_cmp(&(map_data.key), &key) == 0;
}

bool operator== (key_t &key, Map_t &map_data)
{
    return map_cmp(&key, &(map_data.key)) == 0;
}



/**
 * Operator << redefenition.
 * @param map_data
 * @return
 */
std::ostream& operator<< (std::ostream &out, const Map_t &map_data)
{
    //out << "key: " << map_data.key << ", val: " << map_data.val;
    out << "(" << map_data.key << ", " << map_data.val << ")";

    return out;
}

/**
 * Operator>>= redefenition.
 * @param map_data
 * @return
 */
std::istream& operator>> (std::istream &in, Map_t &map_data)
{
    in >> map_data.key;
    in >> map_data.val;

    return in;
}

#endif //MAP_MAP_OPERATORS_H
