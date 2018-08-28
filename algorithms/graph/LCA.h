#pragma once
#include "stdafx.h"
using namespace std;

class LCA {
public:
    int *depth, *father, *sz, n, lgn;
    vector<int *> ancient;
    vector<int> * T;
    LCA(int nn) {
        depth = new int[nn << 1];
        father = new int[nn << 1];
        sz = new int[nn << 1];
        ancient.resize(64);
        for (auto &i : ancient) i = new int[nn << 1];
    }
    void init(vector<int> *, int, int);
    void dfs(int, int, int);
    int query(int, int);
    ~LCA() {
        delete[] depth;
        delete[] father;
        delete[] sz;
        for (auto &i : ancient) delete[] i;
    }
};
void LCA::dfs(int root, int fa, int dep) {
    ancient[0][root] = fa;
    depth[root] = dep;
    sz[root] = 1;
    for (int i = 0; i < T[root].size(); i++) {
        int u = T[root][i];
        if (u == fa) continue;
        dfs(u, root, dep + 1);
        sz[root] += sz[u];
    }
}
void LCA::init(vector<int> * G, int root, int nn) {
    T = G, n = nn, lgn = 1;
    while (nn) lgn++, nn >>= 1;
    dfs(root, -1, 0);
    for (int i = 0; i < lgn; i++) ancient[i][root] = -1;
    for (int i = 1; i < lgn; i++) {
        for (int j = 1; j <= n; j++) {
            if (ancient[i - 1][j] == -1) ancient[i][j] = -1;
            else ancient[i][j] = ancient[i - 1][ancient[i - 1][j]];
        }
    }
}
int LCA::query(int u, int v) {
    if (depth[u] > depth[v]) swap(u, v);
    int d = 0;
    while (depth[u] != depth[v]) {
        if ((depth[v] - depth[u]) & (1 << d)) v = ancient[d][v];
        d++;
    }
    if (u == v) return u;
    for (int i = lgn; i >= 0; i--) {
        if (ancient[i][u] != ancient[i][v]) u = ancient[i][u], v = ancient[i][v];
    }
    return ancient[0][u];
}
