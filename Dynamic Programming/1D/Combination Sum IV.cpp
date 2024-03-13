// Program to find the number of possible combinations that add up to "target" ~ coded by Hiren
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

// #1 Class to implement the Top-down approach:
class TopDown_V1 {
public:
    // Method to find the number of possible combinations that add up to "target", using recursion with memoization - O(N*T) & O(T) : Where N is the size of "nums" and T is the "target" 
    int combinationSum4(vector<int>& nums, int target) {
        vector<int> cache(target + 1, -1);
        return solveWithMemo(cache, nums, nums.size(), target);
    }

private:
    // O(N*T) & O(T)
    int solveWithMemo(vector<int>& cache, vector<int>& nums, int N, int target) {
        // If the "target value" becomes zero, then one valid combination is possible
        if(target == 0)
            return 1;

        // Memoization table: If the current state is already computed, then return the computed value
        if(cache[target] != -1)
            return cache[target];

        // Stores the result value
        int count = 0;

        // Try each number of "nums" to find the number of possible combinations that add up to "target"
        for(int J=0; J<N; J++) {
            if(nums[J] <= target) {
                count += solveWithMemo(cache, nums, N, target-nums[J]);
            }
        }

        // Store the result value to the "memoization table" and then return it
        return cache[target] = count;
    }

    // O(2^T) & O(T)
    int solveWithoutMemo(vector<int>& nums, int N, int target) {
        // If the "target value" becomes zero, then one valid combination is possible
        if(target == 0)
            return 1;

        // Stores the result value
        int count = 0;

        // Try each number of "nums" to find the number of possible combinations that add up to "target"
        for(int J=0; J<N; J++) {
            if(nums[J] <= target) {
                count += solveWithoutMemo(nums, N, target-nums[J]);
            }
        }

        // Return the result value
        return count;
    }
};

// #2 Class to implement the Top-down approach:
class TopDown_V2 {
public:
    // Method to find the number of possible combinations that add up to "target", using recursion with memoization - O(N*T) & O(T) : Where N is the size of "nums" and T is the "target" 
    int combinationSum4(vector<int>& nums, int target) {
        sort(begin(nums), end(nums));
        vector<int> cache(target + 1, -1);
        return solveWithMemo(cache, nums, nums.size(), target);
    }

private:
    // O(N*T) & O(T)
    int solveWithMemo(vector<int>& cache, vector<int>& nums, int N, int target) {
        // If the "target value" becomes zero, then one valid combination is possible
        if(target == 0)
            return 1;

        // Memoization table: If the current state is already computed, then return the computed value
        if(cache[target] != -1)
            return cache[target];

        // Stores the result value
        int count = 0;

        // Try possible numbers of "nums" to find the number of combinations that add up to "target"
        for(int J = 0; (J < N && nums[J] <= target); ++J) 
            count += solveWithMemo(cache, nums, N, target - nums[J]);

        // Store the result value to the "memoization table" and then return it
        return cache[target] = count;
    }

    // O(2^T) & O(T)
    int solveWithoutMemo(vector<int>& nums, int N, int target) {
        // If the "target value" becomes zero, then one valid combination is possible
        if(target == 0)
            return 1;

        // Stores the result value
        int count = 0;

        // Try possible numbers of "nums" to find the number of combinations that add up to "target"
        for(int J = 0; (J < N && nums[J] <= target); ++J)
            count += solveWithoutMemo(nums, N, target - nums[J]);

        // Store the result value to the "memoization table" and then return it
        return count;
    }
};

// Class to implement the Bottom-up approach:
class BottomUp {
public:
    // #1 Method to find the number of possible combinations that add up to "target", using 1D buffer for tabulation - O(N*T) & O(T) : Where N is the size of "nums" and T is the "target" 
    int combinationSum4_V1(vector<int>& nums, int target) {
        int N = nums.size();

        // Tabulation buffer: dp[target] stores the number of possible combinations that add up to "target"
        vector<unsigned int> dp(target + 1);

        // If the "target value" is zero, then one valid combination is possible
        dp[0] = 1;

        // Treat each index as an "individual target" and find the number of possible combinations that add up to it
        for(int currTarget = 1; currTarget <= target; ++currTarget) {
            // Try every number of "nums" to find the number of combinations that add up to "currTarget"
            for(int J = 0; J < N; ++J) {
                if(nums[J] <= currTarget) {
                    dp[currTarget] += dp[currTarget - nums[J]];
                }
            }
        }

        // Return the number of possible combinations that add up to "target" 
        return dp[target];
    }

    // #2 Method to find the number of possible combinations that add up to "target", using 1D buffer for tabulation - O(N*T) & O(T) : Where N is the size of "nums" and T is the "target" 
    int combinationSum4_V2(vector<int>& nums, int target) {
        int N = nums.size();
        sort(begin(nums), end(nums));

        // Tabulation buffer: dp[target] stores the number of possible combinations that add up to "target"
        vector<unsigned int> dp(target + 1);
        
        // If the "target value" is zero, then one valid combination is possible
        dp[0] = 1; 

        // Treat each index as an "individual target" and find the number of possible combinations that add up to it
        for(int currTarget = 1; currTarget <= target; ++currTarget) {
            // Try possible numbers of "nums" to find the number of combinations that add up to "currTarget"
            for(int J = 0; (J < N && nums[J] <= currTarget); ++J) {
                dp[currTarget] += dp[currTarget - nums[J]];
            }
        }

        // Return the number of possible combinations that add up to "target" 
        return dp[target];
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

        // Input the target value
        int target;
        cout<<"Enter the target value: ";
        cin>>target;

        // Check the given values are valid or not
        if(N <= 0 || N >= 201) {
            cout<<"You must enter a size which lies between 1 and 200!";
        }   
        else if(target <= 0 || target >= 1001) {
            cout<<"You must enter a target which lies between 1 and 1000!";
        }
        else {
            // Stores the array values
            vector<int> nums(N);

            // Input the array values
            cout<<"\nNote: You must enter unique values for the array or the application will throw wrong outputs!\n";
            for(int index = 0; index < N;) {
                cout<<"Enter the value of "<<index<<"th index: ";
                cin>>nums[index];
                if(nums[index] <= 0 || nums[index] >= 1001) {
                    cout<<"You must enter a value which lies between 1 and 1000!\n";
                    continue;
                }
                index++;
            }

            // Call to find the number of possible combinations that add up to "target"
            BottomUp bottomUp;
            int count = bottomUp.combinationSum4_V2(nums, target);
            cout<<"\nThe total number of possible combinations that add up to target "<<target<<" is: "<<count;
        }

        // Input section to control the flow of iterations of the application
        char userChoice; 
        cout<<"\n\nPress \'R\' to restart the application, else it will exist: "; 
        cin>>userChoice; 
        userWantsOperation = (userChoice == 'R' ? true : false);
    }
}
/*
    Topics: Array | Dynamic Programming
    Link: https://leetcode.com/problems/combination-sum-iv/
*/
