// Program to find the number of combinations that make up the given amount ~ coded by Hiren
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

// #1 Class to implement the Top-down approach:
class TopDown_V1 {
public:
    // Method to find the number of combinations that make up the given amount, using recursion with memoization - O(N*A) & O(N*A) : Where N let be the array size and A let be the amount
    int countWaysToMakeAmount(int amount, vector<int>& coins) {
        int N = coins.size();
        vector<vector<int>> memory(N, vector<int>(amount + 1, -1));
        return solveWithMemo(memory, coins, N, 0, amount);
    }

private:
    // O(N*A) & O(N*A)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& coins, int N, int index, int amount) {
        // Base case: If all the elements are exhausted, then you can't pick any more element
        if(index == N)
            return (amount == 0);

        // Base case: If the amount becomes zero, then there exists one valid combination
        if(amount == 0)
            return 1;

        // Memoization table: If the current state is already computed, then return the computed value
        if(memory[index][amount] != -1)
            return memory[index][amount];   

        // There are always two possibilities to perform at each index
        int currSkip = solveWithMemo(memory, coins, N, index + 1, amount); // Is to skip the index value and move to the next index
        int currTake = 0;                                                 // Is to take the index value and stay at the same index

        // If possible then take the index value
        if(coins[index] <= amount)   
            currTake = solveWithMemo(memory, coins, N, index, amount - coins[index]);

        // Store the value of "the total number of combinations that make up the amount" to the memoization table and then return it
        return memory[index][amount] = currTake + currSkip;
    }

    // O(2^A) & O(A)
    int solveWithoutMemo(vector<int>& coins, int N, int index, int amount) {
        // Base case: If all the elements are exhausted, then you can't pick any more element
        if(index == N)
            return (amount == 0);

        // Base case: If the amount becomes zero, then there exists one valid combination
        if(amount == 0)
            return 1;

        // There are always two possibilities to perform at each index
        int currSkip = solveWithoutMemo(coins, N, index + 1, amount); // Is to skip the index value and move to the next index
        int currTake = 0;                                            // Is to take the index value and stay at the same index

        // If possible then take the index value
        if(coins[index] <= amount)
            currTake = solveWithoutMemo(coins, N, index, amount - coins[index]);

        // Return the value of the total number of combinations that make up the amount
        return currTake + currSkip;
    }
};

// #2 Class to implement the Top-down approach:
class TopDown_V2 {
public:
    // Method to find the number of combinations that make up the given amount, using recursion with memoization - O(N*A) & O(N*A) : Where N let be the array size and A let be the amount
    int countWaysToMakeAmount(int amount, vector<int>& coins) {
        int N = coins.size();
        vector<vector<int>> memory(N, vector<int>(amount + 1, -1));
        return solveWithMemo(memory, coins, N, 0, amount);
    }

private:
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& coins, int N, int startIndex, int amount) {
        // Base case: If all the elements are exhausted, then you can't pick any more element
        if(startIndex == N)
            return (amount == 0);

        // Base case: If the amount becomes zero, then there exists one valid combination
        if(amount == 0)
            return 1;

        // Memoization table: If the current state is already computed, then return the computed value
        if(memory[startIndex][amount] != -1)
            return memory[startIndex][amount];

        // Stores the "the total number of combinations that make up the amount / result value"
        int count = 0;

        // Iterate and if possible then take the index value and try to make up the amount from it
        for(int index = startIndex; index < N; ++index) {
            if(coins[index] <= amount) {
                count += solveWithMemo(memory, coins, N, index, amount - coins[index]);
            }
        }
            
        // Store the value of "the total number of combinations that make up the amount" to the memoization table and then return it
        return memory[startIndex][amount] = count;
    }

    // O(2^A) & O(A)
    int solveWithoutMemo(vector<int>& coins, int N, int startIndex, int amount) {
        // Base case: If all the elements are exhausted, then you can't pick any more element
        if(startIndex == N)
            return (amount == 0);

        // Base case: If the amount becomes zero, then there exists one valid combination
        if(amount == 0)
            return 1;

        // Stores the "the total number of combinations that make up the amount / result value"
        int count = 0;

        // Iterate and if possible then take the index value and try to make up the amount from it
        for(int index = startIndex; index < N; ++index) {
            if(coins[index] <= amount) {
                count += solveWithoutMemo(coins, N, index, amount - coins[index]);
            }
        }
        
        // Return the value of the total number of combinations that make up the amount
        return count;
    }
};

// Class to implement the Bottom-up approach:
class BottomUp {
public:
    // #1 Method to find the number of combinations that make up the given amount, using 2D buffer for tabulation - O(N*A) & O(N*A) : Where N let be the array size and A let be the amount
    int countWaysToMakeAmount_V1(int amount, vector<int>& coins) {
        int N = coins.size();

        // Tabulation buffer: dp[index][currAmount] represents the total number of combinations that make up the "currAmount" by taking the "index" elements from the start of the array
        vector<vector<int>> dp(N + 1, vector<int>(amount + 1, 0));

        // Base case: If the array is empty and the amount is zero, then there exists one valid combination 
        dp[0][0] = 1;

        // Treat each index as "the number of elements can take from the start of the array" and count the total number of combinations that make up the "currAmount"
        for(int index = 1; index <= N; ++index) {
            for(int currAmount = 0; currAmount <= amount; ++currAmount) {
                int currSkip = dp[index - 1][currAmount];
                int currTake = 0;
                if(coins[index - 1] <= currAmount) {
                    currTake = dp[index][currAmount - coins[index - 1]];
                }
                dp[index][currAmount] = currTake + currSkip;
            }
        }

        // Return the count of the total number of combinations that make up the given amount
        return dp[N][amount];
    }

    // #2 Method to find the number of combinations that make up the given amount, using 1D buffer for tabulation - O(N*A) & O(A) : Where N let be the array size and A let be the amount
    int countWaysToMakeAmount_V2(int amount, vector<int>& coins) {
        int N = coins.size();

        // Tabulation buffer: "prevRow[currAmount] / currRow[currAmount]" represents the total number of combinations that make up the "currAmount" by taking the "index" elements from the start of the array
        vector<int> prevRow(amount + 1, 0), currRow(amount + 1, 0);

        // Base case: If the array is empty and the amount is zero, then there exists one valid combination 
        prevRow[0] = 1;

        // Treat each index as "the number of elements can take from the start of the array" and count the total number of combinations that make up the "currAmount"
        for(int index = 1; index <= N; ++index) {
            for(int currAmount = 0; currAmount <= amount; ++currAmount) {
                int currSkip = prevRow[currAmount];
                int currTake = 0;
                if(coins[index - 1] <= currAmount) {
                    currTake = currRow[currAmount - coins[index - 1]];
                }
                currRow[currAmount] = currTake + currSkip;
            }
            prevRow = currRow;
        }

        // Return the count of the total number of combinations that make up the given amount
        return prevRow[amount];
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
        cout<<"Enter the total number of coins: ";
        cin>>N;

        // Input the amount value
        int amount;
        cout<<"Enter the amount value: ";
        cin>>amount;

        // Check the given values are valid or not
        if(N <= 0 || N >= 301) {
            cout<<"You must enter the size which lies between 1 and 300!";
        }   
        else if(amount <= 0 || amount >= 5001) {
            cout<<"You must enter the amount which lies between 1 and 5000!";
        }
        else {
            // Stores the array values
            vector<int> coins(N, 0);

            // Input the array values
            cout<<"\nNote: You must enter unique values for the array or the application will throw wrong outputs!\n";
            for(int index = 0; index < N;) {
                cout<<"Enter the value of "<<index<<"th coin: ";
                cin>>coins[index];
                if(coins[index] <= 0 || coins[index] >= 5001) {
                    cout<<"You must enter a value which lies within the range 1 and 5000!\n";
                    continue;
                }
                index++;
            }

            // Call to find the number of combinations that make up the given amount
            BottomUp bottomUp;
            int count = bottomUp.countWaysToMakeAmount_V2(amount, coins);
            cout<<"\nThe total number of combinations that make up the given amount "<<amount<<" is: "<<count;
            
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
    Link: https://leetcode.com/problems/coin-change-ii/description/
*/
