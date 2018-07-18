#pragma once
#include "stdafx.h"
#include "algorithms/graph/Tarjan.h"

class Two_SAT {
public:
    int size;

    Tarjan *ta;
    vector<int> *G, *iDAG;
    int n, *solve;

    int *d, *mark;
    vector<int> *ct;

    Two_SAT(Tarjan *iTa, int sz) : ta(iTa), n(0), size(sz) {
        G = new vector<int>[sz << 2];
        ct = new vector<int>[sz << 2];
        d = new int[sz << 2], mark = new int[sz << 2];
        iDAG = new vector<int>[sz << 2];
        solve = new int[sz << 2];
    };
    void init(int);
    inline void addEdge(int, int);
    /*
    0:u,v不能同时取
    1:u,v不能同时不取
    2:u,v要么都取，要么都不取
    */
    void addRestrict(int, int, int, int, int);
    /*
    0:u,u'必取u
    1:u,u'必取u'
    */
    void addRestrict(int, int);
    bool judge();
    void push(int);
    void build();
    ~Two_SAT() {
        delete[] G, delete ta, delete[] solve, delete[] d, delete[] mark, delete[] ct, delete[] iDAG;
    };
};
void Two_SAT::init(int iN) {
    n = iN;
    for (int i = 0; i <= 2 * n + 1; i++) G[i].clear(), ct[i].clear(), iDAG[i].clear();
}
inline void Two_SAT::addEdge(int u, int v) {
    G[u].push_back(v);
}
void Two_SAT::addRestrict(int type, int u, int au, int v, int av) {
    u = 2 * u + au, v = 2 * v + av;
    switch (type) {
        case 0: {
                addEdge(u, v ^ 1);
                addEdge(v, u ^ 1);
                break;
            }
        case 1: {
                addEdge(u ^ 1, v);
                addEdge(v ^ 1, u);
                break;
            }
        case 2: {
                addEdge(u, v);
                addEdge(v, u);
                addEdge(u ^ 1, v ^ 1);
                addEdge(v ^ 1, u ^ 1);
                break;
            }
        default: {
                return;
            }
    }
}
void Two_SAT::addRestrict(int type, int u) {
    if (type == 0) addEdge(u * 2 + 1, u * 2);
    else addEdge(u * 2, u * 2 + 1);
}
bool Two_SAT::judge() {
    ta->init(G, 2 * n + 1);
    ta->run(true);
    for (int i = 1; i <= n; i++) {
        int u = ta->color[2 * i] + 1, v = ta->color[2 * i + 1] + 1;
        if (u == v) return false;
        ct[u].push_back(v), ct[v].push_back(u);
    }
    return true;
}
void Two_SAT::push(int u) {
    mark[u] = -1;
    for (int i = 0; i < iDAG[u].size(); i++) {
        int v = iDAG[u][i];
        if (mark[v] != -1) push(v);
    }
}
void Two_SAT::build() {
    memset(d, 0, sizeof(int) * (2 * n + 2));
    memset(mark, 0, sizeof(int) * (2 * n + 2));
    ta->getDAG();
    int nDAG = ta->Scc.size();
    for (int i = 1; i <= nDAG; i++) {
        for (int j = 0; j < ta->DAG[i].size(); j++) {
            int u = i, v = G[i][j];
            iDAG[v].push_back(u);
            d[u]++;
        }
    }
    queue<int> q;
    for (int i = 1; i <= nDAG; i++) if (d[i] == 0) q.push(i);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < iDAG[u].size(); i++) {
            int v = G[u][i];
            d[v]--;
            if (d[v] == 0) q.push(v);
        }
        if (mark[u] == 0) {
            mark[u] = 1;
            for (int i = 0; i < ct[u].size(); i++) {
                int v = ct[u][i];
                if (mark[v] != -1) push(v);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (mark[ta->color[2 * i] + 1] == 1) solve[i] = 0;
        else solve[i] = 1;
    }
}
