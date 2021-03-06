#include <vector>
namespace NS_BTKColoring {
using namespace std;
void BTKColoring(int v);
//void BTKColoringStack();
int CheckColoring(int v);
void Output();
static int N, K;
static vector<vector<int>> AdjM;
static vector<int> Colors;
static bool Done;
static vector<int> Stack;
void BTKColoringCaller(int n, int k, 
    vector<vector<int>> &adjM)
{
    N = n;
    K = k;
    AdjM = adjM;
    Colors.clear();
    Colors.resize(N);
    Colors[0] = 1;
    Colors[1] = 2;
    Done = false;
    BTKColoring(2);
    //BTKColoringStack();
    Output();
}
void BTKColoring(int v)
{
    //int c = 1;
    for (int c = 1; !Done && c <= K; c++)
    {
        Colors[v] = c;
        if (CheckColoring(v) == -1)
            if (v == N - 1)
              Done = true;
            else {
              BTKColoring(v + 1);
            }
        //c++;
    }
    //if (!Colors[N - 1] && c > K)
    //    Colors[v] = 0;
}
int CheckColoring(int v)
{
    for (int u = 0; u < v; u++)
        if (AdjM[v][u] && Colors[u] == Colors[v])
            return u;
    return -1;
}
void BTKColoringStack()
{
    Stack.clear();
    Stack.push_back(1);
    Stack.push_back(2);
    while (!Stack.empty())
    {
        int v = Stack.back();
        Stack.pop_back();
        int c = Stack.back();
        Stack.pop_back();
        while (!Colors[N - 1] && c <= K)
        {
            Colors[v] = c;
            if (CheckColoring(v) == -1)
            {
                if (v < N - 1)
                {
                    Stack.push_back(c + 1);
                    Stack.push_back(v);
                    Stack.push_back(1);
                    Stack.push_back(v + 1);
                }
                else
                    Stack.clear();
                break;
            }
            else
                Colors[v] = 0;
            c++;
        } //while c
        if (!Colors[N - 1] && c < K)
            Colors[v] = 0;
    } //while (!Stack.empty())
}
void OutputAdjMatrix()
{
    printf("N = %d.\n", N);
    printf("The adjacency matrix:\n");
    printf("%3c", ' ');
    for (int j = 0; j < N; j++)
        printf("%3d", j + 1);
    printf("\n");
    for (int i = 0; i < N; i++)
    {
        printf("%3d", i + 1);
        for (auto j : AdjM[i])
            printf("%3d", j);
        printf("\n");
    }
}
void Output()
{
    printf("K coloring with backtracking.\n");
    printf("The input graph:\n");
    OutputAdjMatrix();
    printf("K = %d.\n", K);
    printf("The result:\n");
    if (!Colors[N - 1])
    {
      printf("The graph cann't be colored ");
      printf("with %d colors.\n", K);
    }
    else
    {
        printf("The graph can be colored ");
        printf("with %d colors:\n", K);
        for (int v = 0; v < N; v++)
            printf("(%d,%d)", v, Colors[v]);
        printf("\n");
    }
}
} //namespace NS_BTKColoring
using namespace NS_BTKColoring;
void TestBTKColoring(int K = 3)
{
  vector<vector<vector<int>>> adjM = {
    //06U-01: Dijkstra's algorithm on Wikipedia
    //K=3: (0,1)(1,2)(2,3)(3,1)(4,3)(5,2)
    {
        { 0, 1, 1, 0, 0, 1 },
        { 1, 0, 1, 1, 0, 0 },
        { 1, 1, 0, 1, 0, 1 },
        { 0, 1, 1, 0, 1, 0 },
        { 0, 0, 0, 1, 0, 1 },
        { 1, 0, 1, 0, 1, 0 },
    },
    //06U-04: XJ-Shen's exercise-5
    //K=4: (0,1)(1,2)(2,1)(3,3)(4,4)(5,2)
    {
        { 0, 1, 0, 1, 1, 1 },
        { 1, 0, 1, 1, 1, 0 },
        { 0, 1, 0, 1, 0, 0 },
        { 1, 1, 1, 0, 1, 0 },
        { 1, 1, 0, 1, 0, 1 },
        { 1, 0, 0, 0, 1, 0 },
    },
  };
  for (size_t i = 0; i < adjM.size(); i++)
    BTKColoringCaller(adjM[i].size(), K, adjM[i]);
}