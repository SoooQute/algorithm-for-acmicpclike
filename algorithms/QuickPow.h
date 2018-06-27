#include "../stdafx.h"
using namespace std;
inline long long pow(long long a, long long b, long long p) {
    long long rtn = 1;
    while (b) {
        if (b & 1) rtn = rtn * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return rtn;
}