#include <vector>
#include <utility> //swap
namespace NS_PermutingIter {
  using namespace std;
  void PermutingIter();
  void OutputOnePermutation();
  static vector<int> x;
  //static vector<vector<int>> stack;
  static int N;
  void PermutingIterCaller(int n)
  {
    N = n;
    for (int i = 0; i < n; ++i)
      x.push_back(i + 1);
    PermutingIter();
  }
  void PermutingIter()
  {
    vector<vector<int>> stack;
    stack.push_back({ 0, 0, 0 });
    while (!stack.empty()) {
      vector<int> v = stack.back();
      stack.pop_back();
      if (v[0] == 0) {
        if (v[1] == N - 1) {
          printf("Got 1st permutation.\n");
          break;
        }
        else {
          swap(x[v[1]], x[v[2]]);
          stack.push_back({ 1, v[1], v[2] });
          stack.push_back({ 0, v[1] + 1, v[1] + 1 });
        }
      }
      else {
        swap(x[v[1]], x[v[2]]);
        if (v[2] < N - 1) {
          stack.push_back({ 0, v[1], v[2] + 1 });
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
} //namespace NS_PermutingIter
using namespace NS_PermutingIter;
void TestPermutingIter(int n)
{
  printf("Testing PermutingIter: n = %d\n", n);
  x.clear();
  PermutingIterCaller(n);
}
