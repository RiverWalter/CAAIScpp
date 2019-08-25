#include "../../include/headers.h"
void TestESTSP_UT_SD(int low = 0, int high = 0)
{
    const char *cityNames[] =
    { "����", "�ൺ", "�Ͳ�", "��ׯ", "��Ӫ", "��̨", "Ϋ��", "����",
      "̩��", "����", "����", "����", "����", "����", "�ĳ�", "����", "����"
    };
    int N0 = 8;
    int distMat0[] = {
        3665, 1156, 2339, 2292, 4589, 2129, 1831, 
              2641, 4153, 2763, 2300, 1598, 4199, 
                    3123, 1277, 3574, 1114, 2698, 
                          4318, 6003, 3801, 1181, 
                                3477, 1283, 3977, 
                                      2538, 6062, 
                                            3817 };

    int N1 = 9;
    int distMat1[] = {
        3665, 1156, 2339, 2292, 4589, 2129, 1831,  776,
              2641, 4153, 2763, 2300, 1598, 4199, 3361,
                    3123, 1277, 3574, 1114, 2698, 1466,
                          4318, 6003, 3801, 1181, 1747,
                                3477, 1283, 3977, 2745,
                                      2538, 6062, 5050,
                                            3817, 2585,
                                                  1315 };
    int N2 = 10;
    int distMat2[] = {
        3665, 1156, 2339, 2292, 4589, 2129, 1831,  776, 5203,
              2641, 4153, 2763, 2300, 1598, 4199, 3361, 2730,
                    3123, 1277, 3574, 1114, 2698, 1466, 4188,
                          4318, 6003, 3801, 1181, 1747, 6617,
                                3477, 1283, 3977, 2745, 4091,
                                      2538, 6062, 5050,  654,
                                            3817, 2585, 3138,
                                                  1315, 6678,
                                                        5652 };
    int N3 = 11;
    int distMat3[] = {
        3665, 1156, 2339, 2292, 4589, 2129, 1831,  776, 5203, 3467,
              2641, 4153, 2763, 2300, 1598, 4199, 3361, 2730, 1470,
                    3123, 1277, 3574, 1114, 2698, 1466, 4188, 2973,
                          4318, 6003, 3801, 1181, 1747, 6617, 2797,
                                3477, 1283, 3977, 2745, 4091, 3259,
                                      2538, 6062, 5050,  654, 3334,
                                            3817, 2585, 3138, 2278,
                                                  1315, 6678, 2858,
                                                        5652, 2762,
                                                              3943 };
    int N4 = 12;
    int distMat4[] = {
        3665, 1156, 2339, 2292, 4589, 2129, 1831,  776, 5203, 3467,  999,
              2641, 4153, 2763, 2300, 1598, 4199, 3361, 2730, 1470, 2782,
                    3123, 1277, 3574, 1114, 2698, 1466, 4188, 2973,  890,
                          4318, 6003, 3801, 1181, 1747, 6617, 2797, 2251,
                                3477, 1283, 3977, 2745, 4091, 3259, 2169,
                                      2538, 6062, 5050,  654, 3334, 4473,
                                            3817, 2585, 3138, 2278, 2008,
                                                  1315, 6678, 2858, 1819,
                                                        5652, 2762,  569,
                                                              3943, 5082,
                                                                    2476 };
    int N5 = 13;
    int distMat5[] = {
        3665, 1156, 2339, 2292, 4589, 2129, 1831,  776, 5203, 3467,  999, 2617,
              2641, 4153, 2763, 2300, 1598, 4199, 3361, 2730, 1470, 2782, 2752,
                    3123, 1277, 3574, 1114, 2698, 1466, 4188, 2973,  890, 2369,
                          4318, 6003, 3801, 1181, 1747, 6617, 2797, 2251, 1452,
                                3477, 1283, 3977, 2745, 4091, 3259, 2169, 2930,
                                      2538, 6062, 5050,  654, 3334, 4473, 4615,
                                            3817, 2585, 3138, 2278, 2008, 2421,
                                                  1315, 6678, 2858, 1819, 2010,
                                                        5652, 2762,  569, 1912,
                                                              3943, 5082, 5224,
                                                                    2476, 1406,
                                                                          1625 };
    int N6 = 14;
    int distMat6[] = {
        3665, 1156, 2339, 2292, 4589, 2129, 1831,  776, 5203, 3467,  999, 2617, 1124,
              2641, 4153, 2763, 2300, 1598, 4199, 3361, 2730, 1470, 2782, 2752, 4577,
                    3123, 1277, 3574, 1114, 2698, 1466, 4188, 2973,  890, 2369, 2069,
                          4318, 6003, 3801, 1181, 1747, 6617, 2797, 2251, 1452, 3245,
                                3477, 1283, 3977, 2745, 4091, 3259, 2169, 2930, 2503,
                                      2538, 6062, 5050,  654, 3334, 4473, 4615, 5517,
                                            3817, 2585, 3138, 2278, 2008, 2421, 3053,
                                                  1315, 6678, 2858, 1819, 2010, 2728,
                                                        5652, 2762,  569, 1912, 1638,
                                                              3943, 5082, 5224, 6127,
                                                                    2476, 1406, 4375,
                                                                          1625, 2156,
                                                                                3522 };
    int N7 = 15;
    int distMat7[] = {
        3665, 1156, 2339, 2292, 4589, 2129, 1831,  776, 5203, 3467,  999, 2617, 1124, 1120,
              2641, 4153, 2763, 2300, 1598, 4199, 3361, 2730, 1470, 2782, 2752, 4577, 4641,
                    3123, 1277, 3574, 1114, 2698, 1466, 4188, 2973,  890, 2369, 2069, 2134,
                          4318, 6003, 3801, 1181, 1747, 6617, 2797, 2251, 1452, 3245, 2973,
                                3477, 1283, 3977, 2745, 4091, 3259, 2169, 2930, 2503, 3278,
                                      2538, 6062, 5050,  654, 3334, 4473, 4615, 5517, 5582,
                                            3817, 2585, 3138, 2278, 2008, 2421, 3053, 3117,
                                                  1315, 6678, 2858, 1819, 2010, 2728, 1688,
                                                        5652, 2762,  569, 1912, 1638, 1220,
                                                              3943, 5082, 5224, 6127, 6191,
                                                                    2476, 1406, 4375, 3898,
                                                                          1625, 2156, 2190,
                                                                                3522, 3045,
                                                                                      1741 };
    int N8 = 16;
    int distMat8[] = {
        3665, 1156, 2339, 2292, 4589, 2129, 1831,  776, 5203, 3467,  999, 2617, 1124, 1120, 1633,
              2641, 4153, 2763, 2300, 1598, 4199, 3361, 2730, 1470, 2782, 2752, 4577, 4641, 3344,
                    3123, 1277, 3574, 1114, 2698, 1466, 4188, 2973,  890, 2369, 2069, 2134,  836,
                          4318, 6003, 3801, 1181, 1747, 6617, 2797, 2251, 1452, 3245, 2973, 3758,
                                3477, 1283, 3977, 2745, 4091, 3259, 2169, 2930, 2503, 3278,  794,
                                      2538, 6062, 5050,  654, 3334, 4473, 4615, 5517, 5582, 4284,
                                            3817, 2585, 3138, 2278, 2008, 2421, 3053, 3117, 1819,
                                                  1315, 6678, 2858, 1819, 2010, 2728, 1688, 3327,
                                                        5652, 2762,  569, 1912, 1638, 1220, 2077,
                                                              3943, 5082, 5224, 6127, 6191, 4893,
                                                                    2476, 1406, 4375, 3898, 3675,
                                                                          1625, 2156, 2190, 1507,
                                                                                3522, 3045, 2995,
                                                                                      1741, 1954,
                                                                                            2223 };
    int N9 = 17;
    int distMat9[] = {
        3665, 1156, 2339, 2292, 4589, 2129, 1831,  776, 5203, 3467,  999, 2617, 1124, 1120, 1633, 2404,
              2641, 4153, 2763, 2300, 1598, 4199, 3361, 2730, 1470, 2782, 2752, 4577, 4641, 3344, 5292,
                    3123, 1277, 3574, 1114, 2698, 1466, 4188, 2973,  890, 2369, 2069, 2134,  836, 3568,
                          4318, 6003, 3801, 1181, 1747, 6617, 2797, 2251, 1452, 3245, 2973, 3758, 2470,
                                3477, 1283, 3977, 2745, 4091, 3259, 2169, 2930, 2503, 3278,  794, 4712,
                                      2538, 6062, 5050,  654, 3334, 4473, 4615, 5517, 5582, 4284, 7016,
                                            3817, 2585, 3138, 2278, 2008, 2421, 3053, 3117, 1819, 4552,
                                                  1315, 6678, 2858, 1819, 2010, 2728, 1688, 3327, 1193,
                                                        5652, 2762,  569, 1912, 1638, 1220, 2077, 2396,
                                                              3943, 5082, 5224, 6127, 6191, 4893, 7626,
                                                                    2476, 1406, 4375, 3898, 3675, 3947,
                                                                          1625, 2156, 2190, 1507, 2897,
                                                                                3522, 3045, 2995, 3094,
                                                                                      1741, 1954, 3310,
                                                                                            2223, 1733,
                                                                                                  4051 };

    for (int i = low; i <= high; i++)
    {
        switch (i)
        {
        case 0:
            TestESTSP_UT_N(N0, cityNames, distMat0);
            break;
        case 1:
            TestESTSP_UT_N(N1, cityNames, distMat1);
            break;
        case 2:
            TestESTSP_UT_N(N2, cityNames, distMat2);
            break;
        case 3:
            TestESTSP_UT_N(N3, cityNames, distMat3);
            break;
        case 4:
            TestESTSP_UT_N(N4, cityNames, distMat4);
            break;
        case 5:
            TestESTSP_UT_N(N5, cityNames, distMat5);
            break;
        case 6:
            TestESTSP_UT_N(N6, cityNames, distMat6);
            break;
        case 7:
            TestESTSP_UT_N(N7, cityNames, distMat7);
            break;
        case 8:
            TestESTSP_UT_N(N8, cityNames, distMat8);
            break;
        case 9:
            TestESTSP_UT_N(N9, cityNames, distMat9);
            break;
        }
    }
}