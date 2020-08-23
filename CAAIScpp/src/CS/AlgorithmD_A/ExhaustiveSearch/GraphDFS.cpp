#include <stdio.h>
#include <vector>
namespace NS_GraphDFS {
using namespace std;
void GraphDFS(int u);
void OutputAdjacencyList();
void OutputDFSVisitingOrder();
void Initialization();
void Finalization();
static vector<vector<int>> AdjL;
static vector<bool> Visited;
static vector<pair<int, int>*> PreOrder;
static vector<pair<int, int>*> PostOrder;
static int N, V0, Order;
void GraphDFSCaller(int n, 
    vector<vector<int>> &adjL, int v0)
{
    N = n;
    V0 = v0;
    AdjL = adjL;
    OutputAdjacencyList();
    Initialization();
    GraphDFS(v0);
    OutputDFSVisitingOrder();
    Finalization();
}
void GraphDFS(int v)
{
    Visited[v] = true;
    PreOrder.push_back(new pair<int, int>(v, ++Order));
    for (auto u: AdjL[v])
        if (!Visited[u])
            GraphDFS(u);
    PostOrder.push_back(new pair<int, int>(v, ++Order));
}
void OutputAdjacencyList()
{
    printf("N = %d\n", N);
    printf("The adjacency list:\n");
    for (int i = 0; i < N; i++)
    {
        printf("%3d: ", i + 1);
        for (auto j : AdjL[i])
            printf("%2d", j + 1);
        printf("\n");
    }
    printf("Starting vertex: %d\n", V0 + 1);
}
void OutputDFSVisitingOrder()
{
    printf("DFS preorder: \n");
    for (int i = 0; i < N; i++)
    {
        if (i != 0)
            printf(",");
        printf("(%d,%d)", PreOrder[i]->first + 1,
            PreOrder[i]->second);
    }
    printf("\n");
    printf("DFS postorder: \n");
    for (int i = 0; i < N; i++)
    {
        if (i != 0)
            printf(",");
        printf("(%d,%d)", PostOrder[i]->first + 1,
            PostOrder[i]->second);
    }
    printf("\n\n");
}
void Initialization()
{
    Order = 0;
    PreOrder.clear();
    PostOrder.clear();
    Visited.clear();
    for (int i = 0; i < N; i++)
        Visited.push_back(false);
}
void Finalization()
{
    for (auto p : PreOrder)
        delete p;
    for (auto p : PostOrder)
        delete p;
}
} //namespace NS_GraphDFS
using namespace NS_GraphDFS;
void TestGraphDFS(int v0)
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
        GraphDFSCaller(nv[i], adjLists[i], u0);
    }
}
