#include <random>
namespace NS_TwoWayMerge {
using namespace std;
void TwoWayMerge(int a[], int p, int q, int r)
{
    int* b = new int[r + 1];
    int i = p, j = q + 1, k = p;
    while (i <= q && j <= r) {
        if (a[i] < a[j])
            b[k++] = a[i++];
        else
            b[k++] = a[j++];
    }
    if (i == q + 1)
        for (; j <= r; j++)
            b[k++] = a[j];
    else
        for (; i<= q; i++)
            b[k++] = a[i];
    for (i = p; i <= r; i++)
        a[i] = b[i];
    delete[]b;
}
void InsertionSort(int a[], int n)
{
    int x, j;
    for (int i = 1; i < n; i++) {
        x = a[i];
        j = i - 1;
        while (j >= 0 && a[j] > x) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = x;
    }
}
} //namespace NS_SelectionSort
using namespace NS_TwoWayMerge;
void TestTwoWayMerge(int L, int R)
{
    random_device rdev{};
    default_random_engine e{ rdev() };
    int n = L + R;
    uniform_int_distribution<int> rnd{ 0, 99 };
    int* a = new int[n];
    for (int i = 0; i < n; i++)
        a[i] = rnd(e);
    printf("测试二路归并算法：L=%d, R=%d\n", L, R);
    printf("原始数组:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    InsertionSort(a, L);
    InsertionSort(a + L, R);
    printf("左右两部分分别排序后数组:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    TwoWayMerge(a, 0, L - 1, n - 1);
    printf("归并后数组:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    delete[]a;
}
