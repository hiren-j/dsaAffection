// Program to count the total number of partitions in which S1 is greater than or equal to S2 and the difference between S1 and S2 is equal to D ~ coded by Hiren
#include <iostream>
#include <numeric>
#include <vector>
#define mod 1000000007
using namespace std;

// Class to implement the Top-down approach:    
class TopDown {
public:
    // Method to count the total number of partitions such that the difference between S1 and S2 is equal to D, using recursion with memoization - O(N*T) & O(N*T) : Where N let be the array size and T let be the target
    int countPartitions(int N, int D, vector<int>& nums) {
        int totalSum = accumulate(begin(nums), end(nums), 0);
        
        // Edge case: If the difference becomes negative or odd, then you can't have valid partitions
        if(totalSum - D < 0 || (totalSum - D) % 2 != 0)
            return false;

        // If the difference is an even value, then you can have valid partitions 
        int target = (totalSum - D) / 2;

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
        int currSkip = solveWithMemo(memory, nums, N, index - 1, target) % mod; // Is to skip the index value and move on
        int currTake = 0;                                                       // Is to take the index value and move on  
        
        // If possible, then take the index value
        if(nums[index] <= target)
            currTake = solveWithMemo(memory, nums, N, index - 1, target - nums[index]) % mod;

        // Store the count of all the subsets to the memoization table and then return it   
        return memory[index][target] = (currTake + currSkip) % mod;
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
        int currSkip = solveWithoutMemo(nums, N, index - 1, target) % mod; // Is to skip the index value and move on
        int currTake = 0;                                                  // Is to take the index value and move on 
            
        // If possible, then take the index value
        if(nums[index] <= target)
            currTake = solveWithoutMemo(nums, N, index - 1, target - nums[index]) % mod;
            
        // Return the count of all the subsets whose sum is equal to the target
        return (currTake + currSkip) % mod;
    }
};

// Class to implement the Bottom-up approach:
class BottomUp {
public:
    // #1 Method to count the total number of partitions such that the difference between S1 and S2 is equal to D, using 2D buffer for tabulation - O(N*T) & O(N*T) : Where N let be the array size and T let be the target
    int countPartitions_V1(int N, int D, vector<int>& nums) {
        int totalSum = accumulate(begin(nums), end(nums), 0);
        
        // Edge case: If the difference becomes negative or odd, then you can't have valid partitions
        if(totalSum - D < 0 || (totalSum - D) % 2 != 0)
            return false;
            
        // If the difference is an even value, then you can have valid partitions 
        int target = (totalSum - D) / 2;
        
        // Tabulation buffer: dp[index][currTarget] stores the count of all the subsets lying within the "index" elements of the start of the array, such that their sum equals to the "currTarget"
        vector<vector<int>> dp(N + 1, vector<int>(target + 1, 0));

        // Edge case: If the array is empty and the target is 0, then there always exists a single subset with sum 0
        dp[0][0] = 1;
        
        // Treat each index as the "number of elements can take from the start of the array" and count all the subsets lying within, whose sum is equal to the "currTarget"
        for(int index = 1; index <= N; ++index) {
            for(int currTarget = 0; currTarget <= target; ++currTarget) {
                int currSkip = dp[index - 1][currTarget] % mod;
                int currTake = 0; 
                if(nums[index - 1] <= currTarget) {
                    currTake = dp[index - 1][currTarget - nums[index - 1]] % mod;
                }
                dp[index][currTarget] = (currTake + currSkip) % mod;
            }
        }

        // Return the count of all the subsets with sum equal to the target 
        return dp[N][target];
    }

    // #2 Method to count the total number of partitions such that the difference between S1 and S2 is equal to D, using 1D buffer for tabulation - O(N*T) & O(T) : Where N let be the array size and T let be the target
    int countPartitions_V2(int N, int D, vector<int>& nums) {
        int totalSum = accumulate(begin(nums), end(nums), 0);
        
        // Edge case: If the difference becomes negative or odd, then you can't have valid partitions
        if(totalSum - D < 0 || (totalSum - D) % 2 != 0)
            return false;
            
        // If the difference is an even value, then you can have valid partitions 
        int target = (totalSum - D) / 2;

        // Tabulation buffer: prevRow[currTarget] / currRow[currTarget]" stores the count of all the subsets lying within the "index" elements of the start of the array, such that their sum equals to the "currTarget"
        vector<int> prevRow(target + 1, 0), currRow(target + 1, 0);

        // Edge case: If the array is empty and the target is 0, then there always exists a single subset with sum 0
        prevRow[0] = 1;
        
        // Treat each index as the "number of elements can take from the start of the array" and count all the subsets lying within, whose sum is equal to the "currTarget"
        for(int index = 1; index <= N; ++index) {
            for(int currTarget = 0; currTarget <= target; ++currTarget) {
                int currSkip = prevRow[currTarget] % mod;
                int currTake = 0; 
                if(nums[index - 1] <= currTarget) {
                    currTake = prevRow[currTarget - nums[index - 1]] % mod;
                }
                currRow[currTarget] = (currTake + currSkip) % mod;
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
        cout<<"Enter size of the array (N): ";
        cin>>N;

        // Input the difference value
        int D;
        cout<<"Enter the difference value (D): ";
        cin>>D;

        // Check the given values are lying within the problem constraints or not
        if(N <= 0 || N >= 501) {
            cout<<"You must enter the N value, which lies between 1 and 500!";
        }
        else if(D <= -1 || D >= 25001) {
            cout<<"You must enter the D value, which lies between 0 and 25000!";
        }
        else {
            // Stores the array values
            vector<int> nums(N);

            // Input the array values
            for(int index = 0; index < N;) {
                cout<<"Enter the value of "<<index<<"th index: ";
                cin>>nums[index];
                if(nums[index] <= -1 || nums[index] >= 51) {
                    cout<<"You must enter a value, which lies between 0 and 50!\n";
                    continue;
                }
                index++;
            }

            // Call to get the count of total number of partitions such that the difference between S1 and S2 is equal to D
            BottomUp bottomUp;
            int count = bottomUp.countPartitions_V2(N, D, nums);
            cout<<"\nThe total number of such partitions are: "<<count;
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
    Link: https://www.geeksforgeeks.org/problems/partitions-with-given-difference/1
*/
