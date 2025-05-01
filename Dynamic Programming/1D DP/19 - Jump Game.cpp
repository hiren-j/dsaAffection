// Code to check whether you can reach the last index of the array or not. You are initially positioned at the array's first index, and each element in the array represents your maximum jump length at that position ~ coded by Hiren

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    // O(M^N) & O(N) : Where M = maximum element of array
    bool solveWithoutMemo(vector<int>& nums, int index) {
        if(index == n-1)
            return true;

        for(int jump = 1; (jump <= nums[index] && index + jump < n); ++jump)
            if(solveWithoutMemo(nums, index + jump)) 
                return true; // Return true if you reach last index from any of the possibility

        return false;
    }

    // O(M*N) & O(2*N) : Where M = maximum element of array
    bool solveWithMemo(vector<int>& dp, vector<int>& nums, int index) {
        if(index == n-1)
            return true;
        
        if(dp[index] != -1)
            return dp[index];

        for(int jump = 1; (jump <= nums[index] && index + jump < n); ++jump)
            if(solveWithMemo(dp, nums, index + jump))
                return dp[index] = true; // Return true if you reach last index from any of the possibility

        return dp[index] = false;
    }

public:
    bool canReachLastIndex(vector<int>& nums) {
        n = nums.size();
        vector<int> dp(n-1, -1);
        return solveWithMemo(dp, nums, 0);
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // O(N*M) & O(1*N) : Where M = maximum element of array
    bool canReachLastIndex(vector<int>& nums) {
        int n = nums.size();

        vector<bool> dp(n, false);
        dp[n - 1] = true; 

        for(int index = n-2; index >= 0; --index) {
            // dp[index] = false; // If you want dp array like this: vector<int> dp(n, -1); Then uncomment this line 
            
            for(int jump = 1; (jump <= nums[index] && index + jump < n); ++jump) {
                if(dp[index + jump]) {
                    dp[index] = true;
                    break;
                }
            }   
        }

        return dp[0];
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Greedy
Link  : https://leetcode.com/problems/jump-game/
