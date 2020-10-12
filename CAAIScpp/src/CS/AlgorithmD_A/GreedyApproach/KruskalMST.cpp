#include <stdio.h>
#include <vector>
#include <algorithm>
namespace NS_KruskalMST {
using namespace std;
void KruskalMST();
int FindSet(int u);
void UnionSets(int u, int v);
void Initialization();
void GenEdges();
void MakeSet();
void Output(int v0);
#define INF INT_MAX
static int n;
static vector<vector<int>> WMatrix;
static vector<pair<int, pair<int, int>>> Edges;
//Node struct for the disjoint set
struct DJSNode {
    int Parent; int Rank;
    DJSNode(int p) : Parent(p), Rank(0) {}
};
static vector<DJSNode> DisjointSet;
static vector<pair<int, int>> MST;
//The adjacency list for MST
static vector<vector<int>> MSTList;
static vector<int> Prev;
void KruskalMSTCaller(int an, 
    vector<vector<int>> &wMatrix, int v0)
{
    n = an;
    WMatrix = wMatrix;
    Initialization();
    KruskalMST();
    Output(v0);
}
void KruskalMST()
{
    for (auto &e: Edges)
    {
        int u = e.second.first;
        int v = e.second.second;
        int setU = FindSet(u);
        int setV = FindSet(v);
        if (setU != setV)
        {
            MST.push_back(e.second);
            if (MST.size() == n - 1)
                break;
            UnionSets(setU, setV);
        }
    }
}
int FindSet(int u)
{
    while (u != DisjointSet[u].Parent)
        u = FindSet(DisjointSet[u].Parent);
        //For path compression:
        //DisjointSet[u].Parent = 
        //    Find(DisjointSet[u].Parent);
    return u;
}
void UnionSets(int u, int v)
{
    if (DisjointSet[u].Rank >= DisjointSet[v].Rank)
        DisjointSet[v].Parent = u;
    else
        DisjointSet[u].Parent = v;
    if (DisjointSet[u].Rank == DisjointSet[v].Rank)
        DisjointSet[u].Rank++;
}
void Initialization()
{
    GenEdges();
    sort(Edges.begin(), Edges.end());
    MakeSet();
    MST.clear();
}
void GenEdges()
{
    Edges.clear();
    //Traverse the upper triangle of WMatrix
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
            if (WMatrix[i][j] != INF)
                Edges.push_back({ WMatrix[i][j], 
                    {i, j} });
    }
}
void MakeSet()
{
    DisjointSet.clear();
    for (int i = 0; i < n; i++)
        DisjointSet.push_back(DJSNode(i));
}
void OutputWMatrix()
{
    printf("n = %d\n", n);
    printf("The weight matrix:\n");
    printf("%3c", ' ');
    for (int j = 0; j < n; j++)
        printf("%3d", j + 1);
    printf("\n");
    for (int i = 0; i < n; i++)
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
void GenMSTList()
{
    MSTList.clear();
    MSTList.resize(n);
    for (auto &e: MST)
    {
        MSTList[e.first].push_back(e.second);
        MSTList[e.second].push_back(e.first);
    }

}
void GenPrev(int v)
{
    for (auto &u : MSTList[v])
        if (u != -1)
        {
            Prev[u] = v;
            auto w = find(MSTList[u].begin(), 
                MSTList[u].end(), v);
            MSTList[u][w - MSTList[u].begin()] = -1;
            GenPrev(u);
        }
}
void Output(int v0)
{
    printf("Kruskal's MST algorithm\n");
    OutputWMatrix();
    int wSum = 0;
    for (int i = 0; i < n - 1; i++)
        wSum += WMatrix[MST[i].first][MST[i].second];
    GenMSTList();
    Prev.clear();
    Prev.resize(n);
    for (int i = 0; i < n; i++)
        Prev[i] = -2;
    Prev[v0] = -1;
    GenPrev(v0);
    printf("The MST edges:\n");
    printf("Edge Weight\n");
    for (auto &e : MST)
        printf(" %d-%d  %d\n", e.first + 1, e.second + 1,
            WMatrix[e.first][e.second]);
    printf("Total MST weight: %d\n", wSum);
    printf("The MST paths from vertex %d:\n", v0 + 1);
    for (int u = 0; u < n; u++)
        if (u != v0)
        {
            printf("%3d: ", u + 1);
            OutputPath(u);
            printf("\n");
        }
    printf("\n");
}
} //namespace NS_KruskalMST
using namespace NS_KruskalMST;
void TestKruskalMST(int v0 = 0)
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
      KruskalMSTCaller(w[i].size(), w[i], v0);
    }
}