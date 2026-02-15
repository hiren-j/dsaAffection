// Code to find the maximum possible sum of a strictly increasing subarray ~ coded by vHiren

---------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    // O(2^N) & O(N)
    int solveWithoutMemo(const vector<int>& nums, int i, bool prevPick, int prev_i) {
        if(i == n)
            return 0;

        if(prevPick) {
            int pickInSubarr = nums[prev_i] < nums[i] 
                                ? solveWithoutMemo(nums, i + 1, true, i) + nums[i] 
                                : 0;
            int stopHere = 0;
            return max(pickInSubarr, stopHere);
        }
        else {
            int startCurr = solveWithoutMemo(nums, i + 1, true, i) + nums[i];
            int startNext = solveWithoutMemo(nums, i + 1, false, 0);
            return max(startCurr, startNext);
        }
    }

    // O(N*N) & O(N*N)
    int solveWithMemo(vector<vector<vector<int>>>& dp, const vector<int>& nums, int i, bool prevPick, int prev_i) {
        if(i == n)
            return 0;

        if(dp[i][prevPick][prev_i] != -1)  
            return dp[i][prevPick][prev_i];

        if(prevPick) {
            int pickInSubarr = nums[prev_i] < nums[i] 
                                ? solveWithMemo(dp, nums, i + 1, true, i) + nums[i] 
                                : 0;
            int stopHere = 0;
            return dp[i][prevPick][prev_i] = max(pickInSubarr, stopHere);
        }
        else {
            int startCurr = solveWithMemo(dp, nums, i + 1, true, i) + nums[i];
            int startNext = solveWithMemo(dp, nums, i + 1, false, 0);
            return dp[i][prevPick][prev_i] = max(startCurr, startNext);
        }
    }

public:
    int maxAscendingSum(vector<int>& nums) {
        n = nums.size(); 
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(n, -1)));  
        return solveWithMemo(dp, nums, 0, false, 0);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    // O(N*N) & O(N*N)
    int solveBy3DTable(const vector<int>& nums) {
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(n, -1)));  

        for(int prevPick = 0; prevPick < 2; ++prevPick)
            for(int prev_i = 0; prev_i < n; ++prev_i)
                dp[n][prevPick][prev_i] = 0;

        for(int i = n - 1; i >= 0; --i) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                for(int prev_i = n - 1; prev_i >= 0; --prev_i) {
                    if(prevPick) {
                        int pickInSubarr = nums[prev_i] < nums[i] 
                                            ? dp[i + 1][true][i] + nums[i] 
                                            : 0;
                        int stopHere = 0;
                        dp[i][prevPick][prev_i] = max(pickInSubarr, stopHere);
                    }
                    else {
                        int startCurr = dp[i + 1][true][i] + nums[i];
                        int startNext = dp[i + 1][false][0];
                        dp[i][prevPick][prev_i] = max(startCurr, startNext);
                    }
                }
            }
        }

        return dp[0][false][0];
    }

    // O(N*N) & O(N*N)
    int solveBy3DEnhanced(const vector<int>& nums) {
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(n, 0)));  

        for(int i = n - 1; i >= 0; --i) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                for(int prev_i = n - 1; prev_i >= 0; --prev_i) {
                    if(prevPick) {
                        int pickInSubarr = nums[prev_i] < nums[i] 
                                            ? dp[i + 1][true][i] + nums[i] 
                                            : 0;
                        int stopHere = 0;
                        dp[i][prevPick][prev_i] = max(pickInSubarr, stopHere);
                    }
                    else {
                        int startCurr = dp[i + 1][true][i] + nums[i];
                        int startNext = dp[i + 1][false][0];
                        dp[i][prevPick][prev_i] = max(startCurr, startNext);
                    }
                }
            }
        }

        return dp[0][false][0];
    }

    // O(N*N) & O(N)
    int solveBy2DTable(const vector<int>& nums) {
        vector<vector<int>> next(2, vector<int>(n, 0)); // i + 1th table

        for(int i = n - 1; i >= 0; --i) {
            vector<vector<int>> curr(2, vector<int>(n, 0)); // ith table

            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                for(int prev_i = n - 1; prev_i >= 0; --prev_i) {
                    if(prevPick) {
                        int pickInSubarr = nums[prev_i] < nums[i] 
                                            ? next[true][i] + nums[i] 
                                            : 0;
                        int stopHere = 0;
                        curr[prevPick][prev_i] = max(pickInSubarr, stopHere);
                    }
                    else {
                        int startCurr = next[true][i] + nums[i];
                        int startNext = next[false][0];
                        curr[prevPick][prev_i] = max(startCurr, startNext);
                    }
                }
            }

            swap(next, curr);
        }

        return next[false][0];
    }

public:
    int maxAscendingSum(vector<int>& nums) {
        n = nums.size(); 
        return solveBy2DTable(nums);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------

class Greedy {
    int n;

    // O(N*N) & O(1)
    int bruteForce(const vector<int>& nums) {
        int maxSum = 0;

        for(int i = 0; i < n; ++i) {
            int subarrSum = nums[i];
            for(int j = i + 1; (j < n && nums[j - 1] < nums[j]); ++j) {
                subarrSum += nums[j];
            }
            maxSum = max(maxSum, subarrSum);
        }

        return maxSum;
    }

    // O(N) & O(1)
    int slidingWindow(const vector<int>& nums) {
        int i = 0, j = 0;
        int subarrSum = 0, maxSum = 0;

        while(j < n) {
            subarrSum += nums[j];
            while(i < j && (j == i || nums[j - 1] >= nums[j])) {
                subarrSum -= nums[i];
                i++;
            }
            maxSum = max(maxSum, subarrSum);
            j++;
        }

        return maxSum;
    }

    // O(N) & O(1)
    int traceStrictlyIncreasingSubarrs(const vector<int>& nums) {
        int subarrSum = 0;
        int maxSum = 0;
        int i = 0;

        while(i < n) {
            if(i == 0 || nums[i - 1] < nums[i]) {
                subarrSum += nums[i];
            }
            else {
                maxSum = max(maxSum, subarrSum);
                subarrSum = nums[i];
            }
            i++;
        }
        maxSum = max(maxSum, subarrSum); // Don't miss the last subarray ending at index n - 1

        return maxSum;
    }

public:
    int maxAscendingSum(vector<int>& nums) {
        n = nums.size(); 
        return traceStrictlyIncreasingSubarrs(nums);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Greedy | Dynamic Programming
Link  : https://leetcode.com/problems/maximum-ascending-subarray-sum/description/
