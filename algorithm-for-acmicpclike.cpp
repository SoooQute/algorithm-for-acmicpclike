// algorithm-for-acmicpclike.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "algorithms/RemainderGroup.h"

int main() {
    RemainderGroup rg(3);
    rg.addEquation(3, 2);
    rg.addEquation(5, 4);
    rg.addEquation(7, 6);
    cout << rg.getSolution() << endl;
    return 0;
}

