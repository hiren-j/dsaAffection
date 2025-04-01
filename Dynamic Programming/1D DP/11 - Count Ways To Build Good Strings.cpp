// Code to find the number of good strings the can be constructed satisfying the mentioned properties ~ coded by Hiren

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
    DON'T IGNORE MUST READ: Starting from the 11th problem, you’ll notice a shift in the approach. The bottom-up solutions will now be direct conversions from the memoized ones. 
                            This change aims to reduce time and avoid the need for pen and paper, making the process more efficient. As you work through the bottom-up solutions, switch tabs to view the memoized solution side-by-side. 
                            This will help you see how the values passed as parameters in the memoized solution correspond to what we calculate and store in the bottom-up approach. 
                            With practice, you’ll be able to create bottom-up solutions within minutes or even seconds, as I have developed the habit of doing. 
                            This conversion technique will be applied to the remaining problems across all DP patterns.
*/    
  
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class TopDown {
    const int MOD = 1e9+7;

    // O(2^strLen) & O(H)
    int solveWithoutMemo(int low, int high, int zero, int one, int strLen) {
        if(strLen > high)
            return 0;

        int appendZero  = solveWithoutMemo(low, high, zero, one, strLen + zero);
        int appendOne   = solveWithoutMemo(low, high, zero, one, strLen + one);
        int numGoodStrs = ((appendZero + appendOne) % MOD + (strLen >= low && strLen <= high)) % MOD;

        return numGoodStrs;
    }
    
    // O(2*H) & O(2*H)
    int solveWithMemo(vector<int>& dp, int low, int high, int zero, int one, int strLen) {
        if(strLen > high)
            return 0;
        
        if(dp[strLen] != -1)
            return dp[strLen];

        int appendZero  = solveWithMemo(dp, low, high, zero, one, strLen + zero);
        int appendOne   = solveWithMemo(dp, low, high, zero, one, strLen + one);
        int numGoodStrs = ((appendZero + appendOne) % MOD + (strLen >= low && strLen <= high)) % MOD;

        return dp[strLen] = numGoodStrs;
    }

public:
    // Method to find the number of good strings, using recursion with memoization - O(H) & O(H) : Where H = high
    int countGoodStrings(int low, int high, int zero, int one) {
        vector<int> dp(high + 1, -1);
        return solveWithMemo(dp, low, high, zero, one, 0);
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e9+7;

public:
    // Method to find the number of good strings, using 1D tabulation - O(H) & O(H)
    int countGoodStrings(int low, int high, int zero, int one) {
        vector<int> dp(high + 1, 0);

        for(int strLen = high; strLen >= 0; --strLen) {
            int newIndex1 = strLen + zero;
            int newIndex2 = strLen + one;
            int appendZero  = (newIndex1 <= high) ? dp[newIndex1] : 0;
            int appendOne   = (newIndex2 <= high) ? dp[newIndex2] : 0;
            int numGoodStrs = ((appendZero + appendOne) % MOD + (strLen >= low && strLen <= high)) % MOD;
            dp[strLen] = numGoodStrs;
        }

        return dp[0];
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming 
Link  : https://leetcode.com/problems/count-ways-to-build-good-strings/description/?envType=daily-question&envId=2024-12-30 
