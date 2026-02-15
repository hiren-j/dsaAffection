// Code to find length of the longest strictly increasing or strictly decreasing subarray ~ coded by vHiren

--------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    bool findIncreasing;
    int n;

    // O(2^N) & O(N)
    int solveWithoutMemo(const vector<int>& nums, int i, bool prevPick, int prev_i) {
        if(i == n)
            return 0;

        if(prevPick) {
            int pickInSubarr = ((findIncreasing && nums[prev_i] < nums[i]) || (!findIncreasing && nums[prev_i] > nums[i])) 
                                ? solveWithoutMemo(nums, i + 1, true, i) + 1
                                : 0;
            int stopHere = 0;
            return max(pickInSubarr, stopHere);
        }
        else {
            int startCurr = solveWithoutMemo(nums, i + 1, true, i) + 1;
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
            int pickInSubarr = ((findIncreasing && nums[prev_i] < nums[i]) || (!findIncreasing && nums[prev_i] > nums[i])) 
                                ? solveWithMemo(dp, nums, i + 1, true, i) + 1
                                : 0;
            int stopHere = 0;
            return dp[i][prevPick][prev_i] = max(pickInSubarr, stopHere);
        }
        else {
            int startCurr = solveWithMemo(dp, nums, i + 1, true, i) + 1;
            int startNext = solveWithMemo(dp, nums, i + 1, false, 0);
            return dp[i][prevPick][prev_i] = max(startCurr, startNext);
        }
    }

public:
    int longestMonotonicSubarray(vector<int>& nums) {
        n = nums.size();
        
        vector<vector<vector<int>>> dp1(n, vector<vector<int>>(2, vector<int>(n, -1)));
        vector<vector<vector<int>>> dp2(n, vector<vector<int>>(2, vector<int>(n, -1)));

        findIncreasing = true;  int maxLenStrictlyInc = solveWithMemo(dp1, nums, 0, false, 0);
        findIncreasing = false; int maxLenStrictlyDec = solveWithMemo(dp2, nums, 0, false, 0);

        return max(maxLenStrictlyInc, maxLenStrictlyDec);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    bool findIncreasing;
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
                        int pickInSubarr = ((findIncreasing && nums[prev_i] < nums[i]) || (!findIncreasing && nums[prev_i] > nums[i])) 
                                            ? dp[i + 1][true][i] + 1
                                            : 0;
                        int stopHere = 0;
                        dp[i][prevPick][prev_i] = max(pickInSubarr, stopHere);
                    }
                    else {
                        int startCurr = dp[i + 1][true][i] + 1;
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
                        int pickInSubarr = ((findIncreasing && nums[prev_i] < nums[i]) || (!findIncreasing && nums[prev_i] > nums[i])) 
                                            ? dp[i + 1][true][i] + 1
                                            : 0;
                        int stopHere = 0;
                        dp[i][prevPick][prev_i] = max(pickInSubarr, stopHere);
                    }
                    else {
                        int startCurr = dp[i + 1][true][i] + 1;
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
        vector<vector<int>> curr(2, vector<int>(n, 0)); // ith table

        for(int i = n - 1; i >= 0; --i) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                for(int prev_i = n - 1; prev_i >= 0; --prev_i) {
                    if(prevPick) {
                        int pickInSubarr = ((findIncreasing && nums[prev_i] < nums[i]) || (!findIncreasing && nums[prev_i] > nums[i])) 
                                            ? next[true][i] + 1
                                            : 0;
                        int stopHere = 0;
                        curr[prevPick][prev_i] = max(pickInSubarr, stopHere);
                    }
                    else {
                        int startCurr = next[true][i] + 1;
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
    int longestMonotonicSubarray(vector<int>& nums) {
        n = nums.size();
        findIncreasing = true;  int maxLenStrictlyInc = solveBy2DTable(nums); 
        findIncreasing = false; int maxLenStrictlyDec = solveBy2DTable(nums); 
        return max(maxLenStrictlyInc, maxLenStrictlyDec);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------

class Greedy {
    int n;

    bool isInc(int num1, int num2) {
        return num1 < num2;
    }
    bool isDec(int num1, int num2) {
        return num1 > num2;
    }

    // O(N*N) & O(1)
    int bruteForce(const vector<int>& nums, bool findInc) {
        int maxLen = 0;

        for(int i = 0; i < n; ++i) {
            int subarrLen = 1;
            for(int j = i + 1; (j < n && (findInc && isInc(nums[j - 1], nums[j]) || !findInc && isDec(nums[j - 1], nums[j]))); ++j) {
                subarrLen++;
            }
            maxLen = max(maxLen, subarrLen);
        }

        return maxLen;
    }

    // O(N) & O(1)
    int slidingWindow(const vector<int>& nums, bool findInc) {
        int i = 0, j = 0;
        int maxLen = 0;

        while(j < n) {
            while(i < j && ((findInc && !isInc(nums[j - 1], nums[j])) || (!findInc && !isDec(nums[j - 1], nums[j])))) {
                i++;
            }
            maxLen = max(maxLen, j - i + 1);
            j++;
        }

        return maxLen;
    }

    // O(N) & O(1)
    int traceSpecifiedSubarrs(const vector<int>& nums, bool findInc) {
        int i = 0;
        int subarrLen = 0;
        int maxLen = 0;

        while(i < n) {
            if(i == 0 || (findInc && isInc(nums[i - 1], nums[i]) || !findInc && isDec(nums[i - 1], nums[i]))) {
                subarrLen++;
            }
            else {
                maxLen = max(maxLen, subarrLen);
                subarrLen = 1;
            }
            i++;
        }
        maxLen = max(maxLen, subarrLen); // Don't miss the last subarray ending at index n - 1

        return maxLen;
    }

public:
    int longestMonotonicSubarray(vector<int>& nums) {
        n = nums.size();
        int maxLenStrictlyInc = traceSpecifiedSubarrs(nums, true);
        int maxLenStrictlyDec = traceSpecifiedSubarrs(nums, false);
        return max(maxLenStrictlyInc, maxLenStrictlyDec);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Greedy | Dynamic Programming
Link  : https://leetcode.com/problems/longest-strictly-increasing-or-strictly-decreasing-subarray/description/
