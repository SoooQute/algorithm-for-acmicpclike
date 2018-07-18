#pragma once
#include "stdafx.h"
using namespace std;
/*
dir表示是有向图还是无向图
color表示该点属于哪个强连通分量
Scc表示强连通分量，当图是无向图时，Scc表示删掉图中的桥后划分出的各个部分
bridge表示图中的桥
cutvertex表示当图是无向图时图中的割点
*/
class Tarjan {
public:
    int size;
    int n, *color;
    bool *cutvertex, *root;
    vector<vector<int>> Scc;
    vector<vector<int>> dfsTree;
    vector<pair<int, int>> bridge;

    int *dfn, *low;
    bool *inStack;
    vector<int> *G, *DAG;
    int dep;
    stack<int> pStack;
    vector<int> component;

    Tarjan(int sz) : size(sz), n(0) {
        dfn = new int[sz << 1], low = new int[sz << 1], inStack = new bool[sz << 1], cutvertex = new bool[sz << 1], root = new bool[sz << 1], color = new int[sz << 1];
    }
    void init(vector<int> *, int);
    void dfs(int, int, bool);
    void run(bool);
    void getDAG();
    ~Tarjan() {
        delete[] dfn, delete[] low, delete[] inStack, delete[] color, delete[] cutvertex, delete[] root, delete[] DAG;
    }
};
void Tarjan::init(vector<int> *iG, int sz) {
    G = iG;
    n = sz;
    Scc.clear(), bridge.clear();
    memset(dfn, 0, sizeof(int) * (n + 1));
    memset(low, 0, sizeof(int) * (n + 1));
    memset(inStack, false, sizeof(bool) * (n + 1));
    memset(cutvertex, false, sizeof(bool) * (n + 1));
    memset(color, 0, sizeof(int) * (n + 1));
    memset(root, false, sizeof(bool) * (n + 1));
    dfsTree.resize(n + 1);
    for (int i = 1; i <= n; i++) dfsTree[i].clear();
    dep = 0;
    while (!pStack.empty()) pStack.pop();
}
void Tarjan::dfs(int x, int fa, bool dir) {
    if (x > n) return;
    if (fa == -1) root[x] = true;
    inStack[x] = true;
    dfn[x] = low[x] = ++dep;
    pStack.push(x);
    for (int i = 0; i < G[x].size(); i++) {
        int u = G[x][i];
        if (!dir && u == fa) continue;
        if (dfn[u] == 0) {
            dfsTree[x].push_back(u);
            if (!dir && fa == -1 && dfsTree[x].size() > 1) cutvertex[x] = true;
            dfs(u, x, dir);
            low[x] = min(low[x], low[u]);
            if (!dir && fa != -1 && low[u] >= dfn[x]) cutvertex[x] = true;
            if (dfn[x] < low[u]) bridge.push_back(make_pair(x, u));
        } else if (inStack[u]) low[x] = min(low[x], dfn[u]);
    }
    if (low[x] == dfn[x]) {
        component.clear();
        while (!pStack.empty()) {
            int u = pStack.top();
            pStack.pop();
            component.push_back(u);
            color[u] = Scc.size();
            inStack[u] = false;
            if (u == x) break;
        }
        Scc.push_back(component);
    }
}
void Tarjan::run(bool dir) {
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) dfs(i, -1, dir);
    }
}
void Tarjan::getDAG() {
    for (int i = 0; i <= n; i++) DAG[i].clear();
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < G[i].size(); j++) {
            int u = i, v = G[i][j];
            if (color[u] != color[v]) DAG[color[u] + 1].push_back(color[v] + 1);
        }
    }
}
