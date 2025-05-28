// https://codeforces.com/contest/1703/problem/D
// https://codeforces.com/contest/1703/problem/E
// https://codeforces.com/contest/1790/problem/B
// https://codeforces.com/contest/1846/problem/B

// Code to find the minimum cost of painting all the houses such that no adjacent houses are painted with the same color ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    // O(2^N) & O(N) 
    int solveWithoutMemo(vector<vector<int>>& costs, int house, int skipColor) {
        if(house == n)
            return 0;

        int minCost = INT_MAX;

        for(int color = 0; color < 3; ++color)
            if(color != skipColor)
                minCost = min(minCost, costs[house][color] + solveWithoutMemo(costs, house + 1, color));

        return minCost;
    }

    // O(2*N*4) & O(N*4+N) 
    int solveWithMemo(vector<vector<int>>& dp, vector<vector<int>>& costs, int house, int skipColor) {
        if(house == n)
            return 0;

        if(dp[house][skipColor] != -1)
            return dp[house][skipColor];

        int minCost = INT_MAX;

        for(int color = 0; color < 3; ++color)
            if(color != skipColor)
                minCost = min(minCost, costs[house][color] + solveWithMemo(dp, costs, house + 1, color));

        return minCost;
    }

public:
    // Method to find minimum cost to paint all houses, using recursion with memoization - O(N) & O(N) 
    int minCost(vector<vector<int>>& costs) {
        n = costs.size();
        vector<vector<int>> dp(n, vector<int>(4, -1));
        return solveWithMemo(dp, costs, 0, 3); // I passed 3 as skip-color but you can pass any value just avoid the columns indeces 0, 1, 2
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    // O(N*4*3) & O(N*4) 
    int solveWith2DTable(vector<vector<int>>& costs) {
        vector<vector<int>> dp(n + 1, vector<int>(4, -1));

        for(int skipColor = 0; skipColor <= 3; ++skipColor) // Init edge case
            dp[n][skipColor] = 0;

        for(int house = n-1; house >= 0; --house) {
            for(int skipColor = 0; skipColor <= 3; ++skipColor) {
                int minCost = INT_MAX;

                for(int color = 0; color < 3; ++color) {
                    if(color != skipColor) {
                        minCost = min(minCost, costs[house][color] + dp[house + 1][color]);
                    }
                }

                dp[house][skipColor] = minCost;
            }
        }

        return dp[0][3];
    }

    // O(N*4*3) & O(2*4) 
    int solveWith1DTable(vector<vector<int>>& costs) {
        vector<int> nextRow(4, -1), idealRow(4, -1);

        for(int skipColor = 0; skipColor <= 3; ++skipColor)
            nextRow[skipColor] = 0;

        for(int house = n-1; house >= 0; --house) {
            for(int skipColor = 0; skipColor <= 3; ++skipColor) {
                int minCost = INT_MAX;

                for(int color = 0; color < 3; ++color) {
                    if(color != skipColor) {
                        minCost = min(minCost, costs[house][color] + nextRow[color]);
                    }
                }

                idealRow[skipColor] = minCost;
            }
            nextRow = idealRow;
        }

        return nextRow[3];
    }

public:
    int minCost(vector<vector<int>>& costs) {
        n = costs.size();
        return solveWith1DTable(costs);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Links : https://www.naukri.com/code360/problems/paint-house_1460385
	https://leetcode.com/problems/paint-house/description/
