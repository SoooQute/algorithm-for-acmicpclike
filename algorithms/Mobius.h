#pragma once
#include "../stdafx.h"
using namespace std;

/*
�ٶ���һ�����������������ĺ���f(n)������F(n)=sigma[f(d)]��d|n��F��Ϊf �ĺͺ�������

��ô������ǵõ���F�������Ϳ���ͨ��Ī����˹���ݹ�ʽ�õ�f������f(n)=sigma[u(d)*F(n/d)]��d|n

����u��Ī����˹�����ļǺţ��䶨��Ϊ��

u(n)    = 1         n=1
        = (-1)^r    n=p1*p2*......pr������piΪ������ͬ������
        = 0         ����






Ī����˹���������ʣ�

1��Ī����˹�����ǻ��Ժ���

2����Ī����˹��������Ī����˹���ݣ��õ��ĺ�����f(1)=1���Ϊ0��

//��f��ŷ����������f(n)=n*(sigma[u(d)/d]),d|n��
*/
//û�����⣬��֪���Բ��ԡ�
class Mobius {
public:
    int *u, sz, *p, pn, *r, rn;
    bool *v;
    Mobius(int n): sz(n), pn(0), u(new int[n + 1]), p(new int[n + 1]), r(new int[n + 1]), v(new bool[n + 1]) {
        memset(v, true, sizeof(v));
        v[0] = v[1] = false;
        for (int i = 2; i <= n; i++) {
            if (!v[i]) continue;
            p[pn++] = i;
            for (int j = i + i; j <= n; j += i) v[j] = false;
        }
        for (int i = 1; i <= n; i++) u[i] = 1;
        for (int i = 0; i < pn; i++) {
            for (int j = p[i]; j <= n; j += p[i]) u[j] *= -1;
            int pp = p[i] * p[i];
            for (int j = pp; j <= n; j += pp) u[j] = 0;
        }
    }
    void invert(int *F, int *f, int n) {
        memset(f, 0, sizeof(int) * (n + 1));
        for (int d = 1; d <= n; d++) {
            int m = n / d, q = 0;
            for (int i = 1; i <= m; i++) {
                q += d;
                f[q] += u[d] * F[i];
            }
        }
    }
    int invert(int *F, int x) {
        rn = 0;
        for (int i = 0; i < pn; i++) {
            if (x % p[i] == 0) r[rn++] = p[i];
            if (x < p[i]) break;
        }
        int ans = 0;
        for (int i = 0; i < (1 << rn); i++) {
            int cnt = 0, m = 1;
            for (int j = 0; j < rn; j++) {
                if (i & (1 << j)) cnt++, m *= r[j];
            }
            if (cnt & 1) ans -= F[x / m];
            else ans += F[x / m];
        }
        return ans;
    }
    ~Mobius() {
        delete[] u, delete[] p, delete[] r, delete[] v;
    }
};