// Code to find length of the longest common subarray ~ coded by vHiren

--------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n, m;

    // O(3^(N+M)) & O(max(N,M))
    int solveWithoutMemo(const vector<int>& nums1, const vector<int>& nums2, int i, int j, bool prevPick) {
        if(i == n || j == m)
            return 0;

        if(prevPick) {
            int pickInSubarr = nums1[i] == nums2[j]
                               ? solveWithoutMemo(nums1, nums2, i + 1, j + 1, true) + 1
                               : 0;
            int stopHere = 0;
            return max(pickInSubarr, stopHere);
        }
        else {
            int startCurr = nums1[i] == nums2[j]
                            ? solveWithoutMemo(nums1, nums2, i + 1, j + 1, true) + 1
                            : 0;
            int startNext1 = solveWithoutMemo(nums1, nums2, i, j + 1, false);
            int startNext2 = solveWithoutMemo(nums1, nums2, i + 1, j, false);
            return max({startCurr, startNext1, startNext2});
        }
    }

    // O(N*M) & O(N*M)
    int solveWithMemo(vector<vector<vector<int>>>& dp, const vector<int>& nums1, const vector<int>& nums2, int i, int j, bool prevPick) {
        if(i == n || j == m)
            return 0;

        if(dp[i][j][prevPick] != -1)
            return dp[i][j][prevPick];

        if(prevPick) {
            int pickInSubarr = nums1[i] == nums2[j]
                               ? solveWithMemo(dp, nums1, nums2, i + 1, j + 1, true) + 1
                               : 0;
            int stopHere = 0;
            return dp[i][j][prevPick] = max(pickInSubarr, stopHere);
        }
        else {
            int startCurr = nums1[i] == nums2[j]
                            ? solveWithMemo(dp, nums1, nums2, i + 1, j + 1, true) + 1
                            : 0;
            int startNext1 = solveWithMemo(dp, nums1, nums2, i, j + 1, false);
            int startNext2 = solveWithMemo(dp, nums1, nums2, i + 1, j, false);
            return dp[i][j][prevPick] = max({startCurr, startNext1, startNext2});
        }
    }

public:
    int longestCommonSubarray(vector<int>& nums1, vector<int>& nums2) {
        n = nums1.size(), m = nums2.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(2, -1)));
        return solveWithMemo(dp, nums1, nums2, 0, 0, false);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n, m;

    // O(N*M) & O(N*M)
    int solveBy3DTable(const vector<int>& nums1, const vector<int>& nums2) {
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(m + 1, vector<int>(2, -1)));

        for(int j = 0; j <= m; ++j)
            for(int prevPick = 0; prevPick < 2; ++prevPick)
                dp[n][j][prevPick] = 0;
        
        for(int i = 0; i <= n; ++i)
            for(int prevPick = 0; prevPick < 2; ++prevPick)
                dp[i][m][prevPick] = 0;

        for(int i = n - 1; i >= 0; --i) {
            for(int j = m - 1; j >= 0; --j) {
                for(int prevPick = 1; prevPick >= 0; --prevPick) {
                    if(prevPick) {
                        int pickInSubarr = (nums1[i] == nums2[j]) ? dp[i + 1][j + 1][true] + 1 : 0;
                        int stopHere = 0;
                        dp[i][j][prevPick] = max(pickInSubarr, stopHere);
                    }
                    else {
                        int startCurr  = (nums1[i] == nums2[j]) ? dp[i + 1][j + 1][true] + 1 : 0;
                        int startNext1 = dp[i][j + 1][false];
                        int startNext2 = dp[i + 1][j][false];
                        dp[i][j][prevPick] = max({startCurr, startNext1, startNext2});
                    }
                }
            }
        }

        return dp[0][0][false];
    }

    // O(N*M) & O(N*M)
    int solveBy3DEnhanced(const vector<int>& nums1, const vector<int>& nums2) {
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(m + 1, vector<int>(2, 0)));

        for(int i = n - 1; i >= 0; --i) {
            for(int j = m - 1; j >= 0; --j) {
                for(int prevPick = 1; prevPick >= 0; --prevPick) {
                    if(prevPick) {
                        int pickInSubarr = (nums1[i] == nums2[j]) ? dp[i + 1][j + 1][true] + 1 : 0;
                        int stopHere = 0;
                        dp[i][j][prevPick] = max(pickInSubarr, stopHere);
                    }
                    else {
                        int startCurr  = (nums1[i] == nums2[j]) ? dp[i + 1][j + 1][true] + 1 : 0;
                        int startNext1 = dp[i][j + 1][false];
                        int startNext2 = dp[i + 1][j][false];
                        dp[i][j][prevPick] = max({startCurr, startNext1, startNext2});
                    }
                }
            }
        }

        return dp[0][0][false];
    }

    // O(N*M) & O(M)
    int solveBy2DTable(const vector<int>& nums1, const vector<int>& nums2) {
        vector<vector<int>> next(m + 1, vector<int>(2, 0)); // i + 1th table

        for(int i = n - 1; i >= 0; --i) {
            vector<vector<int>> curr(m + 1, vector<int>(2, 0)); // ith table

            for(int j = m - 1; j >= 0; --j) {
                for(int prevPick = 1; prevPick >= 0; --prevPick) {
                    if(prevPick) {
                        int pickInSubarr = (nums1[i] == nums2[j]) ? next[j + 1][true] + 1 : 0;
                        int stopHere = 0;
                        curr[j][prevPick] = max(pickInSubarr, stopHere);
                    }
                    else {
                        int startCurr  = (nums1[i] == nums2[j]) ? next[j + 1][true] + 1 : 0;
                        int startNext1 = curr[j + 1][false];
                        int startNext2 = next[j][false];
                        curr[j][prevPick] = max({startCurr, startNext1, startNext2});
                    }
                }
            }

            swap(next, curr);
        }

        return next[0][false];
    }

public:
    int longestCommonSubarray(vector<int>& nums1, vector<int>& nums2) {
        n = nums1.size(), m = nums2.size();
        return solveBy2DTable(nums1, nums2);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------
  
https://leetcode.com/problems/maximum-length-of-repeated-subarray/
https://www.geeksforgeeks.org/problems/longest-common-substring1452/1
