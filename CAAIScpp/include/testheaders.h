#pragma once
#include "headers.h"

//Ancient
void TestLiuhui();

//Test random number utilities functions
void RandRangeTest(int n, int low, int high);
void RandRangeSetTest(int n);
void RandDblTest(int n);
//void RandTest(int n);
void RandTest();

//sorting tests
void TestSelectionSort(int n);
void TestBubbleSort(int n);
void TestInsertionSort(int n);
void TestQuickSort(int n);
void TestTwoWayMerge(int m, int n);
void TestMergeSort(int n);
void TestMaxHeapify(int n);
void TestHeapSort(int n);
void TestSorting();

//classical
void TestSequentialSearch(int n);
void BinarySearchRTest(int n);
void TestShuffle(int n);

//Divide and Conquer
void TestBinarySearch(int n);
void TestChessBoardTiling(int n);

//EuclidGCD
void TestEuclidGCDR(int a, int b);
void TestEuclidGCDStepsR(int a, int b);
void TestEuclidGCDTypicalCasesR(bool showSteps = false);

void TestEuclidGCD();
void TestEuclidGCDSteps();

//Primality test
void TestPrimalTestTrialDiv(int n);
void TestPrimalTestTrialDivDetail(int n);
void TestPrimalTestTrialDivRange(int m, bool detail = false);

//Exhaustive search
void TestSubsetting(int n);
void TestPermuting(int n);
void TestPermuting1(int n);
void TestPermutingIter(int n);
void TestPermutingIterA(int n);
void TestPermutingIterT(int n);
void TestPermutingSJT(int n);
void TestGraphBFS(int v0);
void TestGraphDFS(int v0);

void TestESTSP18SD(int n);
void TestESTSP18();
void TestES0_1KnapsackA();
void TestES0_1KnapsackR(int n = 6, int wRange = 20, int vRange = 20);
void ESPermutationTreeI(int n);
void ESPermutationTreeJ(int n);
void ESPermutationTreeT(int n);
void TestESTSPA();
void TestESTSP_UTA();
void TestESTSP_UT_FA();
void TestESTSP_UT_SD(int low, int high);
void TestESTSP_UT_SD_P(int low, int high);
void TestESTSP_UT_SD_TH(int low, int high);

//Dynamic programming
void TestLSEditDist();
void TestLSEditDist1();
void TestDPMatrixChain();
void TestDP0_1Knapsack();
void TestTSP_BHK_DPvA();
void TestTSP_BHK_DPA();
void TestTSP_BHK_DP_N_SD(int N);
void TestDPTSP();
void TestDPTSP8();
void TestDPTSP8a();
//void TestDPTSPRandom();

//RSA
void TestRSA(int mx = 0, int my = 20);
void TestMRPT();
void TestRS4ME();
void TestExtEucGCDNonRec();
void TestExtEuclidGCD();
void TestMODInverse();
void TestChnRA();

//Graph
void TestDFSM_BFSM(char t);

//Greedy search
void TestKruskalMST(int v0 = 0);
void TestPrimMST(int v0 = 0);
void TestDijkstraSSSP(int v0 = 0);
void TestHuffmanCoding();

//Branch and Bound
void TestBB0_1Knapsack();
void TestBBTSP();
void TestBBTSPRandom();
int TestBBTSPtd();
void TestBBTSPt();

//Backtracking
void TestBTnQueens(int n = 4);
void TestBTKColoring(int K = 3);