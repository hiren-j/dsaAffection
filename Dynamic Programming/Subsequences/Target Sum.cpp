// Program to find the number of different expressions that you can build using specified way such that they evaluates to target ~ coded by Hiren
#include <unordered_map>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

// #1 Class to implement the Top-down approach:    
class TopDown_V1 {
public:
    // Method to find the total number of different expressions that evaluates to target, using recursion with memoization - O(N*T) & O(N*T) : Where N let be the array size and T let be the target
    int findTargetSumWays(vector<int>& nums, int target) {
        int N = nums.size();
        unordered_map<string, int> memory;
        return solveWithMemo(memory, nums, nums.size(), target, 0, 0);
    }

private:
    // O(N*T) & O(N*T)
    int solveWithMemo(unordered_map<string, int>& memory, vector<int>& nums, int N, int target, int index, int currSum) {
        // Edge case: If all the elements are exhausted and if the sum value is equal to target, then you got 1 valid expression that evaulates to target
        if(index == N)
            return (currSum == target);

        string key = to_string(index) + "_" + to_string(currSum);

        // Memoization table: If the current state is already computed, then return the computed value
        if(memory.count(key))
            return memory[key];

        // There are always two possibilities to perform at each index
        int addNum = solveWithMemo(memory, nums, N, target, index + 1, currSum + nums[index]); // Is to add the index value in the sum 
        int subNum = solveWithMemo(memory, nums, N, target, index + 1, currSum - nums[index]); // Is to subtract the index value in the sum 

        // Store the value of the "total number of different expressions" to the memoization table and then return it 
        return memory[key] = (addNum + subNum);
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(vector<int>& nums, int N, int target, int index, int currSum) {
        // Edge case: If all the elements are exhausted and if the sum value is equal to target, then you got 1 valid expression that evaulates to target
        if(index == N)
            return (currSum == target);

        // There are always two possibilities to perform at each index
        int addNum = solveWithoutMemo(nums, N, target, index + 1, currSum + nums[index]); // Is to add the index value in the sum 
        int subNum = solveWithoutMemo(nums, N, target, index + 1, currSum - nums[index]); // Is to subtract the index value in the sum 

        // Return the total number of different expressions that evaluates to target
        return (addNum + subNum);
    }
};

// #2 Class to implement the Top-down approach:    
class TopDown_V2 {
public:
    // Method to find the total number of different expressions that evaluates to target, using recursion with memoization - O(N*T) & O(N*T) : Where N let be the array size and T let be the target
    int findTargetSumWays(vector<int>& nums, int target) {
        int N = nums.size();
        int totalSum = accumulate(begin(nums), end(nums), 0);
        
        // Edge case: If the difference becomes negative or odd, then you can't have valid partitions
        if(totalSum - target < 0 || (totalSum - target) % 2 != 0)
            return false;

        // If the difference is an even value, then you can have valid partitions 
        target = (totalSum - target) / 2;

        // Table for memoization
        vector<vector<int>> memory(N, vector<int>(target + 1, -1));

        // Count and return the total number of subsets whose sum is equal to the target
        return solveWithMemo(memory, nums, N, N - 1, target);
    }
    
private:
    // O(N*T) & O(N*T)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& nums, int N, int index, int target) {
        // Edge case: If you reached the 0th index, then compute the count of all the subsets according to their existence
        if(index == 0) {
            if(target == 0) 
                return (nums[index] == 0) ? 2 : 1;
            else
                return (nums[index] == target) ? 1 : 0;
        }
        
        // Memoization table: If the current state is already computed, then return the computed value
        if(memory[index][target] != -1)
            return memory[index][target];
            
        // There are always two possibilties to perform at each index
        int currSkip = solveWithMemo(memory, nums, N, index - 1, target); // Is to skip the index value and move on
        int currTake = 0;                                                 // Is to take the index value and move on  
        
        // If possible, then take the index value
        if(nums[index] <= target)
            currTake = solveWithMemo(memory, nums, N, index - 1, target - nums[index]);

        // Store the count of all the subsets to the memoization table and then return it   
        return memory[index][target] = (currTake + currSkip);
    }
    
    // O(2^N) & O(N)
    int solveWithoutMemo(vector<int>& nums, int N, int index, int target) {
        // Edge case: If you reached the 0th index, then compute the count of all the subsets according to their existence
        if(index == 0) {
            if(target == 0) 
                return (nums[index] == 0) ? 2 : 1;
            else
                return (nums[index] == target) ? 1 : 0;
        }
            
        // There are always two possibilties to perform at each index
        int currSkip = solveWithoutMemo(nums, N, index - 1, target); // Is to skip the index value and move on
        int currTake = 0;                                            // Is to take the index value and move on 
            
        // If possible, then take the index value
        if(nums[index] <= target)
            currTake = solveWithoutMemo(nums, N, index - 1, target - nums[index]);
            
        // Return the count of all the subsets whose sum is equal to the target
        return (currTake + currSkip);
    }
};

// Class to implement the Bottom-up approach:
class BottomUp {
public:
    // #1 Method to find the total number of different expressions that evaluates to target, using 2D buffer for tabulation - O(N*T) & O(N*T) : Where N let be the array size and T let be the target
    int findTargetSumWays_V1(vector<int>& nums, int target) {
        int N = nums.size();
        int totalSum = accumulate(begin(nums), end(nums), 0);
        
        // Edge case: If the difference becomes negative or odd, then you can't have valid partitions
        if(totalSum - target < 0 || (totalSum - target) % 2 != 0)
            return false;

        // If the difference is an even value, then you can have valid partitions 
        target = (totalSum - target) / 2;
        
        // Tabulation buffer: dp[index][currTarget] stores the count of all the subsets lying within the "index" elements of the start of the array, such that their sum equals to the "currTarget"
        vector<vector<int>> dp(N + 1, vector<int>(target + 1, 0));

        // Edge case: If the array is empty and the target is 0, then there always exists a single subset with sum 0
        dp[0][0] = 1;
        
        // Treat each index as the "number of elements can take from the start of the array" and count all the subsets lying within, whose sum is equal to the "currTarget"
        for(int index = 1; index <= N; ++index) {
            for(int currTarget = 0; currTarget <= target; ++currTarget) {
                int currSkip = dp[index - 1][currTarget];
                int currTake = 0; 
                if(nums[index - 1] <= currTarget) {
                    currTake = dp[index - 1][currTarget - nums[index - 1]];
                }
                dp[index][currTarget] = (currTake + currSkip);
            }
        }

        // Return the count of all the subsets with sum equal to the target 
        return dp[N][target];
    }

    // #2 Method to find the total number of different expressions that evaluates to target, using 1D buffer for tabulation - O(N*T) & O(T) : Where N let be the array size and T let be the target
    int findTargetSumWays_V2(vector<int>& nums, int target) {
        int N = nums.size();
        int totalSum = accumulate(begin(nums), end(nums), 0);
        
        // Edge case: If the difference becomes negative or odd, then you can't have valid partitions
        if(totalSum - target < 0 || (totalSum - target) % 2 != 0)
            return false;

        // If the difference is an even value, then you can have valid partitions 
        target = (totalSum - target) / 2;

        // Tabulation buffer: prevRow[currTarget] / currRow[currTarget]" stores the count of all the subsets lying within the "index" elements of the start of the array, such that their sum equals to the "currTarget"
        vector<int> prevRow(target + 1, 0), currRow(target + 1, 0);

        // Edge case: If the array is empty and the target is 0, then there always exists a single subset with sum 0
        prevRow[0] = 1;
        
        // Treat each index as the "number of elements can take from the start of the array" and count all the subsets lying within, whose sum is equal to the "currTarget"
        for(int index = 1; index <= N; ++index) {
            for(int currTarget = 0; currTarget <= target; ++currTarget) {
                int currSkip = prevRow[currTarget];
                int currTake = 0; 
                if(nums[index - 1] <= currTarget) {
                    currTake = prevRow[currTarget - nums[index - 1]];
                }
                currRow[currTarget] = (currTake + currSkip);
            }
            prevRow = currRow;
        }
        
        // Return the count of all the subsets with sum equal to the target
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

        cout<<"The application only accepts non-decimal numeric type value, unless specified!\n\n";

        // Input the array size
        int N;
        cout<<"Enter size of the array: ";
        cin>>N;

        // Input the target value
        int target;
        cout<<"Enter the target value: ";
        cin>>target;

        // Check the given values are lying within the problem constraints or not
        if(N <= 0 || N >= 21) {
            cout<<"You must enter the size, which lies between 1 and 20!";
        }
        else if(target <= -1001 || target >= 1001) {
            cout<<"You must enter the target value, which lies between -1000 and 1000!";
        }
        else {
            // Stores the array values
            vector<int> nums(N);

            // Input the array values
            for(int index = 0; index < N;) {
                cout<<"Enter the value of "<<index<<"th index: ";
                cin>>nums[index];
                if(nums[index] <= -1 || nums[index] >= 1001) {
                    cout<<"You must enter a value, which lies between 0 and 1000!\n";
                    continue;
                }
                index++;
            }

            // Call to find the total number of different expressions that evaluates to target
            BottomUp bottomUp;
            int numExpressions = bottomUp.findTargetSumWays_V2(nums, target);
            cout<<"\nThe total number of different expressions that evaluates to target "<<target<<" is: "<<numExpressions;
        }

        // Input section to control the flow of iterations of the application
        char userChoice;
        cout<<"\n\nPress \'R\' to restart the application, else it will exit: ";
        cin>>userChoice;
        userWantsOperation = (userChoice == 'R');
    }

    return 0;
}
/*
    Topics: Array | Dynamic Programming | Backtracking 
    Link: https://leetcode.com/problems/target-sum/description/?envType=list&envId=50vif4uc
*/
