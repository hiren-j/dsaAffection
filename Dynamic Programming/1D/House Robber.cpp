// Program to find the maximum amount of money that you can rob tonight without alerting the police ~ coded by Hiren
#include <iostream>
#include <cstdlib>
#include <vector>

// Class to implement the "Top Down Approach"
class TopDown {
public:
    // Method to find the maximum amount of money you can rob, using recursion without memoization - O(N) & O(N)
    int getMaxMoney(std::vector<int>& houses) {
        int N = houses.size();
        std::vector<int> memory(N+1, -1);
        return solveWithMemo(houses, memory, N, 0);
    }

private:
    // O(2^N) & O(N)
    int solveWithoutMemo(std::vector<int>& houses, int N, int J) {
        // Edge case: If all the houses are exhausted, then it's not possible to rob anymore
        if(J >= N)
            return 0;

        // There are always two possibilities at each house for the robber
        int currHouseRob  = houses[J] + solveWithoutMemo(houses, N, J+2); // Is to rob the current house and then advance two steps ahead from this house
        int currHouseSkip = solveWithoutMemo(houses, N, J+1);             // Is to skip the current house and move to the next house

        // Return the maximum money get from both the possibilities
        return std::max(currHouseRob, currHouseSkip);
    }

    // O(N) & O(N)
    int solveWithMemo(std::vector<int>& houses, std::vector<int>& memory, int N, int J) {
        // Edge case: If all the houses are exhausted, then it's not possible to rob anymore
        if(J >= N)
            return 0;

        // Memoization table: If the current state is already computed, then return the computed value
        if(memory[J] != -1)
            return memory[J];

        // There are always two possibilities at each house for the robber
        int currHouseRob  = houses[J] + solveWithMemo(houses, memory, N, J+2); // Is to rob the current house and then advance two steps ahead from this house
        int currHouseSkip = solveWithMemo(houses, memory, N, J+1);             // Is to skip the current house and move to the next house

        // Store the maximum money (get from both the possibilities) to the "memoization table" and then return the value
        return memory[J] = std::max(currHouseRob, currHouseSkip);
    }
};

// Class to implement the "Bottom Up Approach"
class BottomUp {
public:
    // #1 Method to find the maximum amount of money you can rob, using 1D buffer for tabulation - O(N) & O(N)
    int getMaxMoney_A(std::vector<int>& houses) {
        int N = houses.size();

        // Tabulation buffer: dp[J] represents the maximum money that can be robbed till the Jth house
        std::vector<int> dp(N+1);
        dp[0] = 0;         // Initially no house at the beginning hence consider the money as zero
        dp[1] = houses[0]; // The maximum money for the first house is the money that the house have

        // Iterate and find the maximum money that can be robbed till the Jth house
        for(int J=2; J<=N; J++)
            dp[J] = std::max(houses[J-1] + dp[J-2], dp[J-1]);

        // Stores the overall amount of maximum money that can be robbed
        return dp[N];
    }

    // #2 Method to find the maximum amount of money we can rob, using constant auxiliary space - O(N) & O(1)
    int getMaxMoney_B(std::vector<int>& houses) {
        int N = houses.size();
        
        int prevPrevMoney = 0;     // Initially no house at the beginning hence consider the money as zero
        int prevMoney = houses[0]; // The maximum money for the first house is the money that the house have
        int maxMoney = prevMoney;  // Stores the overall amount of maximum money that can be robbed

        // Iterate and find the maximum money that can be robbed till the Jth house
        for(int J=2; J<=N; J++)
            maxMoney = std::max(houses[J-1] + prevPrevMoney, prevMoney),
            prevPrevMoney = prevMoney,
            prevMoney = maxMoney;

        // Stores the overall amount of maximum money that can be robbed
        return maxMoney;
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userWantsOp = true;

    while(userWantsOp) {
        // Handles console clearance for both "windows" and "linux" user
        system("cls || clear");

        // Input the size of the array
        int N;
        std::cout<<"Enter the number of houses you want: ";
        std::cin>>N;

        // Check the given size is valid or not
        if(N <= 0) {
            std::cout<<"Enter a valid value, applicatin expects a positive integer!";
            return 0;
        }

        // Stores the array values
        std::vector<int> houses(N, 0);

        // Input the array values
        for(int i=0; i<N; i++) {
            std::cout<<"Enter the money you want to stash in the "<<i+1<<"th house: ";
            std::cin>>houses[i];
        }

        // Call to find the maximum amount of money that can be robbed
        BottomUp bottomUp;
        int maxMoney = bottomUp.getMaxMoney_B(houses);
        std::cout<<"\nThe maximum amount of money that you can rob tonight without alerting the police is: "<<maxMoney;

        // Input section to handle the flow of iterations of the application
        char userChoise;
        std::cout<<"\n\nPress \'R\' to restart the application, else it will exit automatically: ";
        std::cin>>userChoise;
        userWantsOp = (userChoise == 'R' ? true : false);
    }

    return 0;
}
/*
    Topics: Array | Dynamic Programming
    Links: https://leetcode.com/problems/house-robber/description/?envType=daily-question&envId=2024-01-21
           https://www.codingninjas.com/studio/problems/maximum-sum-of-non-adjacent-elements_843261 
           https://www.geeksforgeeks.org/problems/stickler-theif-1587115621/1?itm_source=geeksforgeeks&itm_medium=article&itm_campaign=bottom_sticky_on_article
*/
