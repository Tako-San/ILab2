#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <cstdint>
#include <cassert>
#include <cmath>

using std::vector;

template <typename DataT>
class Matrix final
{
private:
    DataT ** data_;
    uint rows_, cols_;

    class RowT;
public:

    Matrix( uint rows, uint cols );
    Matrix( uint rows, uint cols, const vector<DataT> & dat );
    Matrix( const Matrix<DataT> & orig );

    // TODO: move semantics, move in outer operators
    ~Matrix( );

    static Matrix eye( uint n );

    long double det( ) const;

    Matrix<DataT> & transpose( );

    uint cols( ) const;
    uint rows( ) const;

    RowT operator [] ( uint row ) const;
    Matrix operator - ( ) const;

    Matrix & operator = ( const Matrix & orig );
    Matrix & operator += ( const Matrix & matr );
    Matrix & operator -= ( const Matrix & matr );
    Matrix & operator *= ( const Matrix & matr );
    Matrix & operator *= ( DataT mul );
    bool operator == ( const Matrix & matr );
    bool operator != ( const Matrix & matr );

    bool swap_lines( uint l1, uint l2 );
    bool add_line( uint to, uint from, DataT mul );
    bool mul_line( uint l, DataT mul );
    bool sum_suitable( const Matrix<DataT> & matr ) const;

private:

    void memory_allocation( uint rows, uint cols );
    void kill( );
    void resize( uint rows, uint cols );
};

template <typename DataT>
class Matrix<DataT>::RowT final
{
private:
    DataT * row_;
    uint len_;

    RowT( DataT * row, uint len ) : row_{row}, len_{len}
    {}

    friend class Matrix<DataT>;

public:
    DataT & operator [] ( uint col )
    {
        assert(col < len_);
        return row_[col];
    }

    const DataT & operator [] ( uint col ) const
    {
        assert(col < len_);
        return row_[col];
    }
};

#include "matrix.inl"

#endif //MATRIX_H
