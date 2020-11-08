
template<typename DataT>
Matrix<DataT>::Matrix( uint rows, uint cols ) : rows_{rows}, cols_{cols}
{
    memory_allocation(rows, cols);
}

template<typename DataT>
Matrix<DataT>::Matrix( uint rows, uint cols, const vector<DataT> & dat ) : rows_{rows}, cols_{cols}
{
    memory_allocation(rows, cols);

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

template<typename DataT>
Matrix<DataT>::Matrix( const Matrix<DataT> & orig ) : rows_{orig.rows_}, cols_{orig.cols_}
{
    memory_allocation(orig.rows_, orig.cols_);

    for (uint i = 0; i < rows_; ++i)
        for (uint j = 0; j < cols_; ++j)
            data_[i][j] = orig.data_[i][j];
}

template<typename DataT>
Matrix<DataT>::~Matrix( )
{
    kill();
}

template<typename DataT>
Matrix<DataT> Matrix<DataT>::eye( uint n )
{
    vector<DataT> data{};
    for (uint i = 0; i < n; ++i)
        for (uint j = 0; j < n; ++j)
            data.push_back(j == i ? 1 : 0);

    return Matrix<DataT> {n, n, data};
}

template<typename DataT>
long double Matrix<DataT>::det( ) const
{
    if ((cols_ != rows_))
        return NAN;

    long double sign = 1;

    Matrix<DataT> tmp{*this};
    for (uint i = 0; i < cols_; ++i)
    {
        bool zero_col = true;

        if (tmp.data_[i][i] != 0)
            zero_col = false;
        else
            for (uint j = i + 1; j < rows_; ++j)
                if (tmp.data_[j][i] != 0)
                {
                    tmp.swap_lines(j, i);
                    zero_col = false;
                    sign = -sign;
                    break;
                }

        if (zero_col)
            return 0;

        for (uint k = i + 1; k < rows_; ++k)
        {
            if (tmp.data_[k][i] == 0)
                continue;

            long double mul = static_cast<long double>(tmp.data_[k][i])
                              / static_cast<long double>(tmp.data_[i][i]);
            tmp.add_line(k, i, -mul);
        }
    }

    long double res = sign;
    for (uint i = 0; i < cols_; ++i)
        res *= static_cast<long double>(tmp.data_[i][i]);

    return res;
}

template<typename DataT>
Matrix<DataT> & Matrix<DataT>::transpose( )
{
    vector<DataT> data{};

    data.resize(rows_ * cols_);

    for (uint i = 0; i < cols_; ++i)
        for (uint j = 0; j < rows_; ++j)
            data[i * rows_ + j] = data_[j][i];

    if (cols_ != rows_)
        resize(cols_, rows_);

    for (uint i = 0, end = rows_ * cols_; i < end; ++i)
        data_[i / cols_][i % cols_] = data[i];

    return *this;
}

template<typename DataT>
uint Matrix<DataT>::cols( ) const
{
    return cols_;
}

template<typename DataT>
uint Matrix<DataT>::rows( ) const
{
    return rows_;
}

template<typename DataT>
typename Matrix<DataT>::RowT Matrix<DataT>::operator [] ( uint row ) const
{
    assert(row < rows_);
    return RowT{data_[row], cols_};
}

template<typename DataT>
Matrix<DataT> Matrix<DataT>::operator - ( ) const
{
    vector<DataT> data{};

    for (uint i = 0; i < rows_; ++i)
        for (uint j = 0; j < cols_; ++j)
            data.push_back(-data_[i][j]);

    return Matrix<DataT>{rows_, cols_, data};
}

template<typename DataT>
Matrix<DataT> & Matrix<DataT>::operator = ( const Matrix<DataT> & orig )
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

template<typename DataT>
Matrix<DataT> & Matrix<DataT>::operator += ( const Matrix<DataT> & matr )
{
    assert(sum_suitable(matr));

    for (uint i = 0; i < rows_; ++i)
        for (uint j = 0; j < cols_; ++j)
            data_[i][j] += matr.data_[i][j];

    return *this;
}

template<typename DataT>
Matrix<DataT> & Matrix<DataT>::operator -= ( const Matrix<DataT> & matr )
{
    assert(sum_suitable(matr));

    for (uint i = 0; i < rows_; ++i)
        for (uint j = 0; j < cols_; ++j)
            data_[i][j] -= matr.data_[i][j];

    return *this;
}

template<typename DataT>
Matrix<DataT> & Matrix<DataT>::operator *= ( const Matrix<DataT> & matr )
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

template<typename DataT>
Matrix<DataT> & Matrix<DataT>::operator *= ( DataT mul )
{
    for (uint i = 0; i < rows_; ++i)
        for (uint j = 0; j < cols_; ++j)
            data_[i][j] *= mul;

    return *this;
}


template<typename DataT>
bool Matrix<DataT>::swap_lines( uint l1, uint l2 )
{
    assert(l1 < cols_);
    assert(l2 < cols_);

    DataT * tmp = data_[l1];
    data_[l1] = data_[l2];
    data_[l2] = tmp;

    return true;
}

template<typename DataT>
bool Matrix<DataT>::add_line( uint to, uint from, DataT mul )
{
    if ((to > cols_) || (from > cols_))
        return false;

    for (uint i = 0; i < cols_; ++i)
        data_[to][i] += mul * data_[from][i];

    return true;
}

template<typename DataT>
bool Matrix<DataT>::mul_line( uint l, DataT mul )
{
    assert(l < cols_);

    for (uint i = 0; i < cols_; ++i)
        data_[l][i] *= mul;

    return true;
}

template<typename DataT>
bool Matrix<DataT>::sum_suitable( const Matrix<DataT> & matr ) const
{
    return (cols_ == matr.cols_) && (rows_ == matr.rows_);
}


template<typename DataT>
void Matrix<DataT>::memory_allocation( uint rows, uint cols )
{
    rows_ = rows;
    cols_ = cols;

    if (rows_ * cols_ == 0)
        return;

    data_ = new DataT * [rows_]{};

    for (uint i = 0; i < rows_; ++i)
        data_[i] = new DataT [cols_]{};
}

template<typename DataT>
void Matrix<DataT>::kill( )
{
    if (rows_ * cols_ == 0)
        return;

    for (uint i = 0; i < rows_; ++i)
        delete [] data_[i];

    delete [] data_;

    data_ = nullptr;
    cols_ = rows_ = 0;
}

template<typename DataT>
void Matrix<DataT>::resize( uint rows, uint cols )
{
    assert( rows * cols != 0 );
    kill();
    memory_allocation(rows, cols);
}


template <typename DataT>
std::ostream & operator << ( std::ostream & ost, const Matrix<DataT> & matr )
{
    uint cols = matr.cols(),
            rows = matr.rows();

    for (uint i = 0; i < rows; ++i)
    {
        ost << "|";
        for (uint j = 0; j < cols; ++j)
            ost << " " << std::setw(6) << matr[i][j] << " ";
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
Matrix<DataT> operator * ( const Matrix<DataT> & lhs, const Matrix<DataT> & rhs )
{
    return (Matrix<DataT>{lhs} *= rhs);
}

template<typename DataT>
Matrix<DataT> operator * ( const Matrix<DataT> & matr, DataT mul )
{
    return (Matrix<DataT>{matr} *= mul);
}

template<typename DataT>
Matrix<DataT> operator * ( DataT mul, const Matrix<DataT> & matr )
{
    return (Matrix<DataT>{matr} *= mul);
}

template<typename DataT>
Matrix<DataT> transpose( const Matrix<DataT> & matr )
{
    return (Matrix<DataT>{matr}.transpose());
}

