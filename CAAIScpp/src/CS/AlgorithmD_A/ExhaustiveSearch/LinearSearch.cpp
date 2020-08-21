#include <vector>
#include <random>
namespace NS_LinearSearch {
using namespace std;
int LinearSearch(vector<int> a, int n, int x)
{
    int p = 0;
    while ( p < n && x != a[p])
        p++;
    if (p == n)
        p = -1;
    return p;
}
} //namespace NS_LinearSearch
using namespace NS_LinearSearch;
void TestLinearSearch(int n)
{
    random_device rdev{};
    default_random_engine e{ rdev() };
    vector<int> a(n);
    int m = 3 * n / 2;
    uniform_int_distribution<int> rnd{ 1, m };
    for (int i = 0; i < n; i++)
        a[i] = rnd(e);
    int x = rnd(e);
    int p = LinearSearch(a, n, x);
    printf("线性查找测试:\n");
    printf("数组：\n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    printf("待查元素: %d\n", x);
    if (p != -1)
        printf("位置: %d\n", p);
    else
        printf("未找到！\n");
}
