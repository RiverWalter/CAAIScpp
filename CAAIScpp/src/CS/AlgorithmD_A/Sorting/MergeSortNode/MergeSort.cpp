#include <random>
namespace NS_MergeSort {
using namespace std;
void TwoWayMerge(int a[], int p, int q, int r);
void MergeSort(int a[], int low, int high)
{
    if (low < high) {
        int mid = (low + high)/2;
        MergeSort(a, low, mid);
        MergeSort(a, mid + 1, high);
        TwoWayMerge(a, low, mid, high);
    }
}
static void TwoWayMerge(int a[], int p, int q, int r)
{
    int *b = new int[r + 1];
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
        for (; i <= q; i++)
            b[k++] = a[i];
    for (i = p; i <= r; i++)
        a[i] = b[i];
    delete[] b;
}
} //namespace NS_MergeSort
using namespace NS_MergeSort;
void TestMergeSort(int n)
{
    random_device rdev{};
    default_random_engine e{ rdev() };
    int m = n <= 20 ? 99 : n * 10 - 1;
    uniform_int_distribution<int> rnd{ 0, m };
    int* a = new int[n];
    for (int i = 0; i < n; i++)
        a[i] = rnd(e);
    printf("测试归并排序算法：n = %d\n", n);
    printf("排序前数组:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    MergeSort(a, 0, n - 1);
    printf("排序后数组:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    delete[]a;
}
