#pragma once
#include "../stdafx.h"
using namespace std;
class Trie {
#define Trie_MAX_Letter_Num 26
public:
    Trie * next[Trie_MAX_Letter_Num];
    Trie * father;
    int cnt, mark;
    Trie() {
        cnt = 26;
        memset(next, NULL, sizeof(next));
        father = NULL;
        mark = 0;
    }
    void reset() {
        for (int i = 0; i < cnt; i++) {
            if (next[i] != NULL) {
                next[i]->reset();
            }
            delete next[i];
        }
        mark = false;
    }
    void Insert(char * ptr) {
        Trie * root = this;
        while (*ptr != '\0') {
            if (root->next[(*ptr) - 'a'] == NULL) {
                root->next[(*ptr) - 'a'] = new Trie;
                (root->next[(*ptr) - 'a'])->father = root;
            }
            root = (root->next[(*ptr) - 'a']);
            ptr++;
        }
        root->mark++;
    }
    bool Delete(char * ptr) {
        Trie * root = this;
        while (*ptr != '\0') {
            if (root->next[(*ptr) - 'a'] == NULL) {
                return false;
            }
            root = (root->next[(*ptr) - 'a']);
            ptr++;
        }
        root->mark--;
        return true;
    }
    Trie * Search(char * ptr) {
        Trie * root = this;
        while (*ptr != '\0') {
            if (root->next[(*ptr) - 'a'] == NULL) {
                return NULL;
            }
            root = (root->next[(*ptr) - 'a']);
            ptr++;
        }
        return root;
    }
};