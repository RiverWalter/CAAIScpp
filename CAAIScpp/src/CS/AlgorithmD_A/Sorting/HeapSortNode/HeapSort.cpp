#include <utility>
#include <random>
namespace NS_HeapSort {
using namespace std;
void MakeHeap(int H[], int n);
void SiftDown(int H[], int n, int i); 
void HeapSort(int H[], int n)
{
    MakeHeap(H, n);
    for (int i = n - 1; i > 0; i--) {
        swap(H[0], H[i]);
        SiftDown(H, i, 0);
    }
}
void MakeHeap(int H[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--) {
        SiftDown(H, n, i);
    }
}
void SiftDown(int H[], int n, int i)
{
    bool done = false;
    while (!done && (i = 2 * i + 1) < n) {
        if (i + 1 < n && H[i + 1] > H[i])
            i = i + 1;
        if (H[(i - 1) / 2] < H[i])
            swap(H[(i - 1) / 2], H[i]);
        else done = true;
    }
}
} //namespace NS_HeapSort
using namespace NS_HeapSort;
void TestHeapSort(int n)
{
    random_device rdev{};
    default_random_engine e{ rdev() };
    int m = n <= 20 ? 99 : n * 10 - 1;
    uniform_int_distribution<int> rnd{ 0, m };
    int* a = new int[n];
    for (int i = 0; i < n; i++)
        a[i] = rnd(e);
    printf("测试堆排序算法：n = %d\n", n);
    printf("排序前数组:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    HeapSort(a, n);
    printf("排序后数组:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    delete[]a;
}