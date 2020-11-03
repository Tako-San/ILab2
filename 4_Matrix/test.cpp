#include <iostream>
#include "gtest/gtest.h"

#include "matrix.h"

using std::cout;
using std::cin;
using std::endl;

TEST(constructor, tst1)
{
    Matrix<int> m{2, 2};
}

int main( int argc, char ** argv )
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
