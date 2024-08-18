// Code to find the maximum number of points you can achieve. To gain points, you must pick one cell in each row. Picking the cell at coordinates (r, c) will add points[r][c] to your score. However, you will lose points if you pick a cell too far from the cell that you picked in the previous row. For every two adjacent rows r and r + 1 (where 0 <= r < m - 1), picking cells at coordinates (r, c1) and (r + 1, c2) will subtract abs(c1 - c2) from your score ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    typedef long long ll;
    int N, M;

    // O(M^(N*M)) & O(N)
    ll solveWithoutMemo(vector<vector<int>>& points, int R, int prevCol) {
        // Edge case: If all the rows are exhausted then you can't earn points 
        if(R == N)
            return 0;

        ll maxPoints = 0;

        // Consider each cell as a start point and then find the points you can achieve through it's path, then update the result by the maximum value
        for(int C = 0; C < M; ++C) {
            ll score = points[R][C] + solveWithoutMemo(points, R+1, C);
            if(prevCol != -1) {
                score -= abs(prevCol - C);
            }
            maxPoints = max(maxPoints, score);
        }

        return maxPoints;
    }

    // O(M*N*M) & O(N*M + N)
    ll solveWithMemo(vector<vector<ll>>& memory, vector<vector<int>>& points, int R, int prevCol) {
        // Edge case: If all the rows are exhausted then you can't earn points 
        if(R == N)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[R][prevCol + 1] != -1)
            return memory[R][prevCol + 1];

        ll maxPoints = 0;

        // Consider each cell as a start point and then find the points you can achieve through it's path, then update the result by the maximum value
        for(int C = 0; C < M; ++C) {
            ll score = points[R][C] + solveWithMemo(memory, points, R+1, C);
            if(prevCol != -1) {
                score -= abs(prevCol - C);
            }
            maxPoints = max(maxPoints, score);
        }

        // Store the result value to the memoization table and then return it
        return memory[R][prevCol + 1] = maxPoints;
    }

public:
    // Method to find the maximum points you can achieve by performing the specified movements, using recursion with memoization - O(M*N*M) & O(N*M)
    ll maxPoints(vector<vector<int>>& points) {
        N = points.size(), M = points[0].size();
        vector<vector<ll>> memory(N, vector<ll>(M+1, -1));
        return solveWithMemo(memory, points, 0, -1);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp_V1 {
    typedef long long ll;

public:
    // #1 Method to find the maximum points you can achieve by performing the specified movements, using 2D tabulation - O(N*M*M) & O(N*M)
    ll maxPoints_V1(vector<vector<int>>& points) {
        int N = points.size(), M = points[0].size();

        // 2D DP table
        vector<vector<ll>> dp(N+1, vector<ll>(M+1, 0));

        // Fill the table
        for(int R = N-1; R >= 0; --R) {
            for(int prevCol = M-1; prevCol >= -1; --prevCol) {
                ll maxPoints = 0;

                for(int C = 0; C < M; ++C) {
                    ll score = points[R][C] + dp[R+1][C+1];
                    if(prevCol != -1) {
                        score -= abs(prevCol - C);
                    }
                    maxPoints = max(maxPoints, score);
                }

                dp[R][prevCol + 1] = maxPoints;
            }
        }
        
        // Return the result value
        return dp[0][0];
    }

    // #2 Method to find the maximum points you can achieve by performing the specified movements, using 1D tabulation - O(N*M*M) & O(M)
    ll maxPoints_V2(vector<vector<int>>& points) {
        int N = points.size(), M = points[0].size();

        // 1D DP tables
        vector<int> nextRow(M+1, 0), idealRow(M+1, 0);

        // Fill the table
        for(int R = N-1; R >= 0; --R) {
            for(int prevCol = M-1; prevCol >= -1; --prevCol) {
                ll maxPoints = 0;

                for(int C = 0; C < M; ++C) {
                    ll score = points[R][C] + nextRow[C+1];
                    if(prevCol != -1) {
                        score -= abs(prevCol - C);
                    }
                    maxPoints = max(maxPoints, score);
                }
                
                idealRow[prevCol + 1] = maxPoints;
            }
            nextRow = idealRow;
        }

        // Return the result value
        return idealRow[0];
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp_V2 {
    typedef long long ll;

public:
    // Method to find the maximum points you can achieve by performing the specified movements, using 1D tabulation - O(N*M) & O(M)
    ll maxPoints(vector<vector<int>>& points) {
        int N = points.size(), M = points[0].size();

        vector<ll> prevRow(M, 0), currRow(M, 0);

        // Initialize the first row
        for(int C = 0; C < M; ++C)
            prevRow[C] = points[0][C];

        for(int R = 1; R < N; ++R) {
            vector<ll> maxPointLeft(M, 0), maxPointRight(M , 0);
            
            // Fill the maximum points you can gain from the left side of each column
            maxPointLeft[0] = prevRow[0];
            for(int C = 1; C < M; ++C) {
                maxPointLeft[C] = max(maxPointLeft[C-1] - 1, prevRow[C]);
            }

            // Fill the maximum points you can gain from the right side of each column
            maxPointRight[M-1] = prevRow[M-1];
            for(int C = M-2; C >= 0; --C) {
                maxPointRight[C] = max(maxPointRight[C+1] - 1, prevRow[C]);
            }

            // Compute the current row's maximum points
            for(int C = 0; C < M; ++C) {
                currRow[C] = points[R][C] + max(maxPointLeft[C], maxPointRight[C]);
            }

            // Move to the next row
            prevRow = currRow; 
        }  

        // Return the maximum points you can gain from the last row of the matrix
        return *max_element(begin(prevRow), end(prevRow));
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming    
Link  : https://leetcode.com/problems/maximum-number-of-points-with-cost/description/?envType=daily-question&envId=2024-08-17
