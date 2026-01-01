// Code to find the maximum score achievable without exceeding a total cost of k, or -1 if no valid path exists ~ coded by vHiren

----------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int M, N;

    // O(2^(M*N)) & O(M+N)
    int solveWithoutMemo(const vector<vector<int>>& grid, int R, int C, int K) {
        if(R == M || C == N || K < 0)
            return INT_MIN;
        
        if(R == M-1 && C == N-1)
            return (grid[R][C] != 0 && K-1 < 0) ? INT_MIN : grid[R][C];

        int moveRight = solveWithoutMemo(grid, R, C+1, K);
        int moveDown  = solveWithoutMemo(grid, R+1, C, K); 
        int maxScore  = max(moveRight, moveDown);

        return (maxScore == INT_MIN) ? INT_MIN : maxScore + grid[R][C];
    }
    
    // O(2*M*N*K) & O(M*N*K + M+N)
    int solveWithMemo(vector<vector<vector<int>>>& dp, const vector<vector<int>>& grid, int R, int C, int K) {
        if(R == M || C == N || K < 0)
            return INT_MIN;
        
        if(R == M-1 && C == N-1)
            return (grid[R][C] != 0 && K-1 < 0) ? INT_MIN : grid[R][C];

        if(dp[R][C][K] != -1)
            return dp[R][C][K];

        int moveRight = solveWithMemo(dp, grid, R, C+1, (grid[R][C] != 0 ? K-1 : K));
        int moveDown  = solveWithMemo(dp, grid, R+1, C, (grid[R][C] != 0 ? K-1 : K)); 
        int maxScore  = max(moveRight, moveDown);

        return dp[R][C][K] = (maxScore == INT_MIN) ? INT_MIN : maxScore + grid[R][C];
    }

public:
    int maxPathScore(vector<vector<int>>& grid, int K) {
        M = grid.size(), N = grid[0].size();
        vector<vector<vector<int>>> dp(M, vector<vector<int>>(N, vector<int>(K+1, -1)));
        int maxScore = solveWithMemo(dp, grid, 0, 0, K);
        return (maxScore == INT_MIN) ? -1 : maxScore;
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int M, N;

    // O(M*N*GK) & O(M*N*GK) : Where GK = given_K
    int solveBy3DTable(const vector<vector<int>>& grid, int given_K) {
        vector<vector<vector<int>>> dp(M+1, vector<vector<int>>(N+1, vector<int>(given_K+1, -1)));

        for(int C = 0; C <= N; ++C)
            for(int K = 0; K <= given_K; ++K)
                dp[M][C][K] = INT_MIN;

        for(int R = 0; R <= M; ++R)
            for(int K = 0; K <= given_K; ++K)
                dp[R][N][K] = INT_MIN;

        for(int K = 0; K <= given_K; ++K)
            dp[M-1][N-1][K] = (grid[M-1][N-1] != 0 && K-1 < 0) ? INT_MIN : grid[M-1][N-1];  

        for(int R = M-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                if(R == M-1 && C == N-1)
                    continue;
                for(int K = 0; K <= given_K; ++K) {
                    int next_K    = grid[R][C] != 0 ? K-1 : K;
                    int moveRight = (next_K < 0) ? INT_MIN : dp[R][C+1][next_K];
                    int moveDown  = (next_K < 0) ? INT_MIN : dp[R+1][C][next_K]; 
                    int maxScore  = max(moveRight, moveDown);
                    dp[R][C][K] = (maxScore == INT_MIN) ? INT_MIN : maxScore + grid[R][C];
                }
            }
        }  

        int maxScore = dp[0][0][given_K];
        return (maxScore == INT_MIN) ? -1 : maxScore;
    }

    // O(M*N*GK) & O(M*N*GK) : Where GK = given_K
    int solveBy3DEnhanced(const vector<vector<int>>& grid, int given_K) {
        vector<vector<vector<int>>> dp(M+1, vector<vector<int>>(N+1, vector<int>(given_K+1, INT_MIN)));

        for(int K = 0; K <= given_K; ++K)
            dp[M-1][N-1][K] = (grid[M-1][N-1] != 0 && K-1 < 0) ? INT_MIN : grid[M-1][N-1];  

        for(int R = M-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                if(R == M-1 && C == N-1)
                    continue;
                for(int K = 0; K <= given_K; ++K) {
                    int next_K    = grid[R][C] != 0 ? K-1 : K;
                    int moveRight = (next_K < 0) ? INT_MIN : dp[R][C+1][next_K];
                    int moveDown  = (next_K < 0) ? INT_MIN : dp[R+1][C][next_K]; 
                    int maxScore  = max(moveRight, moveDown);
                    dp[R][C][K] = (maxScore == INT_MIN) ? INT_MIN : maxScore + grid[R][C];
                }
            }
        }  

        int maxScore = dp[0][0][given_K];
        return (maxScore == INT_MIN) ? -1 : maxScore;
    }

    // O(M*N*GK) & O(2*N*GK) : Where GK = given_K
    int solveBy2DTable(const vector<vector<int>>& grid, int given_K) {
        vector<vector<int>> next(N+1, vector<int>(given_K+1, INT_MIN)); // R + 1th table
        vector<vector<int>> curr(N+1, vector<int>(given_K+1, INT_MIN)); // Rth table

        for(int R = M-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                for(int K = 0; K <= given_K; ++K) {
                    if(R == M-1 && C == N-1) {
                        curr[N-1][K] = (grid[M-1][N-1] != 0 && K-1 < 0) ? INT_MIN : grid[M-1][N-1];  
                    }
                    else {  
                        int next_K    = grid[R][C] != 0 ? K-1 : K;
                        int moveRight = (next_K < 0) ? INT_MIN : curr[C+1][next_K];
                        int moveDown  = (next_K < 0) ? INT_MIN : next[C][next_K]; 
                        int maxScore  = max(moveRight, moveDown);
                        curr[C][K] = (maxScore == INT_MIN) ? INT_MIN : maxScore + grid[R][C];
                    }
                }
            }
            swap(next, curr);
        }  

        int maxScore = next[0][given_K];
        return (maxScore == INT_MIN) ? -1 : maxScore;
    }

public:
    int maxPathScore(vector<vector<int>>& grid, int K) {
        M = grid.size(), N = grid[0].size();
        return solveBy2DTable(grid, K);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Matrix | Weekly Contest 475
Link  : https://leetcode.com/problems/maximum-path-score-in-a-grid/description/
