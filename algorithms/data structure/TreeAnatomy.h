#pragma once
#include "stdafx.h"
#include "algorithms/data structure/SegmentTree.h"
/*
树链剖分的本质是把树上的节点映射到一条直线，且各不相同，其映射的方法能保证在对树中一条路径进行处理时，把路径上的点映射到直线
上，得到不超过log(n)条线段。然后可以用线段树（或其他数据结构）来维护得到的直线，来达到降低时间花费的目的。
*/
using namespace std;
template<typename Ty> class TreeAnatomy {
#ifndef DEBUG
private:
#else
public:
#endif
    //Tree node index start from 1
    int n, cnt;
    int *dep, *father, *siz, *top, *son, *tid, *rnk;
    Ty *base, *w;
    vector<int> *T;
    SegmentTree<Ty> st;
    void dfs1(int, int, int);
    void dfs2(int, int);
public:
    TreeAnatomy(int sz) : n(sz), st(sz), dep(new int[sz]), father(new int[sz]), siz(new int[sz]), top(new int[sz]),
        son(new int[sz]), tid(new int[sz]), rnk(new int[sz]), base(new Ty[sz]) {}
    void run(vector<int> *, Ty *, int, int);
    Ty query(int);
    Ty query(int, int);
    void modify(int, Ty);
    void modify(int, int, Ty);
};
template<typename Ty> void TreeAnatomy<Ty>::dfs1(int u, int fa, int d) {
    dep[u] = d, father[u] = fa, siz[u] = 1, son[u] = -1;
    for(int i = 0; i < T[u].size(); i++) {
        int v = T[u][i];
        if(v == fa) continue;
        dfs1(v, u, d + 1);
        siz[u] += siz[v];
        if(son[u] == -1 || siz[v] > siz[son[u]]) son[u] = v;
    }
}
template<typename Ty> void TreeAnatomy<Ty>::dfs2(int u, int tp) {
    top[u] = tp;
    tid[u] = ++cnt;
    rnk[tid[u]] = u;
    if(son[u] == -1) return;
    dfs2(son[u], tp);
    for(int i = 0; i < T[u].size(); i++) {
        int v = T[u][i];
        if(v != son[u] && v != father[u]) dfs2(v, v);
    }
}
template<typename Ty> void TreeAnatomy<Ty>::run(vector<int> * Tree, Ty * weight, int size, int root) {
    T = Tree, w = weight, n = size, cnt = 0;
    dfs1(root, -1, 0);
    dfs2(root, root);
    for(int i = 1; i <= n; i++) base[i] = w[rnk[i]];
    st.build(base, 1, n);
}
//query on subtree u
template<typename Ty> Ty TreeAnatomy<Ty>::query(int u) {
    return st.query(tid[u], tid[u] + siz[u] - 1);
}
//query on path u->v
template<typename Ty> Ty TreeAnatomy<Ty>::query(int u, int v) {
    Ty ans = 0;
    while(top[u] != top[v]) {
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        ans = st.merge(ans, st.query(tid[top[u]], tid[u]));
        u = father[top[u]];
    }
    if(tid[u] > tid[v]) swap(u, v);
    ans = st.merge(ans, st.query(tid[u], tid[v]));
    return ans;
}
//update subtree u with k
template<typename Ty> void TreeAnatomy<Ty>::modify(int u, Ty k) {
    st.modify(tid[u], tid[u] + siz[u] - 1, k);
}
//update path u->v with k
template<typename Ty> void TreeAnatomy<Ty>::modify(int u, int v, Ty k) {
    while(top[u] != top[v]) {
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        st.modify(tid[top[u]], tid[u], k);
        u = father[top[u]];
    }
    if(tid[u] > tid[v]) swap(u, v);
    st.modify(tid[u], tid[v], k);
}