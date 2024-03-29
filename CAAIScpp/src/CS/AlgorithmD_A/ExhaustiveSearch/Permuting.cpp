#include <vector>
#include <utility> //swap
namespace NS_Permuting {
  using namespace std;
  void Permuting(int i);
  void OutputOnePermutation();
  static vector<int> x;
  static int N;
  void PermutingCaller(int n)
  {
    N = n;
    for (int i = 0; i < n; ++i)
      x.push_back(i + 1);
    Permuting(0);
  }
  void Permuting(int i)
  {
    if (i < N - 1) {
      for (int j = i; j < N; ++j) {
        swap(x[i], x[j]);
        Permuting(i + 1);
        swap(x[i], x[j]);
      }
    }
    else {
      OutputOnePermutation();
    }
  }
  void OutputOnePermutation()
  {
    static int cnt = 0;
    ++cnt;
    printf("%03d: ", cnt);
    for (auto x : x)
      printf("%d", x);
    printf("\n");
  }
} //namespace NS_Permuting
using namespace NS_Permuting;
void TestPermuting(int n)
{
  printf("Testing Permuting: n = %d\n", n);
  x.clear();
  PermutingCaller(n);
}
