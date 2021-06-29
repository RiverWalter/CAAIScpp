#include "../../include/headers.h"
#include <random>
#include <algorithm>
using namespace NS_QuickSort;
using namespace NS_HeapSort;
using namespace NS_MergeSort;
void TestSortingQ1()
{
  random_device rdev{};
  mt19937 e{ rdev() };
  int k = 1 << 30;
  printf("2^31: %d\n", k);
  uniform_int_distribution<int> rnd{ 0, k };
  int n = 100000;
  int* a = new int[n];
  for (int i = 0; i < n; i++)
    a[i] = rnd(e);
  printf("测试快速排序算法：n = %d\n", n);
  /*
  printf("排序前数组:\n");
  for (int i = 0; i < n; i++)
    printf("%d ", a[i]);
  printf("\n");*/
  QuickSort(a, 0, n - 1);
  /*
  printf("排序后数组:\n");
  for (int i = 0; i < n; i++)
    printf("%d ", a[i]);
  printf("\n");*/
  delete[]a;
}

void TestSortingQ2()
{
  random_device rdev{};
  mt19937 e{ rdev() };
  int k = 1 << 30;
  printf("2^31: %d\n", k);
  uniform_int_distribution<int> rnd{ 0, k };
  int n = 90000;
  int* b = new int[n];
  for (int i = 0; i < n; i++)
    b[i] = rnd(e);
  //HeapSort(b, n);
  int* a = new int[n];
  printf("Heap sort：n = %d\n", n);
  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < n; j++)
      a[j] = b[j];
    clock_t begin = clock();
    HeapSort(a, n);
    clock_t end = clock();
    double time_spent = ((double)end - (double)begin) / CLOCKS_PER_SEC;
    printf("%.3lf\n", time_spent);
    
  }
  printf("Quick sort：n = %d\n", n);
  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < n; j++)
      a[j] = b[j];
    clock_t begin = clock();
    QuickSort(a, 0, n - 1);
    clock_t end = clock();
    double time_spent = ((double)end - (double)begin) / CLOCKS_PER_SEC;
    printf("%.3lf\n", time_spent);
  }
  /*
  printf("Merge sort：n = %d\n", n);
  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < n; j++)
      a[j] = b[j];
    clock_t begin = clock();
    MergeSort(a, 0, n - 1);
    clock_t end = clock();
    double time_spent = ((double)end - (double)begin) / CLOCKS_PER_SEC;
    printf("\t: %2d: %.3lf\n", i, time_spent);
  }*/
  delete[]a;
  delete[]b;
}
void TestSorting()
{
  TestSortingQ2();
}
/*
void SelectionSortTest(int n)
{
	int *a = new int[n];
	printf("测试选择排序算法：n = %d\n", n);
    int high = n <= 20 ? 99 : n * 10 - 1;
	RandRangeArr(n, 0, high, a);
    printf("排序前数组:\n");
    Print1DArr(a, n, false);
    if (n > 20 ) {
        printf("......\n");
    }
	SelectionSort(a, n);
    printf("排序后数组:\n");
    Print1DArr(a, n, false);
    if (n > 20) {
        printf("......\n");
    }
    delete[]a;
}
void BubbleSortTest(int n)
{
    int *a = new int[n];
    printf("测试冒泡排序算法：n = %d\n", n);
    int high = n <= 20 ? 99 : n * 10 - 1;
    RandRangeArr(n, 0, high, a);
    printf("排序前数组:\n");
    Print1DArr(a, n, false);
    if (n > 20) {
        printf("......\n");
    }
    BubbleSort(a, n);
    printf("排序后数组:\n");
    Print1DArr(a, n, false);
    if (n > 20) {
        printf("......\n");
    }
    delete a;
}
void InsertionSortTest(int n)
{
	int *a = new int[n];
	printf("测试插入排序算法：n = %d\n", n);
    int high = n <= 20 ? 99 : n * 10 - 1;
    RandRangeArr(n, 0, high, a);
	printf("排序前数组:\n");
    Print1DArr(a, n, false);
    if (n > 20 ) {
        printf("......\n");
    }
	InsertionSort(a, n);
	printf("排序后数组:\n");
    Print1DArr(a, n, false);
    if (n > 20) {
        printf("......\n");
    }
    delete a;
}
void QuickSortTest(int n)
{
	int *a = new int[n];
	printf("测试快速排序算法：n = %d\n", n);
    int high = n <= 20 ? 99 : n * 10 - 1;
    RandRangeArr(n, 0, high, a);
    printf("排序前数组:\n");
    Print1DArr(a, n, false);
    if (n > 20) {
        printf("......\n");
    };
	QuickSort(a, 0, n - 1);
	printf("排序后数组:\n");
    Print1DArr(a, n, false);
    if (n > 20) {
        printf("......\n");
    }
    delete a;
}
void TwoWayMergeTest(int m, int n)
{
    int k = m + n;
    int *a = new int[k];
    RandRangeArr(k, 0, 99, a);
    printf("对长度为%d和%d的有序数组进行合并。\n", m, n);
    printf("原始数组：\n");
    Print1DArr(a, k);
    BubbleSort(a, m);
    BubbleSort(a + m, n);
    printf("子数组排序：\n");
    Print1DArr(a, k);
	TwoWayMerge(a, 0, m - 1, k - 1);
    printf("合并后：\n");
    Print1DArr(a, k);
    delete a;
}
void MergeSortTest(int n)
{
    int *a = new int[n];
    printf("测试合并排序算法(递归实现)：n = %d\n", n);
    int high = n <= 20 ? 99 : n * 10 - 1;
    RandRangeArr(n, 0, high, a);
    printf("排序前数组:\n");
    Print1DArr(a, n, false);
    if (n > 20) {
        printf("......\n");
    };
    MergeSort(a, 0, n - 1);
    printf("排序后数组:\n");
    Print1DArr(a, n, false);
    if (n > 20) {
        printf("......\n");
    }
    delete a;
}
void MaxHeapifyTest(int n)
{
    int *a = new int[n];
    printf("测试建堆算法：\n");
    RandRangeArr(n, 0, 100, a);
    printf("建堆前数组:\n");
    Print1DArr(a, n);
	MaxHeapify(a, n);
    printf("建堆后数组:\n");
    Print1DArr(a, n);
    delete a;
}
void HeapSortTest(int n)
{
    int *a = new int[n];
    printf("测试堆排序算法：n = %d\n", n);
    int high = n <= 20 ? 99 : n * 10 - 1;
    RandRangeArr(n, 0, high, a);
    printf("排序前数组:\n");
    Print1DArr(a, n, false);
    if (n > 20) {
        printf("......\n");
    };
    HeapSort(a, n);
    printf("排序后数组:\n");
    Print1DArr(a, n, false);
    if (n > 20) {
        printf("......\n");
    }
    delete a;
}
*/
