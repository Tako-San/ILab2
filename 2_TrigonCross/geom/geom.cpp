#include "geom.h"

namespace Geom
{
    using std::abs;
    using std::swap;
    using std::cout;
    using std::endl;

    template <typename T>
    int sign( T value )
    {
        return (T(0) < value) - (T(0) > value);
    }

    bool is_intersect_inv( const Triangle & tr1, const Triangle & tr2 )
    {
        uint8_t sh1 = tr1.shape(),
                sh2 = tr2.shape();

        uint8_t sh_or = sh1 | sh2;

        if (tr1.is_point() && tr2.is_point())
            return tr1[0] == tr2[0];

        if (tr1.is_line() && tr2.is_line())
        {
            auto It1 = LINE_PT.find(static_cast<const DegenT>(sh1 & LINE)),
                 It2 = LINE_PT.find(static_cast<const DegenT>(sh2 & LINE));

            auto i11 = It1->second.first,
                 i12 = It1->second.second,
                 i21 = It2->second.first,
                 i22 = It2->second.second;

            return line_intr(Line{tr1[i11], tr1[i12] - tr1[i11]},
                             Line{tr2[i21], tr2[i22] - tr2[i21]});
        }

        if (tr1.is_line() ^ tr2.is_line())
        {
            uint8_t cur_sh;
            const Triangle * trp1,
                           * trp2;

            if (tr1.is_line())
            {
                cur_sh = sh1;
                trp1 = &tr1;
                trp2 = &tr2;
            }
            else
            {
                cur_sh = sh2;
                trp1 = &tr2;
                trp2 = &tr1;
            }

            auto It = LINE_PT.find(static_cast<const DegenT>(cur_sh & LINE));

            auto i1 = It->second.first,
                 i2 = It->second.second;

            Line l = Line{(*trp1)[i1], (*trp1)[i2] - (*trp1)[i1]};

            if (trp2->is_point())
                return is_on_line(l, Vec {(*trp2)[0]});
            else
                return is_intersect3D(l, *trp2);
        }

        if (tr1.is_point() || tr2.is_point())
        {
            uint8_t cur_sh;
            const Triangle * trp1,
                           * trp2;

            if (tr1.is_point())
            {
                cur_sh = sh1;
                trp1 = &tr1;
                trp2 = &tr2;
            }
            else
            {
                cur_sh = sh2;
                trp1 = &tr2;
                trp2 = &tr1;
            }

            if (std::abs(trp2->plane().sdst((*trp1)[0])) < ACCURACY)
                return false;

            // TODO: write dot triangle intersection
            /*return is_intersect2D(tr1, tr2);*/
        }

        return false;
    }

    bool is_intersect3D( const Line & l, const Triangle & tr )
    {
        Vec e1 = tr[1] - tr[0];
        Vec e2 = tr[2] - tr[0];
        Vec  p = l.get_dir() % e2;
        double tmp = p & e1;

        if (std::abs(tmp) < ACCURACY)
            return false;

        tmp = 1.0 / tmp;
        Vec s = l.get_orig() - tr[0];
        double u = tmp * (s & p);

        if (u < 0.0 || u > 1.0)
            return false;

        Vec q = s % e1;
        double v = tmp * (l.get_dir() & q);
        if (v < 0.0 || v > 1.0)
            return false;

        return true;
    }

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

        if ((sign(sd1[0]) == sign(sd1[1]) && sign(sd1[0]) == sign(sd1[2])) ||
            (sign(sd2[0]) == sign(sd2[1]) && sign(sd2[0]) == sign(sd2[2])))
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
        }
        else
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
            }
            else
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


    void find_cross( const Triangle & tr, double sd[], const Line & int_line, double t[] )
    {
        double pr[3] = {};

        for (int i = 0; i < 3; ++i)
            pr[i] = int_line.get_dir() & (tr[i] - int_line.get_orig());

        if (sign(sd[1]) == sign(sd[2]))
        {
            std::swap(sd[2], sd[0]);
            std::swap(pr[2], pr[0]);
        }
        else if (sign(sd[0]) == sign(sd[2]))
        {
            std::swap(sd[2], sd[1]);
            std::swap(pr[2], pr[1]);
        }

        t[0] = pr[0] + (pr[2] - pr[0]) * sd[0] / (sd[0] - sd[2]);
        t[1] = pr[1] + (pr[2] - pr[1]) * sd[1] / (sd[1] - sd[2]);
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
            if ((&(*mate) != &(*pair_it)) && is_intersect3D(obj, mate->first))
                return true;

        if (node.is_parent())
            for (int i = 0; i < 8; ++i)
                if (node.intersect_subtree(obj, i))
                    return true;

        return false;
    }
}