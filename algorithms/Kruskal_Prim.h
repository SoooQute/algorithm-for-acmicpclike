#pragma once
#include "../stdafx.h"
#include "UnionFindSet.h"
using namespace std;
/*
Kruskal_MAXN：最大点数
Kruskal_MAXM：最大边数
N：点数
void addEdge(int a, int b, int c)：添加一条ab之间长度为c的边
int MST()：最小生成树
*/
class Kruskal {
#define Kruskal_MAXN 100
#define Kruskal_MAXM 10005
public:
	UnionFindSet ufs;
    int x[Kruskal_MAXM], y[Kruskal_MAXM], w[Kruskal_MAXM], N, M;
    Kruskal() {
        N = 0;
        M = 0;
    }
    void clear() {
        N = 0;
        M = 0;
    }
    void addEdge(int a, int b, int c) {
        x[M] = a;
        y[M] = b;
        w[M] = c;
        M++;
        x[M] = b;
        y[M] = a;
        w[M] = c;
        M++;
    }
    void sort(int l, int r) {
        int i = l, j = r, m = w[(l + r) >> 1], t;
        do {
            while (w[i] < m) {
                i++;
            }
            while (m < w[j]) {
                j--;
            }
            if (i <= j) {
                t = x[i];
                x[i] = x[j];
                x[j] = t;
                t = y[i];
                y[i] = y[j];
                y[j] = t;
                t = w[i];
                w[i] = w[j];
                w[j] = t;
                i++;
                j--;
            }
        } while (i <= j);
        if (l < j) {
            sort(l, j);
        }
        if (i < r) {
            sort(i, r);
        }
    }
    int MST() {
        sort(0, M - 1);
        ufs.clear(N + 1);
        int cnt = 0, ret = 0;
        for (int i = 0; i < M; i++) {
            if (cnt == N - 1) {
                return ret;
            }
            if (ufs.getFather(x[i]) != ufs.getFather(y[i])) {
                ufs.merge(x[i], y[i]);
                ret += w[i];
                cnt++;
            }
        }
        if (cnt == N - 1) {
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