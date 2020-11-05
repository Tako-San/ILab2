#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <cstdint>
#include <cmath>

using std::vector;

template <typename DataT>
class Matrix final
{
private:
    DataT ** data_;

    uint rows_, cols_;

public:

    Matrix( uint rows, uint cols ) : rows_{rows}, cols_{cols}
    {
        memory_allocation(rows_, cols_);
    }

    Matrix( uint rows, uint cols, const vector<DataT> & dat ) : rows_{rows}, cols_{cols}
    {
        memory_allocation(rows_, cols_);

        uint max_num = rows_ * cols_;
        uint vec_len = dat.size();

        uint end = vec_len < max_num ? vec_len : max_num;

        for(uint i = 0; i < end; ++i)
        {
            uint row = i / cols_,
                 col = i % cols_;
            data_[row][col] = dat[i];
        }
    }

    Matrix( const Matrix<DataT> & orig ) : rows_{orig.rows_}, cols_{orig.cols_}
    {
        memory_allocation(rows_, cols_);

        for (uint i = 0; i < rows_; ++i)
            for (uint j = 0; j < cols_; ++j)
                data_[i][j] = orig.data_[i][j];
    }

    ~Matrix( )
    {
        kill();
    }

    static Matrix eye( uint n )
    {
        vector<DataT> data{};
        for (uint i = 0; i < n; ++i)
            for (uint j = 0; j < n; ++j)
                data.push_back(j == i ? 1 : 0);

        return Matrix<DataT> {n, n, data};
    }

    long double det( )
    {
        if ((cols_ != rows_))
            return NAN;

        long double sign = 1;

        for (uint i = 0; i < cols_; ++i)
        {
            bool zero_col = true;

            if (data_[i][i] != 0)
                zero_col = false;
            else
                for (uint j = i; j < rows_; ++j)
                    if (data_[j][i] != 0)
                    {
                        swap_lines(j, i);
                        zero_col = false;
                        sign = -sign;
                        break;
                    }

            if (zero_col)
                return 0;

            for (uint k = i + 1; k < rows_; ++k)
            {
                if (data_[k][i] == 0)
                    continue;

                long double mul = data_[k][i] / data_[i][i];
                add_line(k, i, -mul);
            }
        }

        long double res = sign;
        for (uint i = 0; i < cols_; ++i)
            res *= data_[i][i];

        return res;
    }

    bool transpose( )
    {
        // TODO: write
        return false;
    }

    uint cols( ) const
    {
        return cols_;
    }

    uint rows( ) const
    {
        return rows_;
    }

    DataT & elem( uint row, uint col )
    {
        return data_[row][col];
    }

    const DataT & elem( uint row, uint col ) const
    {
        return data_[row][col];
    }

    Matrix<DataT> & operator = ( const Matrix<DataT> & orig )
    {
        if (&orig == this)
            return *this;

        uint rows = orig.rows_,
             cols = orig.cols_;

        if (rows_ != rows || cols_ != cols)
            resize(rows, cols);

        for (uint i = 0; i < rows_; ++i)
            for (uint j = 0; j < cols_; ++j)
                data_[i][j] = orig.data_[i][j];

        return *this;
    }

    Matrix<DataT> & operator += ( const Matrix<DataT> & matr )
    {
        assert(sum_suitable(matr));

        for (uint i = 0; i < rows_; ++i)
            for (uint j = 0; j < cols_; ++j)
                data_[i][j] += matr.data_[i][j];

        return *this;
    }

    Matrix<DataT> & operator -= ( const Matrix<DataT> & matr )
    {
        assert(sum_suitable(matr));

        for (uint i = 0; i < rows_; ++i)
            for (uint j = 0; j < cols_; ++j)
                data_[i][j] -= matr.data_[i][j];

        return *this;
    }

    Matrix<DataT> & operator %= ( const Matrix<DataT> & matr )
    {
        assert(cols_ == matr.rows_);

        Matrix<DataT> tmp{rows_, matr.cols_};

        for (uint i = 0; i < tmp.rows_; ++i)
            for (uint j = 0; j < tmp.cols_; ++j)
                for (uint k = 0; k < cols_; ++k)
                    tmp[i][j] += data_[i][k] * matr.data_[k][j];

        *this = tmp;
        return *this;
    }

    Matrix<DataT> & operator *= ( DataT mul )
    {
        for (uint i = 0; i < rows_; ++i)
            for (uint j = 0; j < cols_; ++j)
                data_[i][j] *= mul;

        return *this;
    }

    Matrix operator - ( ) const
    {
        vector<DataT> data{};

        for (uint i = 0; i < rows_; ++i)
            for (uint j = 0; j < cols_; ++j)
                data.push_back(-data_[i][j]);

        return Matrix<DataT>{rows_, cols_, data};
    }
    
    bool swap_lines( uint l1, uint l2 )
    {
        assert(l1 < cols_);
        assert(l2 < cols_);

        DataT * tmp = data_[l1];
        data_[l1] = data_[l2];
        data_[l2] = tmp;

        return true;
    }

    bool add_line( uint to, uint from, DataT mul )
    {
        if ((to > cols_) || (from > cols_))
            return false;

        for (uint i = 0; i < cols_; ++i)
            data_[to][i] += mul * data_[from][i];

        return true;
    }

    bool mul_line( uint l, DataT mul )
    {
        assert(l < cols_);

        for (uint i = 0; i < cols_; ++i)
            data_[l][i] *= mul;

        return true;
    }

    bool sum_suitable( const Matrix<DataT> & matr ) const
    {
        return (cols_ == matr.cols_) && (rows_ == matr.rows_);
    }

private:

    DataT * operator [] ( uint idx )
    {
        return data_[idx];
    }

    void memory_allocation( uint rows, uint cols )
    {
        if (rows * cols == 0)
            return;

        data_ = new DataT * [rows];

        for (uint i = 0; i < rows; ++i)
            data_[i] = new DataT [cols];
    }

    void kill( )
    {
        if (rows_ * cols_ == 0)
            return;

        for (uint i = 0; i < rows_; ++i)
            delete [] data_[i];

        delete [] data_;
    }
    
    void resize( uint rows, uint cols )
    {
        kill();

        rows_ = rows;
        cols_ = cols;

        memory_allocation(rows_, cols_);
    }
};

template <typename DataT>
std::ostream & operator << ( std::ostream & ost, Matrix<DataT> & matr )
{
    uint cols = matr.cols(),
         rows = matr.rows();

    for (uint i = 0; i < rows; ++i)
    {
        ost << "|";
        for (uint j = 0; j < cols; ++j)
            ost << " " << (matr.elem(i, j)) << " ";
        ost << "|\n";
    }

    return ost;
}


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
Matrix<DataT> operator % ( const Matrix<DataT> & lhs, const Matrix<DataT> & rhs )
{
    return (Matrix<DataT>{lhs} %= rhs);
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

template<typename DataT>
Matrix<DataT> transpose( const Matrix<DataT> & matr )
{
    return (Matrix<DataT>{matr}.transpose());
}

#endif //MATRIX_H
