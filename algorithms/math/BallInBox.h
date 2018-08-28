#pragma once
#include "stdafx.h"
#include "algorithms/math/AandC.h"
#include "algorithms/math/QuickPow.h"
using namespace std;
/*
    k个球          m个盒子        是否允许有空盒子      方案数
1   各不相同        各不相同        是                 mk
2   各不相同        各不相同        否                 m!Stirling2(k, m)
3   各不相同        完全相同        是                 ∑m i=1Stirling2(k, i)
4   各不相同        完全相同        否                 Stirling2(k, m)
5   完全相同        各不相同        是                 C(m + k − 1, k)
6   完全相同        各不相同        否                 C(k − 1, m − 1)
7   完全相同        完全相同        是                 ___________1__________
                                            (1−x)(1−x^2)...(1−x^m) 的 xk 项的系数
8   完全相同        完全相同        否                 __________x^m_________
                                            (1−x)(1−x^2):::(1−x^m) 的 xk 项的系数
*/
class BallInBox {
public:
    long long mod;
    int n;
    BallInBox(long long m, int _n, AandC * _ac) {
        mod = m, n = _n, ac = _ac;
    }
    ~BallInBox() {
        delete ac;
    }
    //k balls,m boxes.
    //5
    AandC *ac;
    long long SameballDiffboxCanempty(int k, int m) {
        return ac->C(m + k - 1, k);
    }
};