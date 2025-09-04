// Code to find the number of strictly increasing paths in the grid such that you can start from any cell and end at any cell ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const vector<vector<int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    const int MOD = 1e9 + 7;
    int M, N;

    bool isValid(int R, int C) {
        return R >= 0 && C >= 0 && R < M && C < N;
    }

    int solveWithMemo(vector<vector<int>>& dp, const vector<vector<int>>& grid, int R, int C) {
        if(dp[R][C] != -1)
            return dp[R][C];

        int count = 1;

        for(const auto& D : dirs) {
            int newR = R + D[0];
            int newC = C + D[1];
            if(isValid(newR, newC) && grid[newR][newC] > grid[R][C]) {
                count = (count + solveWithMemo(dp, grid, newR, newC)) % MOD;
            }
        }

        return dp[R][C] = count;
    }

public:
    // O(M*N) & O(M*N)
    int countPaths(vector<vector<int>>& grid) {
        M = grid.size(), N = grid[0].size();
        int count = 0;

        vector<vector<int>> dp(M, vector<int>(N, -1));

        for(int R = 0; R < M; ++R)
            for(int C = 0; C < N; ++C)
                count = (count + solveWithMemo(dp, grid, R, C)) % MOD;

        return count;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Depth-First Search | Breadth-First Search | Graph | Topological Sort | Memoization | Matrix | Weekly Contest 300
Link  : https://leetcode.com/problems/number-of-increasing-paths-in-a-grid/description/
