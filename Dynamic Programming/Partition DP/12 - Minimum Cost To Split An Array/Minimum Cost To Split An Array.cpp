// Code to find the minimum possible cost of a split of the given array. Split the array into some number of non-empty subarrays. The cost of a split is the sum of the importance value of each subarray in the split. The importance value of a subarray is k + trimmed(subarray).length ~ coded by Hiren

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n, k;

    // O(N^N) & O(N^2)
    int solveWithoutMemo(const vector<int>& nums, int start) {
        if(start == n)
            return 0;
        
        int minCost = INT_MAX;
        int trimmedLen = 0;
        
        vector<int> count(n);

        for(int i = start; i < n; ++i) {
            const int num = nums[i];
            count[num]++;
            if(count[num] == 2) trimmedLen += 2;
            if(count[num]  > 2) trimmedLen++;
            const int nextCost = solveWithoutMemo(nums, i + 1);
            const int impVal   = k + trimmedLen;
            const int currCost = impVal + nextCost;
            minCost = min(minCost, currCost);
        }

        return minCost;
    }

    // O(N^2) & O(N^2)
    int solveWithMemo(vector<int>& dp, const vector<int>& nums, int start) {
        if(start == n)
            return 0;

        if(dp[start] != -1)
            return dp[start];
        
        int minCost = INT_MAX;
        int trimmedLen = 0;
        
        vector<int> count(n);

        for(int i = start; i < n; ++i) {
            const int num = nums[i];
            count[num]++;
            if(count[num] == 2) trimmedLen += 2;
            if(count[num]  > 2) trimmedLen++;
            const int nextCost = solveWithMemo(dp, nums, i + 1);
            const int impVal   = k + trimmedLen;
            const int currCost = impVal + nextCost;
            minCost = min(minCost, currCost);
        }

        return dp[start] = minCost;
    }

public:
    int minCost(vector<int>& nums, int K) {
        n = nums.size(), k = K;
        vector<int> dp(n, -1);
        return solveWithMemo(dp, nums, 0);
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // O(N^2) & O(N^2)
    int minCost(vector<int>& nums, int k) {
        const int n = nums.size();

        vector<int> dp(n + 1, -1);
        dp[n] = 0;

        for(int start = n - 1; start >= 0; --start) {
            int minCost = INT_MAX;
            int trimmedLen = 0;

            vector<int> count(n);

            for(int i = start; i < n; ++i) {
                const int num = nums[i];
                count[num]++;
                if(count[num] == 2) trimmedLen += 2;
                if(count[num]  > 2) trimmedLen++;
                const int nextCost = dp[i + 1];
                const int impVal   = k + trimmedLen;
                const int currCost = impVal + nextCost;
                minCost = min(minCost, currCost);
            }

            dp[start] = minCost;
        }

        return dp[0];
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Hash Table | Dynamic Programming | Counting
Link  : https://leetcode.com/problems/minimum-cost-to-split-an-array/description/
