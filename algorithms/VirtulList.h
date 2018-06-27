#pragma once
#include "../stdafx.h"
using namespace std;
class VirtulList {
public:
    int data[100000], pre[100000], nex[100000], head, end, sz;
    bool exist[100000];
    VirtulList() {};
    void build(int * a, int n) {
        for (int i = 0; i < n; i++) data[i] = a[i];
        head = 0, end = -1, sz = n;
        for (int i = 1; i < n; i++) pre[i] = i - 1;
        for (int i = 0; i < n; i++) nex[i] = i + 1;
        nex[n - 1] = end;
        memset(exist, true, sizeof(exist));
    }
    void insert(int x, int w) {
        int l = x, r = nex[x];
        data[sz] = w;
        nex[l] = sz, pre[sz] = l, nex[sz] = r, pre[r] = sz;
        sz++;
    }
    void erase(int x) {
        if (x == end) return;
        if (x >= sz || !exist[x]) return;
        if (x == head) {
            head = nex[x];
        } else {
            int l = pre[x], r = nex[x];
            nex[l] = r, pre[r] = l;
        }
        exist[x] = false;
    }
    int next(int x) {
        return nex[x];
    }
};