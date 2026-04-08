// Code to find the length of the longest strictly increasing subsequence ~ coded by vHiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    // O(N*N) & O(N)
    int solveWithMemoSpaceReduce(vector<int>& dp, const vector<int>& nums, int i, int prev) {
        if(i == n)
            return 0;

        if(dp[prev] != -1)
            return dp[prev];

        int currSkip = solveWithMemoSpaceReduce(dp, nums, i + 1, prev);
        int currTake = 0;

        if(prev == n || nums[prev] < nums[i]) {
            currTake = solveWithMemoSpaceReduce(dp, nums, i + 1, i) + 1;
        }

        return dp[prev] = max(currSkip, currTake);
    }

public:
    int lengthOfLIS(vector<int>& nums) {
        n = nums.size();
        vector<int> dp(n + 1, -1);
        return solveWithMemoSpaceReduce(dp, nums, 0, n);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    // O(N*N) & O(N)
    int solveWithTableSpaceReduce(const vector<int>& nums) {
        vector<int> dp(n + 1, -1);
        dp[n] = 0;

        for(int i = n - 1; i >= 0; --i) {
            for(int prev = n; prev >= 0; --prev) {
                int currSkip = dp[prev];
                int currTake = 0;

                if(prev == n || nums[prev] < nums[i])
                    currTake = dp[i] + 1;

                dp[prev] = max(currSkip, currTake);
            }
        }       

        return dp[n];
    }

public:
    int lengthOfLIS(vector<int>& nums) {
        n = nums.size();
        if(n == 1) return 1;
        return solveWithTableSpaceReduce(nums);
    }
};
    
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Binary Search | Dynamic Programming
Links : https://leetcode.com/problems/longest-increasing-subsequence/description/
        https://cses.fi/problemset/task/1145
