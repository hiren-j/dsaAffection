// Code to find the minimum absolute difference, The absolute difference between two numbers a and b is the absolute value of a - b. We could Choose one integer from each row in the matrix such that the absolute difference between target and the pathSum of the chosen elements is minimized ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*

NOTE: 1 <= grid[i][j] <= 70
NOTE: 1 <= N, M <= 70
NOTE: So, In the worst case the highest value of pathSum could be 70*70 = 4900. 
      Didn't understand? Imagine the worst case when there will be 70 rows and 70 columns and all the cells contains value 70. 
      So, based on my logic you could see we're looking for the result value by moving from the first row to the last row.
      So, If you add the value 70 of the chosen cells across the path then you'll end up having the pathSum of 4900 at max or when you end up reaching all the rows.
      So, I measured it through the problem constraints. Hope you've got it!
      
*/
      
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
      
class TopDown {
    const int sumLimit = 4901; 
    int M, N;

    int solveWithoutMemo(vector<vector<int>>& grid, int target, int R, int pathSum) {
        if(R == M)
            return abs(target - pathSum);

        int minAbsDiff = INT_MAX;

        for(int C = 0; C < N; ++C)
            minAbsDiff = min(minAbsDiff, solveWithoutMemo(grid, target, R + 1, pathSum + grid[R][C]));

        return minAbsDiff;
    }

    int solveWithMemo(vector<vector<int>>& dp, vector<vector<int>>& grid, int target, int R, int pathSum) {
        if(R == M)
            return abs(target - pathSum);

        if(dp[R][pathSum] != -1)
            return dp[R][pathSum];

        int minAbsDiff = INT_MAX;

        for(int C = 0; C < N; ++C)
            minAbsDiff = min(minAbsDiff, solveWithMemo(dp, grid, target, R + 1, pathSum + grid[R][C]));

        return dp[R][pathSum] = minAbsDiff;
    }

public:
    int minimizeTheDifference(vector<vector<int>>& grid, int target) {
        M = grid.size(), N = grid[0].size();
        vector<vector<int>> dp(M, vector<int>(sumLimit, -1));
        return solveWithMemo(dp, grid, target, 0, 0);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int sumLimit = 4901; 
    int M, N;

    int solveWith2DTable(vector<vector<int>>& grid, int target) {
        vector<vector<int>> dp(M + 1, vector<int>(sumLimit, -1));

        for(int pathSum = 0; pathSum < sumLimit; ++pathSum) 
            dp[M][pathSum] = abs(target - pathSum);

        for(int R = M-1; R >= 0; --R) {
            for(int pathSum = sumLimit-1; pathSum >= 0; --pathSum) {
                int minAbsDiff = INT_MAX;

                for(int C = 0; C < N; ++C) {
                    int newCol = pathSum + grid[R][C];
                    int newSum = (newCol < sumLimit) ? dp[R + 1][newCol] : INT_MAX;
                    minAbsDiff = min(minAbsDiff, newSum);
                }

                dp[R][pathSum] = minAbsDiff;
            }
        }

        return dp[0][0];
    }

    int solveWith1DTable(vector<vector<int>>& grid, int target) {
        vector<int> nextRow(sumLimit, -1), idealRow(sumLimit, -1);

        for(int pathSum = 0; pathSum < sumLimit; ++pathSum) 
            nextRow[pathSum] = abs(target - pathSum);

        for(int R = M-1; R >= 0; --R) {
            for(int pathSum = sumLimit-1; pathSum >= 0; --pathSum) {
                int minAbsDiff = INT_MAX;

                for(int C = 0; C < N; ++C) {
                    int newCol = pathSum + grid[R][C];
                    int newSum = (newCol < sumLimit) ? nextRow[newCol] : INT_MAX;
                    minAbsDiff = min(minAbsDiff, newSum);
                }

                idealRow[pathSum] = minAbsDiff;
            }
            nextRow = idealRow;
        }

        return nextRow[0];
    }

public:
    int minimizeTheDifference(vector<vector<int>>& grid, int target) {
        M = grid.size(), N = grid[0].size();
        return solveWith1DTable(grid, target);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Matrix
Link  : https://leetcode.com/problems/minimize-the-difference-between-target-and-chosen-elements/description/
