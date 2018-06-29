#pragma once
#include "../stdafx.h"
using namespace std;
/*
Ī���㷨�ǰ�һ����˳����б���������˳����Ƶ�ʮ������
*/
struct MoTaoQuery {
    int bid, id, l, r;
    MoTaoQuery() {}
    MoTaoQuery(int a, int b) : l(a), r(b) {}
    bool operator <(const MoTaoQuery & q)const {
        if (bid != q.bid) return bid < q.bid;
        return bid & 1 ? r < q.r : r>q.r;
    }
};
class MoTao {
public:
    MoTaoQuery *query;
    int n;
    function<void(MoTaoQuery &, MoTaoQuery)> transform = [](MoTaoQuery & qa, MoTaoQuery qb)->void {
        /*
		С�ĳ���...�ⲻ������д��
		�����Լ�д��δ�һ����֪�𰸵�����ת�Ƶ���һ�����䣬ʾ�����£���ʾ�������ڳ��ִ���Ϊ1������
        while (qa.r < qb.r) {
            qa.r++;
            c[a[qa.r]]++;
            if (c[a[qa.r]] == 1 && !in[a[qa.r]]) s[sn++] = a[qa.r], in[a[qa.r]] = true;
        }
        while (qa.l > qb.l) {
            qa.l--;
            c[a[qa.l]]++;
            if (c[a[qa.l]] == 1 && !in[a[qa.l]]) s[sn++] = a[qa.l], in[a[qa.l]] = true;
        }
        while (qa.r > qb.r) {
            c[a[qa.r]]--;
            if (c[a[qa.r]] == 1 && !in[a[qa.r]]) s[sn++] = a[qa.r], in[a[qa.r]] = true;
            qa.r--;
        }
        while (qa.l < qb.l) {
            c[a[qa.l]]--;
            if (c[a[qa.l]] == 1 && !in[a[qa.l]]) s[sn++] = a[qa.l], in[a[qa.l]] = true;
            qa.l++;
        }
        while (sn > 0) {
            int x = s[sn - 1];
            if (c[x] != 1) in[x] = false, sn--;
            else break;
        }
        if (sn > 0) ans[qb.id] = s[sn - 1];
        */
    };

    MoTao() : n(0) {}
    void init(MoTaoQuery*, int);
    void run();
};
void MoTao::init(MoTaoQuery *q, int sz) {
    query = q, n = sz;
}
void MoTao::run() {
    sort(query, query + n);
    MoTaoQuery iq(1, 0);
    for (int i = 0; i < n; i++) transform(iq, query[i]);
}

