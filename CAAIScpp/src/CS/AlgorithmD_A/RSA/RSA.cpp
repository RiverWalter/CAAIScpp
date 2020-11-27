#include <stdio.h>
#include <vector>
#include <random>
#include <algorithm>
namespace NS_RSA {
using namespace std;
#define MRPT_S 3
random_device rdev{};
default_random_engine e{ rdev() };
int Get_p();
int Get_q(int p);
void Get_ed(int phi_n, int& e, int& d);
int RS4ME(int a, int b, int n);
bool MRPT(int n, int s);
vector<int> GetUniqueRandNums(int low, int high, int n);
bool Witness(int a, int n);
int Get_t(int n_1);
vector<int> GetBits(int b);
struct Clsdxy {
    int d; int x; int y;
    Clsdxy(int ad, int ax, int ay) :
        d(ad), x(ax), y(ay) {}
};
Clsdxy ExtEuclidGCD(int a, int b);
void RSA(int m)
{
    int p = Get_p();
    int q = Get_q(p);
    int n = p * q;
    int phi_n = (p - 1) * (q - 1);
    int e = 0, d = 0;
    Get_ed(phi_n, e, d);
    int c = RS4ME(m, e, n);
    int dc = RS4ME(c, d, n);
    printf("RSA demonstration:\n");
    printf("\tp = %d, q = %d\n", p, q);
    printf("\tn = %d, phi(n) = %d\n", n, phi_n);
    printf("\te = %d, d = %d\n", e, d);
    printf("\tm = %d, c = %d, dc = %d\n", m, c, dc);
    printf("\n");
}
int Get_p()
{
    uniform_int_distribution<int> d{ 3, 31 };
    int p = d(e);
    if (p % 2 == 0) p++;
    while (!MRPT(p, MRPT_S)) p += 2;
    return p;
}
int Get_q(int p)
{
    //ceiling with pure integer operations
    int q = (256 + p - 1) / p;
    if (q % 2 == 0) q++;
    while (q == p || !MRPT(q, MRPT_S)) q += 2;
    return q;
}
void Get_ed(int phi_n, int& e, int& d)
{
    e = 3;
    auto dxy = ExtEuclidGCD(e, phi_n);
    while (dxy.d != 1)
    {
        e += 2;
        dxy = ExtEuclidGCD(e, phi_n);
    }
    d = dxy.x;
    if (d < 0)
        d += phi_n;
}
bool MRPT(int n, int s)
{
    auto v = GetUniqueRandNums(2, n - 2, s);
    for (auto a: v)
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
        v.push_back(low);
        return v;
    }
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
} //namespace NS_RSA
using namespace NS_RSA;
void TestRSA(int mx = 0, int my = 20)
{
    for (int m = mx; m < my; m++)
        RSA(m);
}
