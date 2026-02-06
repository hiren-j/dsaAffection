// Code to find the sum of minimum element of all the subarrays of an array ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int MOD = 1e9 + 7;
    int n;

    int solveWithoutMemo(const vector<int>& nums, int i, bool prevPick, int subarrMin) {
        if(i == n)
            return subarrMin;

        if(prevPick) {
            int pickInSubarr = solveWithoutMemo(nums, i + 1, true, min(subarrMin, nums[i]));
            int stopHere = subarrMin;
            return (pickInSubarr + stopHere) % MOD;   
        }
        else {
            int startCurr = solveWithoutMemo(nums, i + 1, true, nums[i]);
            int startNext = solveWithoutMemo(nums, i + 1, false, 0);
            return (startCurr + startNext) % MOD;
        }
    }
    // Note: This solution will lead to TLE

    int solveWithMemo(vector<vector<vector<int>>>& dp, const vector<int>& nums, int i, bool prevPick, int subarrMin) {
        if(i == n)
            return subarrMin;

        if(dp[i][prevPick][subarrMin] != -1)
            return dp[i][prevPick][subarrMin];

        if(prevPick) {
            int pickInSubarr = solveWithMemo(dp, nums, i + 1, true, min(subarrMin, nums[i]));
            int stopHere = subarrMin;
            return dp[i][prevPick][subarrMin] = (pickInSubarr + stopHere) % MOD;   
        }
        else {
            int startCurr = solveWithMemo(dp, nums, i + 1, true, nums[i]);
            int startNext = solveWithMemo(dp, nums, i + 1, false, 0);
            return dp[i][prevPick][subarrMin] = (startCurr + startNext) % MOD;
        }
    }
    // Note: This solution will lead to MLE

public:
    int sumSubarrayMins(vector<int>& nums) {
        n = nums.size();
        const int maxElement = *max_element(begin(nums), end(nums));
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(maxElement + 1, -1)));
        return solveWithMemo(dp, nums, 0, false, 0);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e9 + 7;
    int maxElement;
    int n;

    // O(N*ME) & O(N*ME) : Where ME = maxElement
    int solveBy3DTable(const vector<int>& nums) {
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(maxElement + 1, -1)));

        for(int prevPick = 0; prevPick < 2; ++prevPick)
            for(int subarrMin = 0; subarrMin <= maxElement; ++subarrMin)
              dp[n][prevPick][subarrMin] = subarrMin;
        
        for(int i = n - 1; i >= 0; --i) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                for(int subarrMin = maxElement; subarrMin >= 0; --subarrMin) {
                    if(prevPick) {
                        int pickInSubarr = dp[i + 1][true][min(subarrMin, nums[i])];
                        int stopHere = subarrMin;
                        dp[i][prevPick][subarrMin] = (pickInSubarr + stopHere) % MOD;   
                    }
                    else {
                        int startCurr = dp[i + 1][true][nums[i]];
                        int startNext = dp[i + 1][false][0];
                        dp[i][prevPick][subarrMin] = (startCurr + startNext) % MOD;
                    }
                }
            } 
        }

        return dp[0][false][0];
    }

    // O(N*ME) & O(2*ME) : Where ME = maxElement
    int solveBy2DTable(const vector<int>& nums) {
        vector<vector<int>> next(2, vector<int>(maxElement + 1, -1)); // i + 1th table
        vector<vector<int>> curr(2, vector<int>(maxElement + 1, -1)); // ith table

        for(int prevPick = 0; prevPick < 2; ++prevPick)
            for(int subarrMin = 0; subarrMin <= maxElement; ++subarrMin)
              next[prevPick][subarrMin] = subarrMin;
        
        for(int i = n - 1; i >= 0; --i) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                for(int subarrMin = maxElement; subarrMin >= 0; --subarrMin) {
                    if(prevPick) {
                        int pickInSubarr = next[true][min(subarrMin, nums[i])];
                        int stopHere = subarrMin;
                        curr[prevPick][subarrMin] = (pickInSubarr + stopHere) % MOD;   
                    }
                    else {
                        int startCurr = next[true][nums[i]];
                        int startNext = next[false][0];
                        curr[prevPick][subarrMin] = (startCurr + startNext) % MOD;
                    }
                }
            } 
            swap(next, curr);
        }

        return next[false][0];
    }

public:
    int sumSubarrayMins(vector<int>& nums) {
        n = nums.size();
        maxElement = *max_element(begin(nums), end(nums));
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

        return sumMins;
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Stack | Monotonic Stack
Link  : https://leetcode.com/problems/sum-of-subarray-minimums/description/ 
