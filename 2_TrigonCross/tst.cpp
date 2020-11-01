#include <iostream>

#include "g_obj/vec.h"
#include "g_obj/line.h"
#include "g_obj/plane.h"
#include "g_obj/triangle.h"

#include "geom/geom.h"
#include "gtest/gtest.h"

using std::cout;
using std::cin;
using std::endl;

TEST(vector, getters)
{
    Vec v{1, 2, 3};

    EXPECT_DOUBLE_EQ(v[X], 1);
    EXPECT_DOUBLE_EQ(v[Y], 2);
    EXPECT_DOUBLE_EQ(v[Z], 3);
}

TEST(vector, constructors)
{
    Vec v1{1, 2, 3};

    EXPECT_DOUBLE_EQ(v1[X], 1.0);
    EXPECT_DOUBLE_EQ(v1[Y], 2.0);
    EXPECT_DOUBLE_EQ(v1[Z], 3.0);

    Vec v2{7.5};

    EXPECT_DOUBLE_EQ(v2[X], 7.5);
    EXPECT_DOUBLE_EQ(v2[Y], 7.5);
    EXPECT_DOUBLE_EQ(v2[Z], 7.5);

    Vec v3;

    EXPECT_DOUBLE_EQ(v3[X], 0);
    EXPECT_DOUBLE_EQ(v3[Y], 0);
    EXPECT_DOUBLE_EQ(v3[Z], 0);

    Vec v4{v1};

    EXPECT_DOUBLE_EQ(v4[X], 1.0);
    EXPECT_DOUBLE_EQ(v4[Y], 2.0);
    EXPECT_DOUBLE_EQ(v4[Z], 3.0);
}

TEST(vector, comparison)
{
    Vec v1{1, 1, 1};
    Vec v2{1, 1, 2};
    Vec v3{1, 1, 2};

    EXPECT_EQ(v1 == v2, false);
    EXPECT_EQ(v1 != v2, true);

    EXPECT_EQ(v2 == v3, true);
    EXPECT_EQ(v2 != v3, false);
}

TEST(vector, normalise)
{
    Vec v{7, 0, 0};
    Vec v_n{1, 0, 0};

    Vec v2{normalise(v)};
    v.normalise();

    EXPECT_EQ(v, v_n);
    EXPECT_EQ(v2, v_n);
}

TEST(vector, op_eq)
{
    Vec v01{1};
    Vec v02{2};
    Vec v03{3};

    EXPECT_EQ(v01 += v02, v03);

    Vec v11{1};
    Vec v12{2};
    Vec v13{3};

    EXPECT_EQ(v13 -= v11, v12);

    Vec v21{1};
    Vec v22{2};

    EXPECT_EQ(v21 *= 2, v22);

    Vec v31{1};
    Vec v32{2};

    EXPECT_EQ(v32 /= 2, v31);

    Vec v41{1, 2, 3};
    Vec v42 = v41;

    EXPECT_EQ(v41, v42);
}

TEST(vector, op)
{
    Vec v01{1, 2, 3};
    Vec v02 = -v01;

    EXPECT_DOUBLE_EQ(v02[X], -1);
    EXPECT_DOUBLE_EQ(v02[Y], -2);
    EXPECT_DOUBLE_EQ(v02[Z], -3);

    Vec v11{1, 2, 3};
    Vec v12{3, 2, 1};
    Vec v_sum = v11 + v12;
    Vec v_exp{4};

    EXPECT_EQ(v_sum, v_exp);

    Vec v21{1, 2, 3};
    Vec v22{1, 1, 1};
    Vec v_diff = v21 - v22;

    EXPECT_EQ(v_diff, Vec(0, 1, 2));

    Vec v31{1};
    Vec v32{2};

    Vec v33 = v31 * 2;
    Vec v34 = 2 * v31;

    EXPECT_EQ(v33, v32);
    EXPECT_EQ(v34, v32);
}

TEST(vector, dot)
{
    Vec v01{1, 0, 0};
    Vec v02{0, 1, 0};

    Vec v03{0, 0, 1};

    EXPECT_EQ(v01 % v02, v03);

    Vec v11{1, 2, 3};
    Vec v12{3, 2, 1};

    EXPECT_DOUBLE_EQ(v11 & v12, 10);
}

TEST(lines, constructors)
{
    Vec v1{1, 1, 1};
    Vec v2{3, 1, 3};

    Line l1{v1, v2};
    Line l2{l1};

    EXPECT_EQ(l1.get_orig(), l2.get_orig());
    EXPECT_EQ(l1.get_dir(), l2.get_dir());
}

TEST(planes, constructors)
{
    Vec v1{1};
    Vec v2{4, 0, 0};

    Plane pl1{v2, v1};
    Plane pl2{pl1};

    EXPECT_EQ(pl1.get_nrm(), normalise(v2));
    EXPECT_EQ(pl1.get_dst(), 1);

    EXPECT_EQ(pl1.get_nrm(), pl2.get_nrm());
    EXPECT_EQ(pl1.get_dst(), pl2.get_dst());

    Vec v3{1, 0, 0};
    Vec v4{0, 1, 0};
    Vec v5{1, 1, 0};

    Plane pl3{v3, v4, v5};
    EXPECT_EQ(abs(pl3.get_nrm()[Z]), 1);
    EXPECT_EQ(pl3.get_dst(), 0);
}

TEST(triangles, intersection)
{
    Triangle tr1{Vec{1, 0, 0}, Vec{0, 1,  0}, Vec{0, 0, 1}};
    Triangle tr2{Vec{2, 0, 0}, Vec{0, 2, 0}, Vec{0, 0, 0.5}};

    EXPECT_EQ(is_intersect3D(tr1, tr2), true);
}

int main( int argc, char ** argv )
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
