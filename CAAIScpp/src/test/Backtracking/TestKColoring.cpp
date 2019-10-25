#include "../../../include/headers.h"
void TestKColoring(int K = 3)
{
    vector<vector<vector<int>>> adjM = {
        //06U-01: Dijkstra's algorithm on Wikipedia
        {
            { 0, 1, 1, 0, 0, 1 },
            { 1, 0, 1, 1, 0, 0 },
            { 1, 1, 0, 1, 0, 1 },
            { 0, 1, 1, 0, 1, 0 },
            { 0, 0, 0, 1, 0, 1 },
            { 1, 0, 1, 0, 1, 0 },
        },
    };
    for (size_t i = 0; i < adjM.size(); i++)
        BTKColoringCaller(adjM[i].size(), K, adjM[i]);
}