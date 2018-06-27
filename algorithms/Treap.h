#pragma once
#include "../stdafx.h"
using namespace std;
class Treap {
public:
    struct node {
        node* ch[2];
        int v, s, r, c;
        node(int v, node *t) : v(v) {
            ch[0] = ch[1] = t;
            r = rand();
            s = c = 1;
        }
        bool operator < (const node &rhs) const {
            return r < rhs.r;
        }
        void push_up() {
            s = ch[0]->s + ch[1]->s + c;
        }
    }*root, *null;
    Treap() {
        null = new node(0, 0);
        null->s = null->c = 0;
        null->r = -1;
        root = null;
    }
    void rotate(node* &o, bool d) {
        node* k = o->ch[!d];
        o->ch[!d] = k->ch[d];
        k->ch[d] = o;
        o->push_up();
        k->push_up();
        o = k;
    }
    void insert(node* &o, int x) {
        if (o == null) o = new node(x, null);
        else {
            if (o->v == x) {
                o->c++;
                o->s++;
            } else {
                bool d = x > o->v;
                insert(o->ch[d], x);
                if (o->ch[d] < o) rotate(o, !d);
                o->push_up();
            }
        }
    }
    void remove(node* &o, int x) {
        if (o->v == x) {
            if (o->c > 1) o->c--;
            else {
                if (o->ch[0] != null && o->ch[1] != null) {
                    bool d = o->ch[0] < o->ch[1];
                    rotate(o, d);
                    remove(o->ch[d], x);
                } else {
                    node* u = o;
                    if (o->ch[0] == null) o = o->ch[1];
                    else o = o->ch[0];
                    delete u;
                }
            }
        } else {
            bool d = x > o->v;
            if (o->ch[d] != null) remove(o->ch[d], x);
        }
        if (o != null) o->push_up();
    }
    int kth(node* o, int k) {
        int s = o->ch[0]->s + o->c;
        if (k > o->ch[0]->s && k <= s) return o->v;
        if (k <= o->ch[0]->s) return kth(o->ch[0], k);
        else return kth(o->ch[1], k - s);
    }
    int rank(node *o, int x) {
        int s = o->ch[0]->s + o->c;
        if (x == o->v) return o->ch[0]->s + 1;
        if (x < o->v) return (o->ch[0] == null) ? (1) : rank(o->ch[0], x);
        else return (o->ch[1] == null) ? (s + 1) : s + rank(o->ch[1], x);
    }
    int pre(int x) {
        node* t = root;
        int ret = 0;
        while (t != null) {
            if (t->v < x) {
                ret = t->v;
                t = t->ch[1];
            } else t = t->ch[0];
        }
        return ret;
    }
    int suc(int x) {
        node *t = root;
        int ret = 0;
        while (t != null) {
            if (t->v > x) {
                ret = t->v;
                t = t->ch[0];
            } else t = t->ch[1];
        }
        return ret;
    }
};