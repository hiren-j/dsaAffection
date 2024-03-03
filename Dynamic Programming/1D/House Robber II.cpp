// Program to find the maximum amount of money that you can rob tonight without alerting the police ~ coded by Hiren
#include <iostream>
#include <cstdlib>
#include <vector>

// Class to implement the "Top Down Approach":
class TopDown {
public:
    // Method to find the maximum amount of money you can rob, using recursion with memoization - O(N) & O(N)
    int robMaxMoney(std::vector<int>& houses) {
        int N = houses.size();

        // Edge case: When there's only a single house then the maximum money you can rob is the money that the house have
        if(N == 1)
            return houses[0];

        // Tables for memoization
        std::vector<int> memoryA(N+1, -1), memoryB(N+1, -1);
        
        int startFromZero = solveWithMemo(houses, memoryA, 0, N-1); // Visit all the houses excluding the last house
        int startFromOne  = solveWithMemo(houses, memoryB, 1, N);   // Visit all the houses excluding the first house

        // Return the maximum money get from both the possibilities
        return std::max(startFromZero, startFromOne);
    }

private:
    // O(N) & O(N)
    int solveWithMemo(std::vector<int>& houses, std::vector<int>& memory, int start, int end) {
        // Edge case: If all the houses are exhausted, then it's not possible to rob anymore
        if(start >= end)  
            return 0;

        // Memoization table: If the current state is already computed, then return the computed value
        if(memory[start] != -1)
            return memory[start];

        // There are always two possibilities at each house for the robber
        int currHouseRob  = houses[start] + solveWithMemo(houses, memory, start+2, end); // Is to rob the current house and then advance two steps ahead from this house
        int currHouseSkip = solveWithMemo(houses, memory, start+1, end);                 // Is to skip the current house and move to the next house

        // Store the maximum money (get from both the possibilities) to the "memoization table" and then return the value
        return memory[start] = std::max(currHouseRob, currHouseSkip);
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(std::vector<int>& houses, int start, int end) {
        // Edge case: If all the houses are exhausted, then it's not possible to rob anymore
        if(start >= end)  
            return 0;

        // There are always two possibilities at each house for the robber
        int currHouseRob  = houses[start] + solveWithoutMemo(houses, start+2, end); // Is to rob the current house and then advance two steps ahead from this house
        int currHouseSkip = solveWithoutMemo(houses, start+1, end);                 // Is to skip the current house and move to the next house

        // Return the maximum money get from both the possibilities
        return std::max(currHouseRob, currHouseSkip);
    }
};

// #1 Class to implement the "Bottom Up Approach":
class BottomUp_V1 {
public:
    // Method to find the maximum amount of money you can rob, using tabulation - O(N) & O(N)
    int robMaxMoney(std::vector<int>& houses) {
        int N = houses.size();

        // Edge case: When there's only a single house then the maximum money you can rob is the money that the house have
        if(N == 1)
            return houses[0];

        std::vector<int> excLastHouse;  // Buffer to Store the houses excluding the last house
        std::vector<int> excFirstHouse; // Buffer to Store the houses excluding the first house

        // Iterate and store the houses to their corresponding buffer
        for(int J=0; J<N; J++) {
            if(J < N-1) 
                excLastHouse.push_back(houses[J]);
            if(J > 0)
                excFirstHouse.push_back(houses[J]);
        }

        int maxMoneyA = solveWithoutTable(excLastHouse);  // Visit all the houses excluding the last house
        int maxMoneyB = solveWithoutTable(excFirstHouse); // Visit all the houses excluding the first house

        // Return the maximum money get from both the possibilities
        return std::max(maxMoneyA, maxMoneyB);
    }

private:
    // O(N) & O(1)
    int solveWithoutTable(std::vector<int>& houses) {
        int N = houses.size();
        
        int prevPrevMoney = 0;     // Initially no house at the beginning hence consider the money as zero
        int prevMoney = houses[0]; // The maximum money for the first house is the money that the house have
        int maxMoney = prevMoney;  // Stores the overall amount (maximum money) that can be robbed

        // Iterate and find the maximum money that can be robbed till the Jth house
        for(int J=2; J<=N; J++)
            maxMoney = std::max(houses[J-1] + prevPrevMoney, prevMoney),
            prevPrevMoney = prevMoney,
            prevMoney = maxMoney;

        // Return the overall amount (maximum money) that can be robbed
        return maxMoney;
    }

    // O(N) & O(N)
    int solveWithTable(std::vector<int>& houses) {
        int N = houses.size();

        // Tabulation buffer: dp[J] represents the maximum money that can be robbed till the Jth house
        std::vector<int> dp(N+1, 0);
        
        // The maximum money for the first house is the money that the house have
        dp[1] = houses[0]; 

        // Iterate and find the maximum money that can be robbed till the Jth house
        for(int J=2; J<=N; J++)
            dp[J] = std::max(houses[J-1] + dp[J-2], dp[J-1]);

        // Return the overall amount (maximum money) that can be robbed
        return dp[N];
    }
};

// #2 Class to implement the "Bottom Up Approach":
class BottomUp_V2 {
public:
    // Method to find the maximum amount of money you can rob, using tabulation - O(N) & O(N)
    int robMaxMoney(std::vector<int>& houses) {
        int N = houses.size();

        // Edge case: When there's only a single house then the maximum money you can rob is the money that the house have
        if(N == 1)
            return houses[0];

        // Visit all the houses excluding the last house
            // Tabulation buffer: dp1[J] represents the maximum money that can be robbed till the Jth house
            std::vector<int> dp1(N, 0);

            // The maximum money for the first house is the money that the house have
            dp1[1] = houses[0];

            // Iterate and find the maximum money that can be robbed till the Jth house
            for(int J=2; J<N; J++)
                dp1[J] = std::max(houses[J-1] + dp1[J-2], dp1[J-1]);

        // Visit all the houses excluding the first house
            // Tabulation buffer: dp2[J] represents the maximum money that can be robbed till the Jth house
            std::vector<int> dp2(N, 0);

            // The maximum money for the first house is the money that the house have
            dp2[1] = houses[1];
            
            // Iterate and find the maximum money that can be robbed till the Jth house
            for(int J=2; J<N; J++)
                dp2[J] = std::max(houses[J] + dp2[J-2], dp2[J-1]);

        // Return the overall amount (maximum money) that can be robbed
        return std::max(dp1[N-1], dp2[N-1]);
    }
};

// #3 Class to implement the "Bottom Up Approach":
class BottomUp_V3 {
public:
    // Method to find the maximum amount of money you can rob, using constant auxiliary space - O(N) & O(1)
    int robMaxMoney(std::vector<int>& houses) {
        int N = houses.size();

        // Edge case: When there's only a single house then the maximum money you can rob is the money that the house have
        if(N == 1)
            return houses[0];

        int maxMoneyA = getMaxMoney(houses, N, 0, N-2); // Visit all the houses excluding the last house
        int maxMoneyB = getMaxMoney(houses, N, 1, N-1); // Visit all the houses excluding the first house

        // Return the overall amount (maximum money) that can be robbed
        return std::max(maxMoneyA, maxMoneyB);
    }

private:
    // O(N) & O(1)
    int getMaxMoney(std::vector<int>& houses, int N, int start, int end) {
        int prevPrevMoney = 0;         // Initially no house at the beginning hence consider the money as zero
        int prevMoney = houses[start]; // The maximum money for the first house is the money that the house have
        int maxMoney = prevMoney;      // Stores the overall amount of maximum money that can be robbed

        // Iterate and find the maximum money that can be robbed till the Jth house
        for(int J = start+1; J <= end; ++J) 
            maxMoney = std::max(houses[J] + prevPrevMoney, prevMoney),
            prevPrevMoney = prevMoney,
            prevMoney = maxMoney;

        // Return the maximum money that can be robbed
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
        std::cout<<"Enter the number of houses: ";
        std::cin>>N;

        // Check the given size is valid or not
        if(N <= 0 || N >= 101) {
            std::cout<<"Enter a value which lies within the problem constraints! Application expects a positive integer!";
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
        BottomUp_V3 bottomUp;
        int maxMoney = bottomUp.robMaxMoney(houses);
        std::cout<<"\nThe maximum amount of money that you can rob tonight without alerting the police is: "<<maxMoney;

        // Input section to handle the flow of iterations of the application
        char userChoice;
        std::cout<<"\n\nPress \'R\' to restart the application, else it will exit automatically: ";
        std::cin>>userChoice;
        userWantsOp = (userChoice == 'R' ? true : false);
    }

    return 0;
}
/*
    Topics: Array | Dynamic Programming
    Link: ht/tps://leetcode.com/problems/house-robber-ii/
*/
