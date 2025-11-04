// Code to find minimum total cost to reach step n ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    // O(3^N) & O(N)
    int solveWithoutMemo(const vector<int>& costs, int i) {
        if(i == n)
            return 0; // If reached last step, return 0 as indication

        int jump1Step = INT_MAX;
        int jump2Step = INT_MAX;
        int jump3Step = INT_MAX;

        int j = i + 1;
        if(j <= n) {
            int currCost = costs[j - 1] + pow(j - i, 2);
            int nextCost = solveWithoutMemo(costs, j);
            jump1Step = currCost + nextCost;
        }

        j = i + 2;
        if(j <= n) {
            int currCost = costs[j - 1] + pow(j - i, 2);
            int nextCost = solveWithoutMemo(costs, j);
            jump2Step = currCost + nextCost;
        }

        j = i + 3;
        if(j <= n) {
            int currCost = costs[j - 1] + pow(j - i, 2);
            int nextCost = solveWithoutMemo(costs, j);
            jump3Step = currCost + nextCost;
        }

        return min({jump1Step, jump2Step, jump3Step});
    }
    
    // O(3*N) & O(2*N)
    int solveWithMemo(vector<int>& dp, const vector<int>& costs, int i) {
        if(i == n)
            return 0; 

        if(dp[i] != -1)
            return dp[i];

        int jump1Step = INT_MAX;
        int jump2Step = INT_MAX;
        int jump3Step = INT_MAX;

        int j = i + 1;
        if(j <= n) {
            int currCost = costs[j - 1] + pow(j - i, 2);
            int nextCost = solveWithMemo(dp, costs, j);
            jump1Step = currCost + nextCost;
        }

        j = i + 2;
        if(j <= n) {
            int currCost = costs[j - 1] + pow(j - i, 2);
            int nextCost = solveWithMemo(dp, costs, j);
            jump2Step = currCost + nextCost;
        }

        j = i + 3;
        if(j <= n) {
            int currCost = costs[j - 1] + pow(j - i, 2);
            int nextCost = solveWithMemo(dp, costs, j);
            jump3Step = currCost + nextCost;
        }

        return dp[i] = min({jump1Step, jump2Step, jump3Step});
    }

public:
    // Method to find minimum cost to reach step n, using recursion with memoization - O(N) & O(N)
    int climbStairsII(int step_n, vector<int>& costs) {
        n = step_n;
        vector<int> dp(n, -1);
        return solveWithMemo(dp, costs, 0);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    // O(N*3) & O(N)
    int solveWith1DTable(const vector<int>& costs) {
        vector<int> dp(n + 1, -1);
        dp[n] = 0;

        for(int i = n-1; i >= 0; --i) {
            int jump1Step = INT_MAX;
            int jump2Step = INT_MAX;
            int jump3Step = INT_MAX;

            int j = i + 1;
            if(j <= n) {
                int currCost = costs[j - 1] + pow(j - i, 2);
                int nextCost = dp[j];
                jump1Step = currCost + nextCost;
            }

            j = i + 2;
            if(j <= n) {
                int currCost = costs[j - 1] + pow(j - i, 2);
                int nextCost = dp[j];
                jump2Step = currCost + nextCost;
            }

            j = i + 3;
            if(j <= n) {
                int currCost = costs[j - 1] + pow(j - i, 2);
                int nextCost = dp[j];
                jump3Step = currCost + nextCost;
            }

            dp[i] = min({jump1Step, jump2Step, jump3Step});
        }

        return dp[0];
    }

    // O(N*3) & O(1)
    int solveWithoutTable(const vector<int>& costs) {
        int dp_i = -1;  // dp[i]
        int dp_i_1 = 0; // dp[i + 1] 
        int dp_i_2 = 0; // dp[i + 2]
        int dp_i_3 = 0; // dp[i + 3]

        for(int i = n-1; i >= 0; --i) {
            int jump1Step = INT_MAX;
            int jump2Step = INT_MAX;
            int jump3Step = INT_MAX;

            int j = i + 1;
            if(j <= n) {
                int currCost = costs[j - 1] + pow(j - i, 2);
                int nextCost = dp_i_1;
                jump1Step = currCost + nextCost;
            }

            j = i + 2;
            if(j <= n) {
                int currCost = costs[j - 1] + pow(j - i, 2);
                int nextCost = dp_i_2;
                jump2Step = currCost + nextCost;
            }

            j = i + 3;
            if(j <= n) {
                int currCost = costs[j - 1] + pow(j - i, 2);
                int nextCost = dp_i_3;
                jump3Step = currCost + nextCost;
            }

            dp_i = min({jump1Step, jump2Step, jump3Step});

            dp_i_3 = dp_i_2;
            dp_i_2 = dp_i_1;
            dp_i_1 = dp_i;
        }

        return dp_i;
    }

public:
    int climbStairsII(int step_n, vector<int>& costs) {
        n = step_n;
        return solveWithoutTable(costs);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Biweekly Contest 166
Link  : https://leetcode.com/problems/climbing-stairs-ii/description/
