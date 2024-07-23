// Code to find the minimum absolute difference, The absolute difference between two numbers a and b is the absolute value of a - b. We could Choose one integer from each row in the matrix such that the absolute difference between target and the sum of the chosen elements is minimized ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------

Note: 1 <= grid[i][j] <= 70
Note: 1 <= N, M <= 70
Note: So, In the worst case the highest value of sum could be 70*70 = 4900. 
      Didn't understand? Imagine the worst case when there will be 70 rows and 70 columns and all the cells contain value 70. 
      So, based on my logic you could see we're looking for the result value by moving from the first row to the last row.
      So, If you add the value 70 of the chosen cells across the path then you'll end up having the sum of 4900 at max or when you end up reaching all the rows.
      So, I measured it through the problem constraints. Hope you've got it!

--------------------------------------------------------------------------------------------------------------------------------------------------------------

// Class to implement the Top-down approach:
class TopDown {
    int N, M;

    // O(M^(N*M)) & O(N)
    int solveWithoutMemo(vector<vector<int>>& grid, int target, int startRow, int sum) {
        // Edge case: If all the rows are exhausted then return the absolute difference of the current path
        if(startRow == N)
            return abs(target - sum);

        int minAbsDiff = INT_MAX;
        
        // Explore all the possible paths of chosing elements from the cell and update the result by the minimum value
        for(int C = 0; C < M; ++C) 
            minAbsDiff = min(minAbsDiff, solveWithoutMemo(grid, target, startRow + 1, sum + grid[startRow][C]));

        return minAbsDiff;
    } 

    // O(M*N*4901) & O(N*4901 + N)
    int solveWithMemo(vector<vector<int>>& memory, vector<vector<int>>& grid, int target, int startRow, int sum) {
        // Edge case: If all the rows are exhausted then return the absolute difference of the current path
        if(startRow == N)
            return abs(target - sum);

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[startRow][sum] != -1)
            return memory[startRow][sum];

        int minAbsDiff = INT_MAX;

        // Explore all the possible paths of chosing elements from the cell and update the result by the minimum value
        for(int C = 0; C < M; ++C) 
            minAbsDiff = min(minAbsDiff, solveWithMemo(memory, grid, target, startRow + 1, sum + grid[startRow][C]));

        // Store the result value to the memoization table and then return it
        return memory[startRow][sum] = minAbsDiff;
    } 

public:
    // Method to find the minimum absolute difference, using recursion with memoization :-
    int minimizeTheDifference(vector<vector<int>>& grid, int target) {
        N = grid.size(), M = grid[0].size();
        vector<vector<int>> memory(N, vector<int>(4901, -1));
        return solveWithMemo(memory, grid, target, 0, 0);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------

// Class to implement the Bottom-up approach:
class BottomUp {
    int N, M;

public:
    // Method to find the minimum absolute difference, using 2D tabulation - O(N*2501*M) & O(N*4901)
    int minimizeTheDifference_V1(vector<vector<int>>& grid, int target) {
        N = grid.size(), M = grid[0].size();

        vector<vector<int>> dp(N + 1, vector<int>(4901, INT_MAX));

        for(int sum = 0; sum <= 4900; ++sum)
            dp[N][sum] = abs(target - sum);

        for(int startRow = N-1; startRow >= 0; --startRow) {
            for(int sum = 2500; sum >= 0; --sum) {
                int minAbsDiff = INT_MAX;
                for(int C = 0; C < M; ++C) {
                    minAbsDiff = min(minAbsDiff, dp[startRow + 1][sum + grid[startRow][C]]);
                }
                dp[startRow][sum] = minAbsDiff;            
            }
        }

        return dp[0][0];
    }

    // Method to find the minimum absolute difference, using 1D tabulation - O(N*2501*M) & O(2*4901)
    int minimizeTheDifference_V2(vector<vector<int>>& grid, int target) {
        N = grid.size(), M = grid[0].size();

        vector<int> nextRow(4901, INT_MAX), currRow(4901, INT_MAX);

        for(int sum = 0; sum <= 4900; ++sum)
            nextRow[sum] = abs(target - sum);

        for(int startRow = N-1; startRow >= 0; --startRow) {
            for(int sum = 2500; sum >= 0; --sum) {
                int minAbsDiff = INT_MAX;
                for(int C = 0; C < M; ++C) {
                    minAbsDiff = min(minAbsDiff, nextRow[sum + grid[startRow][C]]);
                }
                currRow[sum] = minAbsDiff;            
            }
            nextRow = currRow;
        }

        return currRow[0];
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Matrix
Link  : https://leetcode.com/problems/minimize-the-difference-between-target-and-chosen-elements/description/
