#pragma once
#include "../stdafx.h"
using namespace std;

/*
假定有一个定义域是正整数的函数f(n)，定义F(n)=sigma[f(d)]，d|n（F称为f 的和函数）。

那么如果我们得到了F函数，就可以通过莫比乌斯反演公式得到f函数：f(n)=sigma[u(d)*F(n/d)]，d|n

其中u是莫比乌斯函数的记号，其定义为：

u(n)    = 1         n=1
        = (-1)^r    n=p1*p2*......pr，其中pi为各不相同的素数
        = 0         其它






莫比乌斯函数的性质：

1）莫比乌斯函数是积性函数

2）对莫比乌斯函数进行莫比乌斯反演，得到的函数除f(1)=1外恒为0。

//若f是欧拉函数，则f(n)=n*(sigma[u(d)/d]),d|n。
*/
//没做过题，不知道对不对。
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