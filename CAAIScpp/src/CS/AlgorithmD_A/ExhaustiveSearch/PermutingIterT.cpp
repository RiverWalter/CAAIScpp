#include <vector>
#include <utility> //swap
namespace NS_PermutingIterT {
  using namespace std;
  void PermutingIterT();
  void OutputOnePermutation();
  static vector<int> x;
  static vector<vector<int>> stack(500000, vector<int>(3));
  static int N;
  void PermutingIterCallerT(int n)
  {
    N = n;
    for (int i = 0; i < n; ++i)
      x.push_back(i + 1);
    PermutingIterT();
  }
  void PermutingIterT()
  {
    //stack[0] = { 1, 0, 0 };
    stack[0] = { 0, 0, 0 };
    int k = 1;
    //vector<int>& v = stack[1];
    while (k > 0) {
      vector<int>& v = stack[--k];
      //printf("k=%d: %d %d %d\n", k, v[0], v[1], v[2]);
      if (v[0] == 0) {
        if (v[1] == N - 1)
          OutputOnePermutation();
        else {
          //printf("k1=%d: %d %d %d\n", k-1, stack[k-1][0], stack[k - 1][1], stack[k - 1][2]);
          swap(x[v[1]], x[v[2]]);
          stack[k++] = { 1, v[1], v[2] };
          stack[k++] = { 0, v[1] + 1, v[1] + 1 };
          //printf("k0=%d: %d %d %d\n", k - 1, stack[k - 1][0], stack[k - 1][1], stack[k - 1][2]);
        }
      }
      else {
        swap(x[v[1]], x[v[2]]);
        if (v[2] < N - 1) {
          stack[k++] = { 0, v[1], v[2] + 1 };
          //printf("k00=%d: %d %d %d\n", k - 1, stack[k - 1][0], stack[k - 1][1], stack[k - 1][2]);
        }
      }
    }
  }
  void OutputOnePermutation()
  {
    static int cnt = 0;
    ++cnt;
    printf("%03d: ", cnt);
    //return;
    for (auto x : x)
      printf("%d", x);
    printf("\n");
  }
} //namespace NS_PermutingIterT
using namespace NS_PermutingIterT;
void TestPermutingIterT(int n)
{
  printf("Testing PermutingIterT: n = %d\n", n);
  x.clear();
  PermutingIterCallerT(n);
}
