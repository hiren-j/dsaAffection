// Code to find the first N rows of Pascal's triangle ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int solveWithMemo(vector<vector<int>>& dp, vector<vector<int>>& pascal, int R, int C) {
        if(C == 0 || C == R)
            return 1;
        
        if(dp[R][C] != -1)
            return dp[R][C];

        int moveUp     = solveWithMemo(dp, pascal, R-1, C);
        int moveUpPrev = solveWithMemo(dp, pascal, R-1, C-1);

        return dp[R][C] = pascal[R][C] = moveUp + moveUpPrev;
    }

public:
    vector<vector<int>> generate(int N) {
        vector<vector<int>> pascal;
        for(int R = 0; R < N; ++R) {
            pascal.push_back(vector<int>(R+1, 1));
        }   

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

        for(int R = 0; R < N; ++R) {
            dp[R][0] = dp[R][R] = 1;
        }

        for(int R = 2; R < N; ++R) {
            for(int C = 1; C < R; ++C) {
                int moveUp     = dp[R-1][C];
                int moveUpPrev = dp[R-1][C-1];
                dp[R][C] = pascal[R][C] = moveUp + moveUpPrev;
            }
        }

        return pascal;        
    }

    vector<vector<int>> solveWith1DTable(int N, vector<vector<int>>& pascal) {
        vector<int> prevRow(N, 1);

        for(int R = 2; R < N; ++R) {
            vector<int> idealRow(N, 1); // Setting to 1 also initializes our base case, but to do explicitly then write: idealRow[0] = idealRow[R] = 1;
            for(int C = 1; C < R; ++C) {
                int moveUp     = prevRow[C];
                int moveUpPrev = prevRow[C-1];
                idealRow[C] = pascal[R][C] = moveUp + moveUpPrev;
            }
            prevRow = idealRow;
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
