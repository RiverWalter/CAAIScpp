#include <utility>
#include <random>
namespace NS_SelectionSort {
using namespace std;
void SelectionSort(int a[], int n)
{
    for (int i = n; i >= 1; i--) {
        int p = 0;
        for (int j = 1; j < i; j++)
            if (a[p] < a[j])
                p = j;
        if (p != i - 1)
            swap(a[p], a[i - 1]);
    }
}
} //namespace NS_SelectionSort
using namespace NS_SelectionSort;
void TestSelectionSort(int n)
{
    random_device rdev{};
    default_random_engine e{ rdev() };
    int m = n <= 20 ? 99 : n * 10 - 1;
    uniform_int_distribution<int> rnd{ 0, m };
    int* a = new int[n];
    for (int i = 0; i < n; i++)
        a[i] = rnd(e);
    printf("����ѡ�������㷨��n = %d\n", n);
    printf("����ǰ����:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    SelectionSort(a, n);
    printf("���������:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    delete[]a;
}