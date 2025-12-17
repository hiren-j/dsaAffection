// Code to find the minimum path sum from top to bottom in a triangle ~ coded by vHiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int M;

    // O(2^(M*M)) & O(M)
    int solveWithoutMemo(const vector<vector<int>>& triangle, int R, int C) {
        if(R == M-1)
            return triangle[R][C];

        int moveToSameCol = solveWithoutMemo(triangle, R+1, C);
        int moveToNextCol = solveWithoutMemo(triangle, R+1, C+1);

        return min(moveToSameCol, moveToNextCol) + triangle[R][C];
    }
    
    // O(2*M*M) & O(M*M + M)
    int solveWithMemo(vector<vector<int>>& memory, const vector<vector<int>>& triangle, int R, int C) {
        if(R == M-1)
            return triangle[R][C];

        if(memory[R][C] != INT_MIN)
            return memory[R][C];

        int moveToSameCol = solveWithMemo(memory, triangle, R+1, C);
        int moveToNextCol = solveWithMemo(memory, triangle, R+1, C+1);

        return memory[R][C] = min(moveToSameCol, moveToNextCol) + triangle[R][C];
    }

public:
    int minimumTotal(vector<vector<int>>& triangle) {
        M = triangle.size();
        vector<vector<int>> memory(M, vector<int>(M, INT_MIN));
        return solveWithMemo(memory, triangle, 0, 0);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class BottomUp {
    int M;

    // O(M*M) & O(M*M)
    int solveWith2DTable(const vector<vector<int>>& triangle) {
        vector<vector<int>> dp(M, vector<int>(M, INT_MIN));

        for(int C = 0; C < M; ++C)
            dp[M-1][C] = triangle[M-1][C];

        for(int R = M-2; R >= 0; --R) {
            for(int C = R; C >= 0; --C) {
                int moveToSameCol = dp[R+1][C];
                int moveToNextCol = dp[R+1][C+1];
                dp[R][C] = min(moveToSameCol, moveToNextCol) + triangle[R][C];
            }
        }

        return dp[0][0];
    }

    // O(M*M) & O(2*M)
    int solveWith1DTable(const vector<vector<int>>& triangle) {
        vector<int> nextRow(M, INT_MIN); // R + 1th row

        for(int C = 0; C < M; ++C)
            nextRow[C] = triangle[M-1][C];

        for(int R = M-2; R >= 0; --R) {
            vector<int> currRow(M, INT_MIN); // Rth row

            for(int C = R; C >= 0; --C) {
                int moveToSameCol = nextRow[C];
                int moveToNextCol = nextRow[C+1];
                currRow[C] = min(moveToSameCol, moveToNextCol) + triangle[R][C];
            }

            swap(nextRow, currRow);
        }

        return nextRow[0];
    }

    // O(M*M) & O(M*M)
    int solveWith2DLessBlocks(const vector<vector<int>>& triangle) {
        vector<vector<int>> dp(M);
        
        dp[M-1].resize(M, INT_MIN);
        for(int C = 0; C < M; ++C)
            dp[M-1][C] = triangle[M-1][C];

        for(int R = M-2; R >= 0; --R) {
            dp[R].resize(R+1, INT_MIN);

            for(int C = R; C >= 0; --C) {
                int moveToSameCol = dp[R+1][C];
                int moveToNextCol = dp[R+1][C+1];
                dp[R][C] = min(moveToSameCol, moveToNextCol) + triangle[R][C];
            }
        }

        return dp[0][0];
    }

    // O(M*M) & O(2*M)
    int solveWith1DLessBlocks(const vector<vector<int>>& triangle) {
        vector<int> nextRow(M, INT_MIN); // R + 1th row

        for(int C = 0; C < M; ++C)
            nextRow[C] = triangle[M-1][C];

        for(int R = M-2; R >= 0; --R) {
            vector<int> currRow(R+1, INT_MIN); // Rth row

            for(int C = R; C >= 0; --C) {
                int moveToSameCol = nextRow[C];
                int moveToNextCol = nextRow[C+1];
                currRow[C] = min(moveToSameCol, moveToNextCol) + triangle[R][C];
            }

            swap(nextRow, currRow);
        }

        return nextRow[0];
    }

    // O(M*M) & O(1)
    int solveWithoutTable(vector<vector<int>>& triangle) {
        for(int C = 0; C < M; ++C)
            triangle[M-1][C] = triangle[M-1][C];

        for(int R = M-2; R >= 0; --R) {
            for(int C = R; C >= 0; --C) {
                int moveToSameCol = triangle[R+1][C];
                int moveToNextCol = triangle[R+1][C+1];
                triangle[R][C] = min(moveToSameCol, moveToNextCol) + triangle[R][C];
            }
        }

        return triangle[0][0];
    }

public:
    int minimumTotal(vector<vector<int>>& triangle) {
        M = triangle.size();
        return solveWithoutTable(triangle);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/triangle/
