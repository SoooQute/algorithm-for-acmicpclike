#pragma once
#include "../stdafx.h"
using namespace std;
class SplayNode {
public:
    SplayNode *child[2];
    char value;
    int size;
    bool flip;
    SplayNode(char c) : value(c), size(1), flip(false) {
        child[0] = child[1] = NULL;
    }
    int getPosition()const {
        return child[0] ? child[0]->size + 1 : 1;
    }
    void maintain() {
        size = 1;
        if (child[0]) {
            size += child[0]->size;
        }
        if (child[1]) {
            size += child[1]->size;
        }
    }
    void pushDown() {
        if (flip) {
            swap(child[0], child[1]);
            for (int i = 0; i < 2; i++) {
                if (child[i]) {
                    child[i]->flip ^= 1;
                }
            }
            flip = false;
        }
    }
};
class SplayTree {
public:
    SplayNode *root;
    SplayTree(char *a, int n);
    void build(SplayNode *&node, char *begin, char *end);
    void rotate(SplayNode *&node, int direction);
    void splay(SplayNode *&node, int position);
    void reverse(int begin, int end);
    void traverse(SplayNode *u);
    void traverse();
};
SplayTree::SplayTree(char *a, int n) {
    build(root, a, a + n - 1);
}
void SplayTree::build(SplayNode *&node, char *begin, char *end) {
    if (begin > end) {
        return;
    }
    char *middle = begin + (end - begin >> 1);
    node = new SplayNode(*middle);
    build(node->child[0], begin, middle - 1);
    build(node->child[1], middle + 1, end);
    node->maintain();
}

void SplayTree::rotate(SplayNode *&node, int direction) {
    SplayNode *child = node->child[direction ^ 1];
    node->child[direction ^ 1] = child->child[direction];
    child->child[direction] = node;
    node->maintain();
    child->maintain();
    node = child;
}
void SplayTree::splay(SplayNode *&node, int position) {
    node->pushDown();
    if (node->getPosition() != position) {
        int d = node->getPosition() < position;
        SplayNode *node2 = node->child[d];
        position -= d ? node->getPosition() : 0;
        node2->pushDown();
        if (node2->getPosition() != position) {
            int d2 = node2->getPosition() < position;
            position -= d2 ? node2->getPosition() : 0;
            splay(node2->child[d2], position);
            if (d == d2) {
                rotate(node, d ^ 1);
            } else {
                rotate(node->child[d], d);
            }
        }
        rotate(node, d ^ 1);
    }
}
void SplayTree::reverse(int begin, int end) {
    splay(root, begin);
    splay(root->child[1], end - begin + 2);
    root->child[1]->child[0]->flip ^= 1;
}
void SplayTree::traverse(SplayNode *u) {
    if (!u) {
        return;
    }
    u->pushDown();
    traverse(u->child[0]);
    if (u->value) {
        printf("%c", u->value);
    }
    traverse(u->child[1]);
}
void SplayTree::traverse() {
    traverse(root);
}