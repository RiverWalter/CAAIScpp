#include <stdio.h>
namespace NS_ExtEuclidGCD {
using namespace std;
struct Clsdxy {
  int d; int x; int y;
  Clsdxy(int ad, int ax, int ay) :
    d(ad), x(ax), y(ay) {}
};
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
} //namespace NS_ExtEuclidGCD
using namespace NS_ExtEuclidGCD;
void TestExtEuclidGCD()
{
#define N 22
  int ab[N][2] = {
    //Wikipedia
    { 252, 105 },
    //Introduction to Algorithms
    { 30, 21 },
    { 99, 78 },
    //https://www.calculatorsoup.com/
    { 816, 2260 },
    //Algorithms, S. Dasgupta
    { 1035, 759 },
    //http://everything.explained.today
    { 1386, 3213 },
    //https://www.cs.cornell.edu
    //Example of Extended Euclidean Algorithm
    { 84, 33 },
    { 432, 95256 },
    //https://www.rit.edu, The Euclidean Algorithm
    { 12, 18 },
    { 24, 54 },
    { 168, 180 },
    { 244, 354 },
    { 128, 423 }, //d=1
    { 406, 555 }, //d=1
    { 220, 1323 }, //d=1
    { 3846, 153 },
    { 1424, 3084 },
    { 2415, 3289 },
    { 4278, 8602 },
    //Other
    { 72, 84 },
    { 102, 138 },
    { 26187, 1533 }
  };
  for (int i = 0; i < N; i++) {
    int a = ab[i][0];
    int b = ab[i][1];
    auto dxy = ExtEuclidGCD(a, b);
    printf("%2d: %d = %d*%d + %d*%d\n", i,
      dxy.d, a, dxy.x, b, dxy.y);
  }
}