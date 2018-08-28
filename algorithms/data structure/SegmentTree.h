#pragma once
#include "stdafx.h"
using namespace std;
template <typename T> class SegmentTree {
    /*
    type:
    0:sum
    1:max
    2:min
    */
private:
    T *data, *lazy;
    int type, ll, rr;
    inline void pushup(int rt) {
        if (type == 0) data[rt] = data[rt << 1] + data[((rt << 1) | 1)];
        else if (type == 1) data[rt] = max(data[rt << 1], data[((rt << 1) | 1)]);
        else if (type == 2) data[rt] = min(data[rt << 1], data[((rt << 1) | 1)]);
    }
    inline void pushdown(int rt, T m) {
        if (lazy[rt] == 0) return;
        lazy[rt << 1] += lazy[rt];
        lazy[((rt << 1) | 1)] += lazy[rt];
        if (type == 0) {
            data[rt << 1] += (m - (m >> 1)) * lazy[rt];
            data[((rt << 1) | 1)] += (m >> 1) * lazy[rt];
        } else if (type == 1) {
            data[rt << 1] += lazy[rt];
            data[((rt << 1) | 1)] += lazy[rt];
        } else if (type == 2) {
            data[rt << 1] += lazy[rt];
            data[((rt << 1) | 1)] += lazy[rt];
        }
        lazy[rt] = 0;
    }
    void build_(T * base, int l, int r, int rt) {
        lazy[rt] = 0;
        if (l == r) data[rt] = base[l];
        else {
            int mid = (l + r) >> 1;
            build_(base, l, mid, rt << 1);
            build_(base, mid + 1, r, ((rt << 1) | 1));
            pushup(rt);
        }
    }
    void modify_(int l, int r, int rt, int L, int R, T v) {
        if (L <= l && r <= R) {
            lazy[rt] += v;
            if (type == 0) data[rt] += v * (r - l + 1);
            else if (type == 1) data[rt] += v;
            else if (type == 2) data[rt] += v;
            return;
        }
        pushdown(rt, r - l + 1);
        int mid = (l + r) >> 1;
        if (L <= mid) modify_(l, mid, rt << 1, L, R, v);
        if (R > mid) modify_(mid + 1, r, ((rt << 1) | 1), L, R, v);
        pushup(rt);
    }
    T query_(int l, int r, int rt, int val) {
        if (l == r) return data[rt];
        pushdown(rt, r - l + 1);
        int mid = (l + r) >> 1;
        T ret = 0;
        if (val <= mid) ret = query_(l, mid, rt << 1, val);
        else ret = query_(mid + 1, r, ((rt << 1) | 1), val);
        pushup(rt);
        return ret;
    }
    T query_(int l, int r, int rt, int L, int R) {
        pushdown(rt, r - l + 1);
        if (L == l && R == r) return data[rt];
        int mid = (l + r) >> 1;
        if (R <= mid) return query_(l, mid, rt << 1, L, R);
        if (mid < L) return query_(mid + 1, r, ((rt << 1) | 1), L, R);
        if (type == 0) return query_(l, mid, rt << 1, L, mid) + query_(mid + 1, r, ((rt << 1) | 1), mid + 1, R);
        else if (type == 1) return max(query_(l, mid, rt << 1, L, mid), query_(mid + 1, r, ((rt << 1) | 1), mid + 1, R));
        else if (type == 2) return min(query_(l, mid, rt << 1, L, mid), query_(mid + 1, r, ((rt << 1) | 1), mid + 1, R));
    }
public:
    SegmentTree(int n, int t) : data(new T[n << 3]), lazy(new T[n << 3]), type(t) {}
    void build(T* base, int l, int r) {
        ll = l, rr = r;
        build_(base, ll, rr, 1);
    }
    void modify(int l, int r, int v) {
        if (l > r || l < ll || rr < r) return;
        modify_(ll, rr, 1, l, r, v);
    }
    void modify(int p, int v) {
        if (p < ll || rr < p) return;
        modify_(ll, rr, 1, p, p, v);
    }
    T query(int l, int r) {
        if (l > r || l < ll || rr < r) return (T)(-1);
        return query_(ll, rr, 1, l, r);
    }
    T query(int p) {
        if (p < ll || rr < p) return (T)(-1);
        return query(ll, rr, 1, p);
    }
    ~SegmentTree() {
        delete[] data, delete[] lazy;
    }
};