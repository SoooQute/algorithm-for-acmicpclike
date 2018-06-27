#pragma once
#include "../stdafx.h"
using namespace std;
/*
解决形如
x%a1=m1
x%a2=m2......
*/
class CongruentLinearEquationGroup {
private:
#define MAX_GROUP_SIZE 10
    int groupSize, dis;
    int A[MAX_GROUP_SIZE], M[MAX_GROUP_SIZE];
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
    CongruentLinearEquationGroup() {
        groupSize = 0;
    }
    void clear() {
        groupSize = 0;
    }
    void addEquation(int a, int m) {
        if (m == 0) {
            return;
        }
        A[groupSize] = a;
        M[groupSize++] = m;
    }
    // => Possible solution,not minium positive solution
    int getSolution() {
        int at = A[0], mt = M[0], ap, mp, x, y, z;
        for (int i = 1; i < groupSize; i++) {
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
            while (x <= 0) {
                x += mt;
            }
            at = x;
        }
        dis = mt;
        return x;
    }
    int getNextSolution(int x) {
        return x + dis;
    }
};