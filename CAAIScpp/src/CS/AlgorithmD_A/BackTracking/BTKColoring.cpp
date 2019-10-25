#include <vector>
using namespace std;
static void KColoring(int v);
static void KColoringStack();
static int CheckColoring(int v);
static void Output();
static vector<int> Colors;
static int N, K;
static vector<vector<int>> AdjM;
static vector<int> Stack;

void BTKColoringCaller(int n, int k, vector<vector<int>> &adjM)
{
    N = n;
    K = k;
    AdjM = adjM;
    Colors.clear();
    Colors.resize(N);
    Colors[0] = 1;
    Colors[1] = 2;
    KColoring(2);
    //KColoringStack();
    Output();
}
static void KColoring(int v)
{
    int c = 1;
    while (!Colors[N-1] && c <= K)
    {
        Colors[v] = c;
        if (CheckColoring(v) == -1)
            if (v < N - 1)
                KColoring(v + 1);
            else
                break;
        c++;
    }
    if (!Colors[N - 1] && c > K)
        Colors[v] = 0;
}
static int CheckColoring(int v)
{
    for (int u = 0; u < v; u++)
        if (AdjM[v][u] && Colors[u] == Colors[v])
            return u;
    return -1;
}
static void KColoringStack()
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
static void OutputAdjMatrix()
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
static void Output()
{
    printf("\nK coloring with backtracking.\n");
    printf("\nThe input:\n");
    OutputAdjMatrix();
    printf("K = %d.\n", K);
    printf("\nThe result:\n");
    if (!Colors[N - 1])
        printf("The graph cann't be colored with %d colors.\n", K);
    else
    {
        printf("The graph can be colored with %d colors:\n", K);
        for (int v = 0; v < N; v++)
            printf("(%d,%d)", v, Colors[v]);
        printf("\n");
    }
}

