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
    Pair( );
    Pair( Key key, Val val );
    explicit Pair( Key key );

    Pair( const Pair & ) = default;

    Pair & operator = ( const Pair & pair ) = default;
    Pair & operator = ( const Val & val );

    const Key & get_key( ) const;
    const Val & get_val( ) const;

    bool operator < ( const Pair & pair ) const;
    bool operator > ( const Pair & pair ) const;
    bool operator <= ( const Pair & pair ) const;
    bool operator >= ( const Pair & pair ) const;
    bool operator == ( const Pair & pair ) const;

    friend std::istream & operator >> (std::istream & ist, Pair & pr);
};

#include "pair.ii"

#endif //PAIR_H
