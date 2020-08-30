#include <utility>
#include <random>
namespace NS_QuickSort {
using namespace std;
int partition(int a[], int low, int high);
void QuickSort(int a[], int low, int high)
{
    if (low < high) {
        int p = partition(a, low, high);
        QuickSort(a, low, p - 1);
        QuickSort(a, p + 1, high);
    }
}
/* N. Lomuto Scheme */
int partition(int a[], int low, int high)
{
    int pivot = a[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (a[j] < pivot) {
            i = i + 1;
            if (i < j)
                swap(a[i], a[j]);
        }
    }
    if (a[high] < a[i + 1])
        swap(a[i + 1], a[high]);
    return i + 1;
}
} //namespace NS_QuickSort
using namespace NS_QuickSort;
void TestQuickSort(int n)
{
    random_device rdev{};
    default_random_engine e{ rdev() };
    int m = n <= 20 ? 99 : n * 10 - 1;
    uniform_int_distribution<int> rnd{ 0, m };
    int* a = new int[n];
    for (int i = 0; i < n; i++)
        a[i] = rnd(e);
    printf("���Կ��������㷨��n = %d\n", n);
    printf("����ǰ����:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    QuickSort(a, 0, n - 1);
    printf("���������:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    delete[]a;
}
