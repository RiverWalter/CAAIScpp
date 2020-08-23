#include <stdio.h>
#include <vector>
#include <queue>
namespace NS_GraphBFS {
using namespace std;
void GraphBFS(int v);
void OutputAdjacencyList();
void OutputBFSVisitingOrder();
void Initialization();
static vector<vector<int>> AdjL;
static vector<bool> Visited;
static vector<int> Order;
static int N, V0;
void GraphBFSCaller(int n, 
    vector<vector<int>> &adjL, int v0)
{
    N = n;
    V0 = v0;
    AdjL = adjL;
    OutputAdjacencyList();
    Initialization();
    GraphBFS(v0);
    OutputBFSVisitingOrder();
}
void GraphBFS(int v)
{
    queue<int> q;
    Visited[v] = true;
    Order.push_back(v);
    q.push(v);
    while (!q.empty())
    {
        v = q.front();
        q.pop();
        for (auto u : AdjL[v])
            if (!Visited[u])
            {
                Visited[u] = true;
                Order.push_back(u);
                q.push(u);
            }
    }
}
void OutputAdjacencyList()
{
    printf("N = %d\n", N);
    printf("The adjacency list:\n");
    for (int i = 0; i < N; i++)
    {
        printf("%3d: ", i + 1);
        for (auto j: AdjL[i])
            printf("%2d", j + 1);
        printf("\n");
    }
    printf("Starting vertex: %d\n", V0 + 1);
}
void OutputBFSVisitingOrder()
{
    printf("BFS visiting order: ");
    for (int i = 0; i < N; i++)
    {
        if (i != 0)
            printf(",");
        printf("%d", Order[i] + 1);
    }
    printf("\n\n");
}
void Initialization()
{
    Visited.clear();
    Order.clear();
    for (int i = 0; i < N; i++)
        Visited.push_back(false);
}
} //namespace NS_GraphBFS
using namespace NS_GraphBFS;
void TestGraphBFS(int v0)
{
    //number of vertices
    vector<int> nv = { 6, 9, 8 }; 
    //adjacency lists
    vector<vector<vector<int>>> adjLists = {
        // Dijkstra's algorithm on Wikipedia
        {
            { 1, 2, 5 },
            { 0, 2, 3 },
            { 0, 1, 3, 5 },
            { 1, 2, 4 },
            { 3, 5 },
            { 0, 2, 4 },
        },
        //ZH-Zheng's graph traversal demo
        {
            { 1, 2, 3 },
            { 0, 4, 5 },
            { 0, 3 },
            { 0, 2, 4 },
            { 1, 3, 5, 7 },
            { 1, 4, 8 },
            { 7, 8 },
            { 4, 6, 8 },
            { 5, 6, 7 },
        },
        //XJ-Shen's exercise-2
        {
            { 1, 2, 4 },
            { 0, 5, 7 },
            { 0, 3, 5 },
            { 2, 4, 7 },
            { 0, 3, 6 },
            { 1, 2, 6 },
            { 4, 5, 7 },
            { 1, 3, 6 },
        },
    };
    for (int i = 0; i < nv.size(); i++)
    {
        int u0 = v0 < nv[i] ? v0 : nv[i] - 1;
        GraphBFSCaller(nv[i], adjLists[i], u0);
    }
}
