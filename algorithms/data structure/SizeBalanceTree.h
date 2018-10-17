#pragma once
#include "stdafx.h"
using namespace std;
template<typename Ty> class SizeBalanceTreeNode {
public:
    Ty key;
    int size, son[2];
};
template<typename Ty> class SizeBalanceTree {
public:
    SizeBalanceTreeNode<Ty> *T;
    pair<Ty, Ty> inf;
    int cnt, rt, sz;
    SizeBalanceTree(int n, pair<Ty, Ty> inf) : cnt(0), rt(0), sz(n), inf(inf) {
        T = new SizeBalanceTreeNode<Ty>[n];
        memset(T, 0, sizeof(SizeBalanceTreeNode<Ty>) * n);
    }
	~SizeBalanceTree() { delete[] T; }
    void clear() {
        cnt = rt = 0;
        memset(T, 0, sizeof(SizeBalanceTreeNode<Ty>) * sz);
    }
	inline void pushUp(int x) { T[x].size = T[T[x].son[0]].size + T[T[x].son[1]].size + 1; }
    inline int newNode(Ty);
    void rotate(int, int&);
    void maintain(int&, int);
    //the previous/next node's id of the node whose id is x
    inline int prev(int);
    inline int succ(int);

    void insert(Ty, int&);
	void insert(Ty key) { insert(key, rt); }
    bool erase(Ty, int&);
	bool erase(Ty key) { return erase(key, rt); }
    
    Ty kth(int, int);
	//the value of k th node in ascending order
	Ty kth(int k) { return T[kth(k, rt)].key; }
    int rank(Ty, int);
	//the number of nodes whose value is strickly smaller than key
	int rank(Ty key) { return rank(key, rt); }
    int count(Ty, int);
    //the number of nodes whose value is key
	int count(Ty key) { return count(key, rt); }
    Ty lower_bound(Ty, int&);
    Ty upper_bound(Ty, int&);
    //the largest node's value whose value is strictly less than key
	Ty lower_bound(Ty key) { return lower_bound(key, rt); }
    //the smallest node's value whose value is strictly more than key
	Ty upper_bound(Ty key) { return upper_bound(key, rt); }
    int find(Ty, int);
    //the id of a node whose value is key
	int find(Ty key) { return find(key, rt); }
    void traverse(int);
    //output all
	void traverse() { traverse(rt); cout << endl; }
};
template<typename Ty> inline int SizeBalanceTree<Ty>::newNode(Ty key) {
    ++cnt;
    T[cnt].key = key;
    T[cnt].size = 1;
    T[cnt].son[0] = T[cnt].son[1] = 0;
    return cnt;
}
template<typename Ty> void SizeBalanceTree<Ty>::rotate(int p, int &x) {
    int y = T[x].son[!p];
    T[x].son[!p] = T[y].son[p];
    T[y].son[p] = x;
    pushUp(x);
    pushUp(y);
    x = y;
}
template<typename Ty> void SizeBalanceTree<Ty>::maintain(int &x, int p) {
    if(T[T[T[x].son[p]].son[p]].size > T[T[x].son[!p]].size) rotate(!p, x);
    else if(T[T[T[x].son[p]].son[!p]].size > T[T[x].son[!p]].size) rotate(p, T[x].son[p]), rotate(!p, x);
    else return;
    maintain(T[x].son[0], 0);
    maintain(T[x].son[1], 1);
    maintain(x, 0);
    maintain(x, 1);
}
template<typename Ty> inline int SizeBalanceTree<Ty>::prev(int r) {
    int x = T[r].son[0];
    if(!x) return 0;
    while(T[x].son[1]) x = T[x].son[1];
    return x;
}
template<typename Ty> inline int SizeBalanceTree<Ty>::succ(int r) {
    int x = T[r].son[1];
    if(!x) return 0;
    while(T[x].son[0]) x = T[x].son[0];
    return x;
}
template<typename Ty> void SizeBalanceTree<Ty>::insert(Ty key, int &x) {
    if(!x) x = newNode(key);
    else {
        T[x].size++;
        insert(key, T[x].son[key > T[x].key]);
        maintain(x, key > T[x].key);
    }
}
template<typename Ty> bool SizeBalanceTree<Ty>::erase(Ty key, int &x) {
    if(!x) return 0;
    if(T[x].key == key) {
        if(!T[x].son[0]) {
            x = T[x].son[1];
            return 1;
        }
        if(!T[x].son[1]) {
            x = T[x].son[0];
            return 1;
        }
        int y = prev(x);
        swap(T[x].key, T[y].key);
        T[x].size--;
        return erase(T[y].key, T[x].son[0]);
    } else if(erase(key, T[x].son[key > T[x].key])) {
        T[x].size--;
        return 1;
    }
}
template<typename Ty> int SizeBalanceTree<Ty>::rank(Ty key, int x) {
    if(!x) return 0;
    if(T[x].key < key) return T[T[x].son[0]].size + 1 + rank(key, T[x].son[1]);
    else return rank(key, T[x].son[0]);
}
template<typename Ty> Ty SizeBalanceTree<Ty>::kth(int k, int x) {
    if(!x) return 0;
    if(k == T[T[x].son[0]].size + 1) return x;
    if(k > T[T[x].son[0]].size + 1) return kth(k - T[T[x].son[0]].size - 1, T[x].son[1]);
    else return kth(k, T[x].son[0]);
}
template<typename Ty> Ty SizeBalanceTree<Ty>::count(Ty key, int x) {
    if(!x) return 0;
    int ans = (key == T[x].key);
    if(key <= T[x].key) ans += count(key, T[x].son[0]);
    if(T[x].key <= key) ans += count(key, T[x].son[1]);
    return ans;
}
template<typename Ty> Ty SizeBalanceTree<Ty>::lower_bound(Ty key, int &x) {
    if(!x) return inf.first;
    if(key <= T[x].key) return lower_bound(key, T[x].son[0]);
    return max(T[x].key, lower_bound(key, T[x].son[1]));
}
template<typename Ty> Ty SizeBalanceTree<Ty>::upper_bound(Ty key, int &x) {
    if(!x) return inf.second;
    if(key >= T[x].key) return upper_bound(key, T[x].son[1]);
    return min(T[x].key, upper_bound(key, T[x].son[0]));
}
template<typename Ty> int SizeBalanceTree<Ty>::find(Ty key, int x) {
    if(!x) return 0;
    if(T[x].key == key) return x;
    else return find(key, T[x].son[key > T[x].key]);
}
template<typename Ty> void SizeBalanceTree<Ty>::traverse(int x) {
    if(!x) return;
    traverse(T[x].son[0]);
    cout << T[x].key << ' ';
    traverse(T[x].son[1]);
}