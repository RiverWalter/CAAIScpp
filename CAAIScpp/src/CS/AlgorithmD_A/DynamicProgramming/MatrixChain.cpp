#include <stdio.h>
#include <vector>
#include <string>
using namespace std;
namespace NS_MatrixChainDP {
#define INF INT_MAX
void MatrixChainDP(vector<int> p);
void GenOrder(int i, int j);
void Initialization();
void ShowInput(vector<int> p);
void Show_mMatrix();
void Show_sMatrix();
void ShowResult();
static int N;
static vector<vector<int>> m, s;
static vector<string> order;
void MatrixChainDPCaller(vector<int> p)
{
    N = p.size() - 1;
    ShowInput(p);
    Initialization();
    MatrixChainDP(p);
    Show_mMatrix();
    Show_sMatrix();
    ShowResult();
}
void MatrixChainDP(vector<int> p)
{
    for (int i = 0; i < N; i++)
        m[i][i] = 0;
    for (int l = 2; l <= N; l++)
        for (int i = 0; i <= N - l; i++)
        {
            int j = i + l - 1;
            m[i][j] = INF;
            for (int k = i; k <= j - 1; k++)
            {
                int q = m[i][k]+m[k+1][j]+p[i]*p[k+1]*p[j+1];
                if (q < m[i][j])
                {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    GenOrder(0, N - 1);
}
void GenOrder(int i, int j)
{
    if (i == j)
        order.push_back(string("A") + to_string(i));
    else
    {
        int k = s[i][j];
        order.push_back("(");
        GenOrder(i, k);
        GenOrder(k + 1, j);
        order.push_back(")");
    }
}
void Initialization()
{
    m.resize(N);
    for (auto &a : m)
        a.resize(N, 0);
    s.resize(N);
    for (auto &a : s)
        a.resize(N, 0);
    order.clear();
}
void ShowInput(vector<int> p)
{
    printf("N: %d\n", N);
    printf("Dimensions:");
    for (int i = 0; i <= N; i++)
    {
        if (i > 0)
            printf(",");
        printf(" %d", p[i]);
    }
    printf("\n");
}
void Show_mMatrix()
{
    int k = to_string(m[0][N - 1]).length();
    printf("The m matrix:\n");
    printf("%3c", ' ');
    for (int i = 0; i < N; i++)
        printf(" %*d", k, i);
    printf("\n");
    for (int i = 0; i < N; i++)
    {
        printf("%3d", i);
        for (int j = 0; j < i; j++)
            printf(" %*c", k, '-');
        for (int j = i; j < N; j++)
            printf(" %*d", k, m[i][j]);
        printf("\n");
    }
}
void Show_sMatrix()
{
    printf("The s matrix:\n");
    printf("%3c", ' ');
    for (int i = 0; i < N; i++)
        printf(" %d", i);
    printf("\n");
    for (int i = 0; i < N; i++)
    {
        printf("%3d", i);
        for (int j = 0; j <= i; j++)
            printf(" %c", '-');
        for (int j = i + 1; j < N; j++)
            printf(" %d", s[i][j]);
        printf("\n");
    }
}
void ShowResult()
{
    printf("The optimal value: %d\n", m[0][N - 1]);
    printf("The optimal solution: ");
    for (auto s : order)
        printf("%s", s.c_str());
    printf("\n");
}
} //namespace NS_BBTSP
using namespace NS_MatrixChainDP;
void TestMatrixChainDP()
{
    vector<vector<int>> MatDim =
    {
        //1: AlgoD&A&App-Example
        //李文书、何利力，算法设计、分析与应用教程，3.2节示例
        //Optimal value: 15750
        //Optimal solution: ((A0(A1(A2A3)))(A4A5))
        { 50, 10, 40, 30, 5, 20, 15 },
        //2: AlgoD&A-Wang-Example4-5
        //王秋芬，算法设计与分析，4.2节，示例4-5
        //Optimal value: 150
        //Optimal solution: (A0((A1(A2A3))A4))
        { 3, 2, 5, 10, 2, 3 },
        //3: AlgoDTech&A-Example7.4
        //M.H. Alsuwaiyel, Algorithms Design Techniques and Analysis,Sec. 7.3, Example 7.4
        //Optimal value: 348
        //Optimal solution: (A0(A1(A2(A3A4))))
        { 5, 10, 4, 6, 10, 2 },
        //4: AlgoDTech&A-Exercise7.11
        //M.H. Alsuwaiyel, Algorithms Design Techniques and Analysis,Sec. 7.3, Exercise 7.11
        //Optimal value: 124
        //Optimal solution: ((A0(A1(A2A3)))A4)
        { 2, 3, 6, 4, 2, 7 },
        //5: AlgoDTech&A-Exercise7.9
        //M.H. Alsuwaiyel, Algorithms Design Techniques and Analysis,Sec. 7.3, Exercise 7.9
        //Optimal value: 252
        //Optimal solution: ((A0A1)((A2A3)A4))
        { 4, 5, 3, 6, 4, 5 },
        //6: DSAAinJava-WeissExercise10.29
        //M.A. Weiss, Data Structures and Algorithm Analysis in Java, Exercise 10.29
        //Optimal value: 1150
        //Optimal solution: ((A0A1)(((A2A3)A4)A5))
        { 10, 20, 1, 40, 5, 30, 15 },
        //7: EssCompAlgo-Shen-Exercise
        //沈孝钧，计算机算法基础，第6章，习题1.b
        //Optimal value: 1458
        //Optimal solution: ((A0(A1(A2A3)))A4)
        { 8, 10, 6, 11, 3, 35 },
        //8: FoA-Example3.5
        //Foundations of Algorithms, 5ed, Sec. 3.4, Example 3.5
        //Optimal value: 348
        //Optimal solution: (A0((((A1A2)A3)A4)A5)
        { 5, 2, 3, 4, 6, 7, 8 },
        //9: FoA-Exercise3.4-13
        //Foundations of Algorithms, 5ed, Exercise 3.4-13
        //Optimal value: 1320
        //Optimal solution: ((A0(A1(A2A3)))A4)
        { 10, 4, 5, 20, 2, 50 },
        //10: IntrAlgo-Example
        //Introduction to Algorithms, Sec. 15.2
        //Optimal value: 15125
        //Optimal solution: ((A0(A1A2))((A3A4)A5))
        { 30, 35, 15, 5, 10, 20, 25 },
        //11: IntrAlgo-Exercise15.2-1
        //Introduction to Algorithms, Exercise 15.2-1
        //Optimal value: 2010
        //Optimal solution: ((A0A1)((A2A3)(A4A5))
        { 5, 10, 3, 12, 5, 50, 6 }
    };
    printf("TestMatrixChainDP is working ...\n");
    int n = MatDim.size();
    //int n = 1;
    for (int i = 0; i < n; i++) {
        printf("No: %d\n", i);
        MatrixChainDPCaller(MatDim[i]);
    }
}