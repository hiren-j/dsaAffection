class Solution {
    int n;

    bool isInc(int num1, int num2) {
        return num1 < num2;
    }
    bool isDec(int num1, int num2) {
        return num1 > num2;
    }

    int solveWithoutMemo(const vector<int>& nums, int i, bool prevPick, int prev_i, bool findInc) {
        if(i == n)
            return 0;

        if(prevPick) {
            int stopHere = 0;
            int pickCurr = (findInc && isInc(nums[prev_i], nums[i]) || !findInc && isDec(nums[prev_i], nums[i]))
                            ? solveWithoutMemo(nums, i + 1, true, i, findInc)
                            : INT_MIN;
            if(pickCurr != INT_MIN) pickCurr++;
            return max(stopHere, pickCurr);
        }
        else {
            int startNext = solveWithoutMemo(nums, i + 1, false, prev_i, findInc); 
            int startHere = 1 + solveWithoutMemo(nums, i + 1, true, i, findInc);
            return max(startNext, startHere);
        }
    }

    int solveWithMemo(vector<vector<vector<int>>>& dp, const vector<int>& nums, int i, bool prevPick, int prev_i, bool findInc) {
        if(i == n)
            return 0;

        if(dp[i][prevPick][prev_i] != -1)
            return dp[i][prevPick][prev_i];

        if(prevPick) {
            int stopHere = 0;
            int pickCurr = (findInc && isInc(nums[prev_i], nums[i]) || !findInc && isDec(nums[prev_i], nums[i]))
                            ? solveWithMemo(dp, nums, i + 1, true, i, findInc)
                            : INT_MIN;
            if(pickCurr != INT_MIN) pickCurr++;
            return dp[i][prevPick][prev_i] = max(stopHere, pickCurr);
        }
        else {
            int startNext = solveWithMemo(dp, nums, i + 1, false, prev_i, findInc); 
            int startHere = 1 + solveWithMemo(dp, nums, i + 1, true, i, findInc);
            return dp[i][prevPick][prev_i] = max(startNext, startHere);
        }
    }

    int solveBy3DTable(const vector<int>& nums, bool findInc) {
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(n + 1, -1)));

        for(int prevPick = 0; prevPick <= 1; ++prevPick)
            for(int prev_i = 0; prev_i <= n; ++prev_i)
                dp[n][prevPick][prev_i] = 0;
        
        for(int i = n - 1; i >= 0; --i) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                for(int prev_i = 0; prev_i <= n; ++prev_i) {
                    if(prevPick) {
                        int stopHere = 0;
                        int pickCurr = INT_MIN;
                        if(prev_i < n) {
                            pickCurr = (findInc && isInc(nums[prev_i], nums[i]) || !findInc && isDec(nums[prev_i], nums[i]))
                                        ? dp[i + 1][true][i]
                                        : INT_MIN;
                        }
                        if(pickCurr != INT_MIN) pickCurr++;
                        dp[i][prevPick][prev_i] = max(stopHere, pickCurr);
                    }
                    else {
                        int startNext = dp[i + 1][false][prev_i]; 
                        int startHere = 1 + dp[i + 1][true][i];
                        dp[i][prevPick][prev_i] = max(startNext, startHere);
                    }   
                }
            }
        }

        return dp[0][false][n];
    }

    int solveBy3DEnhanced(const vector<int>& nums, bool findInc) {
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(n, 0)));
        
        for(int i = n - 1; i >= 0; --i) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                for(int prev_i = 0; prev_i < n; ++prev_i) {
                    if(prevPick) {
                        int stopHere = 0;
                        int pickCurr = (findInc && isInc(nums[prev_i], nums[i]) || !findInc && isDec(nums[prev_i], nums[i]))
                                    ? dp[i + 1][true][i]
                                    : INT_MIN;
                        if(pickCurr != INT_MIN) pickCurr++;
                        dp[i][prevPick][prev_i] = max(stopHere, pickCurr);
                    }
                    else {
                        int startNext = dp[i + 1][false][prev_i]; 
                        int startHere = 1 + dp[i + 1][true][i];
                        dp[i][prevPick][prev_i] = max(startNext, startHere);
                    }   
                }
            }
        }

        return dp[0][false][n - 1];
    }

    int solveBy2DTable(const vector<int>& nums, bool findInc) {
        vector<vector<int>> nextRow(2, vector<int>(n, 0));
        
        for(int i = n - 1; i >= 0; --i) {
            vector<vector<int>> idealRow(2, vector<int>(n, 0));

            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                for(int prev_i = 0; prev_i < n; ++prev_i) {
                    if(prevPick) {
                        int stopHere = 0;
                        int pickCurr = (findInc && isInc(nums[prev_i], nums[i]) || !findInc && isDec(nums[prev_i], nums[i]))
                                    ? nextRow[true][i]
                                    : INT_MIN;
                        if(pickCurr != INT_MIN) pickCurr++;
                        idealRow[prevPick][prev_i] = max(stopHere, pickCurr);
                    }
                    else {
                        int startNext = nextRow[false][prev_i]; 
                        int startHere = 1 + nextRow[true][i];
                        idealRow[prevPick][prev_i] = max(startNext, startHere);
                    }   
                }
            }

            swap(nextRow, idealRow);
        }

        return nextRow[false][n - 1];
    }

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
        // vector<vector<vector<int>>> dp1(n, vector<vector<int>>(2, vector<int>(n + 1, -1)));
        // vector<vector<vector<int>>> dp2(n, vector<vector<int>>(2, vector<int>(n + 1, -1)));
        // int maxLenStrictlyInc = solveWithMemo(dp1, nums, 0, false, n, true);
        // int maxLenStrictlyDec = solveWithMemo(dp2, nums, 0, false, n, false);
        int maxLenStrictlyInc = traceSpecifiedSubarrs(nums, true);
        int maxLenStrictlyDec = traceSpecifiedSubarrs(nums, false);
        return max(maxLenStrictlyInc, maxLenStrictlyDec);
    }
};
