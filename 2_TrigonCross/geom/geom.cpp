#include "geom.h"

namespace Geom
{
    using std::abs;
    using std::swap;
    using std::cout;
    using std::endl;

    inline bool is_one_sign( double n0, double n1, double n2 )
    {
        if (n0 * n1 <= 0)
            return false;
        if (n1 * n2 <= 0)
            return false;
        return n0 * n2 > 0;
    }


#define LITR(i11, i12, i21, i22)                        \
    line_intr(Line{tr1[i11], tr1[i12] - tr1[i11]},      \
              Line{tr2[i21], tr2[i22] - tr2[i21]})      \

#define ONLINE(tr1, tr2, i1, i2)                          \
    is_on_line(Line{tr2[i1], tr2[i2] - tr2[i1]}, tr1[0])  \

    bool is_intersect_inv( const Triangle & tr1, const Triangle & tr2 )
    {
        uint8_t sh1 = tr1.shape(),
                sh2 = tr2.shape();

        uint8_t sh_or = sh1 | sh2;

        if (sh1 & sh2 & POINT)
            return tr1[0] == tr2[0];

        if (tr1.is_line() && tr2.is_line())
        {
            auto It1 = LINE_PT.find(static_cast<const DegenT>(sh1 & LINE)),
                 It2 = LINE_PT.find(static_cast<const DegenT>(sh2 & LINE));

            auto i11 = It1->second.first,
                 i12 = It1->second.second,
                 i21 = It2->second.first,
                 i22 = It2->second.second;

            return LITR(i11, i12, i21, i22);
        }

        if (sh_or & (LINE | POINT))
        {
            Line l;
            Vec p;

            auto cur_sh = tr1.is_line() ? sh1 : sh2;

            auto It = LINE_PT.find(static_cast<const DegenT>(cur_sh | LINE));

            auto i1 = It->second.first,
                 i2 = It->second.second;

            if (tr1.is_line())
            {
                l = Line{tr1[i1], tr1[i2] - tr1[i1]};
                p = tr2[0];
            }
            else
            {
                l = Line{tr2[i1], tr2[i2] - tr2[i1]};
                p = tr1[0];
            }

            return ((p - l.get_orig()) % l.get_dir() == ZERO_VEC);
        }

        return false;
    }
#undef LITR
#undef ONLINE

    bool is_intersect3D( const Triangle & tr1, const Triangle & tr2 )
    {
        if (tr1.is_inv() || tr2.is_inv())
            return is_intersect_inv(tr1, tr2);

        Plane pl1 = tr1.plane();
        Plane pl2 = tr2.plane();

        if ((pl1.get_nrm() % pl2.get_nrm() == ZERO_VEC) &&
            (abs((pl1.get_dst()) - (pl2.get_dst())) < ACCURACY))
            return is_intersect2D(tr1, tr2);

        double sd2[3] = {};
        double sd1[3] = {};

        for (int i = 0; i < 3; ++i)
        {
            sd2[i] = pl1.sdst(tr2[i]);
            sd1[i] = pl2.sdst(tr1[i]);
        }

        if (is_one_sign(sd1[0], sd1[1], sd1[2]) ||
            is_one_sign(sd2[0], sd2[1], sd2[2]))
            return false;

        Line int_line = intersection(pl1, pl2);

        if (int_line.is_invalid())
            return false;

        double t1[2] = {};
        double t2[2] = {};

        find_cross(tr1, sd1, int_line, t1);
        find_cross(tr2, sd2, int_line, t2);

        return cmp_seg(t1, t2);
    }


    unsigned ind_of_max( double a, double b, double c )
    {
        int ind = 0;
        double max;

        if (a > b)
        {
            ind = 0;
            max = a;
        } else
        {
            ind = 1;
            max = b;
        }

        if (max < c)
            ind = 2;

        return ind;
    }

    bool is_intersect2D( const Triangle & tr1, const Triangle & tr2 )
    {
        Vec norm{tr1.plane().get_nrm()};

        double OXY = abs(norm & Vec{0, 0, 1}),
                OXZ = abs(norm & Vec{0, 1, 0}),
                OYZ = abs(norm & Vec{1, 0, 0});

        unsigned maxind = ind_of_max(OYZ, OXZ, OXY);

        Vec tr_v1[3] = {};
        Vec tr_v2[3] = {};

        for (unsigned i = 0, j = 0; i < 3 && j < 2; ++i)
        {
            if (i == maxind)
                continue;

            for (unsigned k = 0; k < 3; ++k)
            {
                tr_v1[k].get(j) = tr1[k][i];
                tr_v2[k].get(j) = tr2[k][i];
            }
            ++j;
        }
        return tst_intr(Triangle(tr_v1[0], tr_v1[1], tr_v1[2]),
                        Triangle(tr_v2[0], tr_v2[1], tr_v2[2]));
    }

    int get_mid_ind( int i0, int i1, int N )
    {
        if (i0 < i1)
            return (i0 + i1) / 2;
        else
            return (i0 + i1 + N) / 2 % N;
    }

    int get_extreme_ind( const Triangle & tr, const Vec & pt )
    {
        int i0 = 0, i1 = 0;
        while (true)
        {
            int mid = get_mid_ind(i0, i1, 3);
            int next = (mid + 1) % 3;
            Vec E{tr[next] - tr[mid]};

            if ((pt & E) > 0)
            {
                if (mid != i0)
                    i0 = mid;
                else
                    return i1;
            } else
            {
                int prev = (mid + 3 - 1) % 3;
                E = tr[mid] - tr[prev];
                if ((pt & E) < 0)
                    i1 = mid;
                else
                    return mid;
            }
        }
    }

    bool tst_intr( const Triangle & tr1, const Triangle & tr2 )
    {
        for (int i0 = 0, i1 = 2; i0 < 3; i1 = i0, ++i0)
        {
            Vec D1{(tr1[i0] - tr1[i1]).perp2D()},
                    D2{(tr2[i0] - tr2[i1]).perp2D()};

            int min1 = get_extreme_ind(tr2, -D1),
                    min2 = get_extreme_ind(tr1, -D2);

            Vec diff1{tr2[min1] - tr1[i0]},
                    diff2{tr1[min2] - tr2[i0]};

            if ((D1 & diff1) > 0 || (D2 & diff2) > 0)
                return false;
        }

        return true;
    }


    Line intersection( const Plane & pl1, const Plane & pl2 )
    {
        Vec n1 = pl1.get_nrm(),
                n2 = pl2.get_nrm();

        Vec n1n2_cross = n1 % n2;

        if (n1n2_cross == ZERO_VEC)
            return POISON_LINE;

        double s1 = pl1.get_dst(),
                s2 = pl2.get_dst();

        double n1n2 = n1 & n2,
                n1_2 = n1 & n1,
                n2_2 = n2 & n2;

        double a = (s2 * n1n2 - s1 * n2_2) / (n1n2 * n1n2 - n1_2 * n2_2);
        double b = (s1 * n1n2 - s2 * n1_2) / (n1n2 * n1n2 - n1_2 * n2_2);

        return Line{a * n1 + b * n2, n1n2_cross};
    }


    void find_cross( const Triangle & tr, const double sd[], const Line & int_line, double t[] )
    {
        int rg, /* rogue */
        m0, /* mate0 */
        m1; /* mate1 */

        if ((sd[0] * sd[1]) >= 0)
            rg = 2;
        else if ((sd[1] * sd[2]) >= 0)
            rg = 0;
        else
            rg = 1;

        m0 = (rg + 1) % 3;
        m1 = (rg + 2) % 3;

        double pr[3] = {};

        for (int i = 0; i < 3; ++i)
            pr[i] = int_line.get_dir() & (tr[i] - int_line.get_orig());

        t[0] = pr[m0] + (pr[rg] - pr[m0]) * sd[m0] / (sd[m0] - sd[rg]);
        t[1] = pr[m1] + (pr[rg] - pr[m1]) * sd[m1] / (sd[m1] - sd[rg]);
    }


    bool cmp_seg( double t1[], double t2[] )
    {
        if (t1[0] > t1[1])
            swap(t1[0], t1[1]);

        if (t2[0] > t2[1])
            swap(t2[0], t2[1]);

        return !((t1[1] < t2[0]) || (t1[0] > t2[1]));
    }


    bool intersect_octree( typename list<pair<Triangle, OctNode<Triangle> *>>::iterator pair_it )
    {
        OctNode<Triangle> & node = *(pair_it->second);
        Triangle & obj = pair_it->first;

        for (auto mate : node.get_data())
            if (&(*mate) != &(*pair_it) && is_intersect3D(obj, mate->first))
                return true;

        if (node.is_parent())
            for (int i = 0; i < 8; ++i)
                if (node.intersect_subtree(obj, i))
                    return true;

        return false;
    }
}