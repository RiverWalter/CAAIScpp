#include <vector>
using namespace std;
namespace NS_DP0_1Knapsack {
int DP0_1Knapsack(int n, int W, int *w, int *v);
void Output(int n, int W, int *w, int *v, int OptV);
static vector<vector<int>> V;
static vector<int> x;
void DP0_1KnapsackCaller(int n, int W, int *w, int *v)
{
    V.clear();
    V.resize(n + 1, vector<int>(W + 1, 0));
    x.resize(n + 1);
    int OptV = DP0_1Knapsack(n, W, w, v);
    Output(n, W, w, v, OptV);
}
int DP0_1Knapsack(int n, int W, int *w, int *v)
{
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= W; j++)
            if (j < w[i - 1])
                V[i][j] = V[i - 1][j];
            else if (V[i - 1][j] >=
                V[i - 1][j - w[i - 1]] + v[i - 1])
                V[i][j] = V[i - 1][j];
            else
                V[i][j] = V[i - 1][j - w[i - 1]] + v[i - 1];
    int j = W;
    for (int i = n; i > 0; i--)
        if (V[i][j] == V[i - 1][j])
            x[i] = 0;
        else
        {   x[i] = 1; j -= w[i - 1];  }
    return V[n][W];
}
void Output(int n, int W, int *w, int *v, int OptV)
{
    //inputs
    printf("DP to solve 0-1 knapsack:\n");
    printf("%d items with knapsack capacity %d.\n", n , W);
    printf("%-6s: ", "Weight");
    for (int i = 0; i < n; i++)
        printf("%3d", w[i]);
    printf("\n");
    printf("%-6s: ", "Value");
    for (int i = 0; i < n; i++)
        printf("%3d", v[i]);
    printf("\n");
    //the value matrix
    printf("\nThe value matrix:\n");
    printf("  ");
    for (int j = 0; j <= W; j++)
        printf("%3d", j);
    printf("\n");
    for (int i = 0; i <= n; i++)
    {
        printf("%2d", i);
        for (int j = 0; j <= W; j++)
            printf("%3d", V[i][j]);
        printf("\n");
    }
    //solution
    printf("\nThe optimal value: %d\n", OptV);
    printf("The optimal solution:\n");
    for (int i = 1; i <= n; i++)
        printf("%2d", x[i]);
    printf("\n\n");
}
} //namespace NS_DP0_1Knapsack
using namespace NS_DP0_1Knapsack;
void TestDP0_1Knapsack()
{
    vector<int> N = { 4, 4, 4, 5, 5, 4, 7 };
    vector<int> W = { 16, 7, 10, 10, 15, 8, 15 };
    vector<vector<int>> w = {
        { 2, 5, 10, 5 },
        { 3, 5, 2, 1 },
        { 5, 4, 6, 3 },
        { 2, 2, 6, 5, 4 },
        { 12, 2, 1, 4, 1 },
        { 5, 4, 3, 2 },
        { 2, 3, 5, 7, 1, 4, 1 }
    };
    vector<vector<int>> v = {
        { 40, 10, 50, 30 },
        { 9, 10, 7, 4 },
        { 10, 40, 30, 50 },
        { 6, 3, 5, 4, 6 },
        { 4, 2, 1, 10, 2 },
        { 15, 10, 6, 2 },
        { 10, 5, 15, 7, 6, 18, 3 }
    };

    int m = N.size();
    for (int i = 0; i < m; i++)
    {
        DP0_1KnapsackCaller(N[i], W[i], &w[i][0], &v[i][0]);
    }
}