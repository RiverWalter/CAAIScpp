#include <utility>
#include <random>
namespace NS_BubbleSort {
using namespace std;
void BubbleSort(int a[], int n)
{
   for (int i = n; i >= 2; i--) {
      bool hasSwap = false;
      for (int j = 0; j < i - 1; j++) {
         if (a[j]> a [j + 1]) {
            swap(a[j], a[j + 1]);
            hasSwap = true;
         }
      }
      if (!hasSwap)
          break;
   }
}
} //namespace NS_BubbleSort
using namespace NS_BubbleSort;
void TestBubbleSort(int n)
{
    random_device rdev{};
    default_random_engine e{ rdev() };
    int m = n <= 20 ? 99 : n * 10 - 1;
    uniform_int_distribution<int> rnd{ 0, m };
    int* a = new int[n];
    for (int i = 0; i < n; i++)
        a[i] = rnd(e);
    printf("²âÊÔÃ°ÅÝÅÅÐòËã·¨£ºn = %d\n", n);
    printf("ÅÅÐòÇ°Êý×é:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    BubbleSort(a, n);
    printf("ÅÅÐòºóÊý×é:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    delete[]a;
}