// Code to check if Alice can win the game by assuming both Alice and Bob play optimally, if Alice can't then return false ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to check if Alice can win the game or not, using recursion with memoization - O(N^2) & O(N^2)
    bool divisorGame(int n) {
        vector<vector<int>> memory(n + 1, vector<int>(2, -1));
        return solveWithMemo(memory, n, true);
    }

private:
    // O(N*N*2) & O(N*2 + N)
    bool solveWithMemo(vector<vector<int>>& memory, int n, bool aliceTurn) {
        // Edge case: Both Alice and Bob can replace 'n' and its mentioned that they could choose an integer 'x' such (0 < x < n), So if n is 1 and if its Bob's turn then he can't make a move hence Alice wins the game
        if(n == 1)
            return !aliceTurn;

        // Memoization table: If the current state is already computed then return the computed value 
        if(memory[n][aliceTurn] != -1)
            return memory[n][aliceTurn];

        // Tracks Alice can win or not
        bool canWin = false;

        for(int x = 1; x < n; ++x) {
            if(n % x != 0)
                continue;
            
            // If its Alice's turn then she absolutely wanted to win, so if Alice can win the game by any of the possibility then return true
            if(aliceTurn) {
                canWin = solveWithMemo(memory, n - x, false);
                if(canWin) break;
            }
            // If its Bob's turn then he absolutely wanted Alice to lose, so if she lose the game by any of the possibility then Bob will return false
            else {
                canWin = solveWithMemo(memory, n - x, true);
                if(!canWin) break;
            }
        }

        // Store the result value to the memoization table and then return it
        return memory[n][aliceTurn] = canWin;
    }

    // O(N^N) & O(N)
    bool solveWithoutMemo(int n, bool aliceTurn) {
        // Edge case: Both Alice and Bob can replace 'n' and its mentioned that they could choose an integer 'x' such (0 < x < n), So if n is 1 and if its Bob's turn then he can't make a move hence Alice wins the game
        if(n == 1)
            return !aliceTurn;

        // Tracks Alice can win or not
        bool canWin = false;

        for(int x = 1; x < n; ++x) {
            if(n % x != 0)
                continue;
            
            // If its Alice's turn then she absolutely wanted to win, so if Alice can win the game by any of the possibility then return true
            if(aliceTurn) {
                canWin = solveWithoutMemo(n - x, false);
                if(canWin) break;
            }
            // If its Bob's turn then he absolutely wanted Alice to lose, so if she lose the game by any of the possibility then Bob will return false
            else {
                canWin = solveWithoutMemo(n - x, true);
                if(!canWin) break;
            }
        }

        // Return the result value
        return canWin;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  
class BottomUp {
public:
    // Method to check if Alice can win the game or not, using 2D tabulation - O(N^2) & O(N^2)
    bool divisorGame(int n) {
        // 2D DP table
        vector<vector<bool>> dp(n + 1, vector<bool>(2, false));

        // Initialize the edge case
        dp[1][0] = true;

        // Fill the rest of the table
        for(int num = 2; num <= n; ++num) {
            for(int aliceTurn = 0; aliceTurn <= 1; ++aliceTurn) {
                bool canWin = false;

                for(int x = 1; x < num; ++x) {
                    if(num % x != 0)
                        continue;

                    if(aliceTurn) {
                        canWin = dp[num - x][false];
                        if(canWin) break;
                    }
                    else {
                        canWin = dp[num - x][true];
                        if(!canWin) break;
                    }
                }

                dp[num][aliceTurn] = canWin;
            }
        }

        // Return the result value
        return dp[n][true];
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Math | Dynamic Programming | Brainteaser | Game Theory
Link  : https://leetcode.com/problems/divisor-game/description/?envType=problem-list-v2&envId=game-theory
