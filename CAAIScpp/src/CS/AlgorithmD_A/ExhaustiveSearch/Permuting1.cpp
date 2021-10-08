#include <vector>
#include <utility> //swap
namespace NS_Permuting1 {
  using namespace std;
  void Permuting1(int i);
  void OutputOnePermutation();
  static vector<int> x;
  static int N;
  void PermutingCaller1(int n)
  {
    N = n;
    for (int i = 0; i < n; ++i)
      x.push_back(i + 1);
    Permuting1(0);
  }
  static bool done = false;
  void Permuting1(int i)
  {
    if (i < N - 1) {
      for (int j = i; j < N && !done; ++j) {
        swap(x[i], x[j]);
        Permuting1(i + 1);
        swap(x[i], x[j]);
      }
    }
    else {
      printf("Got 1st permutation.\n");
      done = true;
    }
  }
  void OutputOnePermutation()
  {
    static int cnt = 0;
    ++cnt;
    printf("%03d: ", cnt);
    return;
    for (auto x : x)
      printf("%d", x);
    printf("\n");
  }
} //namespace NS_Permuting1
using namespace NS_Permuting1;
void TestPermuting1(int n)
{
  printf("Testing Permuting: n = %d\n", n);
  x.clear();
  PermutingCaller1(n);
}
