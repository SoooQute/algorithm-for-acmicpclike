#pragma once
#include "../stdafx.h"
using namespace std;
class UnionFindSet {
public:
    int setSize;
    vector<int> father;
    UnionFindSet() {}
    UnionFindSet(int x) {
        setSize = x;
        father = vector<int>(setSize, 0);
        clear();
    }
    void clear() {
        for (int i = 0; i < setSize; i++) {
            father[i] = i;
        }
    }
    void resetFather(vector<int> * v) {
        for (auto it : (*v)) {
            if (it >= setSize) continue;
            father[it] = it;
        }
    }
    int getFather(int x) {
        int ret = x, tmp;
        while (ret != father[ret]) {
            ret = father[ret];
        }
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
        return true;
    }
    int countRoot() {
        int ret = 0;
        for (int i = 0; i < setSize; i++) {
            if (father[i] = i) {
                ret++;
            }
        }
        return ret;
    }
};