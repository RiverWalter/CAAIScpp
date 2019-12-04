#include "../../../include/headers.h"
void TestHuffmanCoding()
{
    vector<vector<pair<char, int>>> charLists = {
        {
            //Introduction to Algorithms
            { {'a', 40}, {'b', 13}, {'c',12}, {'d',16},  {'e',9},  {'f',5}, },
        },
        {
            { {'a', 40}, {'b', 13}, {'c',12}, {'d',16},  {'e',9},  {'f',1}, },
        },
    };
    int n = charLists.size();
    //printf("n=%d\n", n);
    for (int i = 0; i < n; i++)
    {
        //printf("i=%d, size=%d\n", i, charLists[i].size());
        //for (auto p : charLists[i])
        //    printf("char=%c, freq=%d\n", p.first, p.second);
        HuffmanCodingCaller(charLists[i]);
    }
}