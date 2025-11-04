// Code to find the number of possible combinations that add up to target. Note that the array values are distinct ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class TopDown {
    int n;

    // O(N^T) & O(T) : Where T = target
    int solveWithoutMemo(vector<int>& nums, int target) {
        if(target == 0)
            return 1;
        
        int count = 0;

        for(int i = 0; (i < n && nums[i] <= target); ++i)
            count += solveWithoutMemo(nums, target - nums[i]);

        return count;
    }
    
    // O(N*T) & O(2*T) : Where T = target
    int solveWithMemo(vector<int>& dp, vector<int>& nums, int target) {
        if(target == 0)
            return 1;

        if(dp[target] != -1)
            return dp[target];
        
        int count = 0;

        for(int i = 0; (i < n && nums[i] <= target); ++i)
            count += solveWithMemo(dp, nums, target - nums[i]);

        return dp[target] = count;
    }

public:
    int numWaysToSumTarget(vector<int>& nums, int givenTarget) {
        n = nums.size();
        sort(begin(nums), end(nums));
        vector<int> dp(target + 1, -1);
        return solveWithMemo(dp, nums, target);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // O(T*N) & O(1*T) : Where T = givenTarget
    int numWaysToSumTarget(vector<int>& nums, int givenTarget) {
        int n = nums.size();
        sort(begin(nums), end(nums));
      
        vector<int> dp(givenTarget + 1, -1);
        dp[0] = 1;

        for(int target = 1; target <= givenTarget; ++target) {
            unsigned int count = 0;

            for(int i = 0; (i < n && nums[i] <= target); ++i) {
                count += dp[target - nums[i]];
            }

            dp[target] = count;
        }

        return dp[givenTarget];
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Links : https://leetcode.com/problems/combination-sum-iv/
        https://cses.fi/problemset/task/1635/
