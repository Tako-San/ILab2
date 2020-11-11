#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>
#include <cstdint>
#include <cassert>
#include <cmath>

namespace F
{
    using std::initializer_list;
    using std::vector;

    template<typename DataT>
    class Matrix final
    {
    private:
        DataT **data_;
        size_t rows_;
        size_t cols_;

        class RowT;

        using func = DataT(*)(size_t, size_t);

    public:

        Matrix( size_t rows, size_t cols );

        Matrix( Matrix &&orig );

        Matrix( const Matrix &orig );

        Matrix( size_t rows, size_t cols, func action );

        Matrix( size_t rows, size_t cols, const initializer_list<DataT> &dat );

        template <typename Iter>
        Matrix( size_t rows, size_t cols, const Iter & begin, const Iter & end );

        ~Matrix();

        static Matrix eye( size_t n );

        long double det() const;

        Matrix &transpose();

        size_t cols() const;
        size_t rows() const;

        RowT operator[]( size_t row ) const;

        Matrix operator-() const;

        Matrix &operator=( Matrix &&orig );
        Matrix &operator=( const Matrix &orig );

        Matrix &operator+=( const Matrix &matr );
        Matrix &operator-=( const Matrix &matr );
        Matrix &operator*=( const Matrix &matr );
        Matrix &operator*=( DataT mul );

        bool operator==( const Matrix &matr );
        bool operator!=( const Matrix &matr );

        bool swap_lines( size_t l1, size_t l2 );
        bool add_line( size_t to, size_t from, DataT mul );
        bool mul_line( size_t l, DataT mul );

        bool sum_suitable( const Matrix<DataT> &matr ) const;

    private:

        void memory_allocation( size_t rows, size_t cols );

        void resize( size_t rows, size_t cols );

        void kill();
    };

    template<typename DataT>
    class Matrix<DataT>::RowT final
    {
    private:
        DataT * row_;
        size_t len_;

        RowT( DataT *row, size_t len ) : row_{row}, len_{len}
        {}

        friend class Matrix<DataT>;

    public:
        DataT &operator[]( size_t col )
        {
            assert(col < len_);
            return row_[col];
        }

        const DataT &operator[]( size_t col ) const
        {
            assert(col < len_);
            return row_[col];
        }
    };

    template<typename DataT>
    Matrix<DataT> operator+( const Matrix<DataT> &lhs, const Matrix<DataT> &rhs );

    template<typename DataT>
    Matrix<DataT> operator-( const Matrix<DataT> &lhs, const Matrix<DataT> &rhs );

    template<typename DataT>
    Matrix<DataT> operator*( const Matrix<DataT> &lhs, const Matrix<DataT> &rhs );

    template<typename DataT>
    Matrix<DataT> operator*( const Matrix<DataT> &matr, DataT mul );

    template<typename DataT>
    Matrix<DataT> operator*( DataT mul, const Matrix<DataT> &matr );

    template<typename DataT>
    Matrix<DataT> transpose( const Matrix<DataT> &matr );

    #include "matrix.ii"
}

#endif //MATRIX_H
