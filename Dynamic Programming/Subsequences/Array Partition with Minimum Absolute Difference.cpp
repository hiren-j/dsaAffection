// Program to divide the given array S into two sets S1 and S2 such that the absolute difference between their sums is minimum, the task is to find the minimum absolute difference ~ coded by Hiren 
#include <iostream>
#include <numeric>
#include <cstdlib>
#include <climits>
#include <vector>
using namespace std;

// Class to implement the Top-down approach:
class TopDown {
public:
    // Method to partition the array into two sets and to find the minimum absolute difference between their sums, using recursion with memoization - O(N*S) & O(N*S) : Where N let be the array size and S let be the total sum
	int minSubsetSumDifference(vector<int>& nums, int N) {
	    int totalSum = accumulate(begin(nums), end(nums), 0);
	    
        // Tabulation buffer: dp[index][amount] represents, is there exists any subset within the "index" elements of the start of the array, such that their sum equals to the "amount / currSum"
	    vector<vector<int>> dp(N, vector<int>(totalSum + 1, -1));
	    
		// If a single subset exists, then the another subset can easily be identified, hence look for the existence of all the possible subsets through their sum value
	    for(int currSum = 0; currSum <= totalSum; ++currSum) {
	        solveWithMemo(dp, nums, N, N - 1, currSum);
	    }
	    
		// Stores the "minimum absolute difference of two subsets sum after array partition / result value"
	    int minAbsDiff = INT_MAX;
	    
		// Iterate and check the existence of the subsets in the array 
	    for(int subset1Sum = 0; subset1Sum <= totalSum/2; ++subset1Sum) {
			// If a subset exists, then it's a valid partition, hence update the result value by the minimum value
	        if(dp[N - 1][subset1Sum] == 1) {
	            int subset2Sum = totalSum - subset1Sum;
	            minAbsDiff = min(minAbsDiff, abs(subset1Sum - subset2Sum));
	        }
	    }
	    
		// Return the result value
	    return minAbsDiff;
	}
private:
    bool solveWithMemo(vector<vector<int>>& dp, vector<int>& nums, int N, int index, int amount) {
        // Edge case: If the amount becomes zero, then there exists a subset with given amount 
        if(amount == 0)
            return dp[index][amount] = true;        
    
	    // Edge case: If all the elements are exhausted and if the amount becomes zero, then there exists a subset with given amount
        if(index == 0)
            return dp[index][amount] = (nums[index] == amount);
            
		// Memoization table: If the current state is already computed, then return the computed value
        if(dp[index][amount] != -1)
            return dp[index][amount];
            
		// There are always two possibilties to perform at each index
        bool currSkip = solveWithMemo(dp, nums, N, index - 1, amount); // Is to skip the index value and move on
        bool currTake = false;										   // Is to take the index value and move on	
        
		// If the subset equal to given amount doesn't exist, then if possible, then take the index value
        if(!currSkip && nums[index] <= amount) 
            currTake = solveWithMemo(dp, nums, N, index - 1, amount - nums[index]);
            
		// Store the presence information of the subset to the memoization table and then return it
        return dp[index][amount] = (currTake || currSkip);
    }
};

// #1 Class to implement the Bottom-up approach:
class BottomUp_V1 {
public:
    // Method to partition the array into two sets and to find the minimum absolute difference between their sums, using 2D buffer for tabulation - O(N*S) & O(N*S) : Where N let be the array size and S let be the total amount
	int minSubsetSumDifference(vector<int>& nums, int N) {
	    int totalSum = accumulate(begin(nums), end(nums), 0);
	    
        // Tabulation buffer: dp[index][currSum] represents, is there exists any subset within the "index" elements from the start of the array such that their sum equals to the "currSum"
	    vector<vector<bool>> dp(N + 1, vector<bool>(totalSum + 1, false));
		
        // Edge case: If the array is empty and the sum is zero, then there always exists a subset with sum 0
	    dp[0][0] = true;
	    
        // Treat each index as the "number of elements can take from the start of the array" and check the existence of the subset whose sum equals to the "currSum"
        for(int index = 1; index <= N; ++index) {
            for(int currSum = 0; currSum <= totalSum; ++currSum) {
                bool currSkip = dp[index - 1][currSum];
                bool currTake = false;
                if(!currSkip && nums[index - 1] <= currSum) {
                    currTake = dp[index - 1][currSum - nums[index - 1]];
                }
                dp[index][currSum] = currTake || currSkip;
            }
        }
	    
		// Stores the "minimum absolute difference of two subsets sum after array partition / result value"
	    int minAbsDiff = INT_MAX;
	    
		// Iterate and check the existence of the subsets in the array 
	    for(int subset1Sum = 0; subset1Sum <= totalSum/2; ++subset1Sum) {
			// If a subset exists, then it's a valid partition, hence update the result value by the minimum value
	        if(dp[N][subset1Sum] == 1) {
	            int subset2Sum = totalSum - subset1Sum;
	            minAbsDiff = min(minAbsDiff, abs(subset1Sum - subset2Sum));
	        }
	    }
	    
		// Return the result value
	    return minAbsDiff;
	}
};

// #2 Class to implement the Bottom-up approach:
class BottomUp_V2 {
public:
    // Method to partition the array into two sets and to find the minimum absolute difference between their sums, using 1D buffer for tabulation - O(N*S) & O(S) : Where N let be the array size and S let be the total amount
	int minSubsetSumDifference(vector<int>& nums, int N) {
	    int totalSum = accumulate(begin(nums), end(nums), 0);
	    
        // Tabulation buffer: "prevRow[currSum] / currRow[currSum]" represents, is there exists any subset within the "index" elements from the start of the array such that their sum equals to the "currSum"
	    vector<bool> prevRow(totalSum + 1, false), currRow(totalSum + 1, false);

		// Edge case: If the array is empty and the sum is zero, then there always exists a subset with sum 0
	    prevRow[0] = true;
	    
		// Treat each index as the "number of elements can take from the start of the array" and check the existence of the subset whose sum equals to the "currSum"
        for(int index = 1; index <= N; ++index) {
            for(int currSum = 0; currSum <= totalSum; ++currSum) {
                bool currSkip = prevRow[currSum];
                bool currTake = false;
                if(!currSkip && nums[index - 1] <= currSum) {
                    currTake = prevRow[currSum - nums[index - 1]];
                }
                currRow[currSum] = currTake || currSkip;
            }
            prevRow = currRow;
        }
	    	    
		// Stores the "minimum absolute difference of two subsets sum after array partition / result value"
	    int minAbsDiff = INT_MAX;
	    
		// Iterate and check the existence of the subsets in the array 
	    for(int subset1Sum = 0; subset1Sum <= totalSum/2; ++subset1Sum) {
			// If a subset exists, then it's a valid partition, hence update the result value by the minimum value
	        if(prevRow[subset1Sum] == 1) {
	            int subset2Sum = totalSum - subset1Sum;
	            minAbsDiff = min(minAbsDiff, abs(subset1Sum - subset2Sum));
	        }
	    }
	    
		// Return the result value
	    return minAbsDiff;
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
        if(N <= 0 || N >= 1000001) {
            cout<<"You must enter the size which lies between 1 and 10^6!";
        }   
        else {
            // Stores the array values
            vector<int> nums(N, 0);

            // Input the array values
            for(int index = 0; index < N;) {
                cout<<"Enter the value of "<<index<<"th index: ";
                cin>>nums[index];
                if(nums[index] <= -1 || nums[index] >= 100001) {
                    cout<<"You must enter a value which lies within the range 0 and 10^5!\n";
                    continue;
                }
                index++;
            }

            // Call to get the count of all the subsets whose sum is equal to the given sum
            BottomUp_V2 bottomUp;
            int minAbsDiff = bottomUp.minSubsetSumDifference(nums, N);
            cout<<"\nAfter partitioning the array into two sets, the minimum absolute difference between their sums is: "<<minAbsDiff;
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
    Links: https://www.geeksforgeeks.org/problems/minimum-sum-partition3317/1
           https://www.codingninjas.com/studio/problems/partition-a-set-into-two-subsets-such-that-the-difference-of-subset-sums-is-minimum._842494?utm_source=striver&utm_medium=website&utm_campaign=a_zcoursetuf
*/
