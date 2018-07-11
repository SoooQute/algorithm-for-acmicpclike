#pragma once
#include "stdafx.h"
using namespace std;
class TreeDiameter {
public:
    int n;
    vector<int> *G, *W, D, L;
    int *father, *d, *df;
    bool dW;
    TreeDiameter() : n(0), dW(false) {}
    void init(vector<int> *, int);
    void init(vector<int> *, vector<int> *, int);
    void dfs(int, int);
    void run();
    ~TreeDiameter() {
        delete[] father, delete[] d, delete[] df;
        if (dW) delete[] W;
    }
};
void TreeDiameter::init(vector<int> *iG, int iN) {
    G = iG;
    W = new vector<int>[iN << 1], dW = true;
    if (n < iN) {
        delete[] father, delete[] d, delete[] df;
        father = new int[iN << 1], d = new int[iN << 1], df = new int[iN << 1];
    }
    n = iN;
}
void TreeDiameter::init(vector<int> *iG, vector<int> *iW, int iN) {
    delete[] W;
    G = iG, W = iW, dW = false;
    if (n < iN) {
        delete[] father, delete[] d, delete[] df;
        father = new int[iN << 1], d = new int[iN << 1], df = new int[iN << 1];
    }
    n = iN;
}
void TreeDiameter::dfs(int x, int fa) {
    father[x] = fa;
    for (int i = 0; i < G[x].size(); i++) {
        int v = G[x][i];
        if (v == fa) continue;
        df[v] = W[x][i];
        d[v] = d[x] + df[v];
        dfs(v, x);
    }
}
void TreeDiameter::run() {
    d[1] = df[1] = 0;
    dfs(1, -1);
    int A = 1;
    for (int i = 1; i <= n; i++)
        if (d[A] < d[i])
            A = i;
    d[A] = df[A] = 0;
    dfs(A, -1);
    int B = 1;
    for (int i = 1; i <= n; i++) if (d[B] < d[i]) B = i;
    D.clear(), L.clear();
    while (B != father[A]) {
        D.push_back(B), L.push_back(df[B]);
        B = father[B];
    }
}