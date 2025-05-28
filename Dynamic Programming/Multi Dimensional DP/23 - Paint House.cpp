// Code to find the minimum cost of painting all the houses such that no adjacent houses are painted with the same color ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    int solveWithoutMemo(vector<vector<int>>& costs, int house, int prevColor) {
        if(house == n)
            return 0;

        int minCost = INT_MAX;

        for(int color = 0; color < 3; ++color)
            if(color != prevColor)
                minCost = min(minCost, costs[house][color] + solveWithoutMemo(costs, house + 1, color));

        return minCost;
    }

    int solveWithMemo(vector<vector<int>>& dp, vector<vector<int>>& costs, int house, int prevColor) {
        if(house == n)
            return 0;

        if(dp[house][prevColor] != -1)
            return dp[house][prevColor];

        int minCost = INT_MAX;

        for(int color = 0; color < 3; ++color)
            if(color != prevColor)
                minCost = min(minCost, costs[house][color] + solveWithMemo(dp, costs, house + 1, color));

        return minCost;
    }

public:
    int minCost(vector<vector<int>>& costs) {
        n = costs.size();
        vector<vector<int>> dp(n, vector<int>(4, -1));
        return solveWithMemo(dp, costs, 0, 3);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    int solveWith2DTable(vector<vector<int>>& costs) {
        vector<vector<int>> dp(n + 1, vector<int>(4, -1));

        for(int prevColor = 0; prevColor <= 3; ++prevColor)
            dp[n][prevColor] = 0;

        for(int house = n-1; house >= 0; --house) {
            for(int prevColor = 0; prevColor <= 3; ++prevColor) {
                int minCost = INT_MAX;

                for(int color = 0; color < 3; ++color) {
                    if(color != prevColor) {
                        minCost = min(minCost, costs[house][color] + dp[house + 1][color]);
                    }
                }

                dp[house][prevColor] = minCost;
            }
        }

        return dp[0][3];
    }

    int solveWith1DTable(vector<vector<int>>& costs) {
        vector<int> nextRow(4, INT_MAX), idealRow(4, INT_MAX);

        for(int prevColor = 0; prevColor <= 3; ++prevColor)
            nextRow[prevColor] = 0;

        for(int house = n-1; house >= 0; --house) {
            for(int prevColor = 0; prevColor <= 3; ++prevColor) {
                int minCost = INT_MAX;

                for(int color = 0; color < 3; ++color) {
                    if(color != prevColor) {
                        minCost = min(minCost, costs[house][color] + nextRow[color]);
                    }
                }

                idealRow[prevColor] = minCost;
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
