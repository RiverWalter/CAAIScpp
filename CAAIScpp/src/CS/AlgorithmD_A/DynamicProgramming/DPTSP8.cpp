#include <stdio.h>
#include <vector>
#include <set>
#include <map>
using namespace std;
namespace NS_DPTSP8 {
#define INF (INT_MAX / 2)
void DPTSP(const vector<vector<int>>& w);
void Initialization(const vector<vector<int>>& w);
void Output();
//List of subsets in size 0-n 
static vector<vector<set<int>>> Subsets;
//subp_t: type of a subproblem, (subset, end city)
typedef pair<set<int>, int> subp_t;
//subpsol_t: type of subproblem solution
//(subproblem, (previous city, optimal distance))
typedef pair<subp_t, pair<int, int>> subpsol_t;
//Cost matrix of subpsol_t
static map<subp_t, pair<int, int>> Cost;
static int N, n; //n = N - 1
static int OptimalDist;
static vector<int> OptimalTour;
void DPTSPCaller(const vector<vector<int>> &w)
{
    Initialization(w);
    DPTSP(w);
    Output();
}
void DPTSP(const vector<vector<int>> &w)
{
    //Stage 1: Dynamic programming
    //i: subset size
    for (int i = 2; i <= n; i++)
    {
        //ss_is: subsets of size i
        vector<set<int>> ss_is;
        //ss_i_1: a subset of size i - 1
        for (auto &ss_i_1 : Subsets[i - 1])
        {
            //c: city to be added to subset ss_i_1
            for (int c = *prev(ss_i_1.end()) + 1; c <= n; c++)
            {
                //ss_i: a new subset of size i
                auto ss_i = ss_i_1;
                ss_i.insert(c);
                ss_is.push_back(ss_i);
                //let each city e in ss_i be the end city
                //i.e. let (ss_i, e) be a subproblem
                for (auto e : ss_i)
                {
                    //ss_i_e: a subset of ss_i with city e excluded
                    auto ss_i_e = ss_i;
                    ss_i_e.erase(e);
                    //p, d temporary optimal distance and previous city
                    int p = -1, d = INF;
                    //traverse ss_i_e with each of its city as previous of e
                    for (auto pc = ss_i_e.cbegin(); pc != ss_i_e.cend(); pc++)
                    {
                        int dx = Cost[subp_t(ss_i_e, *pc)].second + w[*pc][e];
                        if (dx < d)
                        {
                            d = dx;
                            p = *pc;
                        }
                    }
                    Cost.insert(subpsol_t(subp_t(ss_i, e), pair<int, int>(p, d)));
                } //for e
            } //for c
        } //for ss_i_1
        Subsets.push_back(ss_is);
    } //for i
    //DP Completed
    //Stage 2: Search the last city in an optimal tour
    //sn: the complete set of 1 to n
    auto sn = Subsets[n][0]; 
    int d = INF, c = -1;
    for (int i = 1; i <= n; i++)
    {
        int dx = Cost[subp_t(sn, i)].second + w[i][0];
        if (dx < d)
        {
            d = dx;
            c = i;
        }
    }
    OptimalDist = d;
    //Stage 3: Get the optimal tour by tracing back
    OptimalTour.insert(OptimalTour.begin(), c);
    while (c != 0)
    {
        auto solution = Cost[subp_t(sn, c)];
        sn.erase(c);
        c = solution.first;
        OptimalTour.insert(OptimalTour.begin(), c);
    }
}
void Initialization(const vector<vector<int>>& w)
{
    N = w.size();
    n = N - 1;
    OptimalTour.clear();
    Cost.clear();
    Subsets.clear();
    Subsets.push_back(vector<set<int>>());
    vector<set<int>> s_1;
    for (int i = 1; i <= n; i++)
    {
        s_1.push_back(set<int>({ i }));
        Cost.insert(subpsol_t(subp_t({ i }, i), pair<int, int>(0, w[0][i])));
    }
    Subsets.push_back(s_1);
}
void Output()
{
    printf("Optimal dist: %d\n", OptimalDist);
    printf("Optimal tour: ");
    for (auto i : OptimalTour)
        printf("%d-", i);
    printf("0\n");
}
void OutputW(vector<vector<int>> const& w)
{
    printf("The distance matrix:\n");
    printf("%3c", ' ');
    for (int i = 0; i < w.size(); i++)
        printf("%3d", i);
    printf("\n");
    for (int i = 0; i < w.size(); i++)
    {
        printf("%3d", i);
        for (int j = 0; j < w.size(); j++)
            if (w[i][j] == INF)
                printf("%3c", '*');
            else
                printf("%3d", w[i][j]);
        printf("\n");
    }
}
} //namespace NS_DPTSP8
using namespace NS_DPTSP8;
void TestDPTSP8()
{
    vector<vector<vector<int>>> w =
    {
        //Ö£×Úºº, P248
        //Optimal dist: 65
        //Optimal path: 0-1,1-2,2-4,4-3,3-0
        //Depth : 4, LastNode : M, QLength: 3
        { //0
            { INF,  25,  41,  32,  28 },
            {   5, INF,  18,  31,  26 },
            {  20,  16, INF,   7,   1 },
            {  10,  51,  25, INF,   6 },
            {  23,   9,	  7,  11, INF }
        },
        //Optimal dist: 11
        //Optimal path1: 0-4,4-2,2-1,1-3,3-0
        //Optimal path2: 0-3,3-2,2-1,1-4,4-0
        //Depth: 4, LastNode: K, QLength: 3
        { //1
            { INF,   2,   2,   3,   1 },
            {   2, INF,   4,   4,   2 },
            {   1,	 1, INF,   5,   5 },
            {   3,	 4,	  4, INF,   4 },
            {   1,	 5,	  2,   4, INF }
        },
        //www.techiedelight.com
        //Travelling Salesman Problem using Branch and Bound
        //Optimal dist: 34
        //Optimal path: 0-2,2-3,3-1,1-4,4-0
        //Depth: 3, LastNode: I, QLength: 4
        { //2
            { INF,  10,   8,   9,   7 },
            {  10, INF,  10,   5,   6 },
            {   8,	10, INF,   8,   9 },
            {   9,	 5,	  8, INF,   6 },
            {   7,	 6,	  9,   6, INF }
        },
        //Foundations of Algorithms, 5th Ed., Sec. 6.2
        //R.E. Neapolitan
        //Optimal dist: 30
        //Optimal path: 0-3,3-4,4-1,1-2,2-0
        //Depth: 4, LastNode: M, QLength: 4
        { //3
            { INF,  14,   4,  10,  20 },
            {  14, INF,   7,   8,   7 },
            {   4,   5, INF,   7,  16 },
            {  11,   7,   9, INF,   2 },
            {  18,   7,  17,   4, INF }
        },
        //Data Structures & Algorithm Analysis in C++ (V3.2)
        //C. Shaffer, Chap. 17, p. 554
        //Optimal dist: 9
        //Optimal path: 0-1,1-4,4-3,3-2,2-0
        //Depth: 3, LastNode: K, QLength: 5
        { //4
            { INF,   2,   3,   8,   3 },
            {   2, INF,   6,   1,   2 },
            {   3,   6, INF,   1,   4 },
            {   8,   1,   1, INF,   1 },
            {   3,   2,   4,   1, INF }
        },
        //The Traveling Salesman problem
        //Amanur Rahman Saiyed, Indiana State University
        //April 11, 2012
        //Optimal dist: 28
        //Optimal path: 0-3,3-4,4-1,1-2,2-0
        //Depth: 3, LastNode: G, QLength: 3
        { //5
            { INF,  13,   5,   2,  21 },
            {  13, INF,   9,   4,   9 },
            {   5,   9, INF,   9,  21 },
            {   2,   4,   9, INF,   7 },
            {   4,   5,  21,   7, INF }
        },
        //https://www.slideshare.net/jeanepaguio/graph-theory-27567865
        //Optimal dist: 20
        //Optimal path1: 0-3,3-2,2-4,4-1,1-0
        //Optimal path2: 0-1,1-4,4-3,3-2,2-0
        //Depth: 4, LastNode: M, QLength: 4
        { //6
            { INF,   3,   8,   4,   7 },
            {   3, INF,  10,   9,   2 },
            {   8,  10, INF,   6,   5 },
            {   4,   9,   6, INF,   1 },
            {   7,   2,   5,   1, INF }
        },
        //08U-03
        //Optimal dist : 15
        //Optimal tour : 0-4-5-7-6-3-1-2-0
        {
            { INF,   3,   1,   3,   2, INF, INF, INF },
            {   3, INF,   1,   2,   4, INF, INF, INF },
            {   1,   1, INF, INF, INF,   3, INF, INF },
            {   3,   2, INF, INF,   4, INF,   2,   3 },
            {   2,   4, INF,   4, INF,   1, INF,   3 },
            { INF, INF,   3, INF,   1, INF, INF,   4 },
            { INF, INF, INF,   2, INF, INF, INF,   2 },
            { INF, INF, INF,   3,   3,   4,   2, INF },
        },
        //09U-02
        //Optimal dist: 61
        //Optimal tour: 0-7-8-6-5-4-3-2-1-0
        {
            { INF,   4, INF, INF, INF, INF, INF,   8, INF },
            {   4, INF,   8, INF, INF, INF, INF,  11, INF },
            { INF,   8, INF,   7, INF,   4, INF, INF,   2 },
            { INF, INF,	  7, INF,   9,  14, INF, INF, INF },
            { INF, INF, INF,   9, INF,  10, INF, INF, INF },
            { INF, INF,	  4,  14,  10, INF,	  2, INF, INF },
            { INF, INF, INF, INF, INF,   2, INF,   1,   6 },
            {   8,  11, INF, INF, INF, INF,	  1, INF,   7 },
            { INF, INF,	  2, INF, INF, INF,	  6,   7, INF }
        },
    };
    printf("TestDPTSP is working ...\n");
    int n = w.size();
    //int n = 1;
    for (int i = 0; i < n; i++) {
        printf("No: %d\n", i);
        OutputW(w[i]);
        DPTSPCaller(w[i]);
    }
}
