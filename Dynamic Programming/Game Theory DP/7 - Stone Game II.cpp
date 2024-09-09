// Code to find the maximum number of stones Alice can get. Alice and Bob take turns, with Alice starting first. On each player's turn, that player can take all the stones in the first X remaining piles, where 1 <= X <= 2M. Then, we set M = max(M, X). Initially, M = 1. The game continues until all the stones have been taken. Assume Alice and Bob play optimally ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to find the maximum number of stones Alice can get, using recursion with memoization - O(N^3) & O(N^2)
    int stoneGameII(vector<int>& piles) {
        int N = piles.size();
        vector<vector<vector<int>>> memory(N, vector<vector<int>>(N+1, vector<int>(2, -1)));
        return solveWithMemo(memory, piles, N, 1, 0, true);      
    }

private:
    // O(N*N*N*2) & O(N*N*2 + N)
    int solveWithMemo(vector<vector<vector<int>>>& memory, vector<int>& piles, int N, int M, int startIndex, bool aliceTurn) {
        // Edge case: If all the piles are exhausted then Alice can't take more stones
        if(startIndex == N)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[startIndex][M][aliceTurn] != -1)
            return memory[startIndex][M][aliceTurn];

        int maxStones  = (aliceTurn) ? 0 : INT_MAX;
        int currStones = 0;
        int end = min(startIndex + 2*M, N);

        for(int index = startIndex; index < end; ++index) {
            currStones += piles[index];
            int X = index - startIndex + 1;

            // If its Alice's turn then she absolutely wanted to win, So for that she wants to maximize her score, so she will take the maximum value from all the possibility
            if(aliceTurn) {
                int nextStones = solveWithMemo(memory, piles, N, max(M, X), index + 1, false);
                maxStones = max(maxStones, nextStones + currStones);
            }
            // If its Bob's turn then he absolutely wanted alice to lose, So for that he wants Alice to minimize her score, so he will take the minimum value from all the possibility
            else {
                int nextStones = solveWithMemo(memory, piles, N, max(M, X), index + 1, true);
                maxStones = min(maxStones, nextStones);
            }
        }

        // Store the result value to the memoization table and then return it
        return memory[startIndex][M][aliceTurn] = maxStones;
    }

    // O(N^N) & O(N)
    int solveWithoutMemo(vector<int>& piles, int N, int M, int startIndex, bool aliceTurn) {
        // Edge case: If all the piles are exhausted then Alice can't take more stones
        if(startIndex == N)
            return 0;

        int maxStones  = (aliceTurn) ? 0 : INT_MAX;
        int currStones = 0;
        int end = min(startIndex + 2*M, N);

        for(int index = startIndex; index < end; ++index) {
            currStones += piles[index];
            int X = index - startIndex + 1;

            // If its Alice's turn then she absolutely wanted to win, So for that she wants to maximize her score, so she will take the maximum value from all the possibility
            if(aliceTurn) {
                int nextStones = solveWithoutMemo(piles, N, max(M, X), index + 1, false);
                maxStones = max(maxStones, nextStones + currStones);
            }
            // If its Bob's turn then he absolutely wanted alice to lose, So for that he wants Alice to minimize her score, so he will take the minimum value from all the possibility
            else {
                int nextStones = solveWithoutMemo(piles, N, max(M, X), index + 1, true);
                maxStones = min(maxStones, nextStones);
            }
        }

        return maxStones;
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 

class BottomUp {
public:
    // Method to find the maximum number of stones Alice can get, using 3D tabulation - O(N^3) & O(N^2)
    int stoneGameII(vector<int>& piles) {
        int N = piles.size();

        // 3D DP table
        vector<vector<vector<int>>> dp(N+1, vector<vector<int>>(N+1, vector<int>(2, 0)));

        // Fill the table
        for(int startIndex = N-1; startIndex >= 0; --startIndex) {
            for(int curr_M = N; curr_M >= 1; --curr_M) {
                for(int aliceTurn = 0; aliceTurn <= 1; ++aliceTurn) {
                    int maxStones  = (aliceTurn) ? 0 : INT_MAX;
                    int currStones = 0;
                    int end = min(startIndex + 2*curr_M, N);

                    for(int index = startIndex; index < end; ++index) {
                        currStones += piles[index];
                        int X = index - startIndex + 1;

                        if(aliceTurn) {
                            int nextStones = dp[index + 1][max(curr_M, X)][false];
                            maxStones = max(maxStones, nextStones + currStones);
                        }
                        else {
                            int nextStones = dp[index + 1][max(curr_M, X)][true];
                            maxStones = min(maxStones, nextStones);
                        }
                    }

                    dp[startIndex][curr_M][aliceTurn] = maxStones;
                }
            }
        }

        // Return the result value
        return dp[0][1][true];      
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  
Topics: Array | Math | Dynamic Programming | Prefix Sum | Game Theory
Link  : https://leetcode.com/problems/stone-game-ii/description/
