#include <vector>
#include <utility> //swap
namespace NS_PermutingIterA {
  using namespace std;
  void PermutingIterA();
  void OutputOnePermutation();
  static vector<int> x;
  static vector<vector<int>> stack(1000000, vector<int>(3));
  static int N;
  void PermutingIterCallerA(int n)
  {
    N = n;
    for (int i = 0; i < n; ++i)
      x.push_back(i + 1);
    PermutingIterA();
  }
  void PermutingIterA()
  {
    vector<vector<int>> stack(50000000, vector<int>(3));
    stack[0] = { 0, 0, 0 };
    int k = 1;
    while (k > 0) {
      vector<int>& v = stack[--k];
      if (v[0] == 0) {
        if (v[1] == N - 1) {
          OutputOnePermutation();
          break;
        } else {
          stack[k++] = { 1, v[1], v[2] };
          swap(x[v[1]], x[v[2]]);
          stack[k++] = { 0, v[1] + 1, v[1] + 1 };
        }
      }
      else {
        swap(x[v[1]], x[v[2]]);
        if (v[2] < N - 1) {
          stack[k++] = { 0, v[1], v[2] + 1 };
        }
      }
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
} //namespace NS_PermutingIterA
using namespace NS_PermutingIterA;
void TestPermutingIterA(int n)
{
  printf("Testing PermutingIterA: n = %d\n", n);
  x.clear();
  PermutingIterCallerA(n);
}
