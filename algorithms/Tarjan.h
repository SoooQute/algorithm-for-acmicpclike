#include "../stdafx.h"
using namespace std;
/*
�ܽ�������⣺

1.��ǿ��ͨ����

2.����

ʱ�临�Ӷ�O(n+m)�����⿴����

��ص����⻹�У�

1.��ͼ�ĸ��

2.��ͼ�ĵ���ͨ��

3.��ͼ�ı���ͨ��

�⼸�������������ٲ���

G��ԭͼ�������ʱ���������д��vector<vector<int>> G(10005, vector<int>());�����ֱ�ʾ��Ŀ����������
*/
class Tarjan {
public:
    int n;
    vector<int> dfn, low;
    vector<bool> inStack;
    vector<vector<int>> * G;
    int dep;
    stack<int> pStack;
    vector<vector<int>> Scc;
    vector<int> color;
    vector<pair<int, int>> bridge;
    vector<int> component;

    void init(vector<vector<int>> * G, int size);
    void dfs(int x);
    void runTarjan();
};
void Tarjan::init(vector<vector<int>> * Graph, int size) {
    if (size < 0) return;
    G = Graph, n = size;
    dfn.clear(), low.clear(), inStack.clear(), Scc.clear(), color.clear(), bridge.clear();
    dfn = vector<int>(n + 1, 0);
    low = vector<int>(n + 1, 0);
    inStack = vector<bool>(n + 1, false);
    color = vector<int>(n + 1, 0);
    dep = 0;
    while (!pStack.empty()) pStack.pop();
}
void Tarjan::dfs(int x) {
    if (x > n) return;
    inStack[x] = true;
    dfn[x] = low[x] = ++dep;
    pStack.push(x);
    for (int i = 0; i < (*G)[x].size(); i++) {
        int u = (*G)[x][i];
        if (dfn[u] == 0) {
            dfs(u);
            low[x] = min(low[x], low[u]);
            if (dfn[x] < low[u]) {
                bridge.push_back(make_pair(x, u));
            }
        } else {
            if (inStack[u]) low[x] = min(low[x], dfn[u]);
        }
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
void Tarjan::runTarjan() {
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) dfs(i);
    }
}