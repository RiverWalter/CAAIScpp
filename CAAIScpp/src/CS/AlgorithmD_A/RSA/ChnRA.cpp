#include <stdio.h>
#include <vector>
#include <numeric>
#include <algorithm>
namespace NS_ChnRA {
using namespace std;
struct Clsdxy {
  int d; int x; int y;
  Clsdxy(int ad, int ax, int ay) :
    d(ad), x(ax), y(ay) {}
};
Clsdxy ExtEuclidGCD(int a, int b);
int GetMODInverse(int a, int N);
int ChnRA(vector<int>& a, vector<int>& n)
{
  int N = a.size();
  vector<int> m, m_inv, c;
  int M = accumulate(n.begin(), n.end(), 1, 
    multiplies<int>());
  for (int i = 0; i < N; i++)
    m.push_back(M / n[i]);
  for (int i = 0; i < N; i++)
    m_inv.push_back(GetMODInverse(m[i], n[i]));
  for (int i = 0; i < N; i++)
    c.push_back(m[i] * (m_inv[i] % n[i]));
  vector<int> ac(N);
  transform(a.begin(), a.end(), c.begin(), ac.begin(), 
    multiplies<int>());
  int A = accumulate(ac.begin(), ac.end(), 0) % M;
  return A;
}
//a, N must be coprime
int GetMODInverse(int a, int N)
{
  auto dxy = ExtEuclidGCD(a, N);
  int inv = dxy.x;
  if (inv < 0)
    inv += N;
  return inv;
}
Clsdxy ExtEuclidGCD(int a, int b)
{
  if (b != 0)
  {
    auto dxyp = ExtEuclidGCD(b, a % b);
    Clsdxy dxy(dxyp.d, dxyp.y, dxyp.x - a / b * dxyp.y);
    return dxy;
  }
  else
    return Clsdxy(a, 1, 0);
}
} //namespace NS_ChnRA
using namespace NS_ChnRA;
void TestChnRA()
{
  vector<vector<int>> a = {
    {2, 3}, //CLRS, Sec. 31.5, example; 42
    {4, 5}, //CLRS, Sec. 31.5, exercise 1; 49
    //https://www.directknowledge.com/
    //chinese-remainder-theorem/
    {15, 16}, //96
    //https://www.directknowledge.com/
    //chinese-remainder-theorem/
    {3, 2, 4}, //158
    {1, 2, 3}, //CLRS, Sec. 31.5, exercise 2; 10
    {2, 3, 2}, //《孙子算经》第二十六题; 23
    //https://www.britannica.com/science/
    //Chinese-remainder-theorem
    {0, 6, 10}, //370
    //https://brilliant.org/wiki/
    //chinese-remainder-theorem/
    {1, 4, 6}, //34;
  };
  vector<vector<int>> n = {
    {5, 13}, //CLRS, Sec. 31.5, example
    {5, 11}, //CLRS, Sec. 31.5, exercise 1
    //https://www.directknowledge.com/
    //chinese-remainder-theorem/
    {27, 20}, //96
    //https://www.directknowledge.com/
    //chinese-remainder-theorem/
    {5, 6, 7}, //158
    {9, 8, 7}, //CLRS, Sec. 31.5, exercise 2
    {3, 5, 7}, //《孙子算经》第二十六题
    //https://www.britannica.com/science/
    //Chinese-remainder-theorem;
    {5, 7, 12}, //370
    //https://brilliant.org/wiki/
    //chinese-remainder-theorem/
    {3, 5, 7}, //34;
  };
  int N = a.size();
  for (int i = 0; i < N; i++) {
    printf("%2d: \n", i + 1);
    printf(" a:");
    for (int j = 0; j < a[i].size(); j++) {
      printf("%3d", a[i][j]);
    }
    printf("\n");
    printf(" n:");
    for (int j = 0; j < n[i].size(); j++) {
      printf("%3d", n[i][j]);
    }
    printf("\n");
    int A = ChnRA(a[i], n[i]);
    printf(" A: %d\n", A);
    printf("\n");
  }
}
void TestMODInverse()
{
#define N 3
  int aN[N][2] = {
    { 128, 423 }, //d=1, inv=347
    { 406, 555 }, //d=1, inv=406
    { 220, 1323 }, //d=1, inv=439
  };
  for (int i = 0; i < N; i++) {
    int inv = GetMODInverse(aN[i][0], aN[i][1]);
    printf("%2d: a=%d, N=%d, inv(a) = %d (mod N)\n", 
      i, aN[i][0], aN[i][1], inv);
  }
}