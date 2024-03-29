#include "../include/testheaders.h"
#include "../include/test.h"

int main()
{
	//SetRandSeed(-1);
    //SetRandSeed(23);
    ConfigConsole();
    SetLogFile("SD_TSP_TH_15");
    //SetLogFile("BHK_DP_N_SD(17)");

    char beginTimeStr[100];
    GetDateTime(beginTimeStr);
    printf("Begin time: %s\n", beginTimeStr);
    if (logFP != stdout)
        fprintf(logFP, "Begin time: %s\n", beginTimeStr);
    clock_t begin = clock();
    
    //Error Control
    //TestParityCheck(4, 30, 0);
    //Ancicent
    TestLiuhui();
     
    //RSA
    //TestRSA();
    //TestMRPT();
    //TestRS4ME();
    //TestChnRA();
    //TestMODInverse();
    //TestExtEuclidGCD();
    //TestExtEucGCDNonRec();

    //Backtracking
    //TestBTnQueens(20);
    //TestBTKColoring(4);

    //***Dynamic programming
    //TestLSEditDist();
    //TestLSEditDist1();
    //TestDPMatrixChain();
    //TestDP0_1Knapsack();
    //TestDPTSP();
    //TestDPTSP8();
    //TestDPTSP8a();
    //TestTSP_BHK_DP_N_SD(17);
    //TestTSP_BHK_DPA();
    //TestTSP_BHK_DPvA();

    //***Threading
    //TestESTSP_UT_SD_TH(7, 7);

    //Divide and conquer
    //TestBinarySearch(8);
    //TestChessBoardTiling(4);

    //***Exhaustive search
    //TestESTSP_UT_SD_P(7, 7);
    //TestESTSP_UT_SD(5, 5);
    //TestESTSP_UT_FA();
    //TestESTSP_UTA();
    //TestESTSPA();
    //TestESTSP18();
    //TestESTSP18SD(10);

    //Exhaustive Search
    //TestSubsetting(4);
    //TestPermuting(4);
    //TestPermuting1(4);
    //TestPermuting1(9100);
    //183900 causes stack overflow,
    //but 183800 not at stack size 4M(4194304)
    //18200 for stack size 4M(4194304)
    //TestPermuting(18200);
    //9100 for stack size 2M(2097152)
    //TestPermuting(9100);
    //4500 for stack size 1M(1048576)
    //TestPermuting(4500);
    //TestPermutingIter(4);
    //TestPermutingIter(1000000);
    //TestPermutingIterA(4);
    //TestPermutingIterA(1000000);
    //TestPermutingIterT(3);
    //TestPermutingSJT(3);
    //TestGraphBFS(3);
    //TestGraphDFS(3);

    //EnumSubsetsT(3);
    //TestES0_1KnapsackR(20, 16, 26);
    //TestES0_1KnapsackR();
    //TestES0_1KnapsackA();

    //ESPermutationTreeT(7);
    //ESPermutationTreeJ(7);
    //ESPermutationTreeI(7);
    //ESSubsetTree(7);
    //TestPrimalTestTrialDivRange(100, true);
    //PermutingSJT(4);

    //***Graph
    //TestDFS_BFS('D');
    //TestDFSM_BFSM('B');
    //DFSCaller();
    
    //Greedy Algorithms
    //TestDijkstraSSSP(5);
    //TestPrimMST(0);
    //TestKruskalMST(0);
    //TestHuffmanCoding();

    //Branch and Bound
    //TestBB0_1Knapsack();
    //TestBBTSP();
    //TestBBTSPRandom();
    //TestBBTSPt();
    //TestBBTSPtd();

    //***Classical
    //BinarySearchRTest(8);
    //TestSequentialSearch(8);
	//TestEuclidGCDTypicalCasesR();
	//TestEuclidGCDTypicalCases(true);
    //TestEuclidGCDTypicalCases();
    //TestEuclidGCDSteps(168, 180);
    //TestEuclidGCDSteps(252, 105);
    //TestEuclidGCD();
    //TestShuffle(5);

    //***Sorting
    //TestHeapSort(8);
	//TestMaxHeapify(8);
    //TestMergeSort(10);
	//TestTwoWayMerge(3, 4);
	//TestQuickSort(10);
	//TestInsertionSort(10);
	//TestBubbleSort(10);
    //TestSelectionSort(10);
    //TestSorting();

    //***Pseudo random number
    //RandRangeTest(10, 0, 100);
    //RandRangeSetTest(10);
    //RandDblTest(10);
    //RandTest(10);
    //RandTest();

    //***Pure language test
    ////threading
    //TestThread2();
    //TestThread1();
    ////basic languange tests
    //TestHash();
    //TestTimeb();
    //Testfprintf();
    //test1Dto2D();
    //basicOutputTest();
    ////
    //basicTests();

    clock_t end = clock();

    printf("\nBegin time: %s\n", beginTimeStr);
    char endTimeStr[100];
    GetDateTime(endTimeStr);
    printf("End time: %s\n", endTimeStr);
    double time_spent = ((double)end - (double)begin) / CLOCKS_PER_SEC;
    if (time_spent > 3600) {
        printf("\nTime spent: %.3lf hours.\n", time_spent / 3600);
    }
    else if (time_spent > 60) {
        printf("\nTime spent: %.3lf minutes.\n", time_spent / 60);
    }
    else {
        printf("\nTime spent: %.3lf seconds.\n", time_spent);
    }

    //fprintf(logFP, "What's in your hand, is intelligence.\n");
    if (logFP != stdout)
    {
        fprintf(logFP, "\nBegin time: %s\n", beginTimeStr);
        fprintf(logFP, "End time: %s\n", endTimeStr);
        if (time_spent > 3600) {
            fprintf(logFP, "\nTime spent: %.3lf hours.\n", time_spent / 3600);
        }
        else if (time_spent > 60) {
            fprintf(logFP, "\nTime spent: %.3lf minutes.\n", time_spent / 60);
        }
        else {
            fprintf(logFP, "\nTime spent: %.3lf seconds.\n", time_spent);
        }
        fclose(logFP);
    }

    printf("\nExecution ended, press ENTER to return.\n");
	getchar();
	return 0;
}
