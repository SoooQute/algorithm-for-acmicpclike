#pragma once
#include "stdafx.h"
using namespace std;
/*
dir��ʾ������ͼ��������ͼ
color��ʾ�õ������ĸ�ǿ��ͨ����
Scc��ʾǿ��ͨ��������ͼ������ͼʱ��Scc��ʾɾ��ͼ�е��ź󻮷ֳ��ĸ�������
bridge��ʾͼ�е���
cutvertex��ʾ��ͼ������ͼʱͼ�еĸ��
*/
class Tarjan {
public:
    int n, *color;
    bool *cutvertex, *root;
    vector<vector<int>> Scc;
    vector<vector<int>> dfsTree;
    vector<pair<int, int>> bridge;

    int *dfn, *low;
    bool *inStack;
    vector<int> *G;
    int dep;
    stack<int> pStack;
    vector<int> component;

    Tarjan() : n(0) {}
    void init(vector<int> *G, int size);
    void dfs(int x, int fa, bool dir);
    void run(bool dir);
    ~Tarjan() {
        delete[] dfn, delete[] low, delete[] inStack, delete[] color, delete[] cutvertex, delete[] root;
    }
};
void Tarjan::init(vector<int> *Graph, int size) {
    G = Graph;
    if (n < size) {
        n = size;
        delete[] dfn, delete[] low, delete[] inStack, delete[] color, delete[] cutvertex, delete[] root;
        dfn = new int[n + 1], low = new int[n + 1], inStack = new bool[n + 1], cutvertex = new bool[n + 1], root = new bool[n + 1], Scc.clear(), color = new int[n + 1], bridge.clear();
    }
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