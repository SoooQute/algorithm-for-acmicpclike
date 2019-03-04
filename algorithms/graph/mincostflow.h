#pragma once
#include "stdafx.h"
using namespace std;

class MinCostFlow {
public:
    vector<int> *G, *C, *W, *R;
    int sz, *pre, *pos, *dis;
    bool *vis;
    queue<int> que;
    MinCostFlow(int sz) : sz(sz), pre(new int[sz << 1]), pos(new int[sz << 1]), dis(new int[sz << 1]), vis(new bool[sz << 1]) {
        G = new vector<int>[sz << 1];
        C = new vector<int>[sz << 1];
        W = new vector<int>[sz << 1];
        R = new vector<int>[sz << 1];
    }
    void clear();
    void init(vector<int> *g, vector<int> *c, vector<int> *w, vector<int> *r);
    void addEdge(int u, int v, int capc, int cost);
    bool spfa(int s, int t);
    pair<int, int> run(int s, int t);
};
void MinCostFlow::clear() {
    delete[] G, delete[] C, delete[] W, delete[] R;
}
void MinCostFlow::init(vector<int> *g, vector<int> *c, vector<int> *w, vector<int> *r) {
    clear();
    G = g, C = c, W = w, R = r;
}
void MinCostFlow::addEdge(int u, int v, int capc, int cost) {
    G[u].push_back(v);
    C[u].push_back(capc);
    W[u].push_back(cost);
    G[v].push_back(u);
    C[v].push_back(0);
    W[v].push_back(-cost);
    R[u].push_back(G[v].size() - 1);
    R[v].push_back(G[u].size() - 1);
}

bool MinCostFlow::spfa(int s, int t) {
    memset(pre, -1, sizeof(int) * (sz << 1));
    memset(vis, false, sizeof(bool) * (sz << 1));
    memset(dis, 0x3F, sizeof(int) * (sz << 1));
    que.push(s), pre[s] = s, dis[s] = 0, vis[s] = 1;
    while (!que.empty()) {
        int now = que.front();
        que.pop();
        vis[now] = 0;
        for (int i = 0; i < G[now].size(); i++) {
            int adj = G[now][i];
            if (C[now][i] > 0 && dis[now] + W[now][i] < dis[adj]) {
                dis[adj] = dis[now] + W[now][i];
                pre[adj] = now;
                pos[adj] = i;
                if (!vis[adj]) {
                    vis[adj] = 1;
                    que.push(adj);
                }
            }
        }
    }
    return pre[t] != -1;
}
pair<int, int> MinCostFlow::run(int s, int t) {
    int cost = 0, flow = 0;
    while (spfa(s, t)) {
        int f = INT_MAX;
        for (int i = t; i != s; i = pre[i])
            if (C[pre[i]][pos[i]] < f) {
                f = C[pre[i]][pos[i]];
            }
        flow += f;
        cost += dis[t] * f;
        for (int i = t; i != s; i = pre[i]) {
            C[pre[i]][pos[i]] -= f;
            C[G[pre[i]][pos[i]]][R[pre[i]][pos[i]]] += f;
        }
    }
    return pair<int, int>(flow, cost);
}
