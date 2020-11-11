
template <typename DataT>
Matrix<DataT>::Matrix( size_t rows, size_t cols ) : rows_{rows},
                                                    cols_{cols}
{
    memory_allocation(rows, cols);
}

template <typename DataT>
Matrix<DataT>::Matrix( size_t rows, size_t cols, const initializer_list<DataT> & data ) : rows_{rows},
                                                                                          cols_{cols}
{
    memory_allocation(rows, cols);

    size_t max_num = rows_ * cols_;
    auto cur = data.begin(),
         end = data.end();

    for(size_t i = 0; i < max_num && cur != end; ++i, ++cur)
        data_[i / cols_][i % cols_] = *cur;
}


template <typename DataT>
template <typename IterT>
Matrix<DataT>::Matrix( size_t rows, size_t cols, const IterT & begin, const IterT & end ) : rows_{rows},
                                                                                            cols_{cols}
{
    memory_allocation(rows, cols);

    size_t i = 0;
    size_t el_num = rows_ * cols_;

    for (IterT cur = begin; cur != end, i < el_num; ++i, ++cur)
        data_[i / cols_][i % cols_] = *cur;

}

template <typename DataT>
Matrix<DataT>::Matrix( size_t rows, size_t cols, func action ) : rows_{rows},
                                                                 cols_{cols}
{
    memory_allocation(rows, cols);

    for (size_t i = 0; i < rows_; ++i)
        for (size_t j = 0; j < cols_; ++j)
            data_[i][j] = action(i, j);
}

template <typename DataT>
Matrix<DataT>::Matrix( const Matrix<DataT> & orig ) : rows_{orig.rows_},
                                                      cols_{orig.cols_}
{
    memory_allocation(orig.rows_, orig.cols_);

    for (size_t i = 0; i < rows_; ++i)
        for (size_t j = 0; j < cols_; ++j)
            data_[i][j] = orig.data_[i][j];
}

template <typename DataT>
Matrix<DataT>::Matrix( Matrix<DataT> && orig ) : rows_{orig.rows_},
                                                 cols_{orig.cols_},
                                                 data_{orig.data_}
{
    orig.data_ = nullptr;
    orig.cols_ = orig.rows_ = 0;
}

template <typename DataT>
Matrix<DataT>::~Matrix( )
{
    kill();
}

template <typename DataT>
Matrix<DataT> Matrix<DataT>::eye( size_t n )
{
    return std::move(Matrix<DataT> {n, n, [](size_t i, size_t j)->DataT{ return i == j;}});
}

template <typename DataT>
long double Matrix<DataT>::det( ) const
{
    if ((cols_ != rows_))
        return NAN;

    long double sign = 1;

    Matrix<DataT> tmp{*this};
    for (size_t i = 0; i < cols_; ++i)
    {
        bool zero_col = true;

        if (tmp.data_[i][i] != 0)
            zero_col = false;
        else
            for (size_t j = i + 1; j < rows_; ++j)
                if (tmp.data_[j][i] != 0)
                {
                    tmp.swap_lines(j, i);
                    zero_col = false;
                    sign = -sign;
                    break;
                }

        if (zero_col)
            return 0;

        for (size_t k = i + 1; k < rows_; ++k)
        {
            if (tmp.data_[k][i] == 0)
                continue;

            long double mul = static_cast<long double>(tmp.data_[k][i])
                            / static_cast<long double>(tmp.data_[i][i]);
            tmp.add_line(k, i, -mul);
        }
    }

    long double res = sign;
    for (size_t i = 0; i < cols_; ++i)
        res *= static_cast<long double>(tmp.data_[i][i]);

    return res;
}

template <typename DataT>
Matrix<DataT> & Matrix<DataT>::transpose( )
{
    vector<DataT> data{};

    data.resize(rows_ * cols_);

    for (size_t i = 0; i < cols_; ++i)
        for (size_t j = 0; j < rows_; ++j)
            data[i * rows_ + j] = data_[j][i];

    if (cols_ != rows_)
        resize(cols_, rows_);

    for (size_t i = 0, end = rows_ * cols_; i < end; ++i)
        data_[i / cols_][i % cols_] = data[i];

    return *this;
}

template <typename DataT>
size_t Matrix<DataT>::cols( ) const
{
    return cols_;
}

template <typename DataT>
size_t Matrix<DataT>::rows( ) const
{
    return rows_;
}

template <typename DataT>
typename Matrix<DataT>::RowT Matrix<DataT>::operator [] ( size_t row ) const
{
    assert(row < rows_);
    return RowT{data_[row], cols_};
}

template <typename DataT>
Matrix<DataT> Matrix<DataT>::operator - ( ) const
{
    Matrix<DataT> matr{*this};

    for (size_t i = 0; i < rows_; ++i)
        for (size_t j = 0; j < cols_; ++j)
            matr.data_[i][j] = -data_[i][j];

    return std::move(matr);
}

template <typename DataT>
Matrix<DataT> & Matrix<DataT>::operator = ( Matrix<DataT> && orig )
{
    kill();

    rows_ = orig.rows_;
    cols_ = orig.cols_;
    data_ = orig.data_;

    orig.data_ = nullptr;
    orig.cols_ = orig.rows_ = 0;

    return *this;
}

template <typename DataT>
Matrix<DataT> & Matrix<DataT>::operator = ( const Matrix<DataT> & orig )
{
    if (&orig == this)
        return *this;

    size_t rows = orig.rows_,
         cols = orig.cols_;

    if (rows_ != rows || cols_ != cols)
        resize(rows, cols);

    for (size_t i = 0; i < rows_; ++i)
        for (size_t j = 0; j < cols_; ++j)
            data_[i][j] = orig.data_[i][j];

    return *this;
}

template <typename DataT>
Matrix<DataT> & Matrix<DataT>::operator += ( const Matrix<DataT> & matr )
{
    assert(sum_suitable(matr));

    for (size_t i = 0; i < rows_; ++i)
        for (size_t j = 0; j < cols_; ++j)
            data_[i][j] += matr.data_[i][j];

    return *this;
}

template <typename DataT>
Matrix<DataT> & Matrix<DataT>::operator -= ( const Matrix<DataT> & matr )
{
    assert(sum_suitable(matr));

    for (size_t i = 0; i < rows_; ++i)
        for (size_t j = 0; j < cols_; ++j)
            data_[i][j] -= matr.data_[i][j];

    return *this;
}

template <typename DataT>
Matrix<DataT> & Matrix<DataT>::operator *= ( const Matrix<DataT> & matr )
{
    assert(cols_ == matr.rows_);

    Matrix<DataT> tmp1{rows_, matr.cols_};
    Matrix<DataT> tmp2{matr};
    tmp2.transpose();

    for (size_t i = 0; i < tmp1.rows_; ++i)
        for (size_t j = 0; j < tmp1.cols_; ++j)
            for (size_t k = 0; k < cols_; ++k)
                tmp1[i][j] += data_[i][k] * tmp2.data_[j][k];

    *this = std::move(tmp1);
    return *this;
}

template <typename DataT>
Matrix<DataT> & Matrix<DataT>::operator *= ( DataT mul )
{
    for (size_t i = 0; i < rows_; ++i)
        for (size_t j = 0; j < cols_; ++j)
            data_[i][j] *= mul;

    return *this;
}


template <typename DataT>
bool Matrix<DataT>::operator == ( const Matrix<DataT> & matr )
{
    if (rows_ != matr.rows_ || cols_ != matr.cols_)
        return false;

    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j)
            if (data_[i][j] != matr.data_[i][j])
                return false;

    return true;
}

template <typename DataT>
bool Matrix<DataT>::operator != ( const Matrix<DataT> & matr )
{
    return !operator==(matr);
}

template <typename DataT>
bool Matrix<DataT>::swap_lines( size_t l1, size_t l2 )
{
    assert(l1 < cols_);
    assert(l2 < cols_);

    std::swap(data_[l1], data_[l2]);

    return true;
}

template <typename DataT>
bool Matrix<DataT>::add_line( size_t to, size_t from, DataT mul )
{
    if ((to > cols_) || (from > cols_))
        return false;

    for (size_t i = 0; i < cols_; ++i)
        data_[to][i] += mul * data_[from][i];

    return true;
}

template <typename DataT>
bool Matrix<DataT>::mul_line( size_t l, DataT mul )
{
    assert(l < cols_);

    for (size_t i = 0; i < cols_; ++i)
        data_[l][i] *= mul;

    return true;
}

template <typename DataT>
bool Matrix<DataT>::sum_suitable( const Matrix<DataT> & matr ) const
{
    return (cols_ == matr.cols_) && (rows_ == matr.rows_);
}


template <typename DataT>
void Matrix<DataT>::memory_allocation( size_t rows, size_t cols )
{
    rows_ = rows;
    cols_ = cols;

    if (rows_ * cols_ == 0)
        return;

    data_ = new DataT * [rows_]{};

    for (size_t i = 0; i < rows_; ++i)
        data_[i] = new DataT [cols_]{};
}

template <typename DataT>
void Matrix<DataT>::resize( size_t rows, size_t cols )
{
    assert( rows * cols != 0 );
    kill();
    memory_allocation(rows, cols);
}

template <typename DataT>
void Matrix<DataT>::kill( )
{
    if (rows_ * cols_ == 0)
        return;

    for (size_t i = 0; i < rows_; ++i)
        delete [] data_[i];

    delete [] data_;

    data_ = nullptr;
    cols_ = rows_ = 0;
}


template <typename DataT>
std::ostream & operator << ( std::ostream & ost, const Matrix<DataT> & matr )
{
    size_t cols = matr.cols(),
         rows = matr.rows();

    for (size_t i = 0; i < rows; ++i)
    {
        ost << "|";
        for (size_t j = 0; j < cols; ++j)
            ost << " " << matr[i][j] << " ";
        ost << "|\n";
    }

    return ost;
}

template <typename DataT>
Matrix<DataT> operator + ( const Matrix<DataT> & lhs, const Matrix<DataT> & rhs )
{
    return std::move(Matrix<DataT>{lhs} += rhs);
}

template <typename DataT>
Matrix<DataT> operator - ( const Matrix<DataT> & lhs, const Matrix<DataT> & rhs )
{
    return std::move(Matrix<DataT>{lhs} -= rhs);
}

template <typename DataT>
Matrix<DataT> operator * ( const Matrix<DataT> & lhs, const Matrix<DataT> & rhs )
{
    return std::move(Matrix<DataT>{lhs} *= rhs);
}

template <typename DataT>
Matrix<DataT> operator * ( const Matrix<DataT> & matr, DataT mul )
{
    return std::move(Matrix<DataT>{matr} *= mul);
}

template <typename DataT>
Matrix<DataT> operator * ( DataT mul, const Matrix<DataT> & matr )
{
    return std::move(Matrix<DataT>{matr} *= mul);
}

template <typename DataT>
Matrix<DataT> transpose( const Matrix<DataT> & matr )
{
    return std::move(Matrix<DataT>{matr}.transpose());
}

