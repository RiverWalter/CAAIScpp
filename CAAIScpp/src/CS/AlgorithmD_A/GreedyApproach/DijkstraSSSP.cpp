#include <stdio.h>
#include <vector>
namespace NS_DijkstraSSSP {
using namespace std;
void DijkstraSSSP();
void Initialization(int v0);
void GenAdjList();
int ExtractMin();
void SiftDown(int i);
void SiftUp(int i);
void InsertQ(int w);
void OutputDistMatrix();
void Output(int v0);
#define INF INT_MAX
static int n;
static vector<vector<int>> W, AdjList;
static vector<int> Dist, Prev, Q;
//-1: Free, -2: Finished, Other(>=0): Position in Q
static vector<int> S;
void DijkstraSSSPCaller(int an,
    vector<vector<int>> &w, int v0)
{
    n = an;
    W = w;
    OutputDistMatrix();
    Initialization(v0);
    DijkstraSSSP();
    Output(v0);
}
void DijkstraSSSP()
{
    int v, d;
    while (!Q.empty())
    {
        v = ExtractMin();
        for (auto u: AdjList[v])
            if (S[u] != -2)
            {
                d = Dist[v] + W[v][u];
                if (d < Dist[u])
                {
                    Dist[u] = d;
                    Prev[u] = v;
                    if (S[u] >= 0)
                        SiftUp(S[u]);
                    else
                        InsertQ(u);
                }
            }
    }
}
int ExtractMin()
{
    swap(Q.front(), Q.back());
    S[Q.front()] = 0;
    int w = Q.back();
    S[w] = -2;
    Q.pop_back();
    if (!Q.empty())
        SiftDown(0);
    return w;
}
void SiftDown(int i)
{
    while ((i = (i << 1) + 1) < Q.size()) {
        if (i + 1 < Q.size() && Dist[Q[i + 1]] < Dist[Q[i]])
            i++;
        int p = i - 1 >> 1;
        if (Dist[Q[p]] > Dist[Q[i]])
        {
            S[Q[p]] = i;
            S[Q[i]] = p;
            swap(Q[p], Q[i]);
        }
        else break;
    }
}
void SiftUp(int i)
{
    int p;
    while (i > 0 && Dist[Q[i]] < Dist[Q[p = i - 1 >> 1]]) {
        S[Q[i]] = p;
        S[Q[p]] = i;
        swap(Q[i], Q[p]);
        i = p;
    }
}
void InsertQ(int w)
{
    Q.push_back(w);
    int k = int(Q.size() - 1);
    S[w] = k;
    SiftUp(k);
}
void Initialization(int v0)
{
    GenAdjList();
    Dist.clear();
    Dist.resize(n, INF);
    Dist[v0] = 0;
    Prev.clear();
    Prev.resize(n, -1);
    Q.clear();
    Q.push_back(v0);
    S.clear();
    S.resize(n, -1);
    S[v0] = 0;
}
void GenAdjList()
{
    AdjList.clear();
    for (int i = 0; i < n; i++)
    {
        AdjList.push_back(vector<int>());
        for (int j = 0; j < n; j++)
            if (W[i][j] && W[i][j] != INF)
                AdjList[i].push_back(j);
    }
}
void OutputDistMatrix()
{
    printf("n = %d\n", n);
    printf("The distance matrix:\n");
    printf("%3c", ' ');
    for (int j = 0; j < n; j++)
        printf("%3d", j + 1);
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        printf("%3d", i + 1);
        for (auto j : W[i])
            if (j < INF)
                printf("%3d", j);
            else
                printf("%3c", '*');
        printf("\n");
    }
}
void OutputPath(int u)
{
    if (Prev[u] == -1)
        printf("%d", u + 1);
    else
    {
        OutputPath(Prev[u]);
        printf("-%d", u + 1);
    }
}
void Output(int v0)
{
    printf("The shortest distance and path from node %d:\n",
        v0 + 1);
    for (int u = 0; u < n; u++)
        if (u != v0)
        {
            printf("%3d: ", u + 1);
            printf("%d;", Dist[u]);
            OutputPath(u);
            printf("\n");
        }
    printf("\n");
}
} //namespace NS_DijkstraSSSP
using namespace NS_DijkstraSSSP;
void TestDijkstraSSSP(int v0 = 0)
{
    vector<vector<vector<int>>> w = {
        //https://www.geeksforgeeks.org/
        //prims-minimum-spanning-tree-mst-greedy-algo-5/
        {
            {   0,  2,INF,  6,INF },
            {   2,  0,  3,  8,  5 },
            { INF,  3,  0,INF,  7 },
            {   6,  8,INF,  0,  9 },
            { INF,  5,  7,  9,  0 }
        },
        // Dijkstra's algorithm on Wikipedia
        {
            {   0,  7,  9,INF,INF, 14 },
            {   7,  0, 10, 15,INF,INF },
            {   9, 10,  0, 11,INF,  2 },
            { INF, 15, 11,  0,  6,INF },
            { INF,INF,INF,  6,  0,  9 },
            {  14,INF,  2,INF,  9,  0 },
        },
        //https://www.geeksforgeeks.org/
        //kruskals-minimum-spanning-tree-using-stl-in-c/
        {
            {   0,  4,INF,INF,INF,INF,INF,  8,INF },
            {   4,  0,  8,INF,INF,INF,INF, 11,INF },
            { INF,  8,  0,  7,INF,  4,INF,INF,  2 },
            { INF,INF,  7,  0,  9, 14,INF,INF,INF },
            { INF,INF,INF,  9,  0, 10,INF,INF,INF },
            { INF,INF,  4, 14, 10,  0,  2,INF,INF },
            { INF,INF,INF,INF,INF,  2,  0,  1,  6 },
            {   8, 11,INF,INF,INF,INF,  1,  0,  7 },
            { INF,INF,  2,INF,INF,INF,  6,  7,  0 },
        },
    };
    int k = w.size();
    for (int i = 0; i < k; i++)
    {
      if (v0 > w[i].size() - 1)
        v0 = w[i].size() - 1;
      DijkstraSSSPCaller(w[i].size(), w[i], v0);
    }
}