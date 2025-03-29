// Code to find the minimum possible cost of a split of the given array. Split the array into some number of non-empty subarrays. The cost of a split is the sum of the importance value of each subarray in the split. The importance value of a subarray is k + trimmed(subarray).length ~ coded by Hiren

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    // O(N^N) & O(N*1000)
    int solveWithoutMemo(vector<int>& nums, int k, int start_i) {
        if(start_i == n)
            return 0;

        vector<int> freq(1000);

        int trimmedSubArrLen = 0;
        int minCost = INT_MAX;

        for(int i = start_i; i < n; ++i) {
            int num = nums[i];
            freq[num]++;
            trimmedSubArrLen += (freq[num] == 2 ? 2 : 0);
            trimmedSubArrLen += freq[num] > 2;
            int importanceVal = k + trimmedSubArrLen;
            int nextCost = solveWithoutMemo(nums, k, i + 1);
            minCost = min(minCost, importanceVal + nextCost);
        }

        return dp[start_i] = minCost;
    }

    // O(N*N) & O(N+N*1000)
    int solveWithMemo(vector<int>& dp, vector<int>& nums, int k, int start_i) {
        if(start_i == n)
            return 0;

        if(dp[start_i] != -1)
            return dp[start_i];

        vector<int> freq(1000);

        int trimmedSubArrLen = 0;
        int minCost = INT_MAX;

        for(int i = start_i; i < n; ++i) {
            int num = nums[i];
            freq[num]++;
            trimmedSubArrLen += (freq[num] == 2 ? 2 : 0);
            trimmedSubArrLen += freq[num] > 2;
            int importanceVal = k + trimmedSubArrLen;
            int nextCost = solveWithMemo(dp, nums, k, i + 1);
            minCost = min(minCost, importanceVal + nextCost);
        }

        return dp[start_i] = minCost;
    }

public:
    int minCost(vector<int>& nums, int k) {
        n = nums.size();
        vector<int> dp(n, -1);
        return solveWithMemo(dp, nums, k, 0);
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // O(N*N) & O(N+1000)
    int minCost(vector<int>& nums, int k) {
        int n = nums.size();

        vector<int> dp(n + 1, INT_MAX);
        dp[n] = 0; // Initialize the edge case

        for(int start_i = n-1; start_i >= 0; --start_i) {
            vector<int> freq(1000);

            int trimmedSubArrLen = 0;
            int minCost = INT_MAX;

            for(int i = start_i; i < n; ++i) {
                int num = nums[i];
                freq[num]++;
                trimmedSubArrLen += (freq[num] == 2 ? 2 : 0);
                trimmedSubArrLen += freq[num] > 2;
                int importanceVal = k + trimmedSubArrLen;
                int nextCost = dp[i + 1];
                minCost = min(minCost, importanceVal + nextCost);
            }

            dp[start_i] = minCost;
        }

        return dp[0];
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Hash Table | Dynamic Programming | Counting
Link  : https://leetcode.com/problems/minimum-cost-to-split-an-array/description/
