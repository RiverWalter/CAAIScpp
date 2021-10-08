#include <stdio.h>
#include <cmath>
void LiuHuiPi(int n)
{
  int i = 6;
  double an = 1, a2n, pi;
  while (i <= n)
  {
    pi = 1.0 / 2 * i * an;
    printf("n=%d, pi=%f\n", i, pi);
    a2n = sqrt(2 - sqrt(4 - an * an));
    an = a2n;
    i *= 2;
  }
}
void TestLiuhui()
{
  LiuHuiPi(3072);
}