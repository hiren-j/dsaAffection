// Code to find the maximum number of moves that you can perform in the grid ~ coded by Hiren

------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    vector<vector<int>> directions = {{-1,1}, {0,1}, {1,1}};
    int N, M;

    bool isValid(int R, int C) {
        return R >= 0 && R < N && C < M;
    }

    // O(3^(N*M)) & O(N+M)
    int solveWithoutMemo(vector<vector<int>>& grid, int R, int C) {
        if(!isValid(R, C))
            return INT_MIN;

        int maxMoves = 0;

        for(auto& dir : directions) {
            int reachRow  = R + dir[0];
            int reachCol  = C + dir[1];
            int currMoves = INT_MIN;

            if(isValid(reachRow, reachCol) && grid[reachRow][reachCol] > grid[R][C]) {
                currMoves = solveWithoutMemo(grid, reachRow, reachCol);
            }
            if(currMoves != INT_MIN) {
                maxMoves = max(maxMoves, 1 + currMoves);
            }
        }

        return maxMoves;
    }
    
    // O(3*N*M) & O(N*M + N+M)
    int solveWithMemo(vector<vector<int>>& memory, vector<vector<int>>& grid, int R, int C) {
        if(!isValid(R, C))
            return INT_MIN;

        if(memory[R][C] != -1)
            return memory[R][C];

        int maxMoves = 0;

        for(auto& dir : directions) {
            int reachRow  = R + dir[0];
            int reachCol  = C + dir[1];
            int currMoves = INT_MIN;

            if(isValid(reachRow, reachCol) && grid[reachRow][reachCol] > grid[R][C]) {
                currMoves = solveWithMemo(memory, grid, reachRow, reachCol);
            }
            if(currMoves != INT_MIN) {
                maxMoves = max(maxMoves, 1 + currMoves);
            }
        }

        return memory[R][C] = maxMoves;
    }

public:
    // Method to find the maximum number of moves that you can perform in the grid, using recursion with memoization :-
    int maxMoves(vector<vector<int>>& grid) {
        N = grid.size(), M = grid[0].size(); 

        int result = 0;

        vector<vector<int>> memory(N, vector<int>(M, -1));

        for(int R = 0; R < N; ++R)  
            result = max(result, solveWithMemo(memory, grid, R, 0));

        return result;
    }
};

------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Matrix
Link  : https://leetcode.com/problems/maximum-number-of-moves-in-a-grid/description/
