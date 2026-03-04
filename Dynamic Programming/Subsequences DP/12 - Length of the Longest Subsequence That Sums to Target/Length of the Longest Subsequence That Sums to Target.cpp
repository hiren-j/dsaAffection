// Code to find the length of the longest subsequence of the array that sums up to target. If no such subsequence exists then return -1 ~ coded by vHiren

----------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    // O(2^N) & O(N)
    int solveWithoutMemo(const vector<int>& nums, int i, int target) {
        if(target == 0)
            return 0;

        if(target < 0 || i == n)
            return INT_MIN;

        int currSkip = solveWithoutMemo(nums, i + 1, target);
        int currTake = solveWithoutMemo(nums, i + 1, target - nums[i]);
        if(currTake != INT_MIN) currTake += 1;

        return max(currSkip, currTake);
    }
    
    // O(N*T) & O(N*T) : Where T = target
    int solveWithMemo(vector<vector<int>>& dp, const vector<int>& nums, int i, int target) {
        if(target == 0)
            return 0;

        if(target < 0 || i == n)
            return INT_MIN;

        if(dp[i][target] != -1)
            return dp[i][target];

        int currSkip = solveWithMemo(dp, nums, i + 1, target);
        int currTake = solveWithMemo(dp, nums, i + 1, target - nums[i]);
        if(currTake != INT_MIN) currTake += 1;

        return dp[i][target] = max(currSkip, currTake);
    }
    
    // O(N*N*T) & O(N*T) : Where T = target
    int solveWithMemoLoop(vector<vector<int>>& dp, const vector<int>& nums, int start, int target) {
        if(target == 0)
            return 0;

        if(target < 0 || start == n)
            return INT_MIN;

        if(dp[start][target] != -1)
            return dp[start][target];

        int maxLen = INT_MIN;

        for(int i = start; i < n; ++i) {
            int currTake = solveWithMemoLoop(dp, nums, i + 1, target - nums[i]);
            if(currTake != INT_MIN) currTake += 1;
            maxLen = max(maxLen, currTake);
        }

        return dp[start][target] = maxLen;
    }
    // Note: This solution will lead to TLE

public:
    int lengthOfLongestSubsequence(vector<int>& nums, int target) {
        n = nums.size();
        vector<vector<int>> dp(n, vector<int>(target + 1, -1));
        int result = solveWithMemo(dp, nums, 0, target);
        return (result == INT_MIN) ? -1 : result;
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    // O(N*TG) & O(N*TG) : Where TG = targetGiven
    int solveBy2DTable(const vector<int>& nums, int targetGiven) {
        vector<vector<int>> dp(n + 1, vector<int>(targetGiven + 1, -1));

        for(int i = 0; i <= n; ++i)
            dp[i][0] = 0;

        for(int target = 1; target <= targetGiven; ++target)
            dp[n][target] = INT_MIN;
        
        for(int i = n - 1; i >= 0; --i) {
            for(int target = 1; target <= targetGiven; ++target) {
                int currSkip = dp[i + 1][target];
                int currTake = (target - nums[i] < 0) ? INT_MIN : dp[i + 1][target - nums[i]];
                if(currTake != INT_MIN) currTake += 1;
                dp[i][target] = max(currSkip, currTake); 
            }
        }

        return dp[0][targetGiven] == INT_MIN ? -1 : dp[0][targetGiven];
    }

    // O(N*TG) & O(N*TG) : Where TG = targetGiven
    int solveBy2DEnhanced(const vector<int>& nums, int targetGiven) {
        vector<vector<int>> dp(n + 1, vector<int>(targetGiven + 1, INT_MIN));

        for(int i = 0; i <= n; ++i)
            dp[i][0] = 0;
        
        for(int i = n - 1; i >= 0; --i) {
            for(int target = 1; target <= targetGiven; ++target) {
                int currSkip = dp[i + 1][target];
                int currTake = (target - nums[i] < 0) ? INT_MIN : dp[i + 1][target - nums[i]];
                if(currTake != INT_MIN) currTake += 1;
                dp[i][target] = max(currSkip, currTake); 
            }
        }

        return dp[0][targetGiven] == INT_MIN ? -1 : dp[0][targetGiven];
    }

    // O(N*TG) & O(TG) : Where TG = targetGiven
    int solveBy1DTable(const vector<int>& nums, int targetGiven) {
        vector<int> nextRow(targetGiven + 1, INT_MIN);
        nextRow[0] = 0;
        
        for(int i = n - 1; i >= 0; --i) {
            vector<int> currRow(targetGiven + 1, INT_MIN);
            currRow[0] = 0;

            for(int target = 1; target <= targetGiven; ++target) {
                int currSkip = nextRow[target];
                int currTake = (target - nums[i] < 0) ? INT_MIN : nextRow[target - nums[i]];
                if(currTake != INT_MIN) currTake += 1;
                currRow[target] = max(currSkip, currTake); 
            }

            swap(nextRow, currRow);
        }

        return nextRow[targetGiven] == INT_MIN ? -1 : nextRow[targetGiven];
    }

public:
    int lengthOfLongestSubsequence(vector<int>& nums, int target) {
        n = nums.size();
        return solveBy1DTable(nums, target);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/length-of-the-longest-subsequence-that-sums-to-target/description/
