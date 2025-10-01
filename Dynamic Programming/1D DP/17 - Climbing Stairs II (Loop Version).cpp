class TopDown {
    int n;

    // O(3^N) & O(N)
    int solveWithoutMemo(const vector<int>& costs, int i) {
        if(i == n)
            return 0; // If reached last step, return 0 as indication

        int minCost = INT_MAX;

        for(int jump = 1; (jump <= 3 && i + jump <= n); ++jump) {
            int j = i + jump;
            int jumpCost = costs[j - 1] + pow(j - i, 2);
            int nextCost = solveWithoutMemo(costs, j);
            minCost = min(minCost, jumpCost + nextCost);
        }

        return minCost;
    }

    // O(3*N) & O(2*N)
    int solveWithMemo(vector<int>& dp, const vector<int>& costs, int i) {
        if(i == n)
            return 0;

        if(dp[i] != -1)
            return dp[i];

        int minCost = INT_MAX;

        for(int jump = 1; (jump <= 3 && i + jump <= n); ++jump) {
            int j = i + jump;
            int jumpCost = costs[j - 1] + pow(j - i, 2);
            int nextCost = solveWithMemo(dp, costs, j);
            minCost = min(minCost, jumpCost + nextCost);
        }

        return dp[i] = minCost;
    }

public:
    // O(N) & O(N)
    int climbStairs(int step_n, vector<int>& costs) {
        n = step_n;
        vector<int> dp(n, -1);
        return solveWithMemo(dp, costs, 0);
    }
};

class BottomUp {
public:
    // O(N) & O(N)
    int climbStairs(int n, const vector<int>& costs) {
        vector<int> dp(n + 1, -1);
        dp[n] = 0;

        for(int i = n-1; i >= 0; --i) {
            int minCost = INT_MAX;

            for(int jump = 1; (jump <= 3 && i + jump <= n); ++jump) {
                int j = i + jump;
                int jumpCost = costs[j - 1] + pow(j - i, 2);
                int nextCost = dp[j];
                minCost = min(minCost, jumpCost + nextCost);
            }

            dp[i] = minCost;   
        }

        return dp[0];
    }
};
