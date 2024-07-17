#include "loja.hpp"
#include <iostream>
#include <algorithm>

Store::Store(int Rolls){
    NumRolls = Rolls;
    values.resize(NumRolls);
}

void Store::ReadValues()
{
    for(int i = 0; i < NumRolls; i++){
        std::cin >> values[i];
    }

    std::reverse(values.begin(), values.end());
}

int Store::MaxLengthShelf()
{
    // Vectors for two Dynamic Programming algorithms: Longest Increasing Subsequence (LIS)
    // and Longest Decreasing Subsequence (LDS)

    int LIS[NumRolls];
    int LDS[NumRolls];

    // Base case
    LIS[0] = LDS[0] = 1;

    for(int i = 1; i < NumRolls; i++){
        LIS[i] = LDS[i] = 1;

        for(int j = 0; j < i; j++){
            if(values[i] > values[j])
                LIS[i] = std::max(LIS[i], LIS[j] + 1);

            if(values[i] < values[j])
                LDS[i] = std::max(LDS[i], LDS[j] + 1);
        }
    }

    int sol = 0;

    for(int i = 0; i < NumRolls; i++)
        sol = std::max(sol, LIS[i] + LDS[i] - 1);

    return sol;
}