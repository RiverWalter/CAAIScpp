#include <stdio.h>
#include <vector>
#include <random>
#include <algorithm>
namespace NS_MRPT {
using namespace std;
#define bools(b) (b ? "true" : "false")
bool MRPT(int n, int s);
vector<int> GetUniqueRandNums(int low, int high, int n);
bool Witness(int a, int n);
int Get_t(int n_1);
int RS4ME(int a, int b, int n);
vector<int> GetBits(int b);
bool TrialDivPT(int n);
void MRPT_TrialDiv(int n, int s)
{
  bool mrpt = MRPT(n, s);
  bool trialdiv = TrialDivPT(n);
  printf("Primality test for %d (s=%d):\n", n, s);
  printf("\tMiller-Rabin test: %s\n", bools(mrpt));
  printf("\tTrial division test: %s\n\n", bools(trialdiv));
}
bool MRPT(int n, int s)
{
  auto v = GetUniqueRandNums(2, n - 2, s);
  for (auto a : v)
  {
    if (Witness(a, n))
      return false;
  }
  return true;
}
bool Witness(int a, int n)
{
  bool ret = false;
  int t = Get_t(n - 1);
  int u = (n - 1) >> t;
  int x0 = RS4ME(a, u, n);
  int xi_1 = x0, xi = 0;
  for (int i = 1; i <= t; i++)
  {
    xi = (xi_1 * xi_1) % n;
    if (xi == 1 && xi_1 != 1 && xi_1 != n - 1)
    {
      ret = true;
      break;
    }
    xi_1 = xi;
  }
  if (xi != 1)
    ret = true;
  return ret;
}
int Get_t(int n_1)
{
  int t = 0;
  while (!(n_1 & 1))
  {
    t++;
    n_1 >>= 1;
  }
  return t;
}
int RS4ME(int a, int b, int n)
{
  auto bits = GetBits(b);
  int c = 0;
  int d = 1;
  for (int k = bits.size() - 1; k >= 0; k--)
  {
    c *= 2;
    d = d * d % n;
    if (bits[bits.size() - 1 - k])
    {
      c++;
      d = d * a % n;
    }
  }
  return d;
}
vector<int> GetBits(int b)
{
  vector<int> bits;
  while (b)
  {
    bits.insert(bits.begin(), b & 1);
    b >>= 1;
  }
  return bits;
}
vector<int> GetUniqueRandNums(int low, int high, int k)
{
  vector<int> v;
  if (low > high) //k = 3: low = 2, high = 1
  {
    printf("GetUniqueRandNums: low=%d, high=%d, k=%d\n", low, high, k);
    v.push_back(low);
    return v;
  }
  random_device rdev{};
  default_random_engine e{ rdev() };
  uniform_int_distribution<int> d{ low, high };
  int a;
  if (high - low + 1 <= k)
  {
    for (int i = low; i <= high; i++)
      v.push_back(i);
  }
  else
    for (int i = 0; i < k; i++)
    {
      do {
        a = d(e);
      } while (find(v.begin(), v.end(), a) != v.end());
      v.push_back(a);
    }
  return v;
}
bool TrialDivPT(int n)
{
  bool ret = true;
  int i = 2;
  while (i * i <= n)
  {
    if (n % i == 0)
    {
      ret = false;
      break;
    }
    i++;
  }
  return ret;
}
} //namespace NS_MRPT
using namespace NS_MRPT;
void TestMRPT()
{
  for (int n = 3; n < 100; n += 2)
    MRPT_TrialDiv(n, 3);
  //The first 3 Carmichael numbers
  /*
  vector<int> m = { 561, 1105, 1729 };
  for (auto n: m)
      MRPT_TrialDiv(n, 3);
  */
  /* test Get_t
  for (int n = 3; n < 20; n += 2)
  {
      int t = Get_t(n - 1);
      int u = (n - 1) >> t;
      printf("n=%d, t=%d, u=%d\n", n, t, u);
  }
  */
}
