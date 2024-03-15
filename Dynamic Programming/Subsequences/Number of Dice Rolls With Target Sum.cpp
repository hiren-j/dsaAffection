// Program to find the number of possible ways (out of the K^N total ways) to roll the dice, so the sum of the face-up numbers equals the target value ~ coded by Hiren
#include <iostream>
#include <cstdlib>
#include <vector>
#define mod 1000000007
using namespace std;

// Class to implement the Top-down approach:
class TopDown {
public:
    // Method to find the number of possible ways to roll the dice so the sum of the face-up numbers equals the target, using recursion with memoization - O(K*N*T) & O(N*T) : Where T let be the target
    int numRollsToTarget(int N, int K, int target) {
        vector<vector<int>> memory(N + 1, vector<int>(target + 1, -1));
        return solveWithMemo(memory, N, K, target);
    }

private:
    // O(K*N*T) & O(N*T)
    int solveWithMemo(vector<vector<int>>& memory, int N, int K, int target) {
        // Edge case: If all the dice are rolled, then it's not possible to roll any dice anymore
        if(N == 0) 
            return (target == 0);

        // Memoization table: If the current state is already computed, then return the computed value
        if(memory[N][target] != -1)
            return memory[N][target];

        // Stores the "total number of possible ways so the sum of the face-up numbers equals the target / result value"
        int count = 0;

        // Iterate and if possible, then take the face number in the target
        for(int face = 1; face <= K; ++face) {
            if(face <= target) {
                count = (count + solveWithMemo(memory, N - 1, K, target - face)) % mod;
            }
        }   

        // Store the result value to the memoization table and then return it
        return memory[N][target] = count;
    }

    // O(K^N) & O(N)
    int solveWithoutMemo(int N, int K, int target) {
        // Edge case: If all the dice are rolled, then it's not possible to roll any dice anymore
        if(N == 0) 
            return (target == 0);

        // Stores the "total number of possible ways so the sum of the face-up numbers equals the target / result value"
        int count = 0;

        // Iterate and if possible, then take the face number in the target
        for(int face = 1; face <= K; ++face) {
            if(face <= target) {
                count = (count + solveWithoutMemo(N - 1, K, target - face)) % mod;
            }
        }

        // Return the result value
        return count;
    }
};

// Class to implement the Bottom-up approach:
class BottomUp {
public:
    // #1 Method to find the number of possible ways to roll the dice so the sum of the face-up numbers equals the target, using 2D buffer for tabulation - O(N*T*K) & O(N*T) : Where T let be the target
    int numRollsToTarget_V1(int N, int K, int target) {        
        // Tabulation buffer: dp[dice][currTarget] represents the total number of possible ways so the sum of the face-up numbers equals the "currTarget" such that by rolling "dice" number of dice
        vector<vector<int>> dp(N + 1, vector<int>(target + 1, 0));

        // Edge case: If there is no dice and the target is 0, then there exists a single way
        dp[0][0] = 1;

        // Treat each "dice" as the number of dice rolled and find the total number of possible ways so the sum of the face-up numbers equals the "currTarget"
        for(int dice = 1; dice <= N; ++dice) {
            for(int currTarget = 0; currTarget <= target; ++currTarget) {
                int count = 0;
                for(int face = 1; face <= K; ++face) {
                    if(face <= currTarget) {
                        count = (count + dp[dice - 1][currTarget - face]) % mod;
                    }
                }
                dp[dice][currTarget] = count;
            }
        }
        
        // Return the number of possible ways to roll the dice so the sum of the face-up numbers equals the given target
        return dp[N][target];
    }

    // #2 Method to find the number of possible ways to roll the dice so the sum of the face-up numbers equals the target, using 1D buffer for tabulation - O(N*T*K) & O(T) : Where T let be the target
    int numRollsToTarget_V2(int N, int K, int target) {        
        // Tabulation buffer: "prevRow[currTarget] / currRow[currTarget]" represents the total number of possible ways so the sum of the face-up numbers equals the "currTarget" such that by rolling "dice" number of dice
        vector<int> prevRow(target + 1, 0), currRow(target + 1, 0);

        // Edge case: If there is no dice and the target is 0, then there exists a single way
        prevRow[0] = 1;

        // Treat each "dice" as the number of dice rolled and find the total number of possible ways so the sum of the face-up numbers equals the "currTarget"
        for(int dice = 1; dice <= N; ++dice) {
            for(int currTarget = 0; currTarget <= target; ++currTarget) {
                int count = 0;
                for(int face = 1; face <= K; ++face) {
                    if(face <= currTarget) {
                        count = (count + prevRow[currTarget - face]) % mod;
                    }
                }
                currRow[currTarget] = count;
            }
            prevRow = currRow;
        }

        // Return the number of possible ways to roll the dice so the sum of the face-up numbers equals the given target
        return prevRow[target];
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userWantsOperation = true;

    while(userWantsOperation) {
        // Controls console clearance for both "windows" and "linux" user
        system("cls || clear");

        cout<<"Note: The application only accepts non-decimal numeric type value, unless specified!\n\n";

        // Input the N value
        int N;
        cout<<"Enter the value of N: ";
        cin>>N;

        // Input the K value
        int K;
        cout<<"Enter the value of K: ";
        cin>>K;

        // Input the target value
        int target;
        cout<<"Enter the target value: ";
        cin>>target;

        // Check the given values are valid or not
        if(N <= 0 || N >= 31 || K <= 0 || K >= 31) {
            cout<<"You must enter the value of N and K, which lies between 1 and 30!";
        }
        else if(target <= 0 || target >= 1001) {
            cout<<"You must enter the target value, which lies between 1 and 1000!";
        }
        else {
            BottomUp bottomUp;
            int numWays = bottomUp.numRollsToTarget_V2(N, K, target);
            cout<<"\nThe total number of possible ways to roll the dice so the sum of the face-up numbers equals the target "<<target<<" is: "<<numWays;
        }

        // Input section to control the flow of iterations of the application
        char userChoice;
        cout<<"\n\nPress \'R\' to restart the application, else it will exit: ";
        cin>>userChoice;
        userWantsOperation = (userChoice == 'R' ? true : false);
    }

    return 0;
}
/*
    Topics: Array | Dynamic Programming
    Link: https://leetcode.com/problems/number-of-dice-rolls-with-target-sum/description/?envType=daily-question&envId=2023-12-26
*/
