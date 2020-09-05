#include <random>
#include <vector>
#include <algorithm>
namespace NS_BinarySearch {
using namespace std;
int BinarySearch(vector<int>& a, int x)
{
    int low = 0, high = a.size() - 1, mid, p = -1;
    while (low <= high && p < 0) {
        mid = (low + high) / 2;
        if (x == a[mid]) 
            p = mid;
        else if (x < a[mid])
            high = mid - 1;
        else 
            low = mid + 1;
    }
    return p;
}
} //namespace NS_BinarySearch
using namespace NS_BinarySearch;
void TestBinarySearch(int n)
{
    random_device rdev{};
    default_random_engine e{ rdev() };
    vector<int> a;
    int m = 3 * n / 2;
    uniform_int_distribution<int> rnd{ 1, m };
    for (int i = 0; i < n; i++)
        a.push_back(rnd(e));
    sort(a.begin(), a.end());
    int x = rnd(e);
    int p = BinarySearch(a, x);
    printf("¶þ·ÖËÑË÷²âÊÔ:\n");
    printf("Êý×é£º\n");
    for (auto y: a)
        printf("%d ", y);
    printf("\n");
    printf("´ýËÑË÷ÔªËØ: %d\n", x);
    if (p != -1)
        printf("Î»ÖÃ: %d\n", p);
    else
        printf("Î´ÕÒµ½£¡\n");
}