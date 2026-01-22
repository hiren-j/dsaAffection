
// Code to find the number of strictly increasing paths in the grid such that you can start from any cell and end at any cell ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------

/*
    DON'T IGNORE MUST READ: For the bottom-up solution of this problem, I created it and run it but it didn't passed all the testcases.
                            So I would say there are only 3 problems in the whole series which doesn't contain the bottom-up solution 
                            due to this reason. These 3 problems lies in this folder (Multi-Dimensional DP Folder).
*/
    
-------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const vector<vector<int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    const int MOD = 1e9 + 7;
    int M, N;

    bool isValid(int R, int C) {
        return R >= 0 && C >= 0 && R < M && C < N;
    }

    // O((M*N) * 3^(M*N)) & O(M*N)
    int solveWithoutMemo(const vector<vector<int>>& grid, int R, int C) {
        int count = 1;

        for(const auto& D : dirs) {
            const int newR = R + D[0];
            const int newC = C + D[1];

            if(isValid(newR, newC) && grid[newR][newC] > grid[R][C]) {
                int nextCount = solveWithoutMemo(grid, newR, newC);
                count = (count + nextCount) % MOD;
            }
        }

        return count;
    }

    // O(4*M*N) & O(2*M*N)
    int solveWithMemo(vector<vector<int>>& dp, const vector<vector<int>>& grid, int R, int C) {
        if(dp[R][C] != -1)
            return dp[R][C];

        int count = 1;

        for(const auto& D : dirs) {
            const int newR = R + D[0];
            const int newC = C + D[1];

            if(isValid(newR, newC) && grid[newR][newC] > grid[R][C]) {
                int nextCount = solveWithMemo(dp, grid, newR, newC);
                count = (count + nextCount) % MOD;
            }
        }

        return dp[R][C] = count;
    }

public:
    int countPaths(vector<vector<int>>& grid) {
        M = grid.size(), N = grid[0].size();

        vector<vector<int>> dp(M, vector<int>(N, -1));
        int result = 0;
        
        for(int R = 0; R < M; ++R)
            for(int C = 0; C < N; ++C)
                result = (result + solveWithMemo(dp, grid, R, C)) % MOD;

        return result;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Combinatorics | Depth-First Search | Breadth-First Search | Graph | Topological Sort | Memoization | Matrix | Weekly Contest 300
Link  : https://leetcode.com/problems/number-of-increasing-paths-in-a-grid/description/
