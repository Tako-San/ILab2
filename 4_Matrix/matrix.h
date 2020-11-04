#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <cmath>
#include <cstdint>

using std::vector;

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

    Matrix( int rows, int cols, const vector<DataT> & dat ) : rows_{rows}, cols_{cols}
    {
        memory_allocation(rows_, cols_);

        int max = rows_ * cols_;
        int idx = 0;

        for (auto cur = dat.begin(), end = dat.end(); (cur != end) & (idx < max); ++cur, ++idx )
        {
            int row = idx / cols_,
                col = idx % cols_;
            data_[row][col] = *cur;
        }
    }

    Matrix( const Matrix<DataT> & orig ) : rows_{orig.rows_}, cols_{orig.cols_}
    {
        if (orig.is_inv)
        {
            is_inv = true;
            return;
        }

        memory_allocation(rows_, cols_);

        for (int i = 0, max = cols_ * rows_; i < max; ++i)
        {
            int row = i / cols_,
                col = i % cols_;
            data_[row][col] = orig.data_[row][col];
        }
    }

    ~Matrix( )
    {
        if (!is_inv)
            kill();
    }

    static Matrix eye( int n )
    {
        return Matrix<DataT> {n, n};
    }

    static Matrix eye( int n, const vector<DataT> & dat )
    {
        return Matrix<DataT> {n, n, dat};
    }

    double det( )
    {
        if ((cols_ != rows_) || is_invalid())
            return NAN;

        for (int i = 0; i < cols_; ++i)
        {
            bool zero_col = true;

            if (data_[i][i] == 0)
            {
                for (int j = i; j < rows_; ++j)
                    if (data_[j][i] != 0)
                    {
                        swap_lines(j, i);
                        zero_col = false;
                        break;
                    }
            }
            else
                zero_col = false;

            if (zero_col)
                return 0;

            for (int k = i + 1; k < rows_; ++k)
            {
                if (data_[k][i] == 0)
                    continue;

                double mul = data_[k][i] / data_[i][i];
                add_line(k, i, -mul);
            }
        }

        double res = 1;
        for (int i = 0; i < cols_; ++i)
            res *= data_[i][i];

        return res;
    }

    bool transpose( )
    {
        // TODO: write
        return false;
    }

    int col( ) const
    {
        return cols_;
    }

    int row( ) const
    {
        return rows_;
    }

    DataT * operator [] ( uint idx )
    {
        return is_inv ? nullptr : data_[idx];
    }

    Matrix<DataT> & operator += ( const Matrix<DataT> & m )
    {
        if (is_inv)
            return *this;
        else if (!sum_suitable(m) || m.is_inv)
        {
            kill();
            return *this;
        }

        for (int i = 0; i < rows_; ++i)
            for (int j = 0; j < cols_; ++j)
                data_[i][j] += m.data_[i][j];

        return *this;
    }

    Matrix<DataT> & operator -= ( const Matrix<DataT> & m )
    {
        if (is_inv)
            return *this;
        else if (!sum_suitable(m) || m.is_inv)
        {
            kill();
            return *this;
        }

        for (int i = 0; i < rows_; ++i)
            for (int j = 0; j < cols_; ++j)
                data_[i][j] -= m.data_[i][j];

        return *this;
    }

    Matrix<DataT> & operator *= ( double mul )
    {
        if (is_inv)
            return *this;

        for (int i = 0; i < rows_; ++i)
            for (int j = 0; j < cols_; ++j)
                data_[i][j] *= mul;

        return *this;
    }

    Matrix operator - ( ) const
    {
        vector<DataT> data{};

        for (int i = 0; i < rows_; ++i)
            for (int j = 0; j < cols_; ++j)
                data.push_back(-data_[i][j]);

        return Matrix<DataT>{rows_, cols_, data};
    }
    
    bool swap_lines( uint l1, uint l2 )
    {
        if ((l1 > cols_) || (l2 > cols_) || is_invalid())
            return false;

        DataT * tmp = data_[l1];
        data_[l1] = data_[l2];
        data_[l2] = tmp;

        return true;
    }

    bool add_line( uint to, uint from, double mul = 1 )
    {
        if ((to > cols_) || (from > cols_) || is_invalid())
            return false;

        for (int i = 0; i < cols_; ++i)
            data_[to][i] += mul * data_[from][i];

        return true;
    }

    bool sub_line( uint minuend, uint subtrahend )
    {
        if ((minuend > cols_) || (subtrahend > cols_) || is_invalid())
            return false;

        for (int i = 0; i < cols_; ++i)
            data_[minuend][i] -= data_[subtrahend][i];

        return true;
    }

    bool mul_line( uint l, int mul )
    {
        if ((l > cols_) || is_invalid())
            return false;

        for (int i = 0; i < cols_; ++i)
            data_[l][i] *= mul;

        return true;
    }

    bool sum_suitable( const Matrix<DataT> & matr ) const
    {
        return cols_ == matr.cols_ && rows_ == matr.rows_;
    }

    bool is_invalid( )
    {
        if ((!is_inv) & ((cols_ < 0) || (rows_ < 0)))
            kill();

        return is_inv;
    }

private:

    void memory_allocation( int rows, int cols )
    {
        if ((rows < 0) || (cols < 0))
        {
            cols_ = rows_ = -1;
            is_inv = true;
            return;
        }

        data_ = new DataT * [rows];

        for (int i = 0; i < rows; ++i)
            data_[i] = new DataT [cols];
    }

    void kill( )
    {
        for (int i = 0; i < rows_; ++i)
            delete [] data_[i];

        delete [] data_;

        cols_ = rows_ = -1;
        is_inv = true;
    }
    
    void memory_resize( int rows, int cols )
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
    uint cols = matr.col(),
         rows = matr.row();

    for (uint i = 0; i < rows; ++i)
    {
        ost << "|";
        for (uint j = 0; j < cols; ++j)
            ost << " " << (matr[i][j]) << " ";
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
