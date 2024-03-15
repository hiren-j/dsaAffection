// Program to count all the subsets of the given array with a sum equal to the given sum ~ coded by Hiren
#include <iostream>
#include <cstdlib>
#include <vector>
#define mod 1000000007
#define controlAppFlow() {char userChoice; cout<<"\n\nPress \'R\' to restart the application, else it will exist: "; cin>>userChoice; userWantsOperation = (userChoice == 'R' ? true : false);}
using namespace std;

// Class to implement the Top-down approach:
class TopDown {
public:
    // Method to count all the subsets with a sum equal to the given sum, using recursion with memoization - O(N*S) & O(N*S) : Where N let be the array size and S let be the sum value
    int countSubsetsEqualSum(vector<int>& nums, int N, int sum) {
	vector<vector<int>> memory(N, vector<int>(sum + 1, -1));
	return solveWithMemo(memory, nums, N, N-1, sum);
    }

private:
    // O(N*S) & O(N*S)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& nums, int N, int index, int sum) {
        // Edge case: If you reached the 0th index then compute the count of all the subsets according to their existence
        if(index == 0) {
            if(sum == 0)
                return (nums[index] == 0) ? 2 : 1;
            else
                return (nums[index] == sum) ? 1 : 0;
        }

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[index][sum] != -1)
            return memory[index][sum];
            
        // There are always two possibilties to perform at each index
        int currSkip = solveWithMemo(memory, nums, N, index - 1, sum) % mod; // Is to skip the index value and move on
        int currTake = 0;                                                    // Is to take the index value and move on
        
        // If possible then take the index value
        if(nums[index] <= sum)
            currTake = solveWithMemo(memory, nums, N, index - 1, sum - nums[index]) % mod;
            
        // Store the count of all the subsets to the memoization table and then return it
        return memory[index][sum] = (currTake + currSkip) % mod;
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(vector<int>& nums, int N, int index, int sum) {
        // Edge case: If you reached the 0th index then compute the count of all the subsets according to their existence
        if(index == 0) {
            if(sum == 0)
                return (nums[index] == 0) ? 2 : 1;
            else
                return (nums[index] == sum) ? 1 : 0;
        }
            
        // There are always two possibilties to perform at each index
        int currSkip = solveWithoutMemo(nums, N, index - 1, sum) % mod; // Is to skip the index value and move on
        int currTake = 0;                                               // Is to take the index value and move on
        
        // If possible then take the index value
        if(nums[index] <= sum)
            currTake = solveWithoutMemo(nums, N, index - 1, sum - nums[index]) % mod;
            
        // Return the count of all the subsets
        return (currTake + currSkip) % mod;
    }
};

// Class to implement the Bottom-up approach:
class BottomUp {
public:
    // #1 Method to count all the subsets with a sum equal to the given sum, using 2D buffer for tabulation - O(N*S) & O(N*S) : Where N let be the array size and S let be the sum value
    int countSubsetsEqualSum_V1(vector<int>& nums, int N, int sum) {        
    	// Tabulation buffer: dp[index][currSum] stores the count of all the subsets lying within the "index" elements (consider "index" elements from the start of the array) such that their sum equals to the "currSum"
	vector<vector<int>> dp(N + 1, vector<int>(sum + 1, 0));
        
        // Edge case: If the array is empty and the sum is 0 then there always exists a single subset with sum 0
	dp[0][0] = 1;
	    
        // Treat each index as the "number of elements can take from the start of the array" and count all the subsets lying within whose sum is equal to the "currSum"
	for(int index = 1; index <= N; ++index) {
	    for(int currSum = 0; currSum <= sum; ++currSum) {
	        int currSkip = dp[index - 1][currSum] % mod;
	        int currTake = 0;
	        if(nums[index - 1] <= currSum) {
	            currTake = dp[index - 1][currSum - nums[index - 1]] % mod;
	        }
	        dp[index][currSum] = (currTake + currSkip) % mod;
	    }
	}

        // Return the count of all the subsets with sum equal to the given sum  
	return dp[N][sum];
    }

    // #2 Method to count all the subsets with a sum equal to the given sum, using 1D buffer for tabulation - O(N*S) & O(S) : Where N let be the array size and S let be the sum value
    int countSubsetsEqualSum_V2(vector<int>& nums, int N, int sum) {
	// Tabulation buffer: prevRow[currSum] / currRow[currSum]" stores the count of all the subsets lying within the "index" elements (consider "index" elements from the start of the array) such that their sum equals to the "currSum"
	vector<int> prevRow(sum + 1, 0), currRow(sum + 1, 0);

        // Edge case: If the array is empty and the sum is 0 then there always exists a single subset with sum 0
	prevRow[0] = 1;
	    
        // Treat each index as the "number of elements can take from the start of the array" and count all the subsets lying within whose sum is equal to the "currSum"
	for(int index = 1; index <= N; ++index) {
	    for(int currSum = 0; currSum <= sum; ++currSum) {
	        int currSkip = prevRow[currSum] % mod;
	        int currTake = 0;
	        if(nums[index - 1] <= currSum) {
		    currTake = prevRow[currSum - nums[index - 1]] % mod;
	        }
	        currRow[currSum] = (currTake + currSkip) % mod;
	    }
	    prevRow = currRow;
	}
	    
        // Return the count of all the subsets with sum equal to the given sum  
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

        // Input the sum value
        int sum;
        cout<<"Enter the sum value: ";
        cin>>sum;

        // Check the given values are valid or not
        if(N <= 0 || N >= 1000001 || sum <= 0 || sum >= 1000001) {
            cout<<"You must enter a \"size\" and \"sum\" which lies between 1 and 1000000!";
            controlAppFlow(); // Controls the flow of iterations of the application
            continue;
        }   
        else {
            // Stores the array values
            vector<int> nums(N, 0);

            // Input the array values
            for(int index = 0; index < N;) {
                cout<<"Enter the value of "<<index<<"th index: ";
                cin>>nums[index];
                if(nums[index] <= -1 || nums[index] >= 1000001) {
                    cout<<"You must enter a value which lies within the range 0 and 1000000!\n";
                    continue;
                }
                index++;
            }

            // Call to get the count of all the subsets whose sum is equal to the given sum
            BottomUp bottomUp;
            int count = bottomUp.countSubsetsEqualSum_V2(nums, N, sum);
            cout<<"\nThe count of all the subsets of the given array whose sum is equal to "<<sum<<" is: "<<count;

            // Controls the flow of iterations of the application
            controlAppFlow();
        }
    }

    return 0;
}
/*
    Topics: Array | Dynamic Programming
    Links: https://www.geeksforgeeks.org/problems/perfect-sum-problem5633/1
           https://www.codingninjas.com/studio/problems/count-subsets-with-sum-k_3952532?utm_source=striver&utm_medium=website&utm_campaign=a_zcoursetuf
*/
