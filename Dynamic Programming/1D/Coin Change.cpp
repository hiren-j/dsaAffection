// Program to find the fewest number of coins that you need to make up the amount ~ coded by Hiren
#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
using namespace std;

// #1 Class to implement the Top-down approach:
class TopDown_V1 {
public:
    // Method to find the fewest number of coins, using recursion with memoization - O(N*A) & O(A) : Where N is the array size and A is the amount
    int coinChange(vector<int>& coins, int amount) {
        vector<int> memory(amount + 1, -1);
        int minCoins = solveWithMemo(memory, coins, amount, coins.size());
        return (minCoins == INT_MAX ? -1 : minCoins);
    }

private:
    // O(N*A) & O(A)
    int solveWithMemo(vector<int>& memory, vector<int>& coins, int amount, int N) {
        // Edge case: If the amount becomes zero, then it's not possible to pick any more coin
        if(amount == 0)
            return 0;
        
        // Memoization table: If the current state is already computed, then return the computed value
        if(memory[amount] != -1)
            return memory[amount];

        // Stores the "fewest number of coins which make up the amount / result value"
        int minCoins = INT_MAX;

        // Pick each coin and try to make up the amount from it
        for(int J=0; J<N; J++) {
            if(coins[J] <= amount) {
                int currCoins = solveWithMemo(memory, coins, amount - coins[J], N);
                if(currCoins != INT_MAX) {
                    minCoins = min(minCoins, 1 + currCoins);
                }
            }
        }

        // Store the result value to the memoization table and then return it
        return memory[amount] = minCoins;
    }

    // O(2^A) & O(A)
    int solveWithoutMemo(vector<int>& coins, int amount, int N) {
        // Edge case: If the amount becomes zero, then it's not possible to pick any more coin
        if(amount == 0)
            return 0;
        
        // Stores the "fewest number of coins which make up the amount / result value"
        int minCoins = INT_MAX;

        // Pick each coin and try to make up the amount from it
        for(int J=0; J<N; J++) {
            if(coins[J] <= amount) {
                int currCoins = solveWithoutMemo(coins, amount - coins[J], N);
                if(currCoins != INT_MAX) {
                    minCoins = min(minCoins, 1 + currCoins);
                }
            }
        }

        // Return the result value
        return minCoins;
    }
};

// #2 Class to implement the Top-down approach:
class TopDown_V2 {
public:
    // Method to find the fewest number of coins, using recursion with memoization - O(N*A) & O(A) : Where N is the array size and A is the amount
    int coinChange(vector<int>& coins, int amount) {
        sort(begin(coins), end(coins));
        vector<int> memory(amount + 1, -1);
        int minCoins = solveWithMemo(memory, coins, amount, coins.size());
        return (minCoins == INT_MAX ? -1 : minCoins);
    }

private:
    // O(N*A) & O(A)
    int solveWithMemo(vector<int>& memory, vector<int>& coins, int amount, int N) {
        // Edge case: If the amount becomes zero, then it's not possible to pick any more coin
        if(amount == 0)
            return 0;

        // Memoization table: If the current state is already computed, then return the computed value
        if(memory[amount] != -1)
            return memory[amount];

        // Stores the "fewest number of coins which make up the amount / result value"
        int minCoins = INT_MAX;

        // Pick the coins and make up the amount from it
        for(int J = 0; (J < N && coins[J] <= amount); ++J) {
            int currCoins = solveWithMemo(memory, coins, amount - coins[J], N);
            if(currCoins != INT_MAX) {   
                minCoins = min(minCoins, 1 + currCoins);
            }
        }

        // Store the result value to the memoization table and then return it
        return memory[amount] = minCoins;
    }

    // O(2^A) & O(A)
    int solveWithoutMemo(vector<int>& coins, int amount, int N) {
        // Edge case: If the amount becomes zero, then it's not possible to pick any more coin
        if(amount == 0)
            return 0;

        // Stores the "fewest number of coins which make up the amount / result value"
        int minCoins = INT_MAX;

        // Pick the coins and make up the amount from it
        for(int J = 0; (J < N && coins[J] <= amount); ++J) {
            int currCoins = solveWithoutMemo(coins, amount - coins[J], N);
            if(currCoins != INT_MAX) {   
                minCoins = min(minCoins, 1 + currCoins);
            }
        }

        // Return the result value
        return minCoins;
    }
};

// Class to implement the Bottom-up approach:
class BottomUp {
public:
    // #1 Method to find the fewest number of coins, using 1D buffer for tabulation - O(N*A) & O(A) : Where N is the array size and A is the amount
    int coinChange_V1(vector<int>& coins, int amount) {
        int N = coins.size();

        // Tabulation buffer: dp[amount] represents the fewest number of coins needed to make up the amount 
        vector<int> dp(amount + 1, INT_MAX);
        dp[0] = 0;

        // Treat each index as an individual amount and find the fewest number of coins needed to make it
        for(int currAmount = 1; currAmount <= amount; ++currAmount) {
            // Pick each coin and try to make up the amount from it
            for(int J = 0; J < N; ++J) {
                if(coins[J] <= currAmount) {
                    int currCoins = dp[currAmount - coins[J]];
                    if(currCoins != INT_MAX) {
                        dp[currAmount] = min(dp[currAmount], 1 + currCoins);
                    }
                }
            }
        }
        
        // Return the fewest number of coins needed to make up the given amount 
        return (dp[amount] == INT_MAX) ? -1 : dp[amount];
    }

    // #2 Method to find the fewest number of coins, using 1D buffer for tabulation - O(N*A) & O(A) : Where N is the array size and A is the amount
    int coinChange_V2(vector<int>& coins, int amount) {
        int N = coins.size();
        sort(begin(coins), end(coins));

        // Tabulation buffer: dp[amount] represents the fewest number of coins needed to make up the amount 
        vector<int> dp(amount + 1, INT_MAX);
        dp[0] = 0;

        // Treat each index as an individual amount and find the fewest number of coins needed to make it
        for(int currAmount = 1; currAmount <= amount; ++currAmount) {
            // Pick the coins and make up the amount from it
            for(int J = 0; (J < N && coins[J] <= currAmount); ++J) {
                int currCoins = dp[currAmount - coins[J]];
                if(currCoins != INT_MAX) {
                    dp[currAmount] = min(dp[currAmount], 1 + currCoins);
                }
            }
        }

        // Return the fewest number of coins needed to make up the given amount 
        return (dp[amount] == INT_MAX ? -1 : dp[amount]);  
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

        // Input the array size
        int N;
        cout<<"Enter size of the array: ";
        cin>>N;

        // Input the amount value
        int amount;
        cout<<"Enter the amount value: ";
        cin>>amount;

        // Check the given values are valid or not
        if(N <= 0 || N >= 13) {
            cout<<"You must enter a size which lies between 1 and 12!";
        }   
        else if(amount <= -1 || amount >= 10001) {
            cout<<"You must enter a amount which lies between 0 and 10000!";
        }
        else {
            // Stores the array values
            vector<int> coins(N, 0);

            // Input the array values
            for(int index = 0; index < N;) {
                cout<<"Enter the value of "<<index<<"th index: ";
                cin>>coins[index];
                if(coins[index] <= 0 || coins[index] >= INT_MAX) {
                    cout<<"You must enter a value which lies between 1 and 2147483647!\n";
                    continue;
                }
                index++;
            }

            // Call to find the fewest number of coins that you need to make up the amount
            BottomUp bottomUp;
            int minCoins = bottomUp.coinChange_V2(coins, amount);
            cout<<"\nThe fewest number of coins that you need to make up the amount "<<amount<<" is: "<<minCoins;
        }

        // Input section to control the flow of iterations of the application
        char userChoice; 
        cout<<"\n\nPress \'R\' to restart the application, else it will exist: "; 
        cin>>userChoice; 
        userWantsOperation = (userChoice == 'R' ? true : false);
    }

    return 0;
}
/*
    Topics: Array | Dynamic Programming
    Link: https://leetcode.com/problems/coin-change/description/
*/
