#pragma once
#include "stdafx.h"
using namespace std;
class DisjointSetUnion {
public:
    int n, *father, root;
    DisjointSetUnion(int sz): n(sz) {
        father = new int[sz << 1];
    }
    void init(int x) {
        n = x;
        clear();
    }
    void clear() {
        for (int i = 0; i <= n; i++) father[i] = i;
        root = n;
    }
    int getFather(int x) {
        int ret = x, tmp;
        while (ret != father[ret]) ret = father[ret];
        while (x != father[x]) {
            tmp = father[x];
            father[x] = ret;
            x = tmp;
        }
        return ret;
    }
    bool merge(int a, int b) {
        a = getFather(a);
        b = getFather(b);
        if (a == b) return false;
        father[a] = b;
        root--;
        return true;
    }
    ~DisjointSetUnion() {
        delete[] father;
    }
};