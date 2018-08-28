#pragma once
#include "stdafx.h"
using namespace std;
class AandC {
public:
    long long *fac, *inv, *f;
    long long mod;
    AandC(long long m, int n) {
        mod = m;
        fac = new long long[n + 5], inv = new long long[n + 5], f = new long long[n + 5];
        fac[0] = fac[1] = inv[0] = inv[1] = f[0] = f[1] = 1;
        for (int i = 2; i < n; i++) {
            fac[i] = fac[i - 1] * i % mod;
            f[i] = (mod - mod / i) * f[mod % i] % mod;
            inv[i] = inv[i - 1] * f[i] % mod;
        }
    }
    ~AandC() {
        delete[] fac, delete[] inv, delete[] f;
    }
    //choose b from a
    long long A(int a, int b) {
        return fac[a] * inv[a - b] % mod;
    }
    long long C(int a, int b) {
        return fac[a] * inv[b] % mod * inv[a - b] % mod;
    }
};