#pragma once
#include"stdafx.h";
using namespace std;
template<typename T>class TreeArray {
public:
    int sz, *sum, *data;
    TreeArray(int n) {
        sz = n;
        sum = new T[sz + 5], data = new T[sz + 5];
        memset(sum, 0, sizeof(T) * (n + 5));
        memset(data, 0, sizeof(T) * (n + 5));
    }
    ~TreeArray() {
        delete[] sum, delete[] data;
    }
    void add(int x, T y) {
        for (int i = x; i <= sz; i += i & (-i)) {
            sum[i] += y;
        }
    }
    T query(int x) {
        T ret = 0;
        for (int i = x; i; i -= i & (-i)) {
            ret += sum[i];
        }
        return ret;
    }
};
