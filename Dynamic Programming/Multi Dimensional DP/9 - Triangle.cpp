// Code to find the minimum path sum from top to bottom in a triangle ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int N;

    // O(2^(N*N)) & O(N)
    int solveWithoutMemo(vector<vector<int>>& triangle, int R, int C) {
        if(R == N)
            return 0;
        
        int moveToSameCol = solveWithoutMemo(triangle, R+1, C);
        int moveToNextCol = solveWithoutMemo(triangle, R+1, C+1);

        return min(moveToSameCol, moveToNextCol) + triangle[R][C];
    }

    // O(2*N*N) & O(N*N + N)
    int solveWithMemo(vector<vector<int>>& memory, vector<vector<int>>& triangle, int R, int C) {
        if(R == N)
            return 0;

        if(memory[R][C] != -1)
            return memory[R][C];
        
        int moveToSameCol = solveWithMemo(memory, triangle, R+1, C);
        int moveToNextCol = solveWithMemo(memory, triangle, R+1, C+1);

        return memory[R][C] = min(moveToSameCol, moveToNextCol) + triangle[R][C];
    }

public:
    // Method to find minimum path sum from top to bottom, using recursion with memoization - O(N*N) & O(N*N)
    int minimumTotal(vector<vector<int>>& triangle) {
        N = triangle.size();
        vector<vector<int>> memory(N, vector<int>(N, -1));
        return solveWithMemo(memory, triangle, 0, 0);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class BottomUp {
    int N;

    // O(N*N) & O(N*N)
    int solveWith2DTable(vector<vector<int>>& triangle) {
        vector<vector<int>> dp(N, vector<int>(N, -1));

        for(int R = N-1; R >= 0; --R) {
            for(int C = R; C >= 0; --C) {
                int moveToSameCol = (R+1 < N) ? dp[R+1][C]   : 0;
                int moveToNextCol = (R+1 < N) ? dp[R+1][C+1] : 0;
                dp[R][C] = min(moveToSameCol, moveToNextCol) + triangle[R][C];  
            }
        }

        return dp[0][0];
    }

    // O(N*N) & O(N*N)
    int solveWith2DEnhanced(vector<vector<int>>& triangle) {
        vector<vector<int>> dp(N+1, vector<int>(N+1, 0));

        for(int R = N-1; R >= 0; --R) {
            for(int C = R; C >= 0; --C) {
                int moveToSameCol = dp[R+1][C];
                int moveToNextCol = dp[R+1][C+1];
                dp[R][C] = min(moveToSameCol, moveToNextCol) + triangle[R][C];  
            }
        }

        return dp[0][0];
    }

    // O(N*N) & O(2*N)
    int solveWith1DTable(vector<vector<int>>& triangle) {
        vector<int> nextRow(N+1, 0), idealRow(N+1, 0);

        for(int R = N-1; R >= 0; --R) {
            for(int C = R; C >= 0; --C) {
                int moveToSameCol = nextRow[C];
                int moveToNextCol = nextRow[C+1];
                idealRow[C] = min(moveToSameCol, moveToNextCol) + triangle[R][C];  
            }
            nextRow = idealRow;
        }

        return nextRow[0];
    }

    // O(N*N) & O(N*N)
    int solveWith2DLessBlocks(vector<vector<int>>& triangle) {
        vector<vector<int>> dp(N);

        for(int R = N-1; R >= 0; --R) {
            dp[R] = vector<int>(R+1, 0);
            for(int C = R; C >= 0; --C) {
                int moveToSameCol = (R+1 < N) ? dp[R+1][C]   : 0;
                int moveToNextCol = (R+1 < N) ? dp[R+1][C+1] : 0;
                dp[R][C] = min(moveToSameCol, moveToNextCol) + triangle[R][C];  
            }
        }

        return dp[0][0];
    }

    // O(N*N) & O(2*N)
    int solveWith1DLessBlocks(vector<vector<int>>& triangle) {
        vector<int> nextRow(N+1, 0);

        for(int R = N-1; R >= 0; --R) {
            vector<int> idealRow(R+1, 0);
            for(int C = R; C >= 0; --C) {
                int moveToSameCol = nextRow[C];
                int moveToNextCol = nextRow[C+1];
                idealRow[C] = min(moveToSameCol, moveToNextCol) + triangle[R][C];  
            }
            nextRow = idealRow;
        }

        return nextRow[0];
    }

    // O(N*N) & O(1)
    int solveWithoutTable(vector<vector<int>>& triangle) {
        for(int R = N-2; R >= 0; --R) {
            for(int C = R; C >= 0; --C) {
                int moveToSameCol = triangle[R+1][C];
                int moveToNextCol = triangle[R+1][C+1];
                triangle[R][C] += min(moveToSameCol, moveToNextCol);  
            }
        }

        return triangle[0][0];
    }

public:
    int minimumTotal(vector<vector<int>>& triangle) {
        N = triangle.size();
        return solveWithoutTable(triangle);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/triangle/
