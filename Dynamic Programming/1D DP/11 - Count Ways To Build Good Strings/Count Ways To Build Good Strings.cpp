// Code to find the number of good strings the can be constructed satisfying the mentioned properties ~ coded by Hiren
  
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class TopDown {
    const int MOD = 1e9+7;
    int low, high, zero, one;

    // O(2^strLen) & O(high)
    int solveWithoutMemo(int strLen) {
        if(strLen > high)
            return 0;

        int appendZero = solveWithoutMemo(strLen + zero);
        int appendOne  = solveWithoutMemo(strLen + one);

        return (strLen >= low) + (appendZero + appendOne) % MOD;
    }

    // O(2*high) & O(2*high)
    int solveWithMemo(vector<int>& dp, int strLen) {
        if(strLen > high)
            return 0;

        if(dp[strLen] != -1)
            return dp[strLen];

        int appendZero = solveWithMemo(dp, strLen + zero);
        int appendOne  = solveWithMemo(dp, strLen + one);

        return dp[strLen] = (strLen >= low) + (appendZero + appendOne) % MOD;
    }

public:
    int countGoodStrings(int l, int h, int z, int o) {
        low = l, high = h, zero = z, one = o;
        vector<int> dp(high + 1, -1);
        return solveWithMemo(dp, 0);
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e9+7;

public:
    // O(1*high) & O(1*high)
    int countGoodStrings(int low, int high, int zero, int one) {
        vector<int> dp(high + 1, -1);   
        
        for(int strLen = high; strLen >= 0; --strLen) {
            int nextIndex1 = strLen + zero; 
            int nextIndex2 = strLen + one;
            int appendZero = (nextIndex1 <= high) ? dp[nextIndex1] : 0;
            int appendOne  = (nextIndex2 <= high) ? dp[nextIndex2] : 0;
            dp[strLen] = (strLen >= low) + (appendZero + appendOne) % MOD;
        }

        return dp[0];
    }
    // Note: We can't do space optimization in this, as you could see dp[nextIndex1], dp[nextIndex2], the value of `nextIndex1`, `nextIndex2` could be anything, overall its not constant
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming 
Link  : https://leetcode.com/problems/count-ways-to-build-good-strings/description/?envType=daily-question&envId=2024-12-30 
