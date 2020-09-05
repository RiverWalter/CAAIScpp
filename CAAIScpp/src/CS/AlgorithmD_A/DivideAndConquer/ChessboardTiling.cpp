#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;
namespace NS_ChessBoardTiling {
int RandIntM(int m);
void ChessBoardTilingCaller(int n, int p0, int q0);
void ChessboardTiling(int r, int c, int p, int q, int s);
void OutputChessboard(int m, int p0, int q0);
static vector<vector<int>> Chessboard;
static int TileNo;
static void ChessBoardTilingCaller(int n, int p0, int q0)
{
    int m = 1 << n;
    Chessboard.resize(m);
    for (auto &v: Chessboard)
        v.resize(m);
    Chessboard[p0][q0] = -1;
    TileNo = 0;
    ChessboardTiling(0, 0, p0, q0, m);
    OutputChessboard(m, p0, q0);
}
void ChessboardTiling(int r, int c, 
    int p, int q, int s)
{
    if (s == 1)
        return;
    s /= 2;
    int no = ++TileNo;
    //left-top sub-board
    if (p < r + s && q < c + s)
        ChessboardTiling(r, c, p, q, s);
    else {
        Chessboard[r + s - 1][c + s - 1] = no;
        ChessboardTiling(r, c, r + s - 1, c + s - 1, s);
    }
    //right-top sub-board
    if (p < r + s && q >= c + s)
        ChessboardTiling(r, c + s, p, q, s);
    else {
        Chessboard[r + s - 1][c + s] = no;
        ChessboardTiling(r, c + s, r + s - 1, c + s, s);
    }
    //right-bottom sub-board
    if (p >= r + s && q >= c + s)
        ChessboardTiling(r + s, c + s, p, q, s);
    else {
        Chessboard[r + s][c + s] = no;
        ChessboardTiling(r + s, c + s, r + s, c + s, s);
    }
    //left-bottom sub-board
    if (p >= r + s && q < c + s)
        ChessboardTiling(r + s, c, p, q, s);
    else {
        Chessboard[r + s][c + s - 1] = no;
        ChessboardTiling(r + s, c, r + s, c + s - 1, s);
    }
}
void OutputChessboard(int m, int p0, int q0)
{
    printf("Chessboard tiling:\n");
    printf("Size: %dx%d, Defect position: (%c,%c)\n", 
        m, m, p0 + 65, q0 + 65);
    printf("%3c", ' ');
    for (int i = 0; i < m; i++)
        printf("%3c", i + 65);
    printf("\n");
    for (int i = 0; i < m; i++) {
        printf("%3c", i + 65);
        for (int j = 0; j < m; j++)
            printf("%3d", Chessboard[i][j]);
        printf("\n");
    }
}
//Generate one random integer in the range [0, m)
int RandIntM(int m)
{
    return rand() % (m);
}
} //NS_ChessBoardTiling
using namespace NS_ChessBoardTiling;
void TestChessBoardTiling(int n)
{
    //Set random seed using system time for rand()
    srand((unsigned)time(NULL));

    int m = 1 << n;
    int p0 = RandIntM(m);
    int q0 = RandIntM(m);
    ChessBoardTilingCaller(n, p0, q0);
}
