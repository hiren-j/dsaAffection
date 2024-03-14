// Program to determine if there is a subset of the given set with sum equal to the given sum or not ~ coded by Hiren
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// #1 Class to implement the Top-down approach:
class TopDown_V1 {   
public:
    // Method to determine if there exist the mentioned subset or not, using recursion with memoization - O(N*S) & O(N*S) : Where N let be the array size and S let be the sum value
    bool checkSubsetEqualSum(vector<int>& nums, int sum) {
        int N = nums.size();
        vector<vector<int>> memory(N, vector<int>(sum + 1, -1));
        return solveWithMemo(memory, nums, N, 0, sum);
    }
    
private:
    // O(N*S) & O(N*S)
    bool solveWithMemo(vector<vector<int>>& memory, vector<int>& nums, int N, int index, int sum) {
        // Edge case: If all the elements are exhausted and if the sum becomes zero, then there exists a subset with given sum
        if(index == N)
            return (sum == 0);

        // Edge case: If the sum becomes zero, then there exists a subset with given sum 
        if(sum == 0)
            return true;
            
        // Memoization table: If the current state is already computed, then return the computed value
        if(memory[index][sum] != -1)
            return memory[index][sum];
        
        // There are always two possibilties to perform at each index
        bool currSkip = solveWithMemo(memory, nums, N, index + 1, sum); // Is to skip the index value and move on
        bool currTake = false;                                          // Is to take the index value and move on

        // If the subset equal to given sum doesn't exist, then if possible, then take the index value
        if(!currSkip && nums[index] <= sum)
            currTake = solveWithMemo(memory, nums, N, index + 1, sum - nums[index]);
        
        // Store the presence information of the subset to the memoization table and then return it
        return memory[index][sum] = currTake || currSkip;
    }

    // O(2^N) & O(N)
    bool solveWithoutMemo(vector<int>& nums, int N, int index, int sum) {
        // Edge case: If all the elements are exhausted and if the sum becomes zero, then there exists a subset with given sum
        if(index == N)
            return (sum == 0);
            
        // Edge case: If the sum becomes zero, then there exists a subset with given sum 
        if(sum == 0)
            return true;
            
        // There are always two possibilties to perform at each index
        bool currSkip = solveWithoutMemo(nums, N, index + 1, sum); // Is to skip the index value and move on
        bool currTake = false;                                     // Is to take the index value and move on
        
        // If the subset equal to given sum doesn't exist, then if possible, then take the index value
        if(!currSkip && nums[index] <= sum)
            currTake = solveWithoutMemo(nums, N, index + 1, sum - nums[index]);        

        // Return the presence information of the subset
        return currTake || currSkip;
    }
};

// #2 Class to implement the Top-down approach:
class TopDown_V2 {
public:
    // Method to determine if there exist the mentioned subset or not, using recursion with memoization - O(N*S) & O(N*S) : Where N let be the array size and S let be the sum value
    bool checkSubsetEqualSum(vector<int>& nums, int sum) {
        int N = nums.size();
        vector<vector<int>> memory(N + 1, vector<int>(sum + 1, -1));
        return solveWithMemo(memory, nums, N, 0, sum);
    }

private:
    // O(N*S) & O(N*S)
    bool solveWithMemo(vector<vector<int>>& memory, vector<int>& nums, int N, int startIdx, int sum) {
        // Edge case: If the sum becomes zero, then there exists a subset with given sum 
        if(sum == 0)
            return true;
        
        // Memoization table: If the current state is already computed, then return the computed value
        if(memory[startIdx][sum] != -1)
            return memory[startIdx][sum];
            
        // Tracks the subset with sum equal to the given sum exist or not  
        bool flag = false;    
            
        // If the subset equal to given sum doesn't exist, then if possible, then take the index value
        for(int index = startIdx; (index < N && !flag); ++index) {
            if(nums[index] <= sum) {
                flag |= solveWithMemo(memory, nums, N, index + 1, sum - nums[index]);
            }
        }
        
        // Store the presence information of the subset to the memoization table and then return it
        return memory[startIdx][sum] = flag;
    }

    // O(2^N) & O(N)
    bool solveWithoutMemo(vector<int>& nums, int N, int startIdx, int sum) {
        // Edge case: If the sum becomes zero, then there exists a subset with given sum 
        if(sum == 0)
            return true;
            
        // Tracks the subset with sum equal to the given sum exist or not  
        bool flag = false;    
            
        // If the subset equal to given sum doesn't exist, then if possible, then take the index value
        for(int index = startIdx; (index < N && !flag); ++index) {
            if(nums[index] <= sum) {
                flag |= solveWithoutMemo(nums, N, index + 1, sum - nums[index]);
            }
        }
        
        // Return the presence information of the subset
        return flag;
    }
};

// Class to implement the Bottom-up approach:
class BottomUp {   
public:
    // #1 Method to determine if there exist the mentioned subset or not, using 2D buffer for tabulation - O(N*S) & O(N*S) : Where N let be the array size and S let be the sum value
    bool checkSubsetEqualSum_V1(vector<int>& nums, int sum) {
        int N = nums.size();
        
        // Early exit: If the array size is 1 and the element is equal to the sum, then return true, else false
        if(N == 1)
            return (nums[0] == sum);

        // Tabulation buffer: dp[index][currSum] represents, is there exists any subset within the "index" elements from the start of the array such that their sum equals to the "currSum"
        vector<vector<bool>> dp(N + 1, vector<bool>(sum + 1, false));

        // Edge case: If the array is empty and the sum is 0 then there always exists a subset with sum 0
        dp[0][0] = true;
        
        // Treat each index as the "number of elements can take from the start of the array" and check the existence of the subset whose sum equals to the "currSum"
        for(int index = 1; index <= N; ++index) {
            for(int currSum = 0; currSum <= sum; ++currSum) {
                bool currSkip = dp[index - 1][currSum];
                bool currTake = false;
                if(nums[index - 1] <= currSum) {
                    currTake = dp[index - 1][currSum - nums[index-1]];
                }
                dp[index][currSum] = currTake || currSkip;
            }
        }
        
        // Return the presence information of the subset with sum equal to the given sum
        return dp[N][sum];
    }

    // #2 Method to determine if there exist the mentioned subset or not, using 1D buffer for tabulation - O(N*S) & O(S) : Where N let be the array size and S let be the sum value
    bool checkSubsetEqualSum_V2(vector<int>& nums, int sum) {
        int N = nums.size();
        
        // Early exit: If the array size is 1 and the element is equal to the sum, then return true, else false
        if(N == 1)
            return (nums[0] == sum);

        // Tabulation buffer: "prevRow[currSum] / currRow[currSum]" represents, is there exists any subset within the "index" elements from the start of the array such that their sum equals to the "currSum"
        vector<bool> prevRow(sum + 1, false), currRow(sum + 1, false);

        // Edge case: If the array is empty and the sum is 0 then there always exists a subset with sum 0
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
        
        // Return the presence information of the subset with sum equal to the given sum
        return prevRow[sum];
    }
};

// Driver code
int main() {
    cout<<"Note: The application only accepts non-decimal numeric type value!\n\n";
        
    // Input section to control the flow of iterations of the application
    int testCases;
    cout<<"Enter the number of cases to test: ";
    cin>>testCases;

    while(testCases-- > 0) {
        // Input the array size
        int N;
        cout<<"\nEnter size of the array: ";
        cin>>N;

        // Input the target sum
        int sum;
        cout<<"Enter the sum value: ";
        cin>>sum;

        // Check the given values are valid or not
        if(N <= 0 || N >= 1001) {
            cout<<"You must enter the size which lies within the range [1 - 10^3]\n";
        }
        else if(sum <= -1 || sum >= 1001) {
            cout<<"You must enter the sum which lies within the range [0 - 10^3]\n";
        }
        else {
            // Stores the array values
            vector<int> nums(N, 0);

            // Input the array values
            for(int index = 0; index < N;) {
                cout<<"Enter the value of the "<<index<<"th index: ";
                cin>>nums[index];
                if(nums[index] <= -1 || nums[index] >= 1000000001) {
                    cout<<"You must enter a value which lies within the range [0 - 10^9]\n";
                    continue;
                }
                index++;
            }

            // Determination call
            BottomUp bottomUp;
            if(bottomUp.checkSubsetEqualSum_V2(nums, N)) {
                cout<<"Output: There exists a subset of sum "<<sum<<"\n";
            }
            else {
                cout<<"Output: There exists no subset of sum "<<sum<<"\n";
            }
        }
    }

    return 0;
}
/*
    Topics: Array | Dynamic Programming
    Links: https://www.geeksforgeeks.org/problems/subset-sum-problem-1611555638/1
           https://www.codingninjas.com/studio/problems/subset-sum-equal-to-k_1550954?leftPanelTabValue=PROBLEM
*/
