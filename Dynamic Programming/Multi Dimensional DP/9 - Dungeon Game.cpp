// Code to find the knight's minimum initial health so that he can rescue the princess ~ coded by Hiren

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int M, N;

    // O(2^(M*N)) & O(M+N)
    int solveWithoutMemo(vector<vector<int>>& dungeon, int R, int C) {
        // Edge case: If all the cells are exhausted then its not possible to play the game anymore
        if(R == M || C == N)
            return INT_MAX; // Requires to handle minimum health correctly

        // Edge case: If reached the bottom-right corner then rescue the princess. Calcuate and return the minimum health required for the knight to defeat the demon of the current room or not a demon then he requires minimum of single health to live
        if(R == M-1 && C == N-1)
            return (dungeon[R][C] <= 0) ? -dungeon[R][C] + 1 : 1;

        // There are always two possibilities the knight can perform at each room
        int moveRight = solveWithoutMemo(dungeon, R, C+1); // Is to move right
        int moveDown  = solveWithoutMemo(dungeon, R+1, C); // Is to move down

        // Stores the minimum health required for the knight to live at the current room
        int minHealthToLive = min(moveRight, moveDown) - dungeon[R][C];

        // Ensure the knight dies or not, if dies then he must need single health to live at the current room 
        return (minHealthToLive <= 0) ? 1 : minHealthToLive;
    }

    // O(2*M*N) & O(M*N + M+N)
    int solveWithMemo(vector<vector<int>>& memory, vector<vector<int>>& dungeon, int R, int C) {
        // Edge case: If all cells are exhausted then its not possible to play the game anymore
        if(R == M || C == N)
            return INT_MAX; // Requires to handle minimum health correctly

        // Edge case: If reached the bottom-right corner then rescue the princess. Calcuate and return the minimum health required for the knight to defeat the demon of the current room or not a demon then he requires minimum of single health to live
        if(R == M-1 && C == N-1)
            return (dungeon[R][C] <= 0) ? -dungeon[R][C] + 1 : 1;

        if(memory[R][C] != -1)
            return memory[R][C];

        // There are always two possibilities the knight can perform at each room
        int moveRight = solveWithMemo(memory, dungeon, R, C+1); // Is to move right
        int moveDown  = solveWithMemo(memory, dungeon, R+1, C); // Is to move down

        // Stores the minimum health required for the knight to live at the current room
        int minHealthToLive = min(moveRight, moveDown) - dungeon[R][C];

        // Ensure the knight dies or not, if dies then he must need single health to live at the current room 
        return memory[R][C] = (minHealthToLive <= 0) ? 1 : minHealthToLive;
    }

public:
    // Method to find knight's minimum initial health, using recursion with memoization - O(M*N) & O(M*N)
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        M = dungeon.size(), N = dungeon[0].size();
        vector<vector<int>> memory(M, vector<int>(N, -1));
        return solveWithMemo(memory, dungeon, 0, 0);
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int M, N;

    // O(M*N) & O(M*N)
    int solveWith2DTable(vector<vector<int>>& dungeon) {
        vector<vector<int>> dp(M+1, vector<int>(N+1, INT_MAX));

        // Initialize second edge case
        dp[M-1][N-1] = (dungeon[M-1][N-1] <= 0) ? -dungeon[M-1][N-1] + 1 : 1;

        for(int R = M-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                if(R == M-1 && C == N-1)
                    continue;
                int moveRight = dp[R][C+1]; 
                int moveDown  = dp[R+1][C]; 
                int minHealthToLive = min(moveRight, moveDown) - dungeon[R][C];
                dp[R][C] = (minHealthToLive <= 0) ? 1 : minHealthToLive;   
            }
        }

        return dp[0][0];
    }

    // O(M*N) & O(2*N)
    int solveWith1DTable(vector<vector<int>>& dungeon) {
        vector<int> nextRow(N+1, INT_MAX), currRow(N+1, INT_MAX);

        // Initialize second edge case
        currRow[N-1] = (dungeon[M-1][N-1] <= 0) ? -dungeon[M-1][N-1] + 1 : 1;

        for(int R = M-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                if(R == M-1 && C == N-1)
                    continue;
                int moveRight = currRow[C+1]; 
                int moveDown  = nextRow[C]; 
                int minHealthToLive = min(moveRight, moveDown) - dungeon[R][C];
                currRow[C] = (minHealthToLive <= 0) ? 1 : minHealthToLive;   
            }
            swap(nextRow, currRow);
        }

        return nextRow[0];
    }

    // O(M*N) & O(1)
    int solveWithoutTable(vector<vector<int>>& dungeon) {
        // Initialize second edge case
        dungeon[M-1][N-1] = (dungeon[M-1][N-1] <= 0) ? -dungeon[M-1][N-1] + 1 : 1;

        for(int R = M-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                if(R == M-1 && C == N-1)
                    continue;
                int moveRight = (C+1 < N) ? dungeon[R][C+1] : INT_MAX; 
                int moveDown  = (R+1 < M) ? dungeon[R+1][C] : INT_MAX; 
                int minHealthToLive = min(moveRight, moveDown) - dungeon[R][C];
                dungeon[R][C] = (minHealthToLive <= 0) ? 1 : minHealthToLive;   
            }
        }

        return dungeon[0][0];
    }

public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        M = dungeon.size(), N = dungeon[0].size();
        return solveWithoutTable(dungeon);
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Matrix
Link  : https://leetcode.com/problems/dungeon-game/description/
