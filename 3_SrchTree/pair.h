#ifndef PAIR_H
#define PAIR_H

#include <cstdio>
#include <iostream>
#include <string>

template <typename Key, typename Val>
class Pair
{
private:
    Key key_;
    Val val_;

public:
    Pair( ) : key_{}, val_{}
    {}

    Pair( Key key ) : key_{key}, val_{}
    {}

    Pair( Key key, Val val ) : key_{key}, val_{val}
    {}

    Pair( const Pair & ) = default;

    Pair & operator = ( const Pair & pair ) = default;

    const Key & get_key( )
    { return key_; }

    const Val & get_val( )
    { return val_; }

    bool operator < ( const Pair & pair ) const
    { return key_ < pair.key_; }

    bool operator > ( const Pair & pair ) const
    { return key_ > pair.key_; }

    bool operator <= ( const Pair & pair ) const
    { return key_ <= pair.key_; }

    bool operator >= ( const Pair & pair ) const
    { return key_ >= pair.key_; }

    bool operator == ( const Pair & pair ) const
    { return key_ == pair.key_; }

    friend std::ostream & operator << (std::ostream & ost, const Pair & pr)
    {
        ost << "Key: " << pr.key_ << ", Val: " << pr.val_;
        return ost;
    }

    friend std::istream & operator >> (std::istream & ist, Pair & pr)
    {
        ist >> pr.key_ >> pr.val_;
        return ist;
    }
};

template <typename Key, typename Val>
bool operator < ( Pair<Key, Val> & pair, Key & key )
{ return pair.get_key() < key; }

template <typename Key, typename Val>
bool operator < ( Key & key, Pair<Key, Val> & pair )
{ return key < pair.get_key(); }

template <typename Key, typename Val>
bool operator <= ( Pair<Key, Val> &pair, Key &key )
{ return pair.get_key() <= key; }

template <typename Key, typename Val>
bool operator <= ( Key &key, Pair<Key, Val> &pair )
{ return key < pair.get_key(); }

template <typename Key, typename Val>
bool operator > ( Pair<Key, Val> &pair, Key &key )
{ return pair.get_key() > key; }

template <typename Key, typename Val>
bool operator > ( Key &key, Pair<Key, Val> &pair )
{ return key > pair.get_key(); }

template <typename Key, typename Val>
bool operator >= ( Pair<Key, Val> &pair, Key &key )
{ return pair.get_key() >= key; }

template <typename Key, typename Val>
bool operator >= ( Key &key, Pair<Key, Val> &pair )
{ return key > pair.get_key(); }

template <typename Key, typename Val>
bool operator == ( Pair<Key, Val> & pair, Key &key )
{ return pair.get_key() == key; }

template <typename Key, typename Val>
bool operator == ( Key & key, Pair<Key, Val> &pair )
{ return key == pair.get_key(); }

#endif //PAIR_H
