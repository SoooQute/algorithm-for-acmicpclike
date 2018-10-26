template <typename T> class SegmentTree {
public:
    T merge(T a, T b) {
        /*how to merge the answer when queried*/
        //-----sum-----
        return a + b;
        //-------------
        //
        //---------max---------
        //return a < b ? b : a;
        //---------------------
        //
        //---------min---------
        //return a < b ? a : b;
        //---------------------
    }
    T *data, *lazy;
    int ll, rr;
    inline void pushup(int rt) {
        /*how to merge the data on sub-nodes*/
        //-----------------------sum-----------------------
        data[rt] = data[rt << 1] + data[((rt << 1) | 1)];
        //-------------------------------------------------
        //
        //-----------------------max---------------------------
        //data[rt] = max(data[rt << 1], data[((rt << 1) | 1)]);
        //-----------------------------------------------------
        //
        //-----------------------min---------------------------
        //data[rt] = min(data[rt << 1], data[((rt << 1) | 1)]);
        //-----------------------------------------------------
    }
    inline void addLazy(int rt, int m, T v) {
        /*
        * how to merge the newly added lazy mark with the existing one
        * lazy mark mean the update has been implemented on the very current node but not on its sub-node yet
        * m is the length of the segment
        */
        //-----------straight add-----------
        lazy[rt] += v;
        //----------------------------------
        //#####################################################
        //sub-nodes' data
        //-------------------sum-------------------
        data[rt] += v * m;
        //-----------------------------------------
        //
        //-----------------max/min-----------------
        //data[rt] += v;
        //-----------------------------------------
    }
    inline void pushdown(int rt, int m) {
        if(lazy[rt] == 0) return;
        addLazy(rt << 1, m - (m >> 1), lazy[rt]);
        addLazy((rt << 1) | 1, (m >> 1), lazy[rt]);
        lazy[rt] = (T)(0);
    }
    void build(T * base, int l, int r, int rt) {
        lazy[rt] = 0;
        if(l == r) data[rt] = base[l];
        else {
            int mid = (l + r) >> 1;
            build(base, l, mid, rt << 1);
            build(base, mid + 1, r, ((rt << 1) | 1));
            pushup(rt);
        }
    }
    void modify(int l, int r, int rt, int L, int R, T v) {
        if(L <= l && r <= R) {
            addLazy(rt, r - l + 1, v);
            return;
        }
        pushdown(rt, r - l + 1);
        int mid = (l + r) >> 1;
        if(L <= mid) modify(l, mid, rt << 1, L, R, v);
        if(R > mid) modify(mid + 1, r, ((rt << 1) | 1), L, R, v);
        pushup(rt);
    }
    T query(int l, int r, int rt, int val) {
        if(l == r) return data[rt];
        pushdown(rt, r - l + 1);
        int mid = (l + r) >> 1;
        T ret = 0;
        if(val <= mid) ret = query(l, mid, rt << 1, val);
        else ret = query(mid + 1, r, ((rt << 1) | 1), val);
        pushup(rt);
        return ret;
    }
    T query(int l, int r, int rt, int L, int R) {
        pushdown(rt, r - l + 1);
        if(L == l && R == r) return data[rt];
        int mid = (l + r) >> 1;
        if(R <= mid) return query(l, mid, rt << 1, L, R);
        if(mid < L) return query(mid + 1, r, ((rt << 1) | 1), L, R);
        return merge(query(l, mid, rt << 1, L, mid), query(mid + 1, r, ((rt << 1) | 1), mid + 1, R));
    }
    SegmentTree(int n) : data(new T[n << 3]), lazy(new T[n << 3]) {}
    void build(T *base, int l, int r) {
        ll = l, rr = r;
        build(base, ll, rr, 1);
    }
    void modify(int l, int r, T v) {
        if(l > r || l < ll || rr < r) return;
        modify(ll, rr, 1, l, r, v);
    }
    void modify(int p, T v) {
        if(p < ll || rr < p) return;
        modify(ll, rr, 1, p, p, v);
    }
    T query(int l, int r) {
        if(l > r || l < ll || rr < r) return (T)(0);
        return query(ll, rr, 1, l, r);
    }
    T query(int p) {
        if(p < ll || rr < p) return (T)(0);
        return query(ll, rr, 1, p);
    }
    ~SegmentTree() {
        delete[] data, delete[] lazy;
    }
};