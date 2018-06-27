#include "../stdafx.h"
using namespace std;

class LCA {
public:
    int n;
    int ancient[110000][20], depth[110000], father[110000], sz[110000];
    vector<vector<int>> * T;
    void init(vector<vector<int>> *, int, int);
    void dfs(int, int, int);
    int query(int, int);
};
void LCA::dfs(int root, int fa, int dep) {
    ancient[root][0] = fa;
    depth[root] = dep;
    sz[root] = 1;
    for (int i = 0; i < (*T)[root].size(); i++) {
        int u = (*T)[root][i];
        if (u == fa) continue;
        dfs(u, root, dep + 1);
        sz[root] += sz[u];
    }
}
void LCA::init(vector<vector<int>> * G, int root, int nn) {
    T = G, n = nn;
    dfs(root, -1, 0);
    for (int i = 0; i < 20; i++) ancient[root][i] = -1;
    for (int i = 1; i < 20; i++) {
        for (int j = 1; j <= n; j++) {
            if (ancient[j][i - 1] == -1) ancient[j][i] = -1;
            else ancient[j][i] = ancient[ancient[j][i - 1]][i - 1];
        }
    }
}
int LCA::query(int u, int v) {
    if (depth[u] > depth[v]) swap(u, v);
    int d = 0;
    while (depth[u] != depth[v]) {
        if ((depth[v] - depth[u]) & (1 << d)) v = ancient[v][d];
        d++;
    }
    if (u == v) return u;
    for (int i = 19; i >= 0; i--) {
        if (ancient[u][i] != ancient[v][i]) u = ancient[u][i], v = ancient[v][i];
    }
    return ancient[u][0];
}