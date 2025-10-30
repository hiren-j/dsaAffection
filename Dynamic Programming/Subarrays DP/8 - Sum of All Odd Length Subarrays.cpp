// Code to find the sum of all odd length subarrays of an array ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int arrSum;
    int n;

    // O(2^N) & O(N)
    int solveWithoutMemo(const vector<int>& nums, int i, bool prevPick, int subarrLen, int subarrSum) {
        if(i == n)
            return (subarrLen % 2 != 0) ? subarrSum : 0; // If odd length subarray then return its sum

        if(prevPick) {
            int pickCurr = solveWithoutMemo(nums, i + 1, true, subarrLen + 1, subarrSum + nums[i]);
            int stopHere = (subarrLen % 2 != 0) ? subarrSum : 0;
            return pickCurr + stopHere;
        }
        else {
            int startHere = solveWithoutMemo(nums, i + 1, true, subarrLen + 1, subarrSum + nums[i]);
            int startNext = solveWithoutMemo(nums, i + 1, false, subarrLen, subarrSum);
            return startHere + startNext;
        }
    }

    // O(2*N*2*N*AS) & O(N*2*N*AS + N)
    int solveWithMemo(vector<vector<vector<vector<int>>>>& dp, const vector<int>& nums, int i, bool prevPick, int subarrLen, int subarrSum) {
        if(i == n)
            return (subarrLen % 2 != 0) ? subarrSum : 0; // If odd length subarray then return its sum

        if(dp[i][prevPick][subarrLen][subarrSum] != -1)
            return dp[i][prevPick][subarrLen][subarrSum];

        if(prevPick) {
            int pickCurr = solveWithMemo(dp, nums, i + 1, true, subarrLen + 1, subarrSum + nums[i]);
            int stopHere = (subarrLen % 2 != 0) ? subarrSum : 0;
            return dp[i][prevPick][subarrLen][subarrSum] = pickCurr + stopHere;
        }
        else {
            int startHere = solveWithMemo(dp, nums, i + 1, true, subarrLen + 1, subarrSum + nums[i]);
            int startNext = solveWithMemo(dp, nums, i + 1, false, subarrLen, subarrSum);
            return dp[i][prevPick][subarrLen][subarrSum] = startHere + startNext;
        }
    }

public:
    // Method to find sum of odd length subarrays, using recursion with memoization - O(N*N*AS) & O(N*N*AS) : Where AS = arrSum
    int sumOddLengthSubarrays(vector<int>& nums) {
        n = nums.size();
        arrSum = accumulate(begin(nums), end(nums), 0);
        vector<vector<vector<vector<int>>>> dp(n, vector<vector<vector<int>>>(2, vector<vector<int>>(n, vector<int>(arrSum + 1, -1))));
        return solveWithMemo(dp, nums, 0, false, 0, 0);
    }
};
// Note: This solution will lead to MLE

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int arrSum;
    int n;

    // O(N*2*N*AS) & O(N*2*N*AS) : Where AS = arrSum
    int solveBy4DTable(const vector<int>& nums) {
        vector<vector<vector<vector<int>>>> dp(n + 1, vector<vector<vector<int>>>(2, vector<vector<int>>(n + 2, vector<int>(arrSum + 1, -1))));

        // Init edge case
        for(int prevPick = 0; prevPick <= 1; ++prevPick)
            for(int subarrLen = 0; subarrLen <= n; ++subarrLen) 
                for(int subarrSum = 0; subarrSum <= arrSum; ++subarrSum)
                    dp[n][prevPick][subarrLen][subarrSum] = (subarrLen % 2 != 0) ? subarrSum : 0;
        
        for(int i = n - 1; i >= 0; --i) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                for(int subarrLen = n; subarrLen >= 0; --subarrLen) {
                    for(int subarrSum = arrSum; subarrSum >= 0; --subarrSum) {
                        if(prevPick) {
                            int newSum   = subarrSum + nums[i];
                            int pickCurr = (newSum <= arrSum) ? dp[i + 1][true][subarrLen + 1][newSum] : 0;
                            int stopHere = (subarrLen % 2 != 0) ? subarrSum : 0;
                            dp[i][prevPick][subarrLen][subarrSum] = pickCurr + stopHere;
                        }
                        else {
                            int newSum    = subarrSum + nums[i];
                            int startHere = (newSum <= arrSum) ? dp[i + 1][true][subarrLen + 1][newSum] : 0;
                            int startNext = dp[i + 1][false][subarrLen][subarrSum];
                            dp[i][prevPick][subarrLen][subarrSum] = startHere + startNext;
                        }
                    }
                }
            }
        }

        return dp[0][false][0][0];
    }

    // O(N*2*N*AS) & O(N*2*N*AS) : Where AS = arrSum
    int solveBy4DEnhanced(const vector<int>& nums) {
        vector<vector<vector<vector<int>>>> dp(n + 1, vector<vector<vector<int>>>(2, vector<vector<int>>(n + 2, vector<int>(arrSum + 1, 0))));

        // Init edge case
        for(int prevPick = 0; prevPick <= 1; ++prevPick)
            for(int subarrLen = 0; subarrLen <= n; ++subarrLen) 
                if(subarrLen % 2 != 0)
                    for(int subarrSum = 0; subarrSum <= arrSum; ++subarrSum)
                        dp[n][prevPick][subarrLen][subarrSum] = subarrSum;
        
        for(int i = n - 1; i >= 0; --i) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                for(int subarrLen = n; subarrLen >= 0; --subarrLen) {
                    for(int subarrSum = arrSum; subarrSum >= 0; --subarrSum) {
                        if(prevPick) {
                            int newSum   = subarrSum + nums[i];
                            int pickCurr = (newSum <= arrSum) ? dp[i + 1][true][subarrLen + 1][newSum] : 0;
                            int stopHere = (subarrLen % 2 != 0) ? subarrSum : 0;
                            dp[i][prevPick][subarrLen][subarrSum] = pickCurr + stopHere;
                        }
                        else {
                            int newSum    = subarrSum + nums[i];
                            int startHere = (newSum <= arrSum) ? dp[i + 1][true][subarrLen + 1][newSum] : 0;
                            int startNext = dp[i + 1][false][subarrLen][subarrSum];
                            dp[i][prevPick][subarrLen][subarrSum] = startHere + startNext;
                        }
                    }
                }
            }
        }

        return dp[0][false][0][0];
    }

    // O(N*2*N*AS) & O(2*2*N*AS) : Where AS = arrSum
    int solveBy3DTable(const vector<int>& nums) {
        vector<vector<vector<int>>> nextRow(2, vector<vector<int>>(n + 2, vector<int>(arrSum + 1, 0)));

        // Init edge case
        for(int prevPick = 0; prevPick <= 1; ++prevPick)
            for(int subarrLen = 0; subarrLen <= n; ++subarrLen) 
                if(subarrLen % 2 != 0)
                    for(int subarrSum = 0; subarrSum <= arrSum; ++subarrSum)
                        nextRow[prevPick][subarrLen][subarrSum] = subarrSum;
        
        for(int i = n - 1; i >= 0; --i) {
            vector<vector<vector<int>>> idealRow(2, vector<vector<int>>(n + 2, vector<int>(arrSum + 1, 0)));

            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                for(int subarrLen = n; subarrLen >= 0; --subarrLen) {
                    for(int subarrSum = arrSum; subarrSum >= 0; --subarrSum) {
                        if(prevPick) {
                            int newSum   = subarrSum + nums[i];
                            int pickCurr = (newSum <= arrSum) ? nextRow[true][subarrLen + 1][newSum] : 0;
                            int stopHere = (subarrLen % 2 != 0) ? subarrSum : 0;
                            idealRow[prevPick][subarrLen][subarrSum] = pickCurr + stopHere;
                        }
                        else {
                            int newSum    = subarrSum + nums[i];
                            int startHere = (newSum <= arrSum) ? nextRow[true][subarrLen + 1][newSum] : 0;
                            int startNext = nextRow[false][subarrLen][subarrSum];
                            idealRow[prevPick][subarrLen][subarrSum] = startHere + startNext;
                        }
                    }
                }
            }

            swap(nextRow, idealRow);
        }

        return nextRow[false][0][0];
    }

public:
    int sumOddLengthSubarrays(vector<int>& nums) {
        arrSum = accumulate(begin(nums), end(nums), 0);
        n = nums.size();
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
