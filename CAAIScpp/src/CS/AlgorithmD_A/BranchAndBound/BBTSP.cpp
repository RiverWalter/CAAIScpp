#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <cstring>
#include <climits>
#include <tuple>
#include <random>
using namespace std;
namespace NS_BBTSP {
#define INF INT_MAX
static int OptimalDist = INF;
static vector<pair<int , int>> OptimalPath;
struct ClsDkl {
    int D; int K; int L;
    ClsDkl() : D(-1), K(0), L(0) {}
    void Set(int d, int k, int l) {
        D = d; K = k; L = l;
    }
};
struct ClsNode
{
    vector<int> RowIdx;
    vector<int> ColIdx;
    vector<pair<int, int>> Path;
    vector<vector<int>> W;
    int n, Bound;
    ClsNode() : n(0), Bound(0) {}
    ClsNode(vector<vector<int>> w) : ClsNode()
    {
        W = w;
        n = W.size();
        for (int i = 0; i < n; i++)
        {
            RowIdx.push_back(i);
            ColIdx.push_back(i);
        }
        Bound = Reduce();
    }
    vector<int> RowReduction();
    vector<int> ColReduction();
    int Reduce();
    ClsDkl GetMaxD();
    ClsNode GenLChild(int k, int l);
    ClsNode GenRChild(int k, int l);
private:
    int getd(int r, int c);
};
void BBTSP(vector<vector<int>> w)
{
    auto comp = [](const ClsNode& lhs, const ClsNode& rhs)
    { return lhs.Bound > rhs.Bound; };
    priority_queue < ClsNode, vector<ClsNode>,
        decltype(comp) > PQ(comp);
    ClsNode root(w);
    PQ.push(root);
    while (!PQ.empty())
    {
        auto minNode = PQ.top();
        PQ.pop();
        if (minNode.Bound >= OptimalDist)
            continue;
        auto maxDkl = minNode.GetMaxD();
        auto left = minNode.GenLChild(maxDkl.K, maxDkl.L);
        if (left.Bound < OptimalDist)
        {
            if (left.n == 2)
            {
                OptimalDist = left.Bound;
                OptimalPath = left.Path;
            }
            else
                PQ.push(left);
        }
        auto right = minNode.GenRChild(maxDkl.K, maxDkl.L);
        if (right.Bound < OptimalDist)
            PQ.push(right);
    }
}
vector<int> ClsNode::RowReduction()
{
    vector<int> row(n, INF);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (W[i][j] < row[i])
                row[i] = W[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (W[i][j] != INF && row[i] != INF)
                W[i][j] -= row[i];
    return row;
}
vector<int> ClsNode::ColReduction()
{
    vector<int> col(n, INF);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (W[i][j] < col[j])
                col[j] = W[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (W[i][j] != INF && col[j] != INF)
                W[i][j] -= col[j];
    return col;
}
int ClsNode::Reduce()
{
    auto row = RowReduction();
    auto col = ColReduction();
    int bound = 0;
    for (int i = 0; i < n; i++)
    {
        bound += (row[i] != INF) ? row[i] : 0;
        bound += (col[i] != INF) ? col[i] : 0;
    }
    return bound;
}
ClsDkl ClsNode::GetMaxD()
{
    ClsDkl t;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (W[i][j] == 0)
            {
                int d = getd(i, j);
                if (d > t.D)
                    t.Set(d, i, j);
            }
    return t;
}
int ClsNode::getd(int r, int c)
{
    int rmin = INF;
    for (int i = 0; i < n; i++)
        if (i != c && W[r][i] < rmin)
            rmin = W[r][i];
    int cmin = INF;
    for (int i = 0; i < n; i++)
        if (i != r && W[i][c] < cmin)
            cmin = W[i][c];
    return rmin + cmin;
}
ClsNode ClsNode::GenLChild(int k, int l)
{
    auto node = *this;
    auto r = find(node.RowIdx.begin(), node.RowIdx.end(), 
        node.ColIdx[l]);
    auto c = find(node.ColIdx.begin(), node.ColIdx.end(), 
        node.RowIdx[k]);
    if (r != node.RowIdx.end() && c != node.ColIdx.end())
        node.W[r - node.RowIdx.begin()]
            [c - node.ColIdx.begin()] = INF;
    node.Path.push_back(make_pair(node.RowIdx[k], 
        node.ColIdx[l]));
    node.RowIdx.erase(node.RowIdx.begin() + k);
    node.ColIdx.erase(node.ColIdx.begin() + l);
    node.W.erase(node.W.begin() + k);
    for (auto& x : node.W)
        x.erase(x.begin() + l);
    node.n--;
    if (node.n > 2)
        node.Bound += node.Reduce();
    else
    {
        int DMain = INF;
        if (node.W[0][0] != INF && node.W[1][1] != INF)
            DMain = node.W[0][0] + node.W[1][1];
        int DAux = INF;
        if (node.W[0][1] != INF && node.W[1][0] != INF)
            DAux = node.W[0][1] + node.W[1][0];
        if (DMain < DAux)
        {
            node.Path.push_back({ node.RowIdx[0], 
                node.ColIdx[0] });
            node.Path.push_back({ node.RowIdx[1], 
                node.ColIdx[1] });
            node.Bound += DMain;
        }
        else
        {
            node.Path.push_back({ node.RowIdx[1], 
                node.ColIdx[0] });
            node.Path.push_back({ node.RowIdx[0], 
                node.ColIdx[1] });
            node.Bound += DAux;
        }
    }
    return node;
}
ClsNode ClsNode::GenRChild(int k, int l)
{
    auto node = *this;
    node.W[k][l] = INF;
    int minR = INF;
    for (auto& x : node.W[k])
        if (x < minR)
            minR = x;
    for (auto& x : node.W[k])
        if (x != INF && minR != INF)
            x -= minR;
    int minC = INF;
    for (auto& x : node.W)
        if (x[l] < minC)
            minC = x[l];
    for (auto& x : node.W)
        if (x[l] != INF && minR != INF)
            x[l] -= minC;
    node.Bound += minR + minC;
    return node;
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
} //namespace NS_BBTSP
using namespace NS_BBTSP;
void TestBBTSP()
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
        //Optimal path: 0-3,3-2,2-1,1-4,4-0
        //Depth: 4, LastNode: K, QLength: 3
        { //1
            { INF,   2,   2,   3,   1 },
            {   2, INF,   4,   4,   2 },
            {   1,	 1, INF,   5,   5 },
            {   3,	 4,	  4, INF,   4 },
            {   1,	 5,	  2,   4, INF }
        },
        //www.techiedelight.com
        //TSP using Branch and Bound
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
        //Data Structures & Algorithm Analysis in C++
        //C. Shaffer, Chap. 17, p. 554, (V3.2)
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
        //https://www.slideshare.net/jeanepaguio/
        //graph-theory-27567865
        //Optimal dist: 20
        //Optimal path: 0-1,1-4,4-3,3-2,2-0
        //Depth: 4, LastNode: M, QLength: 4
        { //6
            { INF,   3,   8,   4,   7 },
            {   3, INF,  10,   9,   2 },
            {   8,  10, INF,   6,   5 },
            {   4,   9,   6, INF,   1 },
            {   7,   2,   5,   1, INF }
        },
    };
    printf("TestBBTSP is working ...\n");
    int n = w.size();
    for (int i = 0; i < n; i++) {
        OptimalDist = INF;
        OptimalPath.clear();
        printf("No: %d\n", i);
        OutputW(w[i]);
        BBTSP(w[i]);
        printf("Optimal dist: %d\n", OptimalDist);
        sort(OptimalPath.begin(), OptimalPath.end());
        printf("Optimal path:\n");
        int k = 0;
        for (int j = 0; j < OptimalPath.size(); j++)
        {
            if (j > 0)
                printf(",");
            printf("%d-%d", OptimalPath[k].first, 
                OptimalPath[k].second);
            k = OptimalPath[k].second;
        }
        printf("\n");
    }
}
void TestBBTSPRandom()
{
#define N 5
    random_device rdev{};
    default_random_engine e{ rdev() };
    uniform_int_distribution<int> rnd{ 1, 5 };
    vector<vector<int>> w(N, vector<int>(N));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (i == j)
                w[i][j] = INF;
            else
                w[i][j] = rnd(e);
    printf("TestBBTSP is working ...\n");
    OptimalDist = INF;
    OptimalPath.clear();
    OutputW(w);
    BBTSP(w);
    printf("Optimal dist: %d\n", OptimalDist);
    sort(OptimalPath.begin(), OptimalPath.end());
    printf("Optimal path:\n");
    int k = 0;
    for (int j = 0; j < OptimalPath.size(); j++)
    {
        if (j > 0)
            printf(",");
        printf("%d-%d", OptimalPath[k].first, 
            OptimalPath[k].second);
        k = OptimalPath[k].second;
    }
    printf("\n");
}