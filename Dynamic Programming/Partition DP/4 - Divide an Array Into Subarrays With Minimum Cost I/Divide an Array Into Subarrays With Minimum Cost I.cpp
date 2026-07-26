// Code to find the minimum sum of the cost of splitted array. You are given an array of integers nums of length n. The cost of an array is the value of its first element. For example, the cost of [1,2,3] is 1 while the cost of [3,4,1] is 3. You need to divide nums into 3 disjoint contiguous subarrays ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    // O(N^N) & O(K)
    int solveWithoutMemo(const vector<int>& nums, int start, int k) {
        if(start == n)
            return k == 0 ? 0 : INT_MAX;
        
        if(k < 0)
            return INT_MAX;

        int minCost = INT_MAX;

        for(int i = start; i < n; ++i) {
            const int next = solveWithoutMemo(nums, i + 1, k - 1);

            if(next != INT_MAX) {
                minCost = min(minCost, next + nums[start]);
            }
        }

        return minCost;
    }

    // O(N*N*K) & O(K)
    int solveWithMemo(int dp[][4], const vector<int>& nums, int start, int k) {
        if(start == n)
            return k == 0 ? 0 : INT_MAX;
        
        if(k < 0)
            return INT_MAX;

        if(dp[start][k] != -1)
            return dp[start][k];

        int minCost = INT_MAX;

        for(int i = start; i < n; ++i) {
            const int next = solveWithMemo(dp, nums, i + 1, k - 1);

            if(next != INT_MAX) {
                minCost = min(minCost, next + nums[start]);
            }
        }

        return dp[start][k] = minCost;
    }

public:
    int minimumCost(vector<int>& nums) {
        n = nums.size();
        int dp[50][4];
        memset(dp, -1, sizeof(dp));
        return solveWithMemo(dp, nums, 0, 3);   
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // O(N*K*N) & O(N*K)
    int minimumCost(vector<int>& nums) {
        const int n = nums.size();

        int dp[51][4];
        memset(dp, -1, sizeof(dp));

        dp[n][0] = 0;
        dp[n][1] = INT_MAX;
        dp[n][2] = INT_MAX;
        dp[n][3] = INT_MAX;

        for(int start = n - 1; start >= 0; --start) {
            for(int k = 0; k <= 3; ++k) {
                int minCost = INT_MAX;

                for(int i = start; i < n; ++i) {
                    const int next = (k - 1 < 0) ? INT_MAX : dp[i + 1][k - 1];

                    if(next != INT_MAX) {
                        minCost = min(minCost, next + nums[start]);
                    }
                }

                dp[start][k] = minCost;
            }
        }

        return dp[0][3];
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/divide-an-array-into-subarrays-with-minimum-cost-i/description/ 
