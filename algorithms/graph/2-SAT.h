#pragma once
#include "stdafx.h"
#include "algorithms/graph/Tarjan.h"

class Two_SAT {
public:
    Tarjan *ta;
	//G:����Լ�����������ͼ iDAG:ͼG��ǿ��ͨ���������ѱ�ȫ������õ���ͼ
    vector<int> *G, *iDAG;
	//solve�ǹ������ѡ�񷽰�
    int n, *solve;
	// d:iDAG�Ķ�,������������ mark:ǿ��ͨ�����Ƿ�ѡ��(-1:��ѡ 1:ѡ 0:��ȷ��)
    int *d, *mark;
	//ct[i]��ʾ������ǿ��ͨ����iͬʱѡ���ǿ��ͨ�����б�(ע������ta->color��ֵ��1)
    vector<int> *ct;

    Two_SAT() : ta(new Tarjan), n(0) {};
    void init(int);
    inline void addEdge(int, int);
    /*
    0:u,v����ͬʱȡ
    1:u,v����ͬʱ��ȡ
    2:u,vҪô��ȡ��Ҫô����ȡ
    */
    void addRestrict(int, int, int);
    /*
    0:u,u'��ȡu
    1:u,u'��ȡu'
    */
    void addRestrict(int, int);
	//�ж��Ƿ��н�
    bool judge();
	//���ݲ�ѡ����
    void push(int);
	//����һ���
    void build();
    ~Two_SAT() {
        delete[] G, delete ta, delete[] solve, delete[] d, delete[] mark, delete[] ct;
    };
};
void Two_SAT::init(int iN) {
    if (n < iN) {
        delete[] G, delete[] ct, delete[] d;
        G = new vector<int>[iN << 2];
        ct = new vector<int>[iN << 2];
        d = new int[iN << 2], mark = new int[iN << 2];
    } else for (int i = 0; i <= iN * 2 + 1; i++) G[i].clear(), ct[i].clear();
    n = iN;
}
inline void Two_SAT::addEdge(int u, int v) {
    G[u].push_back(v);
}
void Two_SAT::addRestrict(int type, int u, int v) {
    switch (type) {
        case 0: {
                addEdge(u * 2, v * 2 + 1);
                addEdge(v * 2, u * 2 + 1);
                break;
            }
        case 1: {
                addEdge(u * 2 + 1, v * 2);
                addEdge(v * 2 + 1, u * 2);
                break;
            }
        case 2: {
                addEdge(u * 2, v * 2);
                addEdge(v * 2, u * 2);
                addEdge(u * 2 + 1, v * 2 + 1);
                addEdge(v * 2 + 1, u * 2 + 1);
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
    if (solve != NULL) delete[] solve;
    solve = new int[n << 1];
    memset(d, 0, sizeof(d));
    memset(mark, 0, sizeof(mark));
    if (iDAG != NULL) delete[] iDAG;
    iDAG = new vector<int>[4 * n + 2];
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