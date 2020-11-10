#include <iostream>
#include "gtest/gtest.h"

#include "matrix.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;

using namespace F;

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

TEST(ctor, iter)
{
    std::vector<int> v{0, 1, 2, 3, 4, 5};

    Matrix<int> m1{2, 3, v.begin(), v.end()};

    for (int i = 0; i < 6; ++i)
        EXPECT_EQ(m1[i / 3][i % 3], i);

    Matrix<int> m2{2, 3, v.rbegin(), v.rend()};
}

TEST(ctor, func)
{
    Matrix<int> m{2, 3, [](size_t i, size_t j)->int{return i + j;}};

    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 3; ++j)
            EXPECT_EQ(m[i][j], i + j);
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

    Matrix<double> m3 = m1 * m2;

    EXPECT_DOUBLE_EQ(m3[0][0], 4);
    EXPECT_DOUBLE_EQ(m3[0][1], 4);
}

TEST(constructor, copy)
{
    Matrix<int> m1{2, 2, {0, 1, 2, 3}};
    Matrix<int> m2{m1};

    Matrix<int> m3 = m1 + m2;

    for (int i = 0; i < 4; ++i)
        EXPECT_EQ(m3[i / 2][i % 2], 2 * i);
}

TEST(elem_ops, add)
{
    Matrix<int> m1{2, 2, {1, 1, 1, 1}};

    m1.add_line(1, 0, 3);

    EXPECT_EQ(m1[0][0], 1);
    EXPECT_EQ(m1[0][1], 1);
    EXPECT_EQ(m1[1][0], 4);
    EXPECT_EQ(m1[1][1], 4);
}

TEST(oper, square_brace)
{
    Matrix<int> m1{2, 2, {0, 1, 2, 3}};

    EXPECT_EQ(m1[1][1], 3);
}

TEST(oper, transpose)
{
    Matrix<int> m{1, 4, {0, 1, 2, 3}};

    m.transpose();

    for (int i = 0; i < 4; ++i)
        EXPECT_EQ(m[i][0], i);

    Matrix<int> m1{transpose(m)};

    for (int i = 0; i < 4; ++i)
        EXPECT_EQ(m1[0][i], i);
}

TEST(types, string)
{
    std::vector<string> str_v = {"hello", "world", "i am", "matrix"};
    std::initializer_list<string> init_lst = {"hello", "world", "i am", "matrix"};
    Matrix<string> m1{1, 4, init_lst};

    for (int i = 0; i < 4; ++i)
        EXPECT_EQ(m1[0][i % 4], str_v[i]);

    m1.transpose();

    for (int i = 0; i < 4; ++i)
        EXPECT_EQ(m1[i][0], str_v[i]);

    Matrix<string> m2 = m1 + m1;

    for (int i = 0; i < 4; ++i)
        EXPECT_EQ(m2[i][0], str_v[i] + str_v[i]);

}

TEST(ctor, move)
{
    Matrix<int> m1{1, 4, {0, 1, 2, 3}};
    Matrix<int> m2{1, 4, {0, 0, 0, 0}};

    m2 = m1 + m2;

    for (int i = 0; i < 4; ++i)
        EXPECT_EQ(m2[0][i], i);
}

int main( int argc, char ** argv )
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
