//RandomNumberTest.cpp
#include "../../include/headers.h"
#include <random>

void RandRangeTest(int n, int low, int high)
{
	printf("%d到%d间的%d个随机数\n", low, high, n);
	for (int i=0; i<n; i++)
		printf("%3d:%d\n",i+1, RandRange(low, high));
}
void RandRangeSetTest(int n)
{
	set<int> randSet;
	set<int>::iterator it, it1;
	RandRangeSet(n, 1, 10, randSet);
	printf("生成[1,10]间的%d个随机数存放在集合中：\n", n);
	for (it = randSet.begin(); it != randSet.end(); it++)
		printf("%d ", *it);
	printf("\n");
	it = randSet.begin();
	it1 = randSet.find(*it);
	printf("%d in set: %d\n", *it, it1 != randSet.end());
	it1 = randSet.find(100);
	printf("%d in set: %d\n", 100, it1 != randSet.end());
}
void RandDblTest(int n)
{
	printf("范围在[0,1)间的%d个随机数\n", n);
	for (int i=0; i<n; i++)
		printf("%3d:%lf\n",i+1, RandDbl());
}
void RandTest(int n)
{
	printf("范围在[0,%d]间的%d个随机数\n", RAND_MAX, n);
	for (int i=0; i<n; i++)
		printf("%3d:%d\n",i+1, rand());
}
void RandTest0(int seed = 1)
{
	srand(seed);
	printf("RAND_MAX: %d\n", RAND_MAX);
	for (int i = 0; i < 10; i++)
		printf("%d:%d,", i + 1, rand());
	printf("\n\n");
}
int RandTest1()
{
	static int seed = 23;
	seed = ((long long)214013 * seed + 2531011) % ((long long)1 << 31);
	int r = seed >> 16;
	//printf("seed: %d, s1: %ld, r: %d, sizeof(int): %d, sizeof(long): %d\n", seed, s1, r, sizeof(int), sizeof(long));
	//seed = s1;
	return r;
}
void RandTest1a()
{
	for (int i = 0; i < 10; i++)
		printf("%3d:%d\n", i + 1, RandTest1());
}
void MCRandTest1()
{
	random_device d;
	minstd_rand0 r;
	//r.seed(d());
	for (int i = 0; i < 10; i++)
		printf("%3d:%u\n", i + 1, r());
	r.seed(1);
	for (int i = 0; i < 10; i++)
		printf("%3d:%u\n", i + 1, r());
}
void MCRandTest2()
{
	linear_congruential_engine<uint_fast32_t, 214013, 2531011, 2147483648> ms;
	for (int i = 0; i < 10; i++)
		printf("%3d:%u\n", i + 1, ms()>>16);

}
void TestIntSize()
{
	printf("size: int:%d, long:%d, long long:%d, 1L:%d\n", 
		sizeof(int), sizeof(long), sizeof(long long), sizeof(1LL));
}
void CompromiseMSRand(int r1, int r2)
{
	int seed1 = r1 << 16, seed2, seed3, r, r3, r4;
	for (int i = 0; i <= 0xFFFF; i++) {
		seed2 = (214013LL * seed1++ + 2531011) % (1LL << 31);
		r = seed2 >> 16;
		if (r == r2) {
			seed3 = (214013LL * seed2 + 2531011) % (1LL << 31);
			srand(seed3); r3 = rand(); r4 = rand();
			printf("Compromised: %d, %d, %d, %d\n", r1, r2, r3, r4);
		}
	}
}
void CompromiseMSRand3(int r1, int r2, int r3)
{
	int seed1 = r1 << 16, seed2, seed3, r, r4, r5;
	for (int i = 0; i <= 0xFFFF; i++) {
		seed2 = (214013LL * seed1++ + 2531011) % (1LL << 31);
		r = seed2 >> 16;
		if (r == r2) {
			seed3 = (214013LL * seed2 + 2531011) % (1LL << 31);
			if ((seed3 >> 16) == r3) break;
		}
	}
	srand(seed3); r4 = rand(); r5 = rand();
	printf("Compromised: seed3=%d, r3=%d, r4=%d\n", seed3, r4, r5);
}

void CompromiseRandT(int r1, int r2)
{
	printf("r1:%d, r2:%d\n", r1, r2);
	int seed1 = r1 << 16, seed2, r;
	for (int i = 0; i <= 0xFFFF; i++)
	{
		seed2 = (214013LL * seed1++ + 2531011) % (1LL << 31);
		r = seed2 >> 16;
		if (r == r2)
			break;
		else r = -1;
	}
	if (r == -1)
		printf("Not compromised!\n");
	else {
		srand(1);
		printf("1: %d,%d,%d\n", rand(), rand(), rand());
		int seed2a = (214013LL * (seed1 - 1) + 2531011) % (1LL << 31);
		srand(seed1 - 1);
		//r = seed3 >> 16;
		printf("Compromised! r3:%d, r3a:%d, r3b:%d, %d\n", rand(), rand(), rand(), seed2a >> 16);
		srand(seed2a);
		printf("Seed2a: %d r:%d, seed2:%d\n", seed2a, rand(), seed2);
	}
}
int RandBSDLibc()
{
	static int seed = 5;
	seed = (1103515245LL * seed + 12345) & ((1LL << 31) - 1);
	return seed;
}
struct Clsdxy {
	long long d, x, y;
	Clsdxy(long long ad, long long ax, long long ay) :
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
long long GetMODInverse(long long a, long long N)
{
	auto dxy = ExtEuclidGCD(a, N);
	long long inv = dxy.x;
	if (inv < 0)
		inv += N;
	return inv;
}
long long EuclidGCDLL(long long a, long long b)
{
	long long r;
	a = abs(a); b = abs(b);
	while (b) {
		r = a % b; a = b; b = r;
	}
	return a;
}
long long Geta0(long long m, long long r1, long long r2, long long r3)
{
	long long s1 = r1 - r2, s2 = r2 - r3;
	if (s1 < 0) {
		s1 = -s1; s2 = -s2;
	}
	if (s2 < 0)
		s2 = m + s2;
	long long t = GetMODInverse(s1, m);
	long long a = t * s2 % m;
	//printf("a: %lld, m:%lld, m-a:%lld\n", a, m, m - a);
	return a;
}
long long Geta(long long m, long long t1, long long t2)
{
	if (t1 < 0) {
		t1 = -t1; t2 = -t2;
	}
	if (t2 < 0)
		t2 = m + t2;
	long long t = GetMODInverse(t1, m);
	long long a = t * t2 % m;
	printf("a: %lld, m:%lld, m-a:%lld\n", a, m, m - a);
	return a;
}
void CompromiseRandBSDLibc()
{
	long long r1 = RandBSDLibc(), r2 = RandBSDLibc(),
		r3 = RandBSDLibc(), r4, m, gcd, det, a = 1, c, s1, s2, t;
	int n = -1;
	//get m
	while (n < 3) {
		r4 = RandBSDLibc();
		if (n == -1) {
			m = (r2 * r4 - r3 * r3) - (r1 * r4 - r2 * r3) +
				(r1 * r3 - r2 * r2);
			n = 0;
		} else {
			det = (r2 * r4 - r3 * r3) - (r1 * r4 - r2 * r3) +
				(r1 * r3 - r2 * r2);
			gcd = EuclidGCDLL(m, det);
			if (m == gcd) n++;
			else n = 0;
			m = gcd;
		}
		if (n < 3) {
			r1 = r2; r2 = r3; r3 = r4;
		}
	}
	a = Geta0(m, r1, r2, r3);
	c = (r1 * a - r2) % m;
	printf("m:%lld, a:%lld, c:%lld, m-a:%lld, m-c:%lld\n", m, a, c, m - a, m - c); 
	long long x = (a * r3 + c) % m;
	printf("x:%lld, r4:%lld\n", x, r4);
	a = Geta0(m, r2, r3, r4);
	c = (r2 * a - r3) % m;
	printf("m:%lld, a:%lld, c:%lld, m-a:%lld, m-c:%lld\n", m, a, c, m - a, m - c);
	x = (a * r1 + c) % m;
	printf("x:%lld, r1:%lld\n", x, r2);
	a = m - a;
	c = (r2 * a - r3) % m;
	printf("m:%lld, a:%lld, c:%lld, m-a:%lld, m-c:%lld\n", m, a, c, m - a, m - c);
	x = (a * r1 + c) % m;
	printf("x:%lld, r1:%lld\n", x, r2);
	//printf("m:%lld, a:%lld, c:%lld, m-a:%lld, m-c:%lld\n", m, a, c, m - a, m - c);

	//Geta(m, r2, r3, r4);
	//Geta(m, r3, r4, RandBSDLibc());
	//get a, c
	/*s1 = r2 - r3; s2 = r3 - r4;
	if (s1 < 0) {
		s1 = -s1; s2 = -s2;
	}
	if (s2 < 0)
		s2 = m + s2;
	//while (s1 * a % m != s2) a++;
	t = GetMODInverse(s1, m);
	printf("t:%lld, s1:%lld, m:%lld, t*s1:%lld, GCD(s1,m):%lld\n", t, s1, m, t * s1 % m, EuclidGCDLL(s1, m));
	a = t * s2 % m;
	printf("a:%lld, a*s1 mod m:%lld, s2:%lld,%lld, m-a:%lld\n", a, a * s1 % m, s2, a * s1 % m + s2, m - a);
	c = (r3 * a - r4) % m;
	printf("m:%lld, a:%lld, c:%lld, m-c:%lld\n", m, a, c, m - c);*/
}
void CompromiseRandBSDLibcT3()
{
	long long r1 = RandBSDLibc(), r2 = RandBSDLibc(),
		r3 = RandBSDLibc(), r4, m, gcd, det, a = 1, c, s1, s2;
	int n = -1;
	while (n < 3) {
		r4 = RandBSDLibc();
		printf("r:%lld,%lld,%lld,%lld\n", r1, r2, r3, r4);
		if (n == -1) {
			m = (r2 * r4 - r3 * r3) - (r1 * r4 - r2 * r3) +
				(r1 * r3 - r2 * r2);
			n = 0;
		}
		else {
			det = (r2 * r4 - r3 * r3) - (r1 * r4 - r2 * r3) +
				(r1 * r3 - r2 * r2);
			gcd = EuclidGCDLL(m, det);
			printf("m:%lld, det:%lld, gcd:%lld\n", m, det, gcd);
			if (m == gcd) n++;
			else n = 0;
			m = gcd;
		}
		if (n < 3) {
			r1 = r2; r2 = r3; r3 = r4;
		}
	}
	//get a
	s1 = r2 - r3; s2 = r3 - r4;
	if (s1 < 0) {
		s1 = -s1; s2 = -s2;
	}
	if (s2 < 0)
		s2 = m + s2;
	while (s1 * a % m != s2) a++;
	c = (r3 * a - r4) % m;
	printf("a:%lld, c:%lld, m-c:%lld\n", a, c, m - c);
}
void CompromiseRandBSDLibcT()
{
	long long s1 = RandBSDLibc(), s2 = RandBSDLibc(); 
	long long t1 = s2 - s1;
	s1 = s2; s2 = RandBSDLibc();
	long long t2 = s2 - s1;
	s1 = s2; s2 = RandBSDLibc();
	long long t3 = s2 - s1;
	long long m = t3 * t1 - t2 * t2, m1, gcd, a, c;
	int n = 0, k = 0;
	while (n < 3) {
		k++;
		s1 = s2; s2 = RandBSDLibc();
		t1 = t2; t2 = t3; t3 = s2 - s1;
		m1 = t3 * t1 - t2 * t2;
		gcd = EuclidGCDLL(m, m1);
		if (m == gcd) n++;
		else n = 0;
		m = gcd;
		printf("k:%d,m:%lld\n", k, m);
	}
	a = Geta(m, t1, t2);
	c = (s1 * a - s2) % m;
	printf("c:%lld,m-c:%lld\n", c, m - c);
	Geta(m, t2, t3);
	c = (s1 * a - s2) % m;
	printf("c:%lld,m-c:%lld\n", c, m - c);
}
void TestRandBSDLibc()
{
	for (int i = 0; i < 10; i++)
		printf("%d:%d, ", i + 1, RandBSDLibc());
	printf("\n");
}
int JavaRand()
{
	static long long seed = 1LL;
	long long a = 0x5DEECE66DL, c = 0xBLL;
	seed = (seed * a + c) & ((1LL << 48) - 1);
	long long r = seed >> 16;
	return (int)r;
}
void TestJavaRand(int n = 5)
{
	for (int i = 0; i < n; i++)
		printf("%d:%d, ", i + 1, JavaRand());
	printf("\n");
}
void RandTest()
{
	//41、18467、6334、26500、19169
	//int n = 31;
	//printf("2^%d:%lld\n", n, 1LL << n);
	//RandTest0(3);
	//seed 1: 1:41,2:18467,3:6334,4:26500,5:19169,6:15724,7:11478,8:29358,9:26962,10:24464
	//seed 3: 1:48,2:7196,3:9294,4:9091,5:7031,6:23577,7:17702,8:23503,9:27217,10:12168

	//RandTest1a();
	//MCRandTest2();
	//TestIntSize();
	//CompromiseMSRand(41, 18467);
	//CompromiseMSRand3(41, 18467, 6334);
	//CompromiseMSRand3(15724, 11478, 29358);
	//CompromiseMSRand3(48, 7196, 9294);
	//CompromiseMSRand3(23577, 17702, 23503);
	//TestRandBSDLibc();
	//CompromiseRandBSDLibc();
	//CompromiseRandBSDLibcT();
	TestJavaRand();
}