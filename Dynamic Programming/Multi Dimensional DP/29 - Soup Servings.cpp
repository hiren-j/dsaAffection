// Code to find the probability that A is used up before B plus half the probability that both soups are used up in the same turn ~ coded by Hiren

------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const vector<vector<int>> operations = {{100, 0}, {75, 25}, {50, 50}, {25, 75}};

    // O(4^(N+N)) & O(N+N)
    double solveWithoutMemo(int A, int B) {
        if(A <= 0 && B <= 0)
            return 0.5; // Half the probability of both the soups are used in same turn

        if(A <= 0)
            return 1.0; // Full probability of soup A is used before soup B

        if(B <= 0)
            return 0.0;

        double prob = 0.0;

        for(const auto& op : operations) {
            int newA = A - op[0];
            int newB = B - op[1];
            prob += solveWithoutMemo(newA, newB);
        }

        return 0.25 * prob;
    }

    // O(4*N*N) & O(N*N + N+N)
    double solveWithMemo(vector<vector<double>>& dp, int A, int B) {
        if(A <= 0 && B <= 0)
            return 0.5; // Half the probability of both the soups are used in same turn

        if(A <= 0)
            return 1.0; // Full probability of soup A is used before soup B

        if(B <= 0)
            return 0.0;

        if(dp[A][B] != -1.0)
            return dp[A][B];

        double prob = 0.0;

        for(const auto& op : operations) {
            int newA = A - op[0];
            int newB = B - op[1];
            prob += solveWithMemo(dp, newA, newB);
        }

        return dp[A][B] = 0.25 * prob;
    }

public:
    // Method to find specified probability, using recursion with memoization - O(N^2) & O(N^2)
    double soupServings(int n) {
        if(n >= 6000)
            return 1.0;
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1.0));
        return solveWithMemo(dp, n, n);
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const vector<vector<int>> operations = {{100, 0}, {75, 25}, {50, 50}, {25, 75}};

public:
    // O(N^2) & O(N^2)
    double soupServings(int n) {
        if(n >= 6000)
            return 1.0;

        vector<vector<double>> dp(n + 1, vector<double>(n + 1, -1.0));

        for(int A = 0; A <= n; ++A) {
            for(int B = 0; B <= n; ++B) {
                double prob = 0.0;

                for(const auto& op : operations) {
                    int newA = A - op[0];
                    int newB = B - op[1];
                    if(newA <= 0 && newB <= 0) prob += 0.5;
                    else if(newA <= 0) prob += 1.0;
                    else if(newB <= 0) prob += 0.0;
                    else prob += dp[newA][newB];
                }

                dp[A][B] = 0.25 * prob;
            }
        }

        return dp[n][n];
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Math | Dynamic Programming | Probability and Statistics | Weekly Contest 78
Link  : https://leetcode.com/problems/soup-servings/description/
