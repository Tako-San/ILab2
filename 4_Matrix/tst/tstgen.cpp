#include <iostream>
#include <cstdlib>
#include <ctime>

#include "../matrix.h"

using std::cout;
using std::cin;
using std::endl;

template <typename DataT>
void print_raw ( Matrix<DataT> & matr )
{
    int cols = matr.cols(),
        rows = matr.rows();

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
            cout << " " << (matr[i][j]) << " ";
        cout << "\n";
    }
}

int main( int ac, char ** av )
{
    if (ac != 3)
    {
        cout << "USAGE: ./gen [SIZE] [DET]" << endl;
        return 0;
    }

    int sz{};
    long double det{};

    sscanf(av[1], "%d", &sz);
    sscanf(av[2], "%Lf", &det);

    Matrix<long double> matr = Matrix<long double>::eye(sz);

    matr[0][0] = det;

    for (int i = 1; i < sz; ++i)
        matr[i][i] = 1;

    srand(clock());

    int end = 5 * sz;

    for (int i = 0; i < end; ++i)
    {
        long double sign = (rand() % 2 == 0) ? 1 : -1;

        uint r1 = rand() % sz;
        uint r2 = rand() % sz;

        while (r2 == r1)
        {
            srand(clock());
            r2 = rand() % sz;
        }

        uint div = rand() % 10;
        while (div == 0)
            div = rand() % 10;

        matr.add_line(r1, r2, sign * (rand() % 10) / div);
    }

    cout << sz << endl;
    print_raw(matr);

    return 0;
}