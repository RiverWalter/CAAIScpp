#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
static void BuildHuffmanTree();
static void Initialization(vector<pair<char, int>> chars);
static void Finalization();
struct HFMNode {
    char Ch; int Freq;
    HFMNode* Left, * Right;
    HFMNode(char pCh, int pFreq, HFMNode* pLeft, HFMNode* pRight)
        : Ch(pCh), Freq(pFreq), Left(pLeft), Right(pRight) {}
    HFMNode(char pCh, int pFreq)
        : HFMNode(pCh, pFreq, NULL, NULL) {}
};
static void MinHeapify(vector<HFMNode*>& H);
static void InsertH(vector<HFMNode*>& H, HFMNode* node);
static void SiftDown(vector<HFMNode*>& H, int i);
static void SiftUp(vector<HFMNode*>& H, int i);
static HFMNode* ExtractMin(vector<HFMNode*>& H);
static void DeleteANode(HFMNode* node);
static void ShowInput(vector<pair<char, int>> chars);
static void Output();
static vector<HFMNode *> Q;
void HuffmanCodingCaller(vector<pair<char, int>> chars)
{
    ShowInput(chars);
    Initialization(chars);
    BuildHuffmanTree();
    Output();
    Finalization();
}
void BuildHuffmanTree()
{
    char C = 'A';
    while (Q.size() > 1)
    {
        HFMNode* x = ExtractMin(Q);
        HFMNode* y = ExtractMin(Q);
        HFMNode* z = new HFMNode(C++, x->Freq + y->Freq, x, y);
        InsertH(Q, z);
    }
}
static HFMNode* ExtractMin(vector<HFMNode*>& H)
{
    swap(H.front(), H.back());
    HFMNode* p = H.back();
    H.pop_back();
    if (!H.empty())
        SiftDown(H, 0);
    return p;
}
static void InsertH(vector<HFMNode*>& H, HFMNode* node)
{
    H.push_back(node);
    SiftUp(H, H.size() - 1);
}
static void SiftUp(vector<HFMNode*>& H, int i)
{
    while (i > 0 && H[i]->Freq < H[(i - 1) >> 1]->Freq) {
        swap(H[i], H[(i - 1) >> 1]);
        i = (i - 1) >> 1;
    }
}
static void SiftDown(vector<HFMNode*> &H, int i)
{
    while ((i = (i << 1) + 1) < H.size()) {
        if ((i + 1 < H.size()) && (H[i + 1]->Freq < H[i]->Freq))
            i = i + 1;
        if (H[(i - 1) >> 1]->Freq > H[i]->Freq)
            swap(H[(i - 1) >> 1], H[i]);
        else break;
    }
}
static void MinHeapify(vector<HFMNode*> &H)
{
    for (int i = (H.size() >> 1) - 1; i >= 0; i--) {
        SiftDown(H, i);
    }
}

static void Initialization(vector<pair<char, int>> chars)
{
    Q.clear();
    for (auto ch : chars)
        Q.push_back(new HFMNode(ch.first, ch.second));
    MinHeapify(Q);
}
static void Finalization()
{
    for (auto node : Q)
        DeleteANode(node);
}
static void DeleteANode(HFMNode* node)
{
    if (node->Left)
    {
        DeleteANode(node->Left);
        DeleteANode(node->Right);
    }
    delete node;
}
static void ShowInput(vector<pair<char, int>> chars)
{
    printf("Huffman coding input: \n");
    for (auto c : chars)
        printf("%c,%d; ", c.first, c.second);
    printf("\n");
}
static vector<char> coding;
static vector<pair<char, vector<char>>> codingList;
static void GetHuffmanCoding(HFMNode* node)
{
    if (node->Left)
    {
        coding.push_back('0');
        GetHuffmanCoding(node->Left);
        coding.pop_back();
        coding.push_back('1');
        GetHuffmanCoding(node->Right);
        coding.pop_back();
    }
    else
    {
        codingList.push_back(pair<char, vector<char>>(node->Ch, coding));
    }
}
static void Output()
{
    printf("\nHuffman coding:\n");
    coding.clear();
    codingList.clear();
    GetHuffmanCoding(Q[0]);
    sort(codingList.begin(), codingList.end(),
        [](pair<char, vector<char>>a, pair<char, vector<char>>b) 
        {return a.first < b.first; });
    for (auto c1 : codingList)
    {
        printf("list %c: ", c1.first);
        for (auto c2 : c1.second)
            printf("%c", c2);
        printf("\n");
    }
}
