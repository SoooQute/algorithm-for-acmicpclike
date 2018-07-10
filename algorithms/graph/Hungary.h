#pragma once
#include "stdafx.h"
using namespace std;
/*
N���������
M���ߵ�����
void clear()��������ݽṹ
void addEdge(int a, int b)�����һ��aָ��b��ƥ��
int Max_Match()�����ƥ��
*/
class Hungary {
#define Hungary_MAX_Node 105
#define Hungary_MAX_Edge 10005
public:
    struct EDGE {
        int v;
        int next;
    } edge[Hungary_MAX_Edge];
    int head[Hungary_MAX_Node];
    int Left[Hungary_MAX_Node];
    bool vis[Hungary_MAX_Node];
    int N, M;
    Hungary() {
        clear();
    }
    void clear() {
        N = M = 0;
        memset(Left, 0, sizeof(Left));
        memset(head, -1, sizeof(head));
    }
    void addEdge(int a, int b) {
        edge[M].v = b;
        edge[M].next = head[a];
        head[a] = M++;
    }
    bool dfs(int u) {
        for (int e = head[u]; e != -1; e = edge[e].next) {
            int v = edge[e].v;
            if (!vis[v]) {
                vis[v] = true;
                if (!Left[v] || dfs(Left[v])) {
                    Left[v] = u;
                    return true;
                }
            }
        }
        return false;
    }
    int Max_Match() {
        int ret = 0;
        for (int i = 1; i <= N; i++) {
            memset(vis, 0, sizeof(vis));
            if (dfs(i)) {
                ret++;
            }
        }
        return ret;
    }
};