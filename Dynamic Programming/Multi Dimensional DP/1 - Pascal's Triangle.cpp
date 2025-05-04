// Code to find the first N rows of Pascal's triangle ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int solveWithMemo(vector<vector<int>>& dp, vector<vector<int>>& pascal, int R, int C) {
        // Base case: In pascal's triangle, cells of first column and last column of any row always have value 1
        if(C == 0 || C == R)
            return 1;
        
        if(dp[R][C] != -1)
            return dp[R][C];

        // In pascal's triangle, here cell value is the sum of two values, the coordinates of those values are
        int moveUp     = solveWithMemo(dp, pascal, R-1, C);
        int moveUpPrev = solveWithMemo(dp, pascal, R-1, C-1);
        
        return dp[R][C] = pascal[R][C] = moveUp + moveUpPrev;
    }

public:
    vector<vector<int>> generate(int N) {
        // Create rows of pascal's triangle, if we consider R for rows with 0-based indexing then if we're at Rth row, then total values on that row will be R+1
        vector<vector<int>> pascal;
        for(int R = 0; R < N; ++R) {
            pascal.push_back(vector<int>(R+1, 1));
        }   

        // Start from the last row of pascal's triangle and then find the value of each cell
        vector<vector<int>> dp(N, vector<int>(N, -1));
        for(int C = 1; C <= N-2; ++C) {
            solveWithMemo(dp, pascal, N-1, C);
        }

        return pascal;
    }
};
    
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    vector<vector<int>> solveWith2DTable(int N, vector<vector<int>>& pascal) {
        vector<vector<int>> dp(N, vector<int>(N, -1));

        for(int R = 0; R < N; ++R) { // Initialize the base case
            dp[R][0] = dp[R][R] = 1;
        }

        for(int R = 2; R < N; ++R) { // Based on TopDown, we could start R from 0, it will also work but that's not needed, as no column iterations will be made for R = 0,1
            for(int C = 1; C < R; ++C) {
                int moveUp     = dp[R-1][C];
                int moveUpPrev = dp[R-1][C-1];
                dp[R][C] = pascal[R][C] = moveUp + moveUpPrev;
            }
        }

        return pascal;        
    }
    // Note: We can do space optimization in this one, to find any cell value we are only dependent on the previous row of the current row, hence instead of taking the dp matrix, we could only use two 1D arrays
    
    vector<vector<int>> solveWith1DTable(int N, vector<vector<int>>& pascal) {
        vector<int> prevRow(N, 1); // Consider it represents R = 1, its because the below loop is starting from R = 2

        for(int R = 2; R < N; ++R) {
            vector<int> currRow(N, 1); // Setting to 1 also initializes our base case, but to do explicitly then write: currRow[0] = currRow[R] = 1;
            for(int C = 1; C < R; ++C) {
                int moveUp     = prevRow[C];
                int moveUpPrev = prevRow[C-1];
                currRow[C] = pascal[R][C] = moveUp + moveUpPrev;
            }
            prevRow = currRow; // Update previous row for upcoming row
        }

        return pascal;        
    }

public:
    vector<vector<int>> generate(int N) {
        vector<vector<int>> pascal;
        for(int R = 0; R < N; ++R) {
            pascal.push_back(vector<int>(R+1, 1));
        }   

        return solveWith1DTable(N, pascal);
    }
};
    
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUpEasy {
public:
    vector<vector<int>> generate(int N) {
        vector<vector<int>> pascal;
        for(int R = 0; R < N; ++R)
            pascal.push_back(vector<int>(R+1, 1));

        for(int R = 2; R < N; ++R)
            for(int C = 1; C < R; ++C)
                pascal[R][C] = pascal[R-1][C] + pascal[R-1][C-1];

        return pascal;
    }
};    

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUpEnhanced {
public:
    vector<vector<int>> generate(int N) {
        vector<vector<int>> pascal;

        for(int R = 0; R < N; ++R) {
            pascal.push_back(vector<int>(R+1, 1));
            
            for(int C = 1; C < R; ++C) {
                pascal[R][C] = pascal[R-1][C] + pascal[R-1][C-1];
            }
        }

        return pascal;
    }
};    
// Note: The auxiliary space is considered because even if its not the user's demand but still we have to create the pascal table to get the output

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/pascals-triangle/description/
