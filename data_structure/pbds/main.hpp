#include <bits/extc++.h>
using namespace __gnu_pbds;
template <class KT, class VT = null_type>
using RBTree = tree<KT, VT, std::less<KT>, rb_tree_tag, tree_order_statistics_node_update>;