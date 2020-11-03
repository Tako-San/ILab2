#include <iostream>
#include "gtest/gtest.h"

#include "matrix.h"

using std::cout;
using std::cin;
using std::endl;

TEST(ctor, init_lst)
{
    Matrix<int> m{2, 2, {1, 2, 3, 4}};

    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[0][1], 2);
    EXPECT_EQ(m[1][0], 3);
    EXPECT_EQ(m[1][1], 4);
}

TEST(ctor, copy)
{
    Matrix<int> m1{2, 2, {1, 2, 3, 4}};
    Matrix<int> m2{m1};

    EXPECT_EQ(m2[0][0], 1);
    EXPECT_EQ(m2[0][1], 2);
    EXPECT_EQ(m2[1][0], 3);
    EXPECT_EQ(m2[1][1], 4);
}

TEST(op, mul)
{
    Matrix<int> m1{2, 2, {1, 0, 0, 1}};
    m1 *= 2;

    EXPECT_EQ(m1[0][0], 2);
    EXPECT_EQ(m1[0][1], 0);
    EXPECT_EQ(m1[1][0], 0);
    EXPECT_EQ(m1[1][1], 2);

    Matrix<int> m2{m1 * 2};

    EXPECT_EQ(m2[0][0], 4);
    EXPECT_EQ(m2[0][1], 0);
    EXPECT_EQ(m2[1][0], 0);
    EXPECT_EQ(m2[1][1], 4);

    Matrix<int> m3{2 * m1};

    EXPECT_EQ(m3[0][0], 4);
    EXPECT_EQ(m3[0][1], 0);
    EXPECT_EQ(m3[1][0], 0);
    EXPECT_EQ(m3[1][1], 4);
}

TEST(op, plus_minus)
{
    Matrix<int> m1{2, 2, {0, 1, 2, 3}};
    Matrix<int> m2{m1};

    Matrix<int> sum = m1 + m2;

    for (int i = 0; i < 4; ++i)
        EXPECT_EQ(sum[i / 2][i % 2], 2 * i);

    Matrix<int> diff = m1 - m2;

    for (int i = 0; i < 4; ++i)
        EXPECT_EQ(diff[i / 2][i % 2], 0);
}

int main( int argc, char ** argv )
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
