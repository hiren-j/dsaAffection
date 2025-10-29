// Code to find the sum of minimum element of all the subarrays of an array ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int MOD = 1e9 + 7;
    int LIMIT;
    int n;

    // O(2^N) & O(N) : Where L = LIMIT
    int solveWithoutMemo(const vector<int>& nums, int i, bool prevPick, int subarrMin) {
        if(i == n)
            return (subarrMin == LIMIT) ? 0 : subarrMin;

        if(prevPick) {
            int pickCurr = solveWithoutMemo(nums, i + 1, true, min(subarrMin, nums[i]));
            int stopHere = (subarrMin == LIMIT) ? 0 : subarrMin;
            dp[i][prevPick][subarrMin] = (pickCurr + stopHere) % MOD;
        }
        else {
            int startHere = solveWithoutMemo(nums, i + 1, true, min(subarrMin, nums[i]));
            int startNext = solveWithoutMemo(nums, i + 1, false, subarrMin);
            dp[i][prevPick][subarrMin] = (startHere + startNext) % MOD;
        }
    }
    // Note: This solution will lead to TLE
    
    // O(2*N*2*L) & O(N*2*L + N) : Where L = LIMIT
    int solveWithMemo(vector<vector<vector<int>>>& dp, const vector<int>& nums, int i, bool prevPick, int subarrMin) {
        if(i == n)
            return (subarrMin == LIMIT) ? 0 : subarrMin;

        if(dp[i][prevPick][subarrMin] != -1)
            return dp[i][prevPick][subarrMin];

        if(prevPick) {
            int pickCurr = solveWithMemo(dp, nums, i + 1, true, min(subarrMin, nums[i]));
            int stopHere = (subarrMin == LIMIT) ? 0 : subarrMin;
            return dp[i][prevPick][subarrMin] = (pickCurr + stopHere) % MOD;
        }
        else {
            int startHere = solveWithMemo(dp, nums, i + 1, true, min(subarrMin, nums[i]));
            int startNext = solveWithMemo(dp, nums, i + 1, false, subarrMin);
            return dp[i][prevPick][subarrMin] = (startHere + startNext) % MOD;
        }
    }
    // Note: This solution will lead to MLE

public:
    // Method to find sum of minimum element of all subarrays, using recursion with memoization - O(N*L) & (N*L) : Where L = LIMIT
    int sumSubarrayMins(vector<int>& nums) {
        LIMIT = *max_element(begin(nums), end(nums)) + 1; 
        n = nums.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(LIMIT + 1, -1)));
        return solveWithMemo(dp, nums, 0, false, LIMIT);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e9 + 7;
    int LIMIT;
    int n;
    
    // O(N*2*L) & O(N*2*L) : Where L = LIMIT
    int solveBy3DTable(const vector<int>& nums) {
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(LIMIT + 1, -1)));

        // Init edge case: if(i == n) then (subarrMin == LIMIT : 0)
        dp[n][0][LIMIT] = 0;
        dp[n][1][LIMIT] = 0;

        // Init edge case: if(i == n) then (subarrMin == LIMIT ? subarrMin)
        for(int prevPick = 0; prevPick <= 1; ++prevPick)
            for(int subarrMin = 0; subarrMin < LIMIT; ++subarrMin) 
                dp[n][prevPick][subarrMin] = subarrMin;

        for(int i = n-1; i >= 0; --i) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                for(int subarrMin = 0; subarrMin <= LIMIT; ++subarrMin) {
                    if(prevPick) {
                        int pickCurr = dp[i + 1][true][min(subarrMin, nums[i])];
                        int stopHere = (subarrMin == LIMIT) ? 0 : subarrMin;
                        dp[i][prevPick][subarrMin] = (pickCurr + stopHere) % MOD;
                    }
                    else {
                        int startHere = dp[i + 1][true]
                        [min(subarrMin, nums[i])];
                        int startNext = dp[i + 1][false][subarrMin];
                        dp[i][prevPick][subarrMin] = (startHere + startNext) % MOD;
                    }   
                }
            }
        }

        return dp[0][false][LIMIT];
    }

    // O(N*2*L) & O(2*2*L) : Where L = LIMIT
    int solveBy2DTable(const vector<int>& nums) {
        vector<vector<int>> nextRow(2, vector<int>(LIMIT + 1, -1));

        // Init edge case: if(i == n) then (subarrMin == LIMIT : 0)
        nextRow[0][LIMIT] = 0;
        nextRow[1][LIMIT] = 0;

        // Init edge case: if(i == n) then (subarrMin == LIMIT ? subarrMin)
        for(int prevPick = 0; prevPick <= 1; ++prevPick)
            for(int subarrMin = 0; subarrMin < LIMIT; ++subarrMin) 
                nextRow[prevPick][subarrMin] = subarrMin;

        for(int i = n-1; i >= 0; --i) {
            vector<vector<int>> idealRow(2, vector<int>(LIMIT + 1, -1));

            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                for(int subarrMin = 0; subarrMin <= LIMIT; ++subarrMin) {
                    if(prevPick) {
                        int pickCurr = nextRow[true][min(subarrMin, nums[i])];
                        int stopHere = (subarrMin == LIMIT) ? 0 : subarrMin;
                        idealRow[prevPick][subarrMin] = (pickCurr + stopHere) % MOD;
                    }
                    else {
                        int startHere = nextRow[true][min(subarrMin, nums[i])];
                        int startNext = nextRow[false][subarrMin];
                        idealRow[prevPick][subarrMin] = (startHere + startNext) % MOD;
                    }   
                }
            }

            swap(nextRow, idealRow);
        }

        return nextRow[false][LIMIT];
    }

public:
    int sumSubarrayMins(vector<int>& nums) {
        LIMIT = *max_element(begin(nums), end(nums)) + 1; 
        n = nums.size();
        return solveBy2DTable(nums);
    }
};
// Note: This solution will lead to TLE

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class MonotonicStack {
    int n;

    void getPrevSmallerFromLeft(vector<int>& nums, vector<int>& result) {
        stack<int> st;

        for(int i = 0; i < n; ++i) {
            while(!st.empty() && nums[st.top()] > nums[i])
                st.pop();
            result[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }
    }

    void getNextSmallerFromRight(vector<int>& nums, vector<int>& result) {
        stack<int> st;

        for(int i = n-1; i >= 0; --i) {
            while(!st.empty() && nums[st.top()] >= nums[i])
                st.pop();
            result[i] = st.empty() ? n : st.top();
            st.push(i);
        }
    }

public:
    // Method to find the sum of minimum element of all the subarrays, using monotonic stack technique - O(N) & O(N)
    int sumSubarrayMins(vector<int>& nums) {
        n = nums.size();

        // Stores the index of the previous smaller and next smaller element of each index value
        vector<int> PSE(n), NSE(n);
        getPrevSmallerFromLeft(nums, PSE);
        getNextSmallerFromRight(nums, NSE);

        int sumMins = 0, MOD = 1e9+7;

        for(int i = 0; i < n; ++i) {
            int numElementsLeft  = abs(i - PSE[i]);
            int numElementsRight = abs(i - NSE[i]);
            long long numSubarrays = numElementsLeft * numElementsRight; // Find the number of subarrays the ith element is participating as the smallest element
            sumMins = (sumMins + numSubarrays * nums[i]) % MOD;
        }

        return sumMins % MOD;
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Stack | Monotonic Stack
Link  : https://leetcode.com/problems/sum-of-subarray-minimums/description/ 
