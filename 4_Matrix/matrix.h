#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>

using std::initializer_list;

template <typename DataT>
class Matrix final
{
private:
    DataT ** data_;

    int rows_, cols_;

    bool is_inv{false};

public:

    Matrix( int rows, int cols ) : rows_{rows}, cols_{cols}
    {
        memory_allocation(rows_, cols_);
    }

    Matrix( int rows, int cols, const initializer_list<DataT> & dat ) : rows_{rows}, cols_{cols}
    {
        memory_allocation(rows_, cols_);

        int max = rows_ * cols_;
        int idx = 0;

        for (auto cur = dat.begin(), end = dat.end(); cur != end & idx < max; ++cur, ++idx )
        {
            int row = idx / cols_,
                col = idx % cols_;
            data_[row][col] = *cur;
        }
    }

    Matrix( const Matrix<DataT> & orig ) : rows_{orig.rows_}, cols_{orig.cols_}
    {
        memory_allocation(rows_, cols_);

        for (int i = 0, max = cols_ * rows_; i < max; ++i)
        {
            int col = i / cols_,
                row = i % cols_;
            data_[row][col] = orig.data_[row][col];
        }
    }

    ~Matrix( )
    {
        memory_free();
    }
    
    Matrix<DataT> & operator += ( const Matrix<DataT> & m )
    {
        if (!size_suitable(m))
            memory_free();

        for (int i = 0; i < rows_; ++i)
            for (int j = 0; j < cols_; ++j)
                data_[i][j] += m.data_[i][j];

        return *this;
    }

    Matrix<DataT> & operator -= ( const Matrix<DataT> & m )
    {
        if (!size_suitable(m))
            memory_free();

        for (int i = 0; i < rows_; ++i)
            for (int j = 0; j < cols_; ++j)
                data_[i][j] -= m.data_[i][j];

        return *this;
    }

    Matrix<DataT> & operator *= ( double mul )
    {
        for (int i = 0; i < rows_; ++i)
            for (int j = 0; j < cols_; ++j)
                data_[i][j] *= mul;

        return *this;
    }

    DataT * operator [] ( int idx )
    {
        return data_[idx];
    }

    bool size_suitable( const Matrix<DataT> & matr ) const
    {
        return cols_ == matr.cols_ && rows_ == matr.rows_ && !is_inv && !matr.is_inv;
    }


private:

    void memory_allocation( int rows, int cols )
    {
        data_ = new DataT * [rows];

        for (int i = 0; i < rows; ++i)
            data_[i] = new DataT [cols];
    }
    
    void memory_free( )
    {
        for (int i = 0; i < rows_; ++i)
            delete [] data_[i];

        delete [] data_;

        cols_ = rows_ = -1;
        is_inv = true;
    }
    
    void memory_resize( int rows, int cols )
    {
        rows_ = rows;
        cols_ = cols;
        
        memory_free();
        memory_allocation(rows_, cols_);
    }
};

template<typename DataT>
Matrix<DataT> operator + ( const Matrix<DataT> & lhs, const Matrix<DataT> & rhs )
{
    return (Matrix<DataT>{lhs} += rhs);
}

template<typename DataT>
Matrix<DataT> operator - ( const Matrix<DataT> & lhs, const Matrix<DataT> & rhs )
{
    return (Matrix<DataT>{lhs} -= rhs);
}

template<typename DataT>
Matrix<DataT> operator * ( const Matrix<DataT> & matr, double mul )
{
    return (Matrix<DataT>{matr} *= mul);
}

template<typename DataT>
Matrix<DataT> operator * ( double mul, const Matrix<DataT> & matr )
{
    return (Matrix<DataT>{matr} *= mul);
}

#endif //MATRIX_H
