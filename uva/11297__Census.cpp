#include <iostream> 
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>
#include <memory>
#include <stack>
#include <utility>

using namespace std; 

struct qnode;
using qnode_p = unique_ptr<qnode>;
using mmpair  = pair<size_t, size_t>;

size_t N, Q;
qnode_p treeRoot;

struct point
{
    size_t row;
    size_t col;
};

point nullPoint = {numeric_limits<size_t>::max(), numeric_limits<size_t>::max()};

bool operator==(point const& p1, point const& p2)
{
    return p1.row == p2.row && p1.col == p2.col;
}

struct rectangle
{
    point topLeft;
    point bottomRight;
    bool is_point      () const { return topLeft == bottomRight; }
    bool is_wide_strip () const { return 0 == bottomRight.col - topLeft.col; }
    bool is_tall_strip () const { return 0 == bottomRight.row - topLeft.row; }
    size_t width       () const { return bottomRight.row - topLeft.row; }
    size_t height      () const { return bottomRight.col - topLeft.col; }
};

rectangle nullRect = {nullPoint, nullPoint};

bool operator==(rectangle const& r1, rectangle const& r2)
{
    return r1.topLeft == r2.topLeft && r1.bottomRight == r2.bottomRight;
}

bool operator!=(rectangle const& r1, rectangle const& r2)
{
    return !(r1.topLeft == r2.topLeft && r1.bottomRight == r2.bottomRight);
}

rectangle intersection(rectangle const& r1, rectangle const& r2)
{
    auto const topLeftX     = max(r1.topLeft.row,               r2.topLeft.row);
    auto const bottomRightX = min(r1.topLeft.row + r1.width(),  r2.topLeft.row + r2.width());
    auto const topLeftY     = max(r1.topLeft.col,               r2.topLeft.col);
    auto const bottomRightY = min(r1.topLeft.col + r1.height(), r2.topLeft.col + r2.height());

    if (topLeftX <= bottomRightX && topLeftY <= bottomRightY) 
    {
        return rectangle {{topLeftX, topLeftY}, {bottomRightX, bottomRightY}};
    } 
    else 
    {
        return nullRect;
    }
}

struct qnode
{
    array<qnode_p, 4> sons;
    rectangle         rec;
    size_t            countMin;
    size_t            countMax;
    
    qnode(qnode_p tl, qnode_p tr, qnode_p bl, qnode_p br, rectangle pRec) :
        sons {{move(tl), move(tr), move(bl), move(br)}},
        rec  {pRec} {};

    qnode(rectangle pRec, size_t pCount) :
        sons     {{nullptr, nullptr, nullptr, nullptr}},
        rec      {pRec},
        countMin {pCount},
        countMax {pCount} {};

    bool is_leaf () { return nullptr == sons.at(0); }    
};

qnode_p make_unique(qnode_p tl, qnode_p tr, qnode_p bl, qnode_p br, rectangle pRec)
{
    return qnode_p{new qnode {move(tl), move(tr), move(bl), move(br), pRec}};
}

qnode_p make_unique(rectangle pRec, size_t pCount)
{
    return qnode_p{new qnode {pRec, pCount}};
}

array<rectangle, 4> split(rectangle rec)
{
    auto const midRow = (rec.bottomRight.row - rec.topLeft.row) / 2;
    auto const midCol = (rec.bottomRight.col - rec.topLeft.col) / 2;

    return { rectangle {point {rec.topLeft.row,              rec.topLeft.col },             point {rec.topLeft.row + midRow, rec.topLeft.col + midCol}}
           , rectangle {point {rec.topLeft.row + midRow + 1, rec.topLeft.col },             point {rec.bottomRight.row,      rec.topLeft.col + midCol}}
           , rectangle {point {rec.topLeft.row,              rec.topLeft.col + midCol + 1}, point {rec.topLeft.row + midRow, rec.bottomRight.col}}
           , rectangle {point {rec.topLeft.row + midRow + 1, rec.topLeft.col + midCol + 1}, point {rec.bottomRight.row,      rec.bottomRight.col}} };
}

qnode_p make_node(vector<size_t> const& cs, rectangle rec)
{
    if (rec.is_point())
        return make_unique(rec, cs[rec.topLeft.row * N + rec.topLeft.col]);
    
    auto const splitted = split(rec);

    if (rec.is_wide_strip())
        return make_unique( make_node(cs, splitted.at(0))
                          , make_node(cs, splitted.at(1))
                          , nullptr
                          , nullptr
                          , rec );

    if (rec.is_tall_strip())
        return make_unique( make_node(cs, splitted.at(0))
                          , nullptr
                          , make_node(cs, splitted.at(2))
                          , nullptr
                          , rec );

    return make_unique( make_node(cs, splitted.at(0))
                      , make_node(cs, splitted.at(1))
                      , make_node(cs, splitted.at(2))
                      , make_node(cs, splitted.at(3))
                      , rec );
}

size_t get_max(qnode_p const& n)
{
    return !n ? numeric_limits<size_t>::min() : n->countMax;
}

size_t get_min(qnode_p const& n)
{
    return !n ? numeric_limits<size_t>::max() : n->countMin;
}

void set_min_max(qnode* n)
{
    if (!n)           return;
    if (n->is_leaf()) return;
    
    set_min_max(n->sons.at(0).get());
    set_min_max(n->sons.at(1).get());
    set_min_max(n->sons.at(2).get());
    set_min_max(n->sons.at(3).get());

    n->countMax = max({get_max(n->sons.at(0)), get_max(n->sons.at(1)), get_max(n->sons.at(2)), get_max(n->sons.at(3))});
    n->countMin = min({get_min(n->sons.at(0)), get_min(n->sons.at(1)), get_min(n->sons.at(2)), get_min(n->sons.at(3))});
}

void build_tree(vector<size_t> cs)
{
    qnode_p root = make_node(cs, {{0, 0}, {N - 1, N - 1}});
    set_min_max(root.get());
    treeRoot = move(root);
}

mmpair query_node(qnode* node, rectangle const& rec)
{
    if (node->rec == rec)
    {
        return make_pair(node->countMin, node->countMax);
    }

    size_t cMin = numeric_limits<size_t>::max();
    size_t cMax = numeric_limits<size_t>::min();;

    for (auto& son : node->sons)
    {
        if (nullptr == son) continue;
        auto const intersect = intersection(rec, son->rec);
        if (nullRect == intersect) continue;
        auto const tmpmm = query_node(son.get(), intersect);
        cMin = min(cMin, tmpmm.first);
        cMax = max(cMax, tmpmm.second);
    }

    return make_pair(cMin, cMax);
}

void query_range()
{
    size_t row1, col1, row2, col2;
    cin >> row1 >> col1 >> row2 >> col2;
    row1 -= 1; col1 -= 1; row2 -= 1; col2 -= 1;
    auto const mm = query_node(treeRoot.get(), {{row1, col1}, {row2, col2}});
    cout << mm.second << ' ' << mm.first << endl;
}

void change()
{
    size_t row, col;
    int v;
    cin >> row >> col >> v;
    row -= 1; col -= 1;

    rectangle leafRec = {{row, col}, {row, col}};

    stack<qnode*> path;
    qnode* node = treeRoot.get();
    
    while (!node->is_leaf())
    {
        path.push(node);

        for (auto& son : node->sons)
        {
            if (!son) continue;
            if (nullRect != intersection(leafRec, son->rec)) 
            { 
                node = son.get();
                break;
            }
        }
    }

    node->countMax = v;
    node->countMin = v;

    while (!path.empty())
    {
        auto const n = path.top();
        n->countMax = max({get_max(n->sons.at(0)), get_max(n->sons.at(1)), get_max(n->sons.at(2)), get_max(n->sons.at(3))});
        n->countMin = min({get_min(n->sons.at(0)), get_min(n->sons.at(1)), get_min(n->sons.at(2)), get_min(n->sons.at(3))});
        path.pop();
    }
}

// https://onlinejudge.org/external/112/11297.pdf
// https://en.wikipedia.org/wiki/Quadtree
int main() 
{ 
    cin >> N;    
    vector<size_t> cs(N * N);
    for (size_t row = 0; row < N; ++row)
    {
        for (size_t col = 0; col < N; ++col)
        {
            cin >> cs[row * N + col];
        }
    }

    build_tree(move(cs));

    cin >> Q;
    char c;
    for (size_t i = 0; i < Q; ++i)
    {
        cin >> c;
        switch (c)
        {
            case 'q': query_range();  break;
            case 'c': change();       break;
        }
    }

    return 0; 
}