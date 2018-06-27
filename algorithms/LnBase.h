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
    //����һ�����������������ܱ������������Ա�ʾ������-1;���򷵻ظ��������ӵ�����һ��ά��
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
    //���������ܱ������������Ա�ʾ������1;���򷵻�0
    int find(T v) {
        for (int i = sz - 1; i >= 0; i--) {
            if (v & (T)1 << i && x[i]) v ^= x[i];
            if (!v) return 1;
        }
        return 0;
    }
    //���Ի��ܱ�ʾ�����������
    T max() {
        T s = 0;
        for (int i = sz - 1; i >= 0; i--) {
            if ((s ^ x[i]) > s) s ^= x[i];
        }
        return s;
    }
    //���Ի��ܱ�ʾ������С������Ϊ�շ���-1
    T min() {
        for (int i = 0; i < sz; i++) if (x[i]) return x[i];
        return -1;
    }
    void canonicity() {
        for (int i = sz - 1; i > 0; i--)
            for (int j = i - 1; j >= 0; j--) if (x[i] & (T)1 << j) x[i] ^= x[j];
        for (szc = i = 0; i < sz; i++) if (x[i]) y[szc++] = i;
    }
    //���Ի��ܱ�ʾ���ĵ�k�������
    T kth(long long K) {
        if (szc < 0) canonicity();
        if (K >= 1ll << szc) return -1;
        T s = 0;
        for (int i = szc - 1; i >= 0; i--) if (K & 1ll << i) s ^= x[y[i]];
        return s;
    }
};