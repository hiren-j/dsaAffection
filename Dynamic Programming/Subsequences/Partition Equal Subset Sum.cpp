// Program to determine if you can partition the array into two subsets such that the sum of the elements in both the subsets is equal or not ~ coded by Hiren
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

// #1 Class to implement the Top-down approach:
class TopDown_V1 {
public: 
    // Method to determine if you can partition the array in the specified way or not, using recursion with memoization - O(N*S) & O(N*S) : Where N let be the array size and S let be the sum
    bool canPartition(vector<int>& nums) {
        int N = nums.size();
        int totalSum = accumulate(begin(nums), end(nums), 0);
        
        // Edge case: If the total sum of the array is odd, then you can't partition the array into two subsets
        if(totalSum % 2 != 0)
            return false;
        
        // Partitioning an even sum into two parts are always equal to each other, this means, you can figure out there exist two subsets with equal sum or not, if you check for the one subset and it exists then the another subset will absolutely exist it's because there sum are always equal
        int sum = totalSum / 2;
        
        // Table for memoization
        vector<vector<int>> memory(N, vector<int>(sum + 1, -1));
        
        // Check for the presence of one subset and if it exists then return true, else false
        return solveWithMemo(memory, nums, N, 0, sum);
    }
    
private:
    bool solveWithMemo(vector<vector<int>>& memory, vector<int>& nums, int N, int index, int sum) {
        // Edge case: If all the elements are exhausted and if the sum becomes 0, then there exists a subset with given sum
        if(index == N)
            return (sum == 0);
        
        // Edge case: If the sum becomes 0, then there exists a subset with given sum 
        if(sum == 0)
            return true;
        
        // Memoization table: If the current state is already computed, then return the computed value
        if(memory[index][sum] != -1)
            return memory[index][sum];
        
        // There are always two possibilties to perform at each index
        bool currSkip = solveWithMemo(memory, nums, N, index + 1, sum); // Is to skip the index value and move on
        bool currTake = false;                                          // Is to take the index value and move on  
        
        // If the subset equal to the given sum doesn't exist, then if possible, then take the index value
        if(!currSkip && nums[index] <= sum)
            currTake = solveWithMemo(memory, nums, N, index + 1, sum - nums[index]);

        // Store the presence information of the subset to the memoization table and then return it
        return memory[index][sum] = currTake || currSkip;
    }
};

// #2 Class to implement the Top-down approach:
class TopDown_V2 {
public: 
    // Method to determine if you can partition the array in the specified way or not, using recursion with memoization - O(N*S) & O(N*S) : Where N let be the array size and S let be the sum
    bool canPartition(vector<int>& nums) {
        int N = nums.size();
        int totalSum = accumulate(begin(nums), end(nums), 0);
        
        // Edge case: If the total sum of the array is odd, then you can't partition the array into two subsets
        if(totalSum % 2 != 0)
            return false;
        
        // Partitioning an even sum into two parts are always equal to each other, this means, you can figure out there exist two subsets with equal sum or not, if you check for the one subset and it exists then the another subset will absolutely exist it's because there sum are always equal
        int sum = totalSum / 2;

        // Table for memoization
        vector<vector<int>> memory(N, vector<int>(sum + 1, -1));
        
        // Check for the presence of one subset and if it exists then return true, else false
        return solveWithMemo(memory, nums, N, 0, sum);
    }
    
private:
    bool solveWithMemo(vector<vector<int>>& memory, vector<int>& nums, int N, int startIndex, int sum) {
        // Edge case: If all the elements are exhausted and if the sum becomes 0, then there exists a subset with given sum
        if(startIndex == N)
            return (sum == 0);
        
        // Edge case: If the sum becomes 0, then there exists a subset with given sum 
        if(sum == 0)
            return true;
            
        // Memoization table: If the current state is already computed, then return the computed value
        if(memory[startIndex][sum] != -1)
            return memory[startIndex][sum];

        // Tracks the subset with sum equal to the given sum exist or not  
        bool flag = false;
        
        // If the subset equal to the given sum doesn't exist, then if possible, then take the index value
        for(int index = startIndex; (index < N && !flag); ++index) {
            if(nums[index] <= sum) {
                flag |= solveWithMemo(memory, nums, N, index + 1, sum - nums[index]);
            }
        }

        // Store the presence information of the subset to the memoization table and then return it
        return memory[startIndex][sum] = flag;
    }
};

// Class to implement the Bottom-up approach:
class BottomUp {
public: 
    // #1 Method to determine if you can partition the array in the specified way or not, using 2D buffer for tabulation - O(N*S) & O(N*S) : Where N let be the array size and S let be the sum
    bool canPartition_V1(vector<int>& nums) {
        int N = nums.size();
        int totalSum = accumulate(begin(nums), end(nums), 0);
        
        // Edge case: If the total sum of the array is odd, then you can't partition the array into two subsets
        if(totalSum % 2 != 0)
            return false;
        
        // Partitioning an even sum into two parts are always equal to each other, this means, you can figure out there exist two subsets with equal sum or not, if you check for the one subset and it exists then the another subset will absolutely exist it's because there sum are always equal
        int sum = totalSum / 2;
        
        // Tabulation buffer: dp[index][currSum] represents, is there exists any subset within the "index" elements of the start of the array, such that their sum equals to the "currSum"
        vector<vector<bool>> dp(N + 1, vector<bool>(sum + 1, false));

        // Edge case: If the array is empty and the sum is 0, then there always exists a subset with sum 0
        dp[0][0] = true;

        // Treat each index as the "number of elements can take from the start of the array" and check the existence of the subset whose sum equals to the "currSum"
        for(int index = 1; index <= N; ++index) {
            for(int currSum = 0; currSum <= sum; ++currSum) {
                bool currSkip = dp[index - 1][currSum];
                bool currTake = false;
                if(nums[index - 1] <= currSum) {
                    currTake = dp[index - 1][currSum - nums[index - 1]];
                }
                dp[index][currSum] = currTake || currSkip;
            }
        }
        
        // Return the presence information of the subset with sum equal to the given sum exist or not
        return dp[N][sum];
    }

    // #2 Method to determine if you can partition the array in the specified way or not, using 1D buffer for tabulation - O(N*S) & O(S) : Where N let be the array size and S let be the sum
    bool canPartition_V2(vector<int>& nums) {
        int N = nums.size();
        int totalSum = accumulate(begin(nums), end(nums), 0);
        
        // Edge case: If the total sum of the array is odd, then you can't partition the array into two subsets
        if(totalSum % 2 != 0)
            return false;
        
        // Partitioning an even sum into two parts are always equal to each other, this means, you can figure out there exist two subsets with equal sum or not, if you check for the one subset and it exists then the another subset will absolutely exist it's because there sum are always equal
        int sum = totalSum / 2;
        
        // Tabulation buffer: "prevRow[currSum] / currRow[currSum]" represents, is there exists any subset within the "index" elements of the start of the array, such that their sum equals to the "currSum"
        vector<bool> prevRow(sum + 1, false), currRow(sum + 1, false);

        // Edge case: If the array is empty and the sum is 0, then there always exists a subset with sum 0
        prevRow[0] = true;

        // Treat each index as the "number of elements can take from the start of the array" and check the existence of the subset whose sum equals to the "currSum"
        for(int index = 1; index <= N; ++index) {
            for(int currSum = 0; currSum <= sum; ++currSum) {
                bool currSkip = prevRow[currSum];
                bool currTake = false;
                if(nums[index - 1] <= currSum) {
                    currTake = prevRow[currSum - nums[index - 1]];
                }
                currRow[currSum] = currTake || currSkip;
            }
            prevRow = currRow;
        }

        // Return the presence information of the subset with sum equal to the given sum exist or not
        return prevRow[sum];
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

        // Check the given value is valid or not
        if(N <= 0 || N >= 201) {
            cout<<"You must enter a size which lies within the range 1 and 200!";
        }   
        else {
            // Stores the array values
            vector<int> nums(N, 0);

            // Input the array values
            for(int index = 0; index < N;) {
                cout<<"Enter the value of "<<index<<"th index: ";
                cin>>nums[index];
                if(nums[index] <= 0 || nums[index] >= 101) {
                    cout<<"You must enter a value which lies within the range 1 and 100!\n";
                    continue;
                }
                index++;
            }

            // Call to determine if you can partition the array in the specified way or not
            BottomUp bottomUp;
            if(bottomUp.canPartition_V2(nums))
                cout<<"\nYou can partition the array into two subsets such that the sum of the elements in both the subsets is equal!";
            else
                cout<<"\nYou can't partition the array into two subsets such that the sum of the elements in both the subsets is equal!";
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
    Topics: Array | Dynamic Programming
    Links: https://leetcode.com/problems/partition-equal-subset-sum/description/
           https://www.geeksforgeeks.org/problems/subset-sum-problem2014/1
*/
