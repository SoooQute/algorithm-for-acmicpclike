#pragma once
#include "stdafx.h"
#include "algorithms/data structure/DisjointSetUnion.h"
using namespace std;

struct KruskalEdge {
    int u, v, w;
    KruskalEdge(int x, int y, int z): u(x), v(y), w(z) {}
    bool operator <(const KruskalEdge & e) {
        return w < e.w;
    }
};
class Kruskal {
public:
    DisjointSetUnion *dsu;
    vector<KruskalEdge> edge;
    vector<bool> solution;
    int n;
    Kruskal(DisjointSetUnion *d): dsu(d) {}
    void init(int iN) {
        n = iN;
    }
    void addEdge(int a, int b, int c) {
        edge.push_back(KruskalEdge(a, b, c));
    }
    int MST() {
        sort(edge.begin(), edge.end());
        dsu->clear();
        solution.resize(edge.size());
        int cnt = 0, ret = 0;
        for (int i = 0; i < edge.size(); i++) {
            auto e = edge[i];
            if (cnt == n - 1) {
                return ret;
            }
            if (dsu->getFather(e.u) != dsu->getFather(e.v)) {
                dsu->merge(e.u, e.v);
                ret += e.w;
                solution[i] = true;
                cnt++;
            } else solution[i] = false;
        }
        if (cnt == n - 1) {
            return ret;
        } else {
            return -1;
        }
    }
};

/*
Prim_MAXN：最大点数
Prim_MAXN：最大边数
N：点数
void addEdge(int a, int b, int c)：添加一条ab之间长度为c的边
int MST()：最小生成树
*/
class Prim {
#define Prim_MAXN 505
#define Prim_MAXM 100005
public:
    int N, M;
    int head[Prim_MAXN], dis[Prim_MAXN];
    bool vis[Prim_MAXN];
    struct EDGE {
        int v, d, nex;
    } edge[Prim_MAXM];
    Prim() {
        clear();
    }
    void clear() {
        N = M = 0;
        memset(head, -1, sizeof(head));
    }
    void addEdge(int a, int b, int c) {
        edge[M].v = b;
        edge[M].d = c;
        edge[M].nex = head[a];
        head[a] = M++;
        edge[M].v = a;
        edge[M].d = c;
        edge[M].nex = head[b];
        head[b] = M++;
    }
    int MST() {
        int ret = 0, last, next, min;
        for (int i = 1; i <= N; i++) {
            dis[i] = 0x7FFFFFFF;
        }
        memset(vis, false, sizeof(vis));
        vis[1] = true;
        last = 1;
        for (int i = 1; i < N; i++) {
            for (int e = head[last]; e != -1; e = edge[e].nex) {
                if (dis[edge[e].v] > edge[e].d) {
                    dis[edge[e].v] = edge[e].d;
                }
            }
            min = 0x7FFFFFFF;
            for (int j = 1; j <= N; j++) {
                if (dis[j] < min && !vis[j]) {
                    min = dis[j];
                    next = j;
                }
            }
            if (min == 0x7FFFFFFF) {
                return -1;
            }
            vis[next] = true;
            ret += dis[next];
            last = next;
        }
        return ret;
    }
};