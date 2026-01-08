// Code to find the minimum absolute difference, The absolute difference between two numbers a and b is the absolute value of a - b. We could Choose one integer from each row in the matrix such that the absolute difference between target and the path sum of the chosen elements is minimized ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int LIMIT = 4901;
    int target;
    int M, N;

    // O(N^(M*N)) & O(M)
    int solveWithoutMemo(const vector<vector<int>>& grid, int R, int pathSum) {
        if(R == M)
            return abs(target - pathSum);
        
        int minAbsDiff = INT_MAX;

        for(int C = 0; C < N; ++C) {
            int nextSideDiff = solveWithoutMemo(grid, R + 1, pathSum + grid[R][C]);
            minAbsDiff = min(minAbsDiff, nextSideDiff);
        }

        return minAbsDiff;
    }

    // O(N*M*L) & O(M*L + M) : Where L = LIMIT
    int solveWithMemo(vector<vector<int>>& dp, const vector<vector<int>>& grid, int R, int pathSum) {
        if(R == M)
            return abs(target - pathSum);

        if(dp[R][pathSum] != -1)
            return dp[R][pathSum];
        
        int minAbsDiff = INT_MAX;

        for(int C = 0; C < N; ++C) {
            int nextSideDiff = solveWithMemo(dp, grid, R + 1, pathSum + grid[R][C]);
            minAbsDiff = min(minAbsDiff, nextSideDiff);
        }

        return dp[R][pathSum] = minAbsDiff;
    }

public:
    int minimizeTheDifference(vector<vector<int>>& grid, int T) {
        M = grid.size(), N = grid[0].size(), target = T;
        vector<vector<int>> dp(M, vector<int>(LIMIT, -1));
        return solveWithMemo(dp, grid, 0, 0);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int LIMIT = 4901;
    int target;
    int M, N;

    // O(M*L*N) & O(M*L) : Where L = LIMIT
    int solveBy2DTable(const vector<vector<int>>& grid) {
        vector<vector<int>> dp(M + 1, vector<int>(LIMIT, -1));

        for(int pathSum = 0; pathSum < LIMIT; ++pathSum)
            dp[M][pathSum] = abs(target - pathSum);
        
        for(int R = M-1; R >= 0; --R) {
            for(int pathSum = LIMIT-1; pathSum >= 0; --pathSum) {
                int minAbsDiff = INT_MAX;

                for(int C = 0; C < N; ++C) {
                    int nextPathSum  = pathSum + grid[R][C];
                    int nextSideDiff = (nextPathSum >= LIMIT) ? INT_MAX : dp[R + 1][nextPathSum];
                    minAbsDiff = min(minAbsDiff, nextSideDiff);
                }

                dp[R][pathSum] = minAbsDiff;
            }
        }

        return dp[0][0];
    }

    // O(M*L*N) & O(2*L) : Where L = LIMIT
    int solveBy1DTable(const vector<vector<int>>& grid) {
        vector<int> nextRow(LIMIT, -1); // R + 1th row
        vector<int> currRow(LIMIT, -1); // Rth row

        for(int pathSum = 0; pathSum < LIMIT; ++pathSum)
            nextRow[pathSum] = abs(target - pathSum);
        
        for(int R = M-1; R >= 0; --R) {
            for(int pathSum = LIMIT-1; pathSum >= 0; --pathSum) {
                int minAbsDiff = INT_MAX;

                for(int C = 0; C < N; ++C) {
                    int nextPathSum  = pathSum + grid[R][C];
                    int nextSideDiff = (nextPathSum >= LIMIT) ? INT_MAX : nextRow[nextPathSum];
                    minAbsDiff = min(minAbsDiff, nextSideDiff);
                }

                currRow[pathSum] = minAbsDiff;
            }
            swap(nextRow, currRow);
        }

        return nextRow[0];
    }

public:
    int minimizeTheDifference(vector<vector<int>>& grid, int T) {
        M = grid.size(), N = grid[0].size(), target = T;
        return solveBy1DTable(grid);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Matrix
Link  : https://leetcode.com/problems/minimize-the-difference-between-target-and-chosen-elements/description/
