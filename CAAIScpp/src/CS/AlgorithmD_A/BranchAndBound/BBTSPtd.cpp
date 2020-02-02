#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <cstring>
#include <climits>
using namespace std;

namespace NSBBTSPtd {
#define N 5
    // Sentinal value for representing infinity
#define INF INT_MAX

    void OutputW(vector<vector<int>> const& w)
    {
        printf("%3c", ' ');
        for (int i = 0; i < N; i++)
            printf("%3d", i);
        printf("\n");
        for (int i = 0; i < N; i++)
        {
            printf("%3d", i);
            for (int j = 0; j < N; j++)
                if (w[i][j] == INF)
                    printf("%3c", '*');
                else
                    printf("%3d", w[i][j]);
            printf("\n");
        }
    }
    struct ClsNodetd
    {
        vector<pair<int, int>> Path;
        vector<vector<int>> W;
        int Cost, Vertex, Level;
        ClsNodetd(vector<vector<int>> const& w, vector<pair<int, int>> const& path,
            int level, int u, int v) : W(w), Path(path),
            Cost(0), Level(level), Vertex(v) {
            if (level != 0) {
                Path.push_back(make_pair(u, v));
                for (int k = 0; k < N; k++) {
                    W[u][k] = INF; W[k][v] = INF;
                }
            }
            W[v][0] = INF;
        }
        vector<int> RowReduction();
        vector<int> ColReduction();
        void Reduce();
    };
    vector<int> ClsNodetd::RowReduction()
    {
        vector<int> row(N, INF);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (W[i][j] < row[i])
                    row[i] = W[i][j];
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (W[i][j] != INF && row[i] != INF)
                    W[i][j] -= row[i];
        return row;
    }
    vector<int> ClsNodetd::ColReduction()
    {
        vector<int> col(N, INF);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (W[i][j] < col[j])
                    col[j] = W[i][j];
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (W[i][j] != INF && col[j] != INF)
                    W[i][j] -= col[j];
        return col;
    }
    void ClsNodetd::Reduce()
    {
        auto row = RowReduction();
        auto col = ColReduction();
        for (int i = 0; i < N; i++)
        {
            Cost += (row[i] != INF) ? row[i] : 0,
                Cost += (col[i] != INF) ? col[i] : 0;
        }
    }

    ClsNodetd BBTSPtd(vector<vector<int>> w)
    {
        auto comp = [](const ClsNodetd& lhs, const ClsNodetd& rhs)
        { return lhs.Cost > rhs.Cost; };
        priority_queue < ClsNodetd, vector<ClsNodetd>,
            decltype(comp) > pq(comp);
        vector<pair<int, int>> p;
        ClsNodetd root(w, p, 0, -1, 0);
        root.Reduce();
        pq.push(root);
        ClsNodetd node = root;
        while (!pq.empty())
        {
            node = pq.top();
            pq.pop();
            int u = node.Vertex;
            if (node.Level == N - 1)
            {
                node.Path.push_back(make_pair(u, 0));
                // print list of cities visited;
                //printPath(min->path);
                break;
            }

            // do for each child of min
            // (i, j) forms an edge in space tree
            for (int v = 0; v < N; v++)
            {
                if (node.W[u][v] != INF)
                {
                    // create a child node and calculate its cost
                    ClsNodetd child(node.W, node.Path, node.Level + 1, u, v);
                    child.Reduce();

                    /*Cost of the child =
                       cost of parent node +
                       cost of the edge(i, j) +
                       lower bound of the path starting at node j*/

                    child.Cost += node.Cost + node.W[u][v];

                    // Add child to list of live nodes
                    pq.push(child);
                }
            }
        }
        return node;
    }
}
using namespace NSBBTSPtd;
// https://www.techiedelight.com/travelling-salesman-problem-using-branch-and-bound/
int TestBBTSPtd()
{
    vector<vector<vector<int>>> w =
    {
        { //cost: 34, Path: 0-2,2-3,3-1,1-4,4-0
            { INF,  10,   8,   9,   7 },
            {  10, INF,  10,   5,   6 },
            {   8,	10, INF,   8,   9 },
            {   9,	 5,	  8, INF,   6 },
            {   7,	 6,	  9,   6, INF }
        },
        { //cost: 16, Path: 0-1,1-3,3-4,4-2,2-0
            { INF,   3,   1,   5,   8 },
            {   3, INF,   6,   7,   9 },
            {   1,   6, INF,   4,   2 },
            {   5,   7,   4, INF,   3 },
            {   8,   9,   2,   3, INF }
        },
        { //Cost 17, Path: 0-4,4-1,1-2,2-3,3-0
            { INF,   5, INF,   6,   5,   4 },
            {   5, INF,   2,   4,   3, INF },
            { INF,   2, INF,   1, INF, INF },
            {   6,   4,   1, INF,   7, INF },
            {   5,   3, INF,   7, INF,   3 },
            {   4, INF, INF, INF,   3, INF }
        },
        //Ö£×Úºº, P248
        { //cost: 65, Path: 0-1,1-2,2-4,4-3,3-0
            { INF,  25,  41,  32,  28 },
            {   5, INF,  18,  31,  26 },
            {  20,	16, INF,   7,   1 },
            {  10,	51,	 25, INF,   6 },
            {  23,	 9,	  7,  11, INF }
        },
    };
    int n = w.size();
    for (int i = 0; i < n; i++) {
        auto node = BBTSPtd(w[i]);
        printf("No: %d, Cost: %d\n", i, node.Cost);
        printf("Path: ");
        for (auto p : node.Path)
            printf("%d-%d,", p.first, p.second);
        printf("\n");
    }
    return 0;
}