#pragma once
#include "../stdafx.h"
using namespace std;
/*
DFFT(double * xreal, double * ximag, int n, bool direct)

　　xreal和ximag分别表示离散序列的实部和虚部，n表示序列长度，direct表示变换方向，true为正变换，false为逆变换。

  变换结果的实部和虚部分别保存在Re和Im中。
*/
const double PI = 3.1415926536;
class DiscreteFastFourierTransform {
public:
    DiscreteFastFourierTransform() {}
    void DFFT(double *, double *, int, bool);
    void mainProcess(double *, double *, int, bool);
    double *Re, *Im;
private:
    double *wreal, *wimag;
    void swap(double&, double&);
    void bitrp(double *, double *, int);
};
void DiscreteFastFourierTransform::DFFT(double * xreal, double * ximag, int n, bool direct) {
    free(Re);
    free(Im);
    Re = (double *)malloc((n) * sizeof(double));
    Im = (double *)malloc((n) * sizeof(double));
    wreal = (double *)malloc((n) * sizeof(double));
    wimag = (double *)malloc((n) * sizeof(double));
    memset(wreal, 0, sizeof(wreal));
    memset(wimag, 0, sizeof(wimag));
    memcpy(Re, xreal, n * sizeof(double));
    memcpy(Im, ximag, n * sizeof(double));
    mainProcess(Re, Im, n, direct);
    free(wreal);
    free(wimag);
}
void DiscreteFastFourierTransform::mainProcess(double * xreal, double * ximag, int n, bool direct) {
    double treal, timag, ureal, uimag, arg;
    int m, k, j, t, index1, index2;
    bitrp(xreal, ximag, n);
    arg = 2 * PI / n;
    if (direct) {
        arg *= -1;
    }
    treal = cos(arg);
    timag = sin(arg);
    wreal[0] = 1.0;
    wimag[0] = 0.0;
    for (j = 1; j < n / 2; j++) {
        wreal[j] = wreal[j - 1] * treal - wimag[j - 1] * timag;
        wimag[j] = wreal[j - 1] * timag + wimag[j - 1] * treal;
    }
    for (m = 2; m <= n; m *= 2) {
        for (k = 0; k < n; k += m) {
            for (j = 0; j < m / 2; j++) {
                index1 = k + j;
                index2 = index1 + m / 2;
                t = n * j / m;
                treal = wreal[t] * xreal[index2] - wimag[t] * ximag[index2];
                timag = wreal[t] * ximag[index2] + wimag[t] * xreal[index2];
                ureal = xreal[index1];
                uimag = ximag[index1];
                xreal[index1] = ureal + treal;
                ximag[index1] = uimag + timag;
                xreal[index2] = ureal - treal;
                ximag[index2] = uimag - timag;
            }
        }
    }
    if (!direct) {
        for (j = 0; j < n; j++) {
            xreal[j] /= n;
            ximag[j] /= n;
        }
    }
}
inline void DiscreteFastFourierTransform::swap(double &a, double &b) {
    double t = a;
    a = b;
    b = t;
}
void DiscreteFastFourierTransform::bitrp(double * xreal, double * ximag, int n) {
    //Bit-reversal Permutation
    int i, j, a, b, p;
    for (i = 1, p = 0; i < n; i *= 2) {
        p++;
    }
    for (i = 0; i < n; i++) {
        a = i, b = 0;
        for (j = 0; j < p; j++) {
            b = (b << 1) + (a & 1);
            a >>= 1;
        }
        if (b > i) {
            swap(xreal[i], xreal[b]);
            swap(ximag[i], ximag[b]);
        }
    }
}