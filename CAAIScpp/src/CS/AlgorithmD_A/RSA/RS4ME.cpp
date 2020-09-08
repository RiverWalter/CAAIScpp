#include <stdio.h>
#include <vector>
namespace NS_RS4ME {
using namespace std;
vector<int> GetBits(int b);
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
} //namespace NS_RS4ME
using namespace NS_RS4ME;
void TestRS4ME()
{
  vector<vector<int>> abn = {
    //CLRS, Sec. 31.6, example; p956-957
    {7, 560, 561}, //1
    //http://www.tricki.org/article/
    //To_work_out_powers_mod_n_use_repeated_squaring
    {3, 37, 53}, //32
    //https://www.geeksforgeeks.org/
    //modular-exponentiation-recursive/
    {2312, 3434, 6789}, //6343
    //https://mathlesstraveled.com/
    //2018/08/13/modular-exponentiation/
    {7, 10, 11}, //1
    //https://math.stackexchange.com/questions/
    //2204627/repeated-squaring-techniques
    {3, 383, 7}, //5
    //https://www.khanacademy.org/computing/
    //computer-science/cryptography/modarithmetic/
    //a/modular-exponentiation
    {2, 50, 13}, //4
    {2, 40, 13}, //3
    {2, 90, 13}, //12
    {7, 256, 13}, //9
  };
  int N = abn.size();
  for (int i = 0; i < N; i++) {
    printf("%2d: \n", i + 1);
    int a = abn[i][0];
    int b = abn[i][1];
    int n = abn[i][2];
    printf(" a=%d, b=%d, n=%d.\n", a, b, n);
    int d = RS4ME(a, b, n);
    printf(" %d^%d mod %d = %d\n\n", a, b, n, d);
  }
}
