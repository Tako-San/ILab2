#include <iostream>
#include <cstdint>
#include <vector>
#include "matrix.h"

using std::cout;
using std::cin;
using std::endl;

using std::vector;

int main( )
{
    int size = 0;
    cin >> size;

    vector<double> raw{};
    for (int i = 0, end = size * size; i < end; ++i)
    {
        double tmp;
        cin >> tmp;
        raw.push_back(tmp);
    }

    Matrix<double> matr{size, size, raw};

    cout << matr.det() << endl;

    return 0;
}