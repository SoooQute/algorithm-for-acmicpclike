#pragma once
#include "stdafx.h"
#include "algorithms/data structure/SegmentTree.h"
/*
树链剖分的本质是把树上的节点映射到一条直线，且各不相同，其映射的方法能保证在对树中一条路径进行处理时，把路径上的点映射到直线
上，得到不超过log(n)条线段。然后可以用线段树（或其他数据结构）来维护得到的直线，来达到降低时间花费的目的。
*/
using namespace std;
class TreeAnatomy {
    //Tree node index start from 1
private:
    int n, cnt;
    int *dep, *father, *siz, *top, *son, *tid, *rnk, *base;
    vector<vector<int> > * T;
    int * w;
    SegmentTree<int> st;
    void dfs1(int u, int fa, int d);
    void dfs2(int u, int tp);
public:
	TreeAnatomy(int n) : st(n, 0) {
        dep = (int *)malloc((n << 1) * sizeof(int));
        father = (int *)malloc((n << 1) * sizeof(int));
        siz = (int *)malloc((n << 1) * sizeof(int));
        top = (int *)malloc((n << 1) * sizeof(int));
        son = (int *)malloc((n << 1) * sizeof(int));
        tid = (int *)malloc((n << 1) * sizeof(int));
        rnk = (int *)malloc((n << 1) * sizeof(int));
        base = (int *)malloc((n << 1) * sizeof(int));
    }
    void cut(vector<vector<int> > * Tree, int * weight, int size);
    int query(int u);
    void modify(int u, int v, int k);
};
void TreeAnatomy::dfs1(int u, int fa, int d) {
    dep[u] = d;
    father[u] = fa;
    siz[u] = 1;
    son[u] = -1;
    for (int i = 0; i < (*T)[u].size(); i++) {
        int v = (*T)[u][i];
        if (v == fa) continue;
        dfs1(v, u, d + 1);
        siz[u] += siz[v];
        if (son[u] == -1 || siz[v] > siz[son[u]]) son[u] = v;
    }
}
void TreeAnatomy::dfs2(int u, int tp) {
    top[u] = tp;
    tid[u] = ++cnt;
    rnk[tid[u]] = u;
    if (son[u] == -1) return;
    dfs2(son[u], tp);
    for (int i = 0; i < (*T)[u].size(); i++) {
        int v = (*T)[u][i];
        if (v != son[u] && v != father[u]) dfs2(v, v);
    }
}
void TreeAnatomy::cut(vector<vector<int> > * Tree, int * weight, int size) {
    T = Tree, w = weight, n = size, cnt = 0;
    dfs1(1, -1, 0);
    dfs2(1, 1);
    for (int i = 1; i <= n; i++) base[i] = w[rnk[i]];
    st.build(base, 1, n);
}
int TreeAnatomy::query(int u) {
    return st.query(tid[u], tid[u]);
}
void TreeAnatomy::modify(int u, int v, int k) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        st.modify(tid[top[u]], tid[u], k);
        u = father[top[u]];
    }
    if (tid[u] > tid[v]) swap(u, v);
    st.modify(tid[u], tid[v], k);
}