// Code to determine whether Geek will win the game or not. The player who picks the last coin wins the game. Assume both the players are playing optimally ~ coded by Hiren

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to determine whether Geek will win the game or not, using recursion with memoization - O(N) & O(N)
    bool canGeekWin(int n, int x, int y) {
        vector<vector<int>> memory(n + 1, vector<int>(2, -1));
        return solveWithMemo(memory, n, x, y, true);
    }
    
private:    
    // O(3*N*2) & O(N*2 + N)
    bool solveWithMemo(vector<vector<int>>& memory, int n, int x, int y, bool geekTurn) {
        // Edge case: If its the friend's turn and previously if Geek picked the last coin then the Geek wins  
        if(n == 0)
            return !geekTurn;
        
        // Edge case: If there are no coins and if its Geek's turn then he wins, else he loses
        if(n < 0)
            return geekTurn;
        
        // Memoization table: If the current state is already computed then return the computed value
        if(memory[n][geekTurn] != -1)
            return memory[n][geekTurn];
        
        // If its Geek's turn then he have three posibilities to perform on 'n' 
        if(geekTurn) {
            bool pickXCoin = solveWithMemo(memory, n - x, x, y, false); // Is to pick x coins from it
            bool pickYCoin = solveWithMemo(memory, n - y, x, y, false); // Is to pick y coins from it
            bool pick1Coin = solveWithMemo(memory, n - 1, x, y, false); // Is to pick 1 coin from it 
            return memory[n][geekTurn] = (pickXCoin || pickYCoin || pick1Coin); // If its Geek's turn then he absolutely wanted to win, so if he can win the game by any of the possibility then return true
        }
        // If its friend's turn then he have three posibilities to perform on 'n' 
        else {
            bool pickXCoin = solveWithMemo(memory, n - x, x, y, true); // Is to pick x coins from it
            bool pickYCoin = solveWithMemo(memory, n - y, x, y, true); // Is to pick y coins from it
            bool pick1Coin = solveWithMemo(memory, n - 1, x, y, true); // Is to pick 1 coin from it 
            return memory[n][geekTurn] = !(!pickXCoin || !pickYCoin || !pick1Coin); // If its friend's turn then he absolutely wanted the Geek to lose, so if Geek loses the game by any of the possibility then the friend will return false
        }
    }

    // O(3^N) & O(N)
    bool solveWithoutMemo(int n, int x, int y, bool geekTurn) {
        // Edge case: If its the friend's turn and previously if Geek picked the last coin then the Geek wins  
        if(n == 0)
            return !geekTurn;
        
        // Edge case: If there are no coins and if its Geek's turn then he wins, else he loses
        if(n < 0)
            return geekTurn;
        
        // If its Geek's turn then he have three posibilities to perform on 'n' 
        if(geekTurn) {
            bool pickXCoin = solveWithoutMemo(n - x, x, y, false); // Is to pick x coins from it
            bool pickYCoin = solveWithoutMemo(n - y, x, y, false); // Is to pick y coins from it
            bool pick1Coin = solveWithoutMemo(n - 1, x, y, false); // Is to pick 1 coin from it 
            return (pickXCoin || pickYCoin || pick1Coin); // If its Geek's turn then he absolutely wanted to win, so if he can win the game by any of the possibility then return true
        }
        // If its friend's turn then he have three posibilities to perform on 'n' 
        else {
            bool pickXCoin = solveWithoutMemo(n - x, x, y, true); // Is to pick x coins from it
            bool pickYCoin = solveWithoutMemo(n - y, x, y, true); // Is to pick y coins from it
            bool pick1Coin = solveWithoutMemo(n - 1, x, y, true); // Is to pick 1 coin from it 
            return !(!pickXCoin || !pickYCoin || !pick1Coin); // If its friend's turn then he absolutely wanted the Geek to lose, so if Geek loses the game by any of the possibility then the friend will return false
        }
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to determine whether Geek will win the game or not, using 2D tabulation - O(N) & O(N)
    bool canGeekWin(int n, int x, int y) {
        // 2D DP table
        vector<vector<bool>> dp(n + 1, vector<bool>(2, false));

        // Initialize the first edge case
        dp[0][0] = true;

        // Fill the rest of the table
        for(int coins = 1; coins <= n; ++coins) {
            for(int geekTurn = 0; geekTurn <= 1; ++geekTurn) {
                if(geekTurn) {
                    bool pickXCoin = (coins - x >= 0) ? dp[coins - x][false] : false;
                    bool pickYCoin = (coins - y >= 0) ? dp[coins - y][false] : false;
                    bool pick1Coin = (coins - 1 >= 0) ? dp[coins - 1][false] : false;
                    dp[coins][geekTurn] = (pickXCoin || pickYCoin || pick1Coin);
                }
                else {
                    bool pickXCoin = (coins - x >= 0) ? dp[coins - x][true] : true;
                    bool pickYCoin = (coins - y >= 0) ? dp[coins - y][true] : true;
                    bool pick1Coin = (coins - 1 >= 0) ? dp[coins - 1][true] : true;
                    dp[coins][geekTurn] = !(!pickXCoin || !pickYCoin || !pick1Coin);
                }
            }
        }

        // Return the result value
        return dp[n][true];
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Brainteaser | Game Theory | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/geek-and-its-game-of-coins4043/1?itm_source=geeksforgeeks&itm_medium=article&itm_campaign=practice_card
