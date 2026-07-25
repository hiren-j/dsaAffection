// Code to find the largest number of chunks that we can make to sort the array. You are given an integer array arr of length n that represents a permutation of the integers in the range [0, n - 1]. We split arr into some number of chunks (i.e., partitions), and individually sort each chunk. After concatenating them, the result should equal the sorted array ~ coded by Hiren

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    // O(N^N) & O(N)
    int solveWithoutMemo(const vector<int>& nums, int start, int prevMax) {
        if(start == n)
            return 0;
        
        int minElement = INT_MAX;
        int maxElement = INT_MIN;
        int maxChunks  = INT_MIN;

        for(int i = start; i < n; ++i) {
            minElement = min(minElement, nums[i]);
            maxElement = max(maxElement, nums[i]);

            if(prevMax < minElement) {
                int next  = solveWithoutMemo(nums, i + 1, maxElement);
                maxChunks = max(maxChunks, next + 1);
            }
        }

        return maxChunks;
    }

    // O(N^2) & O(N^2)
    int solveWithMemo(int dp[][11], const vector<int>& nums, int start, int prevMax) {
        if(start == n)
            return 0;

        if(dp[start][prevMax + 1] != -1)
            return dp[start][prevMax + 1];
        
        int minElement = INT_MAX;
        int maxElement = INT_MIN;
        int maxChunks  = INT_MIN;

        for(int i = start; i < n; ++i) {
            minElement = min(minElement, nums[i]);
            maxElement = max(maxElement, nums[i]);

            if(prevMax < minElement) {
                int next  = solveWithMemo(dp, nums, i + 1, maxElement);
                maxChunks = max(maxChunks, next + 1);
            }
        }

        return dp[start][prevMax + 1] = maxChunks;
    }

public:
    int maxChunksToSorted(vector<int>& nums) {
        n = nums.size();
        int dp[10][11];
        memset(dp, -1, sizeof(dp));
        return solveWithMemo(dp, nums, 0, -1);
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // O(N^2) & O(N^2)
    int maxChunksToSorted(vector<int>& nums) {
        const int n = nums.size();

        int dp[11][11];
        memset(dp, 0, sizeof(dp));

        for(int start = n - 1; start >= 0; --start) {
            for(int prevMax = 9; prevMax >= -1; --prevMax) {
                int minElement = INT_MAX;
                int maxElement = INT_MIN;
                int maxChunks  = INT_MIN;

                for(int i = start; i < n; ++i) {
                    minElement = min(minElement, nums[i]);
                    maxElement = max(maxElement, nums[i]);

                    if(prevMax < minElement) {
                        int next  = dp[i + 1][maxElement];
                        maxChunks = max(maxChunks, next + 1);
                    }
                }

                dp[start][prevMax + 1] = maxChunks;
            }
        }

        return dp[0][0];
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Stack | Greedy | Sorting | Monotonic Stack
Link  : https://leetcode.com/problems/max-chunks-to-make-sorted/description/
