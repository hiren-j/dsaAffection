// Code to find the maximum number of points you can achieve. To gain points, you must pick one cell in each row. Picking the cell at coordinates (r, c) will add points[r][c] to your score. However, you will lose points if you pick a cell too far from the cell that you picked in the previous row. For every two adjacent rows r and r + 1 (where 0 <= r < m - 1), picking cells at coordinates (r, c1) and (r + 1, c2) will subtract abs(c1 - c2) from your score ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    typedef long long LL;
    int M, N;

    // O(N^(M*N)) & O(M)
    LL solveWithoutMemo(vector<vector<int>>& points, int R, int prevCol) {
        if(R == M)
            return 0;

        LL maxPoints = 0;

        // Consider each cell as a start point and then find the points you can achieve through it's path, then update the result by maximum value
        for(int C = 0; C < N; ++C) {
            LL score = points[R][C] + solveWithoutMemo(points, R+1, C);
            if(prevCol != N) {
                score -= abs(prevCol - C);
            }
            maxPoints = max(maxPoints, score);
        }

        return maxPoints;
    }

    // O(N*M*N) & O(M*N + M)
    LL solveWithMemo(vector<vector<LL>>& dp, vector<vector<int>>& points, int R, int prevCol) {
        if(R == M)
            return 0;

        if(dp[R][prevCol] != -1)
            return dp[R][prevCol];

        LL maxPoints = 0;

        // Consider each cell as a start point and then find the points you can achieve through it's path, then update the result by maximum value
        for(int C = 0; C < N; ++C) {
            LL score = points[R][C] + solveWithMemo(dp, points, R+1, C);
            if(prevCol != N) {
                score -= abs(prevCol - C);
            }
            maxPoints = max(maxPoints, score);
        }

        return dp[R][prevCol] = maxPoints;
    }

public:
    // Method to find the maximum points you can achieve by performing the specified movements, using recursion with memoization - O(M*N*N) & O(M*N)
    LL maxPoints(vector<vector<int>>& points) {
        M = points.size(), N = points[0].size();
        vector<vector<LL>> dp(M, vector<LL>(N+1, -1));
        return solveWithMemo(dp, points, 0, N);
    }
};
// Note: This solution will lead to time-limit-exceed

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    typedef long long LL;
    int M, N;

    // O(M*N*N) & O(M*N)
    LL solveWith2DTable(vector<vector<int>>& points) {
        vector<vector<LL>> dp(M, vector<LL>(N+1, -1));

        for(int R = M-1; R >= 0; --R) {
            for(int prevCol = 0; prevCol <= N; ++prevCol) {
                LL maxPoints = 0;

                for(int C = 0; C < N; ++C) {
                    LL score = points[R][C] + (R+1 < M ? dp[R+1][C] : 0);
                    if(prevCol != N) {
                        score -= abs(prevCol - C);
                    }
                    maxPoints = max(maxPoints, score);
                }

                dp[R][prevCol] = maxPoints;
            }
        }

        return dp[0][N];
    }

    // O(M*N*N) & O(M*N)
    LL solveWith2DEnhanced(vector<vector<int>>& points) {
        vector<vector<LL>> dp(M+1, vector<LL>(N+1, 0));

        for(int R = M-1; R >= 0; --R) {
            for(int prevCol = 0; prevCol <= N; ++prevCol) {
                LL maxPoints = 0;

                for(int C = 0; C < N; ++C) {
                    LL score = points[R][C] + dp[R+1][C];
                    if(prevCol != N) {
                        score -= abs(prevCol - C);
                    }
                    maxPoints = max(maxPoints, score);
                }

                dp[R][prevCol] = maxPoints;
            }
        }

        return dp[0][N];
    }

    // O(M*N*N) & O(2*N)
    LL solveWith1DTable(vector<vector<int>>& points) {
        vector<LL> nextRow(N+1, 0), idealRow(N+1, 0);

        for(int R = M-1; R >= 0; --R) {
            for(int prevCol = 0; prevCol <= N; ++prevCol) {
                LL maxPoints = 0;

                for(int C = 0; C < N; ++C) {
                    LL score = points[R][C] + nextRow[C];
                    if(prevCol != N) {
                        score -= abs(prevCol - C);
                    }
                    maxPoints = max(maxPoints, score);
                }

                idealRow[prevCol] = maxPoints;
            }
            nextRow = idealRow;
        }

        return nextRow[N];
    }

public:
    LL maxPoints(vector<vector<int>>& points) {
        M = points.size(), N = points[0].size();
        return solveWith1DTable(points);
    }
};
// Note: This solution will lead to time-limit-exceed

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUpIntuitive {
    typedef long long LL;

public:
    // O(M*N) & O(2*N)
    LL maxPoints(vector<vector<int>>& points) {
        int M = points.size(), N = points[0].size();

        vector<LL> prevRow(N, 0), currRow(N, 0);

        for(int C = 0; C < N; ++C) {
            prevRow[C] = points[0][C];
        }

        for(int R = 1; R < M; ++R) {
            vector<LL> maxPointLeft(N, 0), maxPointRight(N , 0);
            
            // Fill the maximum points you can gain from the left side of each column
            maxPointLeft[0] = prevRow[0];
            for(int C = 1; C < N; ++C) {
                maxPointLeft[C] = max(maxPointLeft[C-1] - 1, prevRow[C]);
            }

            // Fill the maximum points you can gain from the right side of each column
            maxPointRight[N-1] = prevRow[N-1];
            for(int C = N-2; C >= 0; --C) {
                maxPointRight[C] = max(maxPointRight[C+1] - 1, prevRow[C]);
            }

            // Compute the current row's maximum points
            for(int C = 0; C < N; ++C) {
                currRow[C] = points[R][C] + max(maxPointLeft[C], maxPointRight[C]);
            }

            prevRow = currRow; 
        }  

        return *max_element(begin(prevRow), end(prevRow));
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming    
Link  : https://leetcode.com/problems/maximum-number-of-points-with-cost/description/?envType=daily-question&envId=2024-08-17
