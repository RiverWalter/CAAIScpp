#include <stdio.h>
#include <vector>
namespace NS_PrimMST {
using namespace std;
void PrimMST();
void Initialization(int v0);
void GenAdjList();
int ExtractMin();
void MinHeapify(int i);
void DecreaseKey(int i);
void EnQueue(int w);
void OutputWMatrix();
void Output(int v0);
#define INF INT_MAX
static int N;
static vector<vector<int>> WMatrix, AdjList;
static vector<int> Dist, Prev, Q;
//-1: Free, -2: Finished, Other(>=0): Position in Q
static vector<int> S;
void PrimMSTCaller(int n, vector<vector<int>> &wMatrix, int v0)
{
    N = n;
    WMatrix = wMatrix;
    OutputWMatrix();
    Initialization(v0);
    PrimMST();
    Output(v0);
}
void PrimMST()
{
    int v, d;
    while (!Q.empty())
    {
        v = ExtractMin();
        for (auto u: AdjList[v])
            if (S[u] != -2)
            {
                if (WMatrix[v][u] < Dist[u])
                {
                    Dist[u] = WMatrix[v][u];
                    Prev[u] = v;
                    if (S[u] >= 0)
                        DecreaseKey(S[u]);
                    else
                        EnQueue(u);
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
        MinHeapify(0);
    return w;
}
void MinHeapify(int i)
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
void DecreaseKey(int i)
{
    int p;
    while (i > 0 && Dist[Q[i]] < Dist[Q[p = i - 1 >> 1]]) {
        S[Q[i]] = p;
        S[Q[p]] = i;
        swap(Q[i], Q[p]);
        i = p;
    }
}
void EnQueue(int w)
{
    Q.push_back(w);
    int n = int(Q.size() - 1);
    S[w] = n;
    DecreaseKey(n);
}
void Initialization(int v0)
{
    GenAdjList();
    Dist.clear();
    Dist.resize(N, INF);
    Dist[v0] = 0;
    Prev.clear();
    Prev.resize(N, -1);
    Q.clear();
    Q.push_back(v0);
    S.clear();
    S.resize(N, -1);
    S[v0] = 0;
}
void GenAdjList()
{
    AdjList.clear();
    for (int i = 0; i < N; i++)
    {
        AdjList.push_back(vector<int>());
        for (int j = 0; j < N; j++)
            if (WMatrix[i][j] && WMatrix[i][j] != INF)
                AdjList[i].push_back(j);
    }
}
void OutputWMatrix()
{
    printf("N = %d\n", N);
    printf("The weight matrix:\n");
    printf("%3c", ' ');
    for (int j = 0; j < N; j++)
        printf("%3d", j + 1);
    printf("\n");
    for (int i = 0; i < N; i++)
    {
        printf("%3d", i + 1);
        for (auto j : WMatrix[i])
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
    int wSum = 0;
    for (int i = 0; i < N; i++)
        wSum += Dist[i];
    printf("Total MST weight: %d\n", wSum);
    printf("The MST paths from vertex %d:\n", v0 + 1);
    for (int u = 0; u < N; u++)
        if (u != v0)
        {
            printf("%3d: ", u + 1);
            OutputPath(u);
            printf("\n");
        }
    printf("The MST edges:\n");
    printf("Edge Weight\n");
    for (int u = 0; u < N; u++)
        if (u != v0)
        {
            printf(" %d-%d  %d\n", Prev[u] + 1, u + 1, Dist[u]);
        }
    printf("\n");
}
} //namespace NS_PrimMST
using namespace NS_PrimMST;
void TestPrimMST(int v0 = 0)
{
    vector<int> n = { 5, 6, 9 };
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
    int k = n.size();
    for (int i = 0; i < k; i++)
    {
        if (v0 > n[i] - 1)
            v0 = n[i] - 1;
        PrimMSTCaller(n[i], w[i], v0);
    }
}