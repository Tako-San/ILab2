#ifndef MATRIX_H
#define MATRIX_H

template <typename DataT>
class Matrix final
{
private:
    DataT ** data_;

    int rows_, cols_;

public:

    Matrix( int rows, int cols ) : rows_{rows}, cols_{cols}
    {
        memory_allocation(rows_, cols_);
    }

    Matrix( const Matrix<DataT> & orig ) : rows_{orig.rows_}, cols_{orig.cols_}
    {
        memory_allocation(rows_, cols_);
    }

    ~Matrix( )
    {
        memory_free();
    }
    
    Matrix<DataT> & operator += ( const Matrix<DataT> & m)
    {
        if (cols_ != m.cols_ || rows_ != m.rows_)
        {
            memory_free();
            cols_ = rows_ = -1;
        }

        for (int i = 0; i < rows_; ++i)
            for (int j = 0; j < cols_; ++j)
                data_[i][j] += m.data_[i][j];

        return *this;
    }

    Matrix<DataT> & operator -= ( const Matrix<DataT> & m)
    {
        if (cols_ != m.cols_ || rows_ != m.rows_)
        {
            memory_free();
            cols_ = rows_ = -1;
        }

        for (int i = 0; i < rows_; ++i)
            for (int j = 0; j < cols_; ++j)
                data_[i][j] -= m.data_[i][j];

        return *this;
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

#endif //MATRIX_H
