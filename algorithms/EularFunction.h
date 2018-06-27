#include "../stdafx.h"
using namespace std;
/*
void Euler_Sieve_Method(int * euler, int n):����ŷ������1~n�ĺ���ֵ��������euler�����С�

ŷ��������һЩ���ʣ�

����ͨʽ��

  ����������(x)=x(1-1/p1)(1-1/p2)......(1-1/pn)

      ����ŷ���������ڻ��ʵ�������a��n����a��(n) �� 1 mod n��

        ����ŷ�������ǻ��Ժ���������m,n���ʣ���(mn)=��(m)��(n)��

          ������aΪN������������(N % a == 0 && (N / a) % a == 0) ����E(N)=E(N / a) * a����(N % a == 0 && (N / a) % a != 0) ���У�E(N) = E(N / a) * (a - 1)��
*/
void Euler_Sieve_Method(int * euler, int n) {
    euler[1] = 1;
    for (int i = 2; i < n; i++) {
        euler[i] = i;
    }
    for (int i = 2; i < n; i++) {
        if (euler[i] == i) {
            for (int j = i; j < n; j += i) {
                euler[j] = euler[j] / i * (i - 1);
            }
        }
    }
}