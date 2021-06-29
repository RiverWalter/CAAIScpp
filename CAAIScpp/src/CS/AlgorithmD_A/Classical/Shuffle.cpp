#include <vector>
#include <utility>  //swap
#include <stdlib.h> //rand
#include <time.h>
namespace NS_Shuffle {
using namespace std;
int RandIntRange(int low, int high);
void Shuffle(vector<int>& a, int n)
{
    int p;
    for (int i = n - 1; i >= 1; i--)
    {
        p = RandIntRange(0, i);
        if (p != i)
            swap(a[p], a[i]);
    }
}
//Generate a random integer in [low, high]
int RandIntRange(int low, int high)
{
    return rand() % (high - low + 1) + low;
}
} //NS_Shuffle
using namespace NS_Shuffle;
void TestShuffle(int n)
{
    //Set random seed for rand()
    srand((unsigned)time(NULL));

    vector<int> a(n);
    printf("Testing shuffle algorithm:"
      " n = %d\n", n);
    for (int i = 0; i < n; i++)
        a[i] = i + 1;
    printf("Before shuffle:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    Shuffle(a, n);
    printf("After shuffle:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}