class Solution {
    const vector<vector<int>> operations = {{100, 0}, {75, 25}, {50, 50}, {25, 75}};

    // O(N^2) & O(N^2)
    double solveWithMemo(vector<vector<double>>& dp, int A, int B) {
        if(A <= 0 && B <= 0)
            return 0.5;

        if(A <= 0)
            return 1.0;

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

    // O(N^2) & O(N^2)
    double solveWith2DTable(int n) {
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

public:
    double soupServings(int n) {
        if(n >= 6000)
            return 1.0;
        return solveWith2DTable(n);
    }
};
