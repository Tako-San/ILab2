#include <cmath>
#include <cassert>
#include <utility>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <initializer_list>

namespace Buf
{
  template <typename T>
  void copy_construct (T * ptr, const T & val)
  {
    new(ptr) T{val};
  }

  template <class T>
  void destr (T * ptr)
  {
    ptr->~T();
  }

  template <typename It>
  void destr (It beg, It end)
  {
    while (beg != end)
      destr(&*beg++);
  }


/*
 *
 * VBuf class
 *
 */

  template <typename DataT>
  struct VBuf
  {
    VBuf (const VBuf &) = delete;

    VBuf & operator= (const VBuf &) = delete;

  protected:

    DataT * arr_;
    size_t size_, used_;

    explicit VBuf (size_t size = 0);

    ~VBuf ();

    void swap (VBuf & rhs) noexcept;
  };


/*
 *
 * VBuf class methods realistaions
 *
 */

  template <typename DataT>
  VBuf<DataT>::VBuf (size_t size) :
          arr_(size == 0 ? nullptr : static_cast<DataT *>(::operator new(sizeof(DataT) * size))),
          size_(size), used_(0)
  {}

  template <typename DataT>
  VBuf<DataT>::~VBuf ()
  {
    destr(arr_, arr_ + used_);
    ::operator delete(arr_);
  }

  template <typename DataT>
  void VBuf<DataT>::swap (VBuf & rhs) noexcept
  {
    std::swap(arr_, rhs.arr_);
    std::swap(size_, rhs.size_);
    std::swap(used_, rhs.used_);
  }
}




namespace MX
{
  using namespace Buf;

  template <typename DataT>
  class Matrix;

  /*
   *
   * Row class
   *
   */

  template <typename DataT>
  struct Row : private VBuf<DataT>
  {
    using VBuf<DataT>::arr_;
    using VBuf<DataT>::size_;
    using VBuf<DataT>::used_;

    friend class Matrix<DataT>;

    explicit Row (size_t size);
    Row (const Row & rhs);
    template <typename It>
    Row (size_t size, It beg, It end);

    Row & operator= (const Row & rhs);

  public:

    const DataT & get (size_t idx) const;
    void set (size_t idx, DataT new_val);
    const DataT & operator[] (size_t idx) const;
  };


/*
 *
 * Row class method realisations
 *
 */

  template <typename DataT>
  Row<DataT>::Row (size_t size) : VBuf<DataT>(size)
  {
    DataT tmp{};
    for (; used_ < size_; ++used_)
      copy_construct(arr_ + used_, tmp);
  }

  template <typename DataT>
  Row<DataT>::Row (const Row & rhs) : VBuf<DataT>(rhs.size_)
  {
    for (; used_ < rhs.used_; ++used_)
      copy_construct(arr_ + used_, *(rhs.arr_ + used_));

    DataT tmp{};
    for (; used_ < size_; ++used_)
      copy_construct(arr_ + used_, tmp);
  }

  template <typename DataT>
  template <typename It>
  Row<DataT>::Row (size_t size, It beg, It end) : VBuf<DataT>(size)
  {
    It cur = beg;

    for (; used_ < size_ && cur != end; ++used_, ++cur)
      copy_construct(arr_ + used_, *cur);

    DataT tmp{};
    for (; used_ < size_; ++used_)
      copy_construct(arr_ + used_, tmp);
  }

  template <typename DataT>
  Row<DataT> & Row<DataT>::operator= (const Row & rhs)
  {
    Row tmp{rhs};
    //------------ Kalb line
    this->swap(tmp);
    return *this;
  }

  template <typename DataT>
  const DataT & Row<DataT>::get (size_t idx) const
  {
    if (idx >= size_)
      throw std::out_of_range("Get index too big.");

    return arr_[idx];
  }

  template <typename DataT>
  void Row<DataT>::set (size_t idx, DataT new_val)
  {
    if (idx >= size_)
      throw std::out_of_range("Set index too big.");

    arr_[idx] = new_val;
  }

  template <typename DataT>
  const DataT & Row<DataT>::operator[] (size_t idx) const
  {
    return get(idx);
  }


  /*
   *
   * Matrix class
   *
   */

  using std::initializer_list;

  template <typename DataT>
  class Matrix : VBuf<Row<DataT>>
  {
    using VBuf<Row<DataT>>::arr_;
    using VBuf<Row<DataT>>::size_;
    using VBuf<Row<DataT>>::used_;

    using func = DataT (*)(size_t, size_t);

    size_t & rows_ = size_;
    size_t cols_{};

  public:

    Matrix ( size_t rows, size_t cols );
    Matrix ( size_t rows, size_t cols, func action );
    Matrix ( size_t rows, size_t cols, const initializer_list<DataT> & dat );
    Matrix ( const Matrix & orig );

    template <typename It>
    Matrix( size_t rows, size_t cols, It beg, It end );

    void swap ( Matrix & rhs ) noexcept;

    size_t cols( ) const noexcept;
    size_t rows( ) const noexcept;

    const DataT & get (size_t row, size_t col) const;
    void set (size_t row, size_t col, DataT val);
    const Row<DataT> & operator[] (size_t row) const;

    long double det( ) const;

    Matrix & transpose ( ) &;

    Matrix operator- ( ) const;

    Matrix & operator= ( const Matrix & orig );

    Matrix & operator+= ( const Matrix & matr );
    Matrix & operator-= ( const Matrix & matr );
    Matrix & operator*= ( const Matrix & matr );
    Matrix & operator*= ( DataT mul );

    bool operator== ( const Matrix & matr ) const;
    bool operator!= ( const Matrix & matr ) const;

    bool swap_lines ( size_t l1, size_t l2 );
    bool add_line ( size_t to, size_t from, DataT mul );
    bool mul_line ( size_t l, DataT mul );

    bool sum_suitable ( const Matrix<DataT> & matr ) const;
  };

  template<typename DataT>
  Matrix<DataT> operator+ ( const Matrix<DataT> & lhs, const Matrix<DataT> & rhs );
  template<typename DataT>
  Matrix<DataT> operator- ( const Matrix<DataT> & lhs, const Matrix<DataT> & rhs );
  template<typename DataT>
  Matrix<DataT> operator* ( const Matrix<DataT> & lhs, const Matrix<DataT> & rhs );
  template<typename DataT>
  Matrix<DataT> operator* ( const Matrix<DataT> & matr, DataT mul );
  template<typename DataT>
  Matrix<DataT> operator* ( DataT mul, const Matrix<DataT> & matr );
  template<typename DataT>
  Matrix<DataT> transpose ( const Matrix<DataT> & matr );

  /*
   *
   * Matrix class method realisations
   *
   */

  template <typename DataT>
  Matrix<DataT>::Matrix (size_t rows, size_t cols) : VBuf<Row<DataT>>(rows),
                                                     cols_(cols)
  {
    Row<DataT> tmp{cols_};
    for (; used_ < size_; ++used_)
      copy_construct(arr_ + used_, tmp);
  }

  template <typename DataT>
  Matrix<DataT>::Matrix ( size_t rows, size_t cols, func action ) : Matrix(rows, cols)
  {
    Matrix<DataT> tmp{rows_, cols_};

    for (size_t i = 0; i < rows_; ++i)
      for (size_t j = 0; j < cols_; ++j)
        tmp.set(i, j, action(i, j));

    swap(tmp);
  }

  template <typename DataT>
  Matrix<DataT>::Matrix ( size_t rows,
                          size_t cols,
                          const initializer_list<DataT> & data ) : Matrix(rows, cols)
  {
    size_t elem_num = rows_ * cols_;

    auto cur = data.begin(),
         end = data.end();

    for (size_t i = 0; i < elem_num && cur != end; ++i, ++cur)
      arr_[i / cols_].set(i % cols_, *cur);
  }

  template <typename DataT>
  Matrix<DataT>::Matrix ( const Matrix & orig ) : Matrix(orig.rows_, orig.cols_)
  {
    Matrix<DataT> tmp{rows_, cols_};

    for (size_t i = 0; i < rows_; ++i)
      for (size_t j = 0; j < cols_; ++j)
        tmp.set(i, j, orig[i][j]);

    swap(tmp);
  }

  template <typename DataT>
  template <typename It>
  Matrix<DataT>::Matrix ( size_t rows,
                          size_t cols,
                          It beg,
                          It end ) : Matrix(rows, cols)
  {
    size_t i = 0;
    size_t elem_num = rows_ * cols_;

    for (It cur = beg; cur != end && i < elem_num; ++i, ++cur)
      arr_[i / cols_].set(i % cols_, *cur);
  }

  template <typename DataT>
  void Matrix<DataT>::swap ( Matrix<DataT> & rhs ) noexcept
  {
    VBuf<Row<DataT>>::swap(rhs);
    std::swap(cols_, rhs.cols_);
  }

  template <typename DataT>
  const DataT & Matrix<DataT>::get (size_t row, size_t col) const
  {
    if (row >= rows_)
      throw std::out_of_range("Row index too big.");
    else if (col >= cols_)
      throw std::out_of_range("Column index too big.");

    return arr_[row].get(col);
  }

  template <typename DataT>
  void Matrix<DataT>::set (size_t row, size_t col, DataT val)
  {
    if (row >= rows_)
      throw std::out_of_range("Row index too big.");
    else if (col >= cols_)
      throw std::out_of_range("Column index too big.");

    arr_[row].set(col, val);
  }

  template <typename DataT>
  const Row<DataT> & Matrix<DataT>::operator[] ( size_t row ) const
  {
    if (row >= rows_)
      throw std::out_of_range("Row index too big.");

    return arr_[row];
  }

  template <typename DataT>
  size_t Matrix<DataT>::cols ( ) const noexcept
  {
    return cols_;
  }

  template <typename DataT>
  size_t Matrix<DataT>::rows ( ) const noexcept
  {
    return rows_;
  }

  template <typename DataT>
  long double Matrix<DataT>::det ( ) const
  {
    if (!std::is_fundamental<DataT>::value)
      throw std::bad_typeid();

    if ((cols_ != rows_))
      throw std::range_error("Matrix should be square.");

    long double sign = 1;

    Matrix<long double> tmp_dbl{rows_, cols_};
    for (size_t i = 0; i < rows_; ++i)
      for (size_t j = 0; j < cols_; ++j)
        tmp_dbl.set(i, j, static_cast<long double>(arr_[i][j]));

    for (size_t i = 0; i < cols_; ++i)
    {
      bool zero_col = true;

      if (tmp_dbl[i][i] != 0) // TODO: EPSILON
        zero_col = false;
      else
        for (size_t j = i + 1; j < rows_; ++j)
          if (tmp_dbl[j][i] != 0)
          {
            tmp_dbl.swap_lines(j, i);
            zero_col = false;
            sign = -sign;
            break;
          }

      if (zero_col)
        return 0;

      for (size_t k = i + 1; k < rows_; ++k)
      {
        if (tmp_dbl[k][i] == 0) // TODO: EPSILON
          continue;

        long double mul = tmp_dbl[k][i] / tmp_dbl[i][i];
        tmp_dbl.add_line(k, i, -mul);
      }
    }

    long double res = sign;
    for (size_t i = 0; i < cols_; ++i)
      res *= tmp_dbl[i][i];

    return res;
  }

  template <typename DataT>
  Matrix<DataT> & Matrix<DataT>::transpose ( ) &
  {
    Matrix<DataT> tmp{cols_, rows_};

    for (size_t i = 0; i < tmp.rows_; ++i)
      for (size_t j = 0; j < tmp.cols_; ++j)
        std::swap(tmp.arr_[i].arr_[j], arr_[j].arr_[i]);

    swap(tmp);
    return *this;
  }

  template <typename DataT>
  Matrix<DataT> Matrix<DataT>::operator- ( ) const
  {
    Matrix<DataT> res{rows_, cols_};

    for (size_t i = 0; i < rows_; ++i)
      for (size_t j = 0; j < cols_; ++j)
        res.set(i, j, -arr_[i][j]);

    return res;
  }

  template <typename DataT>
  Matrix<DataT> & Matrix<DataT>::operator= ( const Matrix & orig )
  {
    Matrix<DataT> tmp{orig};

    swap(tmp);
    return *this;
  }

  template <typename DataT>
  Matrix<DataT> & Matrix<DataT>::operator+= ( const Matrix & matr )
  {
    if (cols_ != matr.cols_ || rows_ != matr.rows_)
      throw std::range_error("Wrong matrix size.");

    Matrix<DataT> tmp{*this};

    for (size_t i = 0; i < rows_; ++i)
      for (size_t j = 0; j < cols_; ++j)
        tmp.set(i, j, tmp[i][j] + matr[i][j]);

    swap(tmp);
    return *this;
  }

  template <typename DataT>
  Matrix<DataT> & Matrix<DataT>::operator-= ( const Matrix & matr )
  {
    if (cols_ != matr.cols_ || rows_ != matr.rows_)
      throw std::range_error("Wrong matrix size.");

    Matrix<DataT> tmp{*this};

    for (size_t i = 0; i < rows_; ++i)
      for (size_t j = 0; j < cols_; ++j)
        tmp.set(i, j, tmp[i][j] - matr[i][j]);

    swap(tmp);
    return *this;
  }

  template <typename DataT>
  Matrix<DataT> & Matrix<DataT>::operator*= ( const Matrix & matr )
  {
    if (cols_ != matr.rows_)
      throw std::range_error("Wrong matrix size.");

    Matrix<DataT> res{rows_, matr.cols_};
    Matrix<DataT> tmp{matr};
    tmp.transpose();

    for (size_t i = 0; i < res.rows_; ++i)
      for (size_t j = 0; j < res.cols_; ++j)
        for (size_t k = 0; k < cols_; ++k)
          res.set(i, j, res[i][j] + arr_[i][k] * tmp[j][k]);

    swap(res);
    return *this;
  }

  template <typename DataT>
  Matrix<DataT> & Matrix<DataT>::operator*= ( DataT mul )
  {
    Matrix<DataT> tmp{*this};

    for (size_t i = 0; i < rows_; ++i)
      for (size_t j = 0; j < cols_; ++j)
        tmp.set(i, j, tmp[i][j] * mul);

    swap(tmp);

    return *this;
  }

  template <typename DataT>
  bool Matrix<DataT>::operator== (const Matrix & matr) const
  {
    if (rows_ != matr.rows_ || cols_ != matr.cols_)
      return false;

    for (size_t i = 0; i < rows_; ++i)
      for (size_t j = 0; j < cols_; ++j)
        if (arr_[i][j] != matr.data_[i][j])
          return false;

    return true;
  }

  template <typename DataT>
  bool Matrix<DataT>::operator!= (const Matrix & matr) const
  {
    return !operator==(matr);
  }

  template <typename DataT>
  bool Matrix<DataT>::swap_lines (size_t l1, size_t l2)
  {
    if (l1 >= cols_ || l2 >= cols_)
      throw std::range_error("Lines' numbers wrong.");

    std::swap(arr_[l1], arr_[l2]);

    return true;
  }

  template <typename DataT>
  bool Matrix<DataT>::add_line (size_t to, size_t from, DataT mul)
  {
    if (to >= cols_ || from >= cols_)
      throw std::range_error("Lines' numbers wrong.");

    Matrix<DataT> tmp{*this};

    for (size_t i = 0; i < cols_; ++i)
      tmp.set(to, i, tmp[to][i] + mul * arr_[from][i]);

    swap(tmp);
    return true;
  }

  template <typename DataT>
  bool Matrix<DataT>::mul_line (size_t l, DataT mul)
  {
    if (l >= cols_)
      throw std::range_error("Line number wrong.");

    Matrix<DataT> tmp{*this};

    for (size_t i = 0; i < cols_; ++i)
      tmp.set(l, i, tmp[l][i] * mul);

    swap(tmp);

    return true;
  }

  template <typename DataT>
  bool Matrix<DataT>::sum_suitable (const Matrix<DataT> & matr) const
  {
    return (cols_ == matr.cols_) && (rows_ == matr.rows_);
  }

  template<typename DataT>
  Matrix<DataT> operator+ ( const Matrix<DataT> & lhs, const Matrix<DataT> & rhs )
  {
    return Matrix<DataT>{lhs} += rhs;
  }

  template<typename DataT>
  Matrix<DataT> operator- ( const Matrix<DataT> & lhs, const Matrix<DataT> & rhs )
  {
    return Matrix<DataT>{lhs} -= rhs;
  }

  template<typename DataT>
  Matrix<DataT> operator* ( const Matrix<DataT> & lhs, const Matrix<DataT> & rhs )
  {
    return Matrix<DataT>{lhs} *= rhs;
  }

  template<typename DataT>
  Matrix<DataT> operator* ( const Matrix<DataT> & matr, DataT mul )
  {
    return Matrix<DataT>{matr} *= mul;
  }

  template<typename DataT>
  Matrix<DataT> operator* ( DataT mul, const Matrix<DataT> & matr )
  {
    return Matrix<DataT>{matr} *= mul;
  }

  template<typename DataT>
  Matrix<DataT> transpose ( const Matrix<DataT> & matr )
  {
    Matrix<DataT> tmp{matr};
    tmp.transpose();
    return tmp;
  }
}
