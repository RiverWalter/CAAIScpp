#include <random>
namespace NS_InsertionSort {
using namespace std;
void InsertionSort(int a[],int n)
{
    int x, j;
    for (int i = 1; i < n; i++) {
        x = a[i];
        j = i - 1;
        while (j >= 0 && a[j] > x) {
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = x;
    }
}
} //namespace NS_InsertionSort
using namespace NS_InsertionSort;
void TestInsertionSort(int n)
{
    random_device rdev{};
    default_random_engine e{ rdev() };
    int m = n <= 20 ? 99 : n * 10 - 1;
    uniform_int_distribution<int> rnd{ 0, m };
    int* a = new int[n];
    for (int i = 0; i < n; i++)
        a[i] = rnd(e);
    printf("���Բ��������㷨��n = %d\n", n);
    printf("����ǰ����:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    InsertionSort(a, n);
    printf("���������:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    delete[]a;
}
