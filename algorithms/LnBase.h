#pragma once
#include "../stdafx.h"
using namespace std;
template <typename T> class LnBase {
public:
    int sz, szc;
    T *x;
    int *y;
    LnBase() {
        x = 0, sz = sizeof(T) << 3;
        szc = -1, resize(sz);
    }
    void resize(int size) {
        sz = size;
        if (!x) delete (x);
        x = new T[sz + 2];
        y = new int[sz + 2];
        memset(x, 0, sz * sizeof(T));
        memset(y, 0, sz << 2);
    }
    T operator[](int h) {
        return x[h];
    }
    //增加一个向量，若该向量能被已有向量线性表示，返回-1;否则返回该向量增加的是哪一个维度
    int add(T v) {
        for (int i = sz - 1; i >= 0; i--)
            if (v & (T)1 << i) {
                if (!x[i]) {
                    x[i] = v;
                    szc = -1;
                    return i;
                }
                v ^= x[i];
            }
        return -1;
    }
    //若该向量能被已有向量线性表示，返回1;否则返回0
    int find(T v) {
        for (int i = sz - 1; i >= 0; i--) {
            if (v & (T)1 << i && x[i]) v ^= x[i];
            if (!v) return 1;
        }
        return 0;
    }
    //线性基能表示出的最大向量
    T max() {
        T s = 0;
        for (int i = sz - 1; i >= 0; i--) {
            if ((s ^ x[i]) > s) s ^= x[i];
        }
        return s;
    }
    //线性基能表示出的最小向量，为空返回-1
    T min() {
        for (int i = 0; i < sz; i++) if (x[i]) return x[i];
        return -1;
    }
    void canonicity() {
        for (int i = sz - 1; i > 0; i--)
            for (int j = i - 1; j >= 0; j--) if (x[i] & (T)1 << j) x[i] ^= x[j];
        for (szc = i = 0; i < sz; i++) if (x[i]) y[szc++] = i;
    }
    //线性基能表示出的第k大的向量
    T kth(long long K) {
        if (szc < 0) canonicity();
        if (K >= 1ll << szc) return -1;
        T s = 0;
        for (int i = szc - 1; i >= 0; i--) if (K & 1ll << i) s ^= x[y[i]];
        return s;
    }
};