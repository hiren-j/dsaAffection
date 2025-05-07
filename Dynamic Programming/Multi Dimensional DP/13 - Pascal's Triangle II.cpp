// Code to return the rowIndexth (0-indexed) row of the Pascal's triangle ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int N;

    // O(2^(N*N)) & O(2*N)
    int solveWithoutMemo(vector<int>& result, int R, int C) {
        if(C == 0 || C == R || C == N)
            return 1;
    
        int moveUp     = solveWithoutMemo(result, R-1, C);
        int moveUpPrev = solveWithoutMemo(result, R-1, C-1);

        if(R == N-1)
            solveWithoutMemo(result, R, C+1);

        return result[C] = moveUp + moveUpPrev;
    }

    // O(2*N*N) & O(N*N + 2*N)
    int solveWithMemo(vector<vector<int>>& dp, vector<int>& result, int R, int C) {
        if(C == 0 || C == R || C == N)
            return 1;
        
        if(dp[R][C] != -1)
            return dp[R][C];

        int moveUp     = solveWithMemo(dp, result, R-1, C);
        int moveUpPrev = solveWithMemo(dp, result, R-1, C-1);

        if(R == N-1)
            solveWithMemo(dp, result, R, C+1);

        return dp[R][C] = result[C] = moveUp + moveUpPrev;
    }

public:
    // Method to return rowIndexth row of pascal triangle, using recursion with memoization - O(N^2) & O(N^2)
    vector<int> getRow(int rowIndex) {
        N = rowIndex + 1;
        vector<vector<int>> dp(N, vector<int>(N, -1));
        vector<int> result(N, 1);
        solveWithMemo(dp, result, N-1, 1);
        return result;
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int N;

    // O(N^2) & O(N^2)
    vector<int> solveWith2DTable() {
        vector<vector<int>> dp(N, vector<int>(N+1, -1));
        vector<int> result(N, 1);

        for(int R = 0; R < N; ++R)
            dp[R][0] = dp[R][R] = dp[R][N] = 1;

        for(int R = 2; R < N; ++R) {
            for(int C = 1; C < R; ++C) {
                int moveUp     = dp[R-1][C];
                int moveUpPrev = dp[R-1][C-1];
                dp[R][C] = result[C] = moveUp + moveUpPrev; 
            }
        }

        return result;
    }

    // O(N^2) & O(3*N)
    vector<int> solveWith1DTable() {
        vector<int> prevRow(N+1, 1), result(N, 1);

        for(int R = 2; R < N; ++R) {
            vector<int> currRow(N+1, 1);
            for(int C = 1; C < R; ++C) {
                int moveUp     = prevRow[C]; 
                int moveUpPrev = prevRow[C-1]; 
                currRow[C] = result[C] = moveUp + moveUpPrev;
            }
            prevRow = currRow;
        }

        return result;
    }

public:
    vector<int> getRow(int rowIndex) {
        N = rowIndex + 1;
        return solveWith1DTable();
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUpEasy {
public:
    // O(N^2) & O(N^2)
    vector<int> getRow(int rowIndex) {
        int N = rowIndex + 1;
        vector<vector<int>> pascal(N, vector<int>(N, 1));

        for(int R = 2; R < N; ++R)
            for(int C = 1; C < R; ++C)
                pascal[R][C] = pascal[R-1][C] + pascal[R-1][C-1];

        return pascal[rowIndex];
    }
};
    
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUpEnhanced {
public:
    // O(N^2) & O(2*N)
    vector<int> getRow(int rowIndex) {
        int N = rowIndex + 1;
        vector<int> prevRow(N, 1);

        for(int R = 2; R < N; ++R) {
            vector<int> currRow(N, 1);
            for(int C = 1; C < R; ++C) {
                currRow[C] = prevRow[C] + prevRow[C-1];
            }
            prevRow = currRow;
        }

        return prevRow;
    }
};
    
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/pascals-triangle/description/
