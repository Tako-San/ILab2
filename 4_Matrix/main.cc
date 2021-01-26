#include <iostream>
#include <cstdint>
#include <vector>
#include "matrix.hh"

using std::cout;
using std::cin;
using std::endl;

using std::vector;
using namespace MX;

int main( )
{
  uint size = 0;
  cin >> size;

  uint el_num = size * size;

  vector<double> raw{};
  raw.reserve(el_num);

  for (int i = 0, end = el_num; i < end; ++i)
  {
    double tmp;
    cin >> tmp;
    raw.push_back(tmp);
  }

  Matrix<double> matr{size, size, raw.begin(), raw.end()};

  cout << matr.det() << endl;

  return 0;
}