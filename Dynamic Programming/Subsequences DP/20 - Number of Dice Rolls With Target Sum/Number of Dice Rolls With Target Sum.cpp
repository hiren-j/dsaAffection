// Code to find the number of possible ways (out of the K^N total ways) to roll the dice, so the sum of the face-up numbers equals the target value ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int MOD = 1e9 + 7;

    // O(K^N) & O(N)
    int solveWithoutMemo(int n, int target, int k) {
        if(n == 0)
            return (target == 0);

        int count = 0;

        for(int face = 1; (face <= k && face <= target); ++face) {
            count = (count + solveWithoutMemo(n - 1, target - face, k)) % MOD;
        }

        return count;
    }

    // O(K*N*T) & O(N*T) : Where T = target
    int solveWithMemo(vector<vector<int>>& dp, int n, int target, int k) {
        if(n == 0)
            return (target == 0);

        if(dp[n][target] != -1)
            return dp[n][target];

        int count = 0;

        for(int face = 1; (face <= k && face <= target); ++face) {
            count = (count + solveWithMemo(dp, n - 1, target - face, k)) % MOD;
        }

        return dp[n][target] = count;
    }

public:
    int numRollsToTarget(int n, int k, int target) {
        vector<vector<int>> dp(n + 1, vector<int>(target + 1, -1));
        return solveWithMemo(dp, n, target, k);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e9 + 7;

    // O(GN*TG*K) & O(GN*TG) : Where GN = given_n, TG = targetGiven 
    int solveBy2DTable(int given_n, int targetGiven, int k) {
        vector<vector<int>> dp(given_n + 1, vector<int>(targetGiven + 1, -1));

        for(int target = 0; target <= targetGiven; ++target)
            dp[0][target] = (target == 0);

        for(int n = 1; n <= given_n; ++n) {
            for(int target = 0; target <= targetGiven; ++target) {
                int count = 0;
                for(int face = 1; (face <= k && face <= target); ++face) {
                    count = (count + dp[n - 1][target - face]) % MOD;
                }
                dp[n][target] = count;
            }
        }

        return dp[given_n][targetGiven];
    }

    // O(GN*TG*K) & O(TG) : Where GN = given_n, TG = targetGiven 
    int solveBy1DTable(int given_n, int targetGiven, int k) {
        vector<int> prevRow(targetGiven + 1, -1), currRow(targetGiven + 1, -1);

        for(int target = 0; target <= targetGiven; ++target)
            prevRow[target] = (target == 0);

        for(int n = 1; n <= given_n; ++n) {
            for(int target = 0; target <= targetGiven; ++target) {
                int count = 0;
                for(int face = 1; (face <= k && face <= target); ++face) {
                    count = (count + prevRow[target - face]) % MOD;
                }
                currRow[target] = count;
            }
            swap(prevRow, currRow);
        }

        return prevRow[targetGiven];
    }

public:
    int numRollsToTarget(int n, int k, int target) {
        return solveBy1DTable(n, target, k);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming
Link  : https://leetcode.com/problems/number-of-dice-rolls-with-target-sum/description/?envType=daily-question&envId=2023-12-26
