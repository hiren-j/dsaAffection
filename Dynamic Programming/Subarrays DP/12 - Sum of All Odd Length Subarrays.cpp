// Code to find the sum of all odd length subarrays of an array ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int arrSum;
    int n;

    // O(2^N) & O(N)
    int solveWithoutMemo(const vector<int>& nums, int i, bool prevPick, int subarrSum, int subarrLen) {
        if(i == n)
            return (prevPick == true && subarrLen % 2 != 0) ? subarrSum : 0;

        if(prevPick) {
            int pickInSubarr = solveWithoutMemo(nums, i + 1, true, subarrSum + nums[i], subarrLen + 1);
            int stopHere = (subarrLen % 2 != 0) ? subarrSum : 0;
            return (pickInSubarr + stopHere);   
        }
        else {
            int startCurr = solveWithoutMemo(nums, i + 1, true, nums[i], 1);
            int startNext = solveWithoutMemo(nums, i + 1, false, 0, 0);
            return (startCurr + startNext);
        }
    }

    // O(N*AS*N) & O(N*AS*N) : Where AS = arrSum
    int solveWithMemo(vector<vector<vector<vector<int>>>>& dp, const vector<int>& nums, int i, bool prevPick, int subarrSum, int subarrLen) {
        if(i == n)
            return (prevPick == true && subarrLen % 2 != 0) ? subarrSum : 0;

        if(dp[i][prevPick][subarrSum][subarrLen] != -1)
            return dp[i][prevPick][subarrSum][subarrLen];

        if(prevPick) {
            int pickInSubarr = solveWithMemo(dp, nums, i + 1, true, subarrSum + nums[i], subarrLen + 1);
            int stopHere = (subarrLen % 2 != 0) ? subarrSum : 0;
            return dp[i][prevPick][subarrSum][subarrLen] = (pickInSubarr + stopHere);   
        }
        else {
            int startCurr = solveWithMemo(dp, nums, i + 1, true, nums[i], 1);
            int startNext = solveWithMemo(dp, nums, i + 1, false, 0, 0);
            return dp[i][prevPick][subarrSum][subarrLen] = (startCurr + startNext);
        }
    }
    // Note: This solution will lead to MLE

public:
    int sumOddLengthSubarrays(vector<int>& nums) {
        n = nums.size();
        arrSum = accumulate(begin(nums), end(nums), 0);

        vector<vector<vector<vector<int>>>> dp(n, 
                vector<vector<vector<int>>>(2, 
                        vector<vector<int>>(arrSum + 1, 
                                vector<int>(n + 1, -1))));

        return solveWithMemo(dp, nums, 0, false, 0, 0);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int arrSum;
    int n;

    // O(N*AS*N) & O(N*AS*N) : Where AS = arrSum
    int solveBy4DTable(const vector<int>& nums) {
        vector<vector<vector<vector<int>>>> dp(n + 1, 
                vector<vector<vector<int>>>(2, 
                        vector<vector<int>>(arrSum + 1, 
                                vector<int>(n + 1, -1))));

        for(int prevPick = 0; prevPick < 2; ++prevPick)
            for(int subarrSum = 0; subarrSum <= arrSum; ++subarrSum)
                for(int subarrLen = 0; subarrLen <= n; ++subarrLen)
                    dp[n][prevPick][subarrSum][subarrLen] = (prevPick == true && subarrLen % 2 != 0) ? subarrSum : 0;

        for(int i = n - 1; i >= 0; --i) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                for(int subarrSum = arrSum; subarrSum >= 0; --subarrSum) {
                    for(int subarrLen = n; subarrLen >= 0; --subarrLen) {
                        if(prevPick) {
                            int newSum = subarrSum + nums[i];
                            int newLen = subarrLen + 1;
                            int pickInSubarr = (newSum <= arrSum && newLen <= n) ? dp[i + 1][true][newSum][newLen] : 0;
                            int stopHere = (prevPick == true && subarrLen % 2 != 0) ? subarrSum : 0;
                            dp[i][prevPick][subarrSum][subarrLen] = (pickInSubarr + stopHere);   
                        }
                        else {
                            int startCurr = dp[i + 1][true][nums[i]][1];
                            int startNext = dp[i + 1][false][0][0];
                            dp[i][prevPick][subarrSum][subarrLen] = (startCurr + startNext);
                        }
                    }
                }
            }
        }

        return dp[0][false][0][0];
    }

    // O(N*AS*N) & O(AS*N) : Where AS = arrSum
    int solveBy3DTable(const vector<int>& nums) {
        // i + 1th table
        vector<vector<vector<int>>> next(2, 
                vector<vector<int>>(arrSum + 1, 
                        vector<int>(n + 1, -1)));
        // ith table
        vector<vector<vector<int>>> curr(2, 
                vector<vector<int>>(arrSum + 1, 
                        vector<int>(n + 1, -1)));
                    
        for(int prevPick = 0; prevPick < 2; ++prevPick)
            for(int subarrSum = 0; subarrSum <= arrSum; ++subarrSum)
                for(int subarrLen = 0; subarrLen <= n; ++subarrLen)
                    next[prevPick][subarrSum][subarrLen] = (prevPick == true && subarrLen % 2 != 0) ? subarrSum : 0;

        for(int i = n - 1; i >= 0; --i) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                for(int subarrSum = arrSum; subarrSum >= 0; --subarrSum) {
                    for(int subarrLen = n; subarrLen >= 0; --subarrLen) {
                        if(prevPick) {
                            int newSum = subarrSum + nums[i];
                            int newLen = subarrLen + 1;
                            int pickInSubarr = (newSum <= arrSum && newLen <= n) ? next[true][newSum][newLen] : 0;
                            int stopHere = (prevPick == true && subarrLen % 2 != 0) ? subarrSum : 0;
                            curr[prevPick][subarrSum][subarrLen] = (pickInSubarr + stopHere);   
                        }
                        else {
                            int startCurr = next[true][nums[i]][1];
                            int startNext = next[false][0][0];
                            curr[prevPick][subarrSum][subarrLen] = (startCurr + startNext);
                        }
                    }
                }
            }
            swap(next, curr);
        }

        return next[false][0][0];
    }

public:
    int sumOddLengthSubarrays(vector<int>& nums) {
        n = nums.size();
        arrSum = accumulate(begin(nums), end(nums), 0);
        return solveBy3DTable(nums);
    }
};
// Note: This solution will lead to MLE

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BruteForce {
public:
    // O(N*N) & O(1)
    int sumOddLengthSubarrays(vector<int>& nums) {
        int n = nums.size();
        int subarraySum, subarrayLen, result = 0;

        for(int i = 0; i < n; ++i) {
            subarraySum = 0;
            subarrayLen = 0;
            for(int j = i; j < n; ++j) {
                subarraySum += nums[j];
                subarrayLen++;
                if(subarrayLen % 2 != 0) result += subarraySum;
            }
        }

        return result;   
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Math | Prefix Sum
Link  : https://leetcode.com/problems/sum-of-all-odd-length-subarrays/
