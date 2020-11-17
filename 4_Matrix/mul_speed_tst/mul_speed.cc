#include <iostream>
#include <vector>
#include <cstdio>
#include <ctime>

#include "../matrix.hh"

using std::cin;
using std::cout;
using std::endl;
using std::vector;

void usage( )
{
    std::cerr << "USAGE: ./PROGNAME [ALGNUM]" << endl;
    std::cerr << "1 for transpose, 0 for no transpose" << endl;
}

using namespace F;

template <typename DataT>
Matrix<DataT> mul( const Matrix<DataT> & lhs, const Matrix<DataT> & rhs )
{
    uint lhs_r = lhs.rows(),
         rhs_r = rhs.rows(),
         lhs_c = lhs.cols(),
         rhs_c = rhs.cols();
    
    Matrix<DataT> tmp{lhs_r, rhs_c};

    for (uint i = 0; i < lhs_r; ++i)
        for (uint j = 0; j < rhs_c; ++j)
            for (uint k = 0; k < lhs_c; ++k)
                tmp[i][j] += lhs[i][k] * rhs[k][j];

    return std::move(tmp);
}

template <typename DataT>
Matrix<DataT> mul_tr( const Matrix<DataT> & lhs, const Matrix<DataT> & rhs )
{
    uint lhs_r = lhs.rows(),
         rhs_r = rhs.rows(),
         lhs_c = lhs.cols(),
         rhs_c = rhs.cols();

    Matrix<DataT> tmp1{lhs_r, rhs_c};
    Matrix<DataT> tmp2{transpose(rhs)};

    for (uint i = 0; i < lhs_r; ++i)
        for (uint j = 0; j < rhs_c; ++j)
            for (uint k = 0; k < lhs_c; ++k)
                tmp1[i][j] += lhs[i][k] * tmp2[j][k];

    return std::move(tmp1);
}

int main( int ac, char ** av )
{
    if (ac != 2)
    {
        usage();
        return 0;
    }

    int flag = atoi(av[1]);

    std::clock_t start;
    double duration;

    uint rows1{};
    uint rows2{};
    uint cols1{};
    uint cols2{};

    cin >> rows1;
    cin >> cols1;

    cin >> rows2;
    cin >> cols2;

    vector<long double> raw1{};
    vector<long double> raw2{};

    for (int i = 0, end = rows1 * cols1; i < end; ++i)
    {
        double tmp;
        cin >> tmp;
        raw1.push_back(tmp);
    }

    for (int i = 0, end = rows2 * cols2; i < end; ++i)
    {
        double tmp;
        cin >> tmp;
        raw2.push_back(tmp);
    }

    Matrix<long double> m1{rows1, cols1, raw1.begin(), raw1.end()};
    Matrix<long double> m2{rows2, cols2, raw2.begin(), raw2.end()};

    assert(cols1 == rows2);

    switch (flag)
    {
        case 0:
            start = std::clock();
            mul(m1, m2);
            duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
            cout<<"no tr: "<< duration <<'\n';
            break;
        case 1:
            start = std::clock();
            mul_tr(m1, m2);
            duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
            cout<<"tr: "<< duration <<'\n';
            break;
        default:
            usage();
            break;
    }

    return 0;
}