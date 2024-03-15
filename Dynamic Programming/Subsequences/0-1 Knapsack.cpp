// Program to find the maximum total value you can collect for the knapsack, you cannot break an item, either pick the complete item or dont pick it (0-1 property) ~ coded by Hiren
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

// #1 Class to implement the Top-down approach:
class TopDown_V1 {
public:
    // Method to find the maximum total value you can collect for the knapsack, using recursion with memoization - O(N*C) & O(N*C) : Where N let be the array size and C let be the capacity
    int knapSack(int capacity, vector<int>& weights, vector<int>& values, int N) {
        vector<vector<int>> memory(N, vector<int>(capacity + 1, -1));
        return solveWithMemo(memory, weights, values, N, 0, capacity);
    }
    
private:
    // O(N*C) & O(N*C)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& weights, vector<int>& values, int N, int index, int capacity) {
        // Edge case: If all the values are exhausted then you can't collect any more values
        if(index == N)
            return 0;
            
        // Edge case: If the capacity becomes zero then you can't fill any more value to the knapsack
        if(capacity <= 0)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[index][capacity] != -1)
            return memory[index][capacity];
        
        // There are always two possibilities to perform at each index
        int currSkip = solveWithMemo(memory, weights, values, N, index + 1, capacity); // Is to skip the index value and move on
        int currTake = 0;                                                              // Is to take the index value and move on
        
        // If possible then take the index value
        if(capacity - weights[index] >= 0)
            currTake = values[index] + solveWithMemo(memory, weights, values, N, index + 1, capacity - weights[index]);

        // Store the maximum value to the memoization table and then return it
        return memory[index][capacity] = max(currTake, currSkip);
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(vector<int>& weights, vector<int>& values, int N, int index, int capacity) {
        // Edge case: If all the values are exhausted then you can't collect any more values
        if(index == N)
            return 0;
            
        // Edge case: If the capacity becomes zero then you can't fill any more value to the knapsack
        if(capacity <= 0)
            return 0;
            
        // There are always two possibilities to perform at each index
        int currSkip = solveWithoutMemo(weights, values, N, index + 1, capacity); // Is to skip the index value and move on
        int currTake = 0;                                                         // Is to take the index value and move on 
        
        // If possible then take the index value
        if(capacity - weights[index] >= 0)
            currTake = values[index] + solveWithoutMemo(weights, values, N, index + 1, capacity - weights[index]);
            
        // Return the maximum value
        return max(currTake, currSkip);
    }
};

// #2 Class to implement the Top-down approach:
class TopDown_V2 {
public:
    // Method to find the maximum total value you can collect for the knapsack, using recursion with memoization - O(N*C) & O(N*C) : Where N let be the array size and C let be the capacity
    int knapSack(int capacity, vector<int>& weights, vector<int>& values, int N) {
        vector<vector<int>> memory(N, vector<int>(capacity + 1, -1));
        return solveWithMemo(memory, weights, values, N, 0, capacity);
    }
    
private:
    // O(N*C) & O(N*C)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& weights, vector<int>& values, int N, int startIndex, int capacity) {
        // Edge case: If all the values are exhausted then you can't collect any more values
        if(startIndex == N)
            return 0;
        
        // Edge case: If the capacity becomes zero then you can't fill any more value to the knapsack
        if(capacity <= 0)
            return 0;
            
        // Memoization table: If the current state is already computed then return the computed value
        if(memory[startIndex][capacity] != -1)
            return memory[startIndex][capacity];
            
        // Stores the maximum value which can be collected for the knapsack
        int maxValue = 0;
        
        // Iterate and if possible then take the index value and update the maximum value each time 
        for(int index = startIndex; index < N; ++index) {
            if(capacity - weights[index] >= 0) {
                maxValue = max(maxValue, values[index] + solveWithMemo(memory, weights, values, N, index + 1, capacity - weights[index]));
            }
        }    
            
        // Store the maximum value to the memoization table and then return it
        return memory[startIndex][capacity] = maxValue;
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(vector<int>& weights, vector<int>& values, int N, int startIndex, int capacity) {
        // Edge case: If all the values are exhausted then you can't collect any more values
        if(startIndex == N)
            return 0;
        
        // Edge case: If the capacity becomes zero then you can't fill any more value to the knapsack
        if(capacity <= 0)
            return 0;
            
        // Stores the maximum value which can be collected for the knapsack
        int maxValue = 0;
            
        // Iterate and if possible then take the index value and update the maximum value each time 
        for(int index = startIndex; index < N; ++index) {
            if(capacity - weights[index] >= 0) {
                maxValue = max(maxValue, values[index] + solveWithoutMemo(weights, values, N, index + 1, capacity - weights[index]));
            }
        }    
            
        // Return the maximum value
        return maxValue;
    }
};

// Class to implement the Bottom-up approach:
class BottomUp {
public:
    // #1 Method to find the maximum total value you can collect for the knapsack, using 2D buffer for tabulation - O(N*C) & O(N*C) : Where N let be the array size and C let be the capacity
    int knapSack_V1(int capacity, vector<int>& weights, vector<int>& values, int N) {
        // Tabulation buffer: dp[index][currCapacity] represents the maximum value which can be collected for the knapsack by taking the "index" elements from the start of the array, such that the overall weight is less than or equal to the "currCapacity"
        vector<vector<int>> dp(N + 1, vector<int>(capacity + 1, 0));
        
        // Treat each index as the "number of elements can take from the start of the array" and find the maximum value which can be collected for the knapsack such that the overall weight is less than or equal to the "currCapacity"
        for(int index = 1; index <= N; ++index) {
            for(int currCapacity = 0; currCapacity <= capacity; ++currCapacity) {
                int currSkip = dp[index - 1][currCapacity];
                int currTake = 0;
                if(currCapacity - weights[index - 1] >= 0) {
                    currTake = values[index - 1] + dp[index - 1][currCapacity - weights[index - 1]];
                }
                dp[index][currCapacity] = max(currTake, currSkip);
            }
        }

        // Return the maximum value which can be collected for the knapsack, such that the overall weight is less than or equal to the given capacity
        return dp[N][capacity];
    }

    // #2 Method to find the maximum total value you can collect for the knapsack, using 1D buffer for tabulation - O(N*C) & O(C) : Where N let be the array size and C let be the capacity
    int knapSack_V2(int capacity, vector<int>& weights, vector<int>& values, int N) {
        // Tabulation buffer: "prevRow[currCapacity] / currRow[currCapacity]" represents the maximum value which can be collected for the knapsack by taking the "index" elements from the start of the array, such that the overall weight is less than or equal to the "currCapacity"
        vector<int> prevRow(capacity + 1, 0), currRow(capacity + 1, 0);
        
        // Treat each index as the "number of elements can take from the start of the array" and find the maximum value which can be collected for the knapsack such that the overall weight is less than or equal to the "currCapacity"
        for(int index = 1; index <= N; ++index) {
            for(int currCapacity = 0; currCapacity <= capacity; ++currCapacity) {
                int currSkip = prevRow[currCapacity];
                int currTake = 0;
                if(currCapacity - weights[index - 1] >= 0) {
                    currTake = values[index - 1] + prevRow[currCapacity - weights[index - 1]];
                }
                currRow[currCapacity] = max(currTake, currSkip);
            }
            prevRow = currRow;
        }
        
        // Return the maximum value which can be collected for the knapsack, such that the overall weight is less than or equal to the given capacity
        return prevRow[capacity];
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userWantsOperation = true;

    while(userWantsOperation) {
        // Controls console clearance for both "windows" and "linux" user
        system("cles || clear");

        cout<<"Note: The application only accepts non-decimal numeric type value, unless specified!\n\n";

        // Input the array size
        int N;
        cout<<"Enter the total number of values: ";
        cin>>N;

        // Input the capacity value
        int capacity;
        cout<<"Enter the capacity of the knapsack: ";
        cin>>capacity;

        // Check the given values are valid or not
        if(N <= 0 || N >= 1001 || capacity <= 0 || capacity >= 1001) {
            cout<<"You must enter the size and the capacity which lies between 1 and 1000!";
        }
        else {
            // Arrays to store the value and weight of each item respectively 
            vector<int> values(N), weights(N);

            // Input the value and weight of each item
            cout<<"\nNote: Each item considers two information - [value, weight]\n";
            for(int index = 0; index < N;) {
                cout<<"Enter the information of the "<<index<<"th item: ";
                cin>>values[index]>>weights[index];
                if(values[index] <= 0 || values[index] >= 1001 || weights[index] <= 0 || weights[index] >= 1001) {
                    cout<<"You must enter the value and the weight which lies between 1 and 1000!\n";
                    continue;
                }
                index++;
            }

            // Call to find the maximum total value you can collect for the knapsack
            BottomUp bottomUp;
            int maxValue = bottomUp.knapSack_V2(capacity, weights, values, N);
            cout<<"\nThe maximum total value you can collect for the knapsack is: "<<maxValue;
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
    Link: https://www.geeksforgeeks.org/problems/0-1-knapsack-problem0945/1
*/
