#pragma once
#include "stdafx.h"
using namespace std;
/*
x%m1=a1
x%m2=a2
...
*/
class RemainderGroup {
private:
    int sz, dis;
    int *M, *A;
    int gcd(int a, int b) {
        int k;
        while (b != 0) {
            k = b;
            b = a % b;
            a = k;
        }
        return a;
    }
    /* * * * * * * * * *
    * a,b=>x,y        *
    * ax+by=gcd(a,b)  *
    * * * * * * * * * */
    int extended_gcd(int a, int b, int &x, int &y) {
        int ans, t;
        if (b == 0) {
            x = 1;
            y = 0;
            return a;
        } else {
            ans = extended_gcd(b, a % b, x, y);
            t = x;
            x = y;
            y = t - (a / b) * y;
        }
        return ans;
    }
public:
    RemainderGroup(int n): sz(0), M(new int [n + 5]), A(new int [n + 5]) {}
    void clear() {
        sz = 0;
    }
    void addEquation(int m, int a) {
        if (m == 0) {
            return;
        }
        A[sz] = a;
        M[sz++] = m;
    }
    int getSolution() {
        int at = A[0], mt = M[0], ap, mp, x, y, z;
        for (int i = 1; i < sz; i++) {
            ap = A[i];
            mp = M[i];
            if ((at - ap) % gcd(mt, mp) != 0) {
                return -1;
            }
            /* * * * * * * * * * * * *
            *  x=mt*y+at            *
            *  x=mp*z+ap            *
            *    => at-ap=mp*z-mt*y *
            * * * * * * * * * * * * */
            extended_gcd(mp, -1 * mt, z, y);
            //  => mp*z-mt*y=gcd(mp,-mt)
            z = z * (at - ap) / gcd(mp, -mt);
            x = mp * z + ap;
            mt = mt * mp / gcd(mt, mp);
            x = (x % mt + mt) % mt;
            at = x;
        }
        dis = mt;
        return x;
    }
    int getNextSolution(int x) {
        return x + dis;
    }
    ~RemainderGroup() {
        delete [] M, delete []A;
    }
};