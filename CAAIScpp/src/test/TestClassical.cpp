#include "../../include/headers.h"
//Binary Search Test - Recursion
void BinarySearchRTest(int n)
{
    int *a = new int[n];
    int m = 3 * n / 2;
    RandRangeArr(n, 1, m, a);
    //InsertionSort(a, n);
    int x = RandRange(1, m);
    int p = BinarySearchR(a, 0, n - 1, x);
    printf("���������㷨����(�ݹ�):\n");
    printf("���飺\n");
    Print1DArr(a, n);
    printf("����Ԫ��: %d\n", x);
    if (p != -1)
        printf("λ��: %d\n", p);
    else
        printf("δ�ҵ���\n");
    delete[] a;
}

