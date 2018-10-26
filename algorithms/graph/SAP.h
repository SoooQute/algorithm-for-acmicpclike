#pragma once
#include "stdafx.h";
using namespace std;
class SAP {
private:
	struct Edge { int from, to, next, cap; } *edge;
    int n, tol, *head, *dep, *gap, *cur, *S, *que;
    void addedge(int u, int v, int w) {
        edge[tol].from = u, edge[tol].to = v, edge[tol].cap = w, edge[tol].next = head[u];
        head[u] = tol++;
        edge[tol].from = v, edge[tol].to = u, edge[tol].cap = 0, edge[tol].next = head[v];
        head[v] = tol++;
    }
    void bfs(int start, int end) {
        memset(dep, -1, sizeof(int) * (n + 1));
        memset(gap, 0, sizeof(int) * (n + 1));
        gap[0] = 1;
        int front = 0, rear = 0;
        dep[end] = 0, que[rear++] = end;
        while(front != rear) {
            int u = que[front++];
            for(int i = head[u]; i != -1; i = edge[i].next) {
                int v = edge[i].to;
                if(dep[v] != -1) continue;
                que[rear++] = v;
                dep[v] = dep[u] + 1;
                ++gap[dep[v]];
            }
        }
    }
public:
    SAP(int maxn, int maxm) : edge(new Edge[maxm << 1]), head(new int[maxn]), dep(new int[maxn]), gap(new int[maxn]), cur(new int[maxn]), S(new int[maxn]), que(new int[maxn]) {}
    void init(vector<int> *G, vector<int> *W, int sz) {
        n = sz, tol = 0;
        memset(head, -1, sizeof(int) * (n + 1));
        for(int i = 1; i <= n; i++) {
            for(int j = 0; j < G[i].size(); j++) {
                addedge(i, G[i][j], W[i][j]);
            }
        }
    }
    int run(int start, int end) {
        int res = 0, top = 0, u = start, i;
        bfs(start, end);
        memcpy(cur, head, sizeof(int) * (n + 1));
        while(dep[start] < n) {
            if(u == end) {
                int temp = INT_MAX, inser;
                for(i = 0; i < top; i++) if(temp > edge[S[i]].cap) temp = edge[S[i]].cap, inser = i;
                for(i = 0; i < top; i++) edge[S[i]].cap -= temp, edge[S[i] ^ 1].cap += temp;
                res += temp, top = inser, u = edge[S[top]].from;
            }
            if(u != end && gap[dep[u] - 1] == 0) break;
            for(i = cur[u]; i != -1; i = edge[i].next) if(edge[i].cap != 0 && dep[u] == dep[edge[i].to] + 1) break;
            if(i != -1) cur[u] = i, S[top++] = i, u = edge[i].to;
            else {
                int mn = n;
                for(i = head[u]; i != -1; i = edge[i].next) {
                    if(edge[i].cap == 0) continue;
                    if(mn > dep[edge[i].to]) mn = dep[edge[i].to], cur[u] = i;
                }
                --gap[dep[u]];
                dep[u] = mn + 1;
                ++gap[dep[u]];
                if(u != start) u = edge[S[--top]].from;
            }
        }
        return res;
    }
};