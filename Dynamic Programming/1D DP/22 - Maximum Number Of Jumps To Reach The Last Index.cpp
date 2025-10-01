// Code to find the maximum number of jumps required to reach the last index of the array with following the mentioned rules ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    // O(N^N) & O(N)
    int solveWithoutMemo(vector<int>& nums, int target, int start) {
        if(start == n-1)
            return 0;
        
        int maxJumps = INT_MIN;

        for(int jumpIdx = start+1; jumpIdx < n; ++jumpIdx) {
            int delta = nums[jumpIdx] - nums[start];

            if(-target <= delta && delta <= target) {
                int nextJumps = solveWithoutMemo(nums, target, jumpIdx);
                if(nextJumps != INT_MIN) {
                    maxJumps = max(maxJumps, nextJumps + 1);
                }
            }
        }

        return maxJumps;
    }

    // O(N*N) & O(2*N)
    int solveWithMemo(vector<int>& dp, vector<int>& nums, int target, int start) {
        if(start == n-1)
            return 0;

        if(dp[start] != -1)
            return dp[start];
        
        int maxJumps = INT_MIN;

        for(int jumpIdx = start+1; jumpIdx < n; ++jumpIdx) {
            int delta = nums[jumpIdx] - nums[start];
            
            if(-target <= delta && delta <= target) {
                int nextJumps = solveWithMemo(dp, nums, target, jumpIdx);
                if(nextJumps != INT_MIN) {
                    maxJumps = max(maxJumps, nextJumps + 1);
                }
            }
        }

        return dp[start] = maxJumps;
    }

public:
    int maxJumpsToLastIndex(vector<int>& nums, int target) {
        n = nums.size();
        vector<int> dp(n-1, -1);
        int maxJumps = solveWithMemo(dp, nums, target, 0);
        return (maxJumps == INT_MIN) ? -1 : maxJumps;
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class BottomUp {
public:
    // O(N*N) & O(1*N)
    int maxJumpsToLastIndex(vector<int>& nums, int target) {
        int n = nums.size();
        
        vector<int> dp(n, -1);
        dp[n - 1] = 0;

        for(int start = n-2; start >= 0; --start) {
            int maxJumps = INT_MIN;

            for(int jumpIdx = start+1; jumpIdx < n; ++jumpIdx) {
                int delta = nums[jumpIdx] - nums[start];

                if(-target <= delta && delta <= target) {
                    int nextJumps = dp[jumpIdx];
                    if(nextJumps != INT_MIN) {
                        maxJumps = max(maxJumps, nextJumps + 1);
                    }
                }
            }

            dp[start] = maxJumps;
        }

        int maxJumps = dp[0];
        return (maxJumps == INT_MIN) ? -1 : maxJumps;
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/maximum-number-of-jumps-to-reach-the-last-index/description/
