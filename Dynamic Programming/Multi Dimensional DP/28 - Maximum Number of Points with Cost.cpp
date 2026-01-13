// Code to find the maximum number of points you can achieve. To gain points, you must pick one cell in each row. Picking the cell at coordinates (r, c) will add points[r][c] to your score. However, you will lose points if you pick a cell too far from the cell that you picked in the previous row. For every two adjacent rows r and r + 1 (where 0 <= r < m - 1), picking cells at coordinates (r, c1) and (r + 1, c2) will subtract abs(c1 - c2) from your score ~ coded by vHiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Solution {
    using LL = long long;
    int M, N;

    // O(N^(M*N)) & O(M)
    LL solveWithoutMemo(const vector<vector<int>>& grid, int R, int C1) {
        if(R == M)
            return 0;

        LL maxPathSum = 0;

        for(int C2 = 0; C2 < N; ++C2) {
            LL nextSideSum = solveWithoutMemo(grid, R+1, C2);
            LL moveCost    = (C1 == -1) ? 0 : abs(C1 - C2);
            LL currPathSum = grid[R][C2] + nextSideSum - moveCost;
            maxPathSum = max(maxPathSum, currPathSum);
        } 

        return maxPathSum;
    }

    // O(N*M*N) & O(M*N + M)
    LL solveWithMemo(vector<vector<LL>>& dp, const vector<vector<int>>& grid, int R, int C1) {
        if(R == M)
            return 0;

        if(dp[R][C1] != -1) 
            return dp[R][C1];

        LL maxPathSum = 0;

        for(int C2 = 0; C2 < N; ++C2) {
            LL nextSideSum = solveWithMemo(dp, grid, R+1, C2);
            LL moveCost    = (C1 == N) ? 0 : abs(C1 - C2);
            LL currPathSum = grid[R][C2] + nextSideSum - moveCost;
            maxPathSum = max(maxPathSum, currPathSum);
        } 

        return dp[R][C1] = maxPathSum;
    }
 
public:
    LL maxPoints(vector<vector<int>>& grid) {
        M = grid.size(), N = grid[0].size(); 
        vector<vector<LL>> dp(M, vector<LL>(N+1, -1));
        return solveWithMemo(dp, grid, 0, N);
    }
};
// Note: This solution will lead to TLE

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    using LL = long long;
    int M, N;

    // O(M*N*N) & O(M*N)
    LL solveBy2DTable(const vector<vector<int>>& grid) {
        vector<vector<LL>> dp(M+1, vector<LL>(N+1, -1));

        for(int C1 = 0; C1 <= N; ++C1)
            dp[M][C1] = 0;
        
        for(int R = M-1; R >= 0; --R) {
            for(int C1 = 0; C1 <= N; ++C1) {
                LL maxPathSum = 0;

                for(int C2 = 0; C2 < N; ++C2) {
                    LL nextSideSum = dp[R+1][C2];
                    LL moveCost    = (C1 == N) ? 0 : abs(C1 - C2);
                    LL currPathSum = grid[R][C2] + nextSideSum - moveCost;
                    maxPathSum = max(maxPathSum, currPathSum);
                } 

                dp[R][C1] = maxPathSum;
            }
        }

        return dp[0][N];
    }
    // Note: This solution will lead to TLE

    // O(M*N*N) & O(M*N)
    LL solveBy2DEnhanced(const vector<vector<int>>& grid) {
        vector<vector<LL>> dp(M+1, vector<LL>(N+1, 0));
        
        for(int R = M-1; R >= 0; --R) {
            for(int C1 = 0; C1 <= N; ++C1) {
                LL maxPathSum = 0;

                for(int C2 = 0; C2 < N; ++C2) {
                    LL nextSideSum = dp[R+1][C2];
                    LL moveCost    = (C1 == N) ? 0 : abs(C1 - C2);
                    LL currPathSum = grid[R][C2] + nextSideSum - moveCost;
                    maxPathSum = max(maxPathSum, currPathSum);
                } 

                dp[R][C1] = maxPathSum;
            }
        }

        return dp[0][N];
    }
    // Note: This solution will lead to TLE

    // O(M*N*N) & O(2*N)
    LL solveBy1DTable(const vector<vector<int>>& grid) {
        vector<LL> nextRow(N+1, 0); // R + 1th row
        vector<LL> currRow(N+1, 0); // Rth row

        for(int R = M-1; R >= 0; --R) {
            for(int C1 = 0; C1 <= N; ++C1) {
                LL maxPathSum = 0;

                for(int C2 = 0; C2 < N; ++C2) {
                    LL nextSideSum = nextRow[C2];
                    LL moveCost    = (C1 == N) ? 0 : abs(C1 - C2);
                    LL currPathSum = grid[R][C2] + nextSideSum - moveCost;
                    maxPathSum = max(maxPathSum, currPathSum);
                } 

                currRow[C1] = maxPathSum;
            }
            swap(nextRow, currRow);
        }

        return nextRow[N];
    }
    // Note: This solution will lead to TLE

    // O(M*N) & O(4*N)
    LL solveBy1DIntuitive(const vector<vector<int>>& grid) {
        vector<LL> prevRow(N); // R - 1th row
        vector<LL> currRow(N); // Rth row

        // Fill all values of 0th row of matrix
        for(int C = 0; C < N; ++C) {
            prevRow[C] = grid[0][C];
        }

        for(int R = 1; R < M; ++R) {
            // Tracks maximum value for each column in previous row
            vector<LL> maxValLeft(N), maxValRight(N);

            // Precompute maximum value from left side of each column
            maxValLeft[0] = prevRow[0];
            for(int C = 1; C < N; ++C) {
                maxValLeft[C] = max(maxValLeft[C-1] - 1, prevRow[C]);
            }

            // Precompute maximum value from right side of each column
            maxValRight[N-1] = prevRow[N-1];
            for(int C = N-2; C >= 0; --C) {
                maxValRight[C] = max(maxValRight[C+1] - 1, prevRow[C]);
            }

            // Compute maxPathSum ending at each column of currRow
            for(int C = 0; C < N; ++C) {
                currRow[C] = grid[R][C] + max(maxValLeft[C], maxValRight[C]);
            }

            swap(prevRow, currRow);
        }

        // Return maxElement lying among all maxPathSum in lastRow
        LL maxElement = 0;
        for(int C = 0; C < N; ++C) {
            maxElement = max(maxElement, prevRow[C]);
        }
        return maxElement;
    }

public:
    LL maxPoints(vector<vector<int>>& grid) {
        M = grid.size(), N = grid[0].size(); 
        return solveBy1DIntuitive(grid);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming    
Link  : https://leetcode.com/problems/maximum-number-of-points-with-cost/description/?envType=daily-question&envId=2024-08-17
