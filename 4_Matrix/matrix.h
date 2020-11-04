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
        if (orig.is_invalid())
        {
            is_inv = true;
            rows_ = cols_ = -1;
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

        double sign = 1;

        for (int i = 0; i < cols_; ++i)
        {
            bool zero_col = true;

            if (data_[i][i] != 0)
                zero_col = false;
            else
                for (int j = i; j < rows_; ++j)
                    if (data_[j][i] != 0)
                    {
                        swap_lines(j, i);
                        zero_col = false;
                        sign = -sign;
                        break;
                    }

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

        double res = sign;
        for (int i = 0; i < cols_; ++i)
            res *= data_[i][i];

        return res;
    }

    bool transpose( )
    {
        // TODO: write
        return false;
    }

    int cols( ) const
    {
        return cols_;
    }

    int rows( ) const
    {
        return rows_;
    }

    DataT * operator [] ( int idx )
    {
        DataT * res = is_invalid() ? nullptr : data_[idx];

        return res;
    }

    Matrix<DataT> & operator = ( const Matrix<DataT> & orig )
    {
        if ((&orig == this) || is_invalid())
            return *this;

        if (orig.is_invalid())
        {
            is_inv = true;
            return *this;
        }

        if (rows_ != orig.rows_ || cols_ != orig.cols())
        {
            memory_resize(rows_, cols_);

            rows_ = orig.rows_;
            cols_ = orig.cols_;
        }

        for (int i = 0, max = cols_ * rows_; i < max; ++i)
        {
            int row = i / cols_,
                    col = i % cols_;
            data_[row][col] = orig.data_[row][col];
        }

        return *this;
    }

    Matrix<DataT> & operator += ( const Matrix<DataT> & matr )
    {
        if (is_invalid())
            return *this;

        else if (!sum_suitable(matr) || matr.is_invalid())
        {
            is_inv = true;
            return *this;
        }

        for (int i = 0; i < rows_; ++i)
            for (int j = 0; j < cols_; ++j)
                data_[i][j] += matr.data_[i][j];

        return *this;
    }

    Matrix<DataT> & operator -= ( const Matrix<DataT> & matr )
    {
        if (is_invalid())
            return *this;

        else if (!sum_suitable(matr) || matr.is_invalid())
        {
            is_inv = true;
            return *this;
        }

        for (int i = 0; i < rows_; ++i)
            for (int j = 0; j < cols_; ++j)
                data_[i][j] -= matr.data_[i][j];

        return *this;
    }

    Matrix<DataT> & operator %= ( const Matrix<DataT> & matr )
    {
        if (is_invalid())
            return *this;

        if ((cols_ != matr.rows_) || matr.is_invalid())
        {
            is_inv = true;
            return *this;
        }

        Matrix<DataT> tmp{rows_, matr.cols_};

        if (tmp.is_invalid())
        {
            is_inv = true;
            return *this;
        }

        for (int i = 0; i < tmp.rows_; ++i)
            for (int j = 0; j < tmp.cols_; ++j)
                for (int k = 0; k < cols_; ++k)
                    tmp[i][j] += data_[i][k] * matr.data_[k][j];

        *this = tmp;
        return *this;
    }

    Matrix<DataT> & operator *= ( double mul )
    {
        if (is_invalid())
            return *this;

        for (int i = 0; i < rows_; ++i)
            for (int j = 0; j < cols_; ++j)
                data_[i][j] *= mul;

        return *this;
    }

    Matrix operator - ( ) const
    {
        if (is_invalid())
            return *this;

        vector<DataT> data{};

        for (int i = 0; i < rows_; ++i)
            for (int j = 0; j < cols_; ++j)
                data.push_back(-data_[i][j]);

        return Matrix<DataT>{rows_, cols_, data};
    }
    
    bool swap_lines( int l1, int l2 )
    {
        if ((l1 > cols_) || (l2 > cols_) || is_invalid())
            return false;

        DataT * tmp = data_[l1];
        data_[l1] = data_[l2];
        data_[l2] = tmp;

        return true;
    }

    bool add_line( int to, int from, double mul = 1 )
    {
        if ((to > cols_) || (from > cols_) || is_invalid())
            return false;

        for (int i = 0; i < cols_; ++i)
            data_[to][i] += mul * data_[from][i];

        return true;
    }

    bool mul_line( int l, int mul )
    {
        if ((l > cols_) || is_invalid())
            return false;

        for (int i = 0; i < cols_; ++i)
            data_[l][i] *= mul;

        return true;
    }

    bool sum_suitable( const Matrix<DataT> & matr ) const
    {
        return (cols_ == matr.cols_) && (rows_ == matr.rows_) &&
               !is_invalid() && !matr.is_invalid();
    }

    bool is_invalid( )
    {
        if ((cols_ < 0) || (rows_ < 0))
            is_inv = true;

        return is_inv;
    }

    bool is_invalid( ) const
    {
        if ((cols_ < 0) || (rows_ < 0))
            return true;

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
        if (cols_ < 0 || rows_ < 0)
            return;

        for (int i = 0; i < rows_; ++i)
            delete [] data_[i];

        delete [] data_;

        cols_ = rows_ = -1;
        is_inv = true;
    }
    
    void memory_resize( int rows, int cols )
    {
        kill();

        is_inv = false;
        rows_ = rows;
        cols_ = cols;
        memory_allocation(rows_, cols_);
    }
};

template <typename DataT>
std::ostream & operator << ( std::ostream & ost, Matrix<DataT> & matr )
{
    if (matr.is_invalid())
        ost << "INVALID MATRIX";

    int cols = matr.cols(),
         rows = matr.rows();

    for (int i = 0; i < rows; ++i)
    {
        ost << "|";
        for (int j = 0; j < cols; ++j)
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
