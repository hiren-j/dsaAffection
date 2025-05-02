// Code to count the total steps required to make the given number equal to 0. On each step, you may subtract one of the digits from the number ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int solveWithoutMemo(int n) {
        if(n == 0)
            return 0;
        
        int minSteps = INT_MAX;
        int num = n;

        while(num) {
            int digit = num % 10;
            num /= 10;
            if(digit == 0) continue;
            int nextSteps = solveWithoutMemo(n - digit);
            minSteps = min(minSteps, nextSteps + 1);
        }

        return minSteps;
    }

    int solveWithMemo(vector<int>& dp, int n) {
        if(n == 0)
            return 0;
        
        if(dp[n] != -1)
            return dp[n];

        int minSteps = INT_MAX;
        int num = n;

        while(num) {
            int digit = num % 10;
            num /= 10;
            if(digit == 0) continue;
            int nextSteps = solveWithMemo(dp, n - digit);
            minSteps = min(minSteps, nextSteps + 1);
        }

        return dp[n] = minSteps;
    }

public:
    int minStepsToMakeZero(int n) {
        vector<int> dp(n + 1, -1);
        return solveWithMemo(dp, n);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    int minStepsToMakeZero(int given_n) {
        vector<int> dp(given_n + 1, -1);
        dp[0] = 0;

        for(int n = 1; n <= given_n; ++n) {
            int minSteps = INT_MAX;
            int num = n;

            while(num) {
                int digit = num % 10;
                num /= 10;
                if(digit == 0) continue;
                int nextSteps = dp[n - digit];
                minSteps = min(minSteps, nextSteps + 1);
            }

            dp[n] = minSteps;
        }

        return dp[given_n];
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Math | Dynamic Programming
Link  : https://cses.fi/problemset/task/1637
