#pragma once
#include "stdafx.h"
using namespace std;
template<_Ty> class VirtulListNode {
    _Ty data;
    int pre, nex, id;
    VirtulListNode *list;
    VirtulListNode() {};
    void set(_Ty _data, int _pre, int _nex, int _id, VirtulListNode *_list) {
        data = _data, pre = _pre, nex = _nex, id = _id, list = _list;
    }
};
template<_Ty> class VirtulList {
public:
    VirtulListNode *list;
    int head, end, sz;
    bool *exist;
    VirtulList(int iN): sz(iN) {
        list = new VirtulListNode[iN << 1], exist = new int[iN << 1];
    };
    void build(_Ty * a, int n) {
        for (int i = 0; i < n; i++) list[i].data = a[i];
        head = 0, end = -1, sz = n;
        for (int i = 1; i < n; i++) list[i].pre = i - 1;
        list[0].pre = -1;
        for (int i = 0; i < n; i++) list[i].nex = i + 1;
        nex[n - 1] = end;
        memset(exist, true, sizeof(exist));
    }
    _Ty & operator [](int x) {
        return list[i].data;
    }
    _Ty operator [] = (int x, _Ty &y) {
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
    ~VirtulList() {
        delete[] list, delete[] exist;
    }
};