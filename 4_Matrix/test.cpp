#include <iostream>
#include "gtest/gtest.h"

#include "matrix.h"

using std::cout;
using std::cin;
using std::endl;

TEST(ctor, init_lst)
{
    Matrix<int> m{2, 3, {1, 2, 3, 4, 5, 6}};

    for (int i = 0; i < 6; ++i)
        EXPECT_EQ(m[i / 3][i % 3], i + 1);
}

TEST(ctor, copy)
{
    Matrix<int> m1{2, 3, {1, 2, 3, 4, 5, 6}};
    Matrix<int> m2{m1};

    for (int i = 0; i < 6; ++i)
        EXPECT_EQ(m2[i / 3][i % 3], i + 1);
}

TEST(op, mul)
{
    Matrix<int> m1{1, 4, {0, 1, 2, 3}};
    m1 *= 2;
    for (int i = 0; i < 4; ++i)
        EXPECT_EQ(m1[i / 4][i % 4], 2 * i);

    Matrix<int> m2{m1 * 2};
    for (int i = 0; i < 4; ++i)
        EXPECT_EQ(m2[i / 4][i % 4], 4 * i);

    Matrix<int> m3{2 * m1};
    for (int i = 0; i < 4; ++i)
        EXPECT_EQ(m3[i / 4][i % 4], 4 * i);
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

    Matrix<int> m3{1, 3};
    Matrix<int> m4{2, 3};

    EXPECT_EQ((m3 + m4).is_invalid(), true);
}

TEST(det, little)
{
    Matrix<double> m1{4, 4, {3, 0, 0, 0,
                             0, 3, 0, 0,
                             0, 0, 3, 0,
                             0, 0, 0, 3}};
    EXPECT_DOUBLE_EQ(m1.det(), 81);

    Matrix<double> m2{4, 4, {0, 3, 0, 0,
                             3, 0, 0, 0,
                             0, 0, 3, 0,
                             0, 0, 0, 3}};
    EXPECT_DOUBLE_EQ(m2.det(), -81);

    Matrix<double> m3{4, 4, {1, 2, 3, 4,
                             2, 0, 1, 3,
                             4, 1, 1, 2,
                             0, 1, 3, 1}};
    EXPECT_DOUBLE_EQ(m3.det(), -39);

    Matrix<double> m4{4, 4, {1, 2, 3, 4,
                             2, 0, 1, 3,
                             4, 1, 1, 2,
                             0, 0, 0, 0}};
    EXPECT_DOUBLE_EQ(m4.det(), 0);

    Matrix<double> m5{4, 4, { 3, -3, -5,  8,
                             -3,  2,  4, -6,
                              2, -5, -7,  5,
                             -4,  3,  5, -6}};

    EXPECT_DOUBLE_EQ(m5.det(), 18);
}

TEST(op, matr_mul)
{
    Matrix<double> m1{1, 4, {1, 1, 1, 1}};
    Matrix<double> m2{4, 2, {1, 1,
                             1, 1,
                             1, 1,
                             1, 1}};

    Matrix<double> m3 = m1 % m2;

    EXPECT_DOUBLE_EQ(m3[0][0], 4);
    EXPECT_DOUBLE_EQ(m3[0][1], 4);
}

int main( int argc, char ** argv )
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
