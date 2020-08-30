#include <utility>
#include <random>
namespace NS_MaxHeapify {
using namespace std;
void SiftDown(int H[], int n, int i);
void MaxHeapify(int H[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--) {
        SiftDown(H, n, i);
    }
}
static void SiftDown(int H[], int n, int i)
{
    bool done = false;
    while (!done && ((i = 2 * i + 1) < n)) {
        if ((i + 1 < n) && (H[i + 1] > H[i]))
            i = i + 1;
        if (H[(i - 1) / 2] < H[i])
            swap(H[(i - 1) / 2], H[i]);
        else done = true;
    }
}
} //namespace NS_MaxHeapify
using namespace NS_MaxHeapify;
void TestMaxHeapify(int n)
{
    random_device rdev{};
    default_random_engine e{ rdev() };
    int m = n <= 20 ? 99 : n * 10 - 1;
    uniform_int_distribution<int> rnd{ 0, m };
    int* a = new int[n];
    for (int i = 0; i < n; i++)
        a[i] = rnd(e);
    printf("测试建堆算法：n = %d\n", n);
    printf("建堆前数组:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    MaxHeapify(a, n);
    printf("建堆后数组:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    delete[]a;
}