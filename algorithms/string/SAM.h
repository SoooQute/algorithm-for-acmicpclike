#pragma once
#include "stdafx.h"
using namespace std;
/*
http:/ /www.cnblogs.com/dramstadt/p/6149464.html
*/
class SAM {
public:
    struct transArray {
        int trans[26];
    } *ch;
    int *fa, *maxlen, *color, Last, sz;
    int *szRight;
    vector<vector<int> > G;
    SAM(int n) : sz(1), Last(1), szRight(NULL) {
        n = n * 2 + 1;
        ch = (transArray *)malloc((n) * sizeof(transArray));
        memset(ch, 0, n * sizeof(transArray));
        fa = (int *)malloc((n) * sizeof(int));
        memset(fa, 0, n * sizeof(int));
        maxlen = (int *)malloc((n) * sizeof(int));
        memset(maxlen, 0, n * sizeof(int));
        color = (int *)malloc((n) * sizeof(int));
        memset(color, 0, n * sizeof(int));
    }
    void add(int x) {
        int np = ++sz, p = Last;
        Last = np;
        maxlen[np] = maxlen[p] + 1;
        color[np] = 1;
        while (p && !ch[p].trans[x]) ch[p].trans[x] = np, p = fa[p];
        if (!p) fa[np] = 1;
        else {
            int q = ch[p].trans[x];
            if (maxlen[p] + 1 == maxlen[q]) fa[np] = q;
            else {
                int nq = ++sz;
                ch[nq] = ch[q];
                maxlen[nq] = maxlen[p] + 1;
                fa[nq] = fa[q];
                fa[q] = fa[np] = nq;
                while (p && ch[p].trans[x] == q) ch[p].trans[x] = nq, p = fa[p];
            }
        }
    }
    pair<int, int> length(int p) {
        return make_pair(maxlen[p], maxlen[fa[p]] + 1);
    }
    void dfs(int x) {
        szRight[x] = color[x];
        for (int i = 0; i < G[x].size(); i++) {
            int p = G[x][i];
            dfs(p);
            szRight[x] += szRight[p];
        }
    }
    void getSzRight() {
        if (szRight != NULL) free(szRight);
        szRight = (int *)malloc((sz + 1) * sizeof(int));
        memset(szRight, 0, (sz + 1) * sizeof(int));
        G.clear();
        G = vector<vector<int> >(sz + 1);
        for (int i = 2; i <= sz; i++) G[fa[i]].push_back(i);
        dfs(1);
    }
};