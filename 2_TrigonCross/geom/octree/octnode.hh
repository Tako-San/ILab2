#ifndef ILAB2_OCTNODE_H
#define ILAB2_OCTNODE_H

#include <vector>

#include "../geom.h"

namespace Geom
{
    const unsigned CHILDREN_NUM = 3;
    const double MIN_DIAG = 0.3;

    using std::vector;
    using std::list;
    using std::pair;

    using namespace Geom;

    template <typename DataT>
    class OctTree;

    template <typename DataT>
    class OctNode final
    {
        friend class OctTree<DataT>;

    private:

        OctNode * parent_;
        OctNode * child_[8];

        bool has_ch_{false};

        list<DataT> data_{};
        Box zone_;

        int lvl_;

    private:

        OctNode();
        explicit OctNode( Box zone, OctNode * parent = nullptr );

        [[nodiscard]] bool is_parent( ) const;
        [[nodiscard]] bool is_in( const DataT & obj ) const;
        [[nodiscard]] bool need_children( ) const;

        OctNode * insert( const DataT & obj, bool hate_children = false );

        bool is_intersect( const DataT & obj, bool not_in_tree = false ) const;
        bool is_intersect_child( const DataT & obj, uint idx, bool not_in_tree = false ) const;

        void print( );

        void clear_sub( );
        void div_box( );
        void divide( );
    };

#include "octnode.ii"

}
#endif //ILAB2_OCTNODE_H
