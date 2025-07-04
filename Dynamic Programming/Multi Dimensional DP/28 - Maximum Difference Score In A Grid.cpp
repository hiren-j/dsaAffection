// Code to find the maximum total score you can achieve. You are given an m x n matrix grid consisting of positive integers. You can move from a cell in the matrix to any other cell that is either to the bottom or to the right (not necessarily adjacent). The score of a move from a cell with the value c1 to a cell with the value c2 is c2 - c1. You can start at any cell, and you have to make at least one move ~ coded by Hiren

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int M, N;

    // O(N*M*N + M*M*N) & O(M*N + M+N)
    int getMaxPositiveScore(vector<vector<int>>& dp, vector<vector<int>>& grid, int startR, int startC) {
        if(dp[startR][startC] != -1)
            return dp[startR][startC];

        int moveRight = 0; 
        int moveDown  = 0; 

        // Explore each right cell and get the score you can get from all the possibility and then update the result by the maximum value
        for(int C = startC+1; C < N; ++C) 
            moveRight = max(moveRight, grid[startR][C] - grid[startR][startC] + getMaxPositiveScore(dp, grid, startR, C));
        
        // Explore each bottom cell and get the score you can get from all the possibility and then update the result by the maximum value
        for(int R = startR+1; R < M; ++R) 
            moveDown = max(moveDown, grid[R][startC] - grid[startR][startC] + getMaxPositiveScore(dp, grid, R, startC));

        return dp[startR][startC] = max(moveRight, moveDown);
    }
    // Note: Without memoization the time complexity of this function will be O(N^(M*N) + M^(M*N)) and the auxiliary space will be O(M+N)

    // O(3*M*N) & O(2*M*N)
    int getMaxNegativeScore(vector<vector<int>>& grid) {
        vector<vector<int>> maxElementRight(M, vector<int>(N, INT_MIN));
        vector<vector<int>> maxElementDown(M, vector<int>(N, INT_MIN));

        // Find the maximum element lying at the right side of each cell
        for(int R = 0; R < M; ++R) {
            maxElementRight[R][N-1] = grid[R][N-1];
            for(int C = N-2; C >= 0; --C) {
                maxElementRight[R][C] = max(grid[R][C], maxElementRight[R][C+1]);
            }
        }

        // Find the maximum element lying at the bottom side of each cell
        for(int C = 0; C < N; ++C) {
            maxElementDown[M-1][C] = grid[M-1][C];
            for(int R = M-2; R >= 0; --R) {
                maxElementDown[R][C] = max(grid[R][C], maxElementDown[R+1][C]);
            }
        }
        
        int maxNegScore = INT_MIN;

        // Move to each cell and update the maximum negative score
        for(int R = 0; R < M; ++R) {
            for(int C = 0; C < N; ++C) {
                int scoreRight = (C + 1 < N) ? maxElementRight[R][C + 1] : INT_MIN;
                int scoreDown  = (R + 1 < M) ? maxElementDown[R + 1][C] : INT_MIN;
                if(scoreRight != INT_MIN) maxNegScore = max(maxNegScore, scoreRight - grid[R][C]);
                if(scoreDown  != INT_MIN) maxNegScore = max(maxNegScore, scoreDown - grid[R][C]);
            }
        }
        
        return maxNegScore;
    }

public:
    // Method to find the maximum score you can achieve, using recursion with memoization and 2D tabulation - O(M*N*(N+M)) & O(M*N)
    int maxScore(vector<vector<int>>& grid) {
        M = grid.size(), N = grid[0].size();

        vector<vector<int>> dp(M, vector<int>(N, -1));
        int maxPosScore = 0;

        // Consider each cell as an unique start point and find the maximum positive score you can get from it and then update the result by the maximum value
        for(int R = 0; R < M; ++R)
            for(int C = 0; C < N; ++C)
                maxPosScore = max(maxPosScore, getMaxPositiveScore(dp, grid, R, C));
        
        // If the maximum positive score is 0 then there is a chance that the result could be a maximum negative value hence find the maximum negative score and then return it
        return (maxPosScore == 0) ? getMaxNegativeScore(grid) : maxPosScore;
    }
};
// Note: This solution will lead to time-limit-exceed

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int M, N;

    // O(3*M*N) & O(2*M*N)
    int getMaxNegativeScore(vector<vector<int>>& grid) {
        vector<vector<int>> maxElementRight(M, vector<int>(N, INT_MIN));
        vector<vector<int>> maxElementDown(M, vector<int>(N, INT_MIN));

        // Find the maximum element lying at the right side of each cell
        for(int R = 0; R < M; ++R) {
            maxElementRight[R][N-1] = grid[R][N-1];
            for(int C = N-2; C >= 0; --C) {
                maxElementRight[R][C] = max(grid[R][C], maxElementRight[R][C+1]);
            }
        }

        // Find the maximum element lying at the bottom side of each cell
        for(int C = 0; C < N; ++C) {
            maxElementDown[M-1][C] = grid[M-1][C];
            for(int R = M-2; R >= 0; --R) {
                maxElementDown[R][C] = max(grid[R][C], maxElementDown[R+1][C]);
            }
        }
        
        int maxNegScore = INT_MIN;

        // Move to each cell and update maximum negative score
        for(int R = 0; R < M; ++R) {
            for(int C = 0; C < N; ++C) {
                int scoreRight = (C+1 < N) ? maxElementRight[R][C+1] : INT_MIN;
                int scoreDown  = (R+1 < M) ? maxElementDown[R+1][C] : INT_MIN;
                if(scoreRight != INT_MIN) maxNegScore = max(maxNegScore, scoreRight - grid[R][C]);
                if(scoreDown  != INT_MIN) maxNegScore = max(maxNegScore, scoreDown - grid[R][C]);
            }
        }

        return maxNegScore;
    }

public:
    // Method to find the maximum score you can achieve, using multi 2D tabulation - O(M*N*(N+M)) & O(M*N)
    int maxScore(vector<vector<int>>& grid) {
        M = grid.size(), N = grid[0].size();

        vector<vector<int>> dp(M, vector<int>(N, 0));
        int maxPosScore = 0;

        // Find the maximum positive score you can get
        for(int startR = M-1; startR >= 0; --startR) {
            for(int startC = N-1; startC >= 0; --startC) {
                int moveRight = 0;
                int moveDown  = 0;

                for(int C = startC+1; C < N; ++C) 
                    moveRight = max(moveRight, grid[startR][C] - grid[startR][startC] + dp[startR][C]);        
                for(int R = startR+1; R < M; ++R) 
                    moveDown = max(moveDown, grid[R][startC] - grid[startR][startC] + dp[R][startC]);
                
                dp[startR][startC] = max(moveRight, moveDown);
                maxPosScore = max(maxPosScore, dp[startR][startC]);
            }
        }

        // If the maximum positive score is 0 then there is a chance that the result could be a maximum negative value hence find the maximum negative score and then return it
        return (maxPosScore == 0) ? getMaxNegativeScore(grid) : maxPosScore;
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Matrix
Link  : https://leetcode.com/problems/maximum-difference-score-in-a-grid/description/
