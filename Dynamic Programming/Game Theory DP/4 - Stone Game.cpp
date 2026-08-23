// Code to check if Alice can win the game by assuming both Alice and Bob play optimally, if Alice can't then return false ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int dp[500][500][2];
    int n;

    int solveWithMemo(const vector<int>& nums, int i, int j, bool aliceTurn) {
        if(i > j)
            return 0;

        if(dp[i][j][aliceTurn] != -1)
            return dp[i][j][aliceTurn];

        if(aliceTurn) {
            const int pickStart = nums[i] + solveWithMemo(nums, i + 1, j, false);
            const int pickEnd   = nums[j] + solveWithMemo(nums, i, j - 1, false);
            return dp[i][j][aliceTurn] = max(pickStart, pickEnd);
        }
        else {
            const int pickStart = solveWithMemo(nums, i + 1, j, true);
            const int pickEnd   = solveWithMemo(nums, i, j - 1, true);
            return dp[i][j][aliceTurn] = min(pickStart, pickEnd);
        }
    }

public:
    // O(N^2) & O(N^2)
    bool stoneGame(vector<int>& nums) {
        n = nums.size();
        memset(dp, -1, sizeof(dp));
        const int aliceScore = solveWithMemo(nums, 0, n - 1, true);
        const int bobScore   = accumulate(begin(nums), end(nums), 0) - aliceScore;
        return aliceScore >= bobScore;
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    // O(N^2) & O(N^2)
    int solveBy3DTable(const vector<int>& nums) {
        int dp[500][500][2];
        memset(dp, 0, sizeof(dp));

        for(int i = n - 1; i >= 0; --i) {
            for(int j = i + 1; j <= n - 1; ++j) {
                for(int aliceTurn = 0; aliceTurn <= 1; ++aliceTurn) {
                    if(aliceTurn) {
                        int pickStart = nums[i] + dp[i + 1][j][false];
                        int pickEnd   = nums[j] + dp[i][j - 1][false];
                        dp[i][j][aliceTurn] = max(pickStart, pickEnd);
                    }
                    else {
                        int pickStart = dp[i + 1][j][true];
                        int pickEnd   = dp[i][j - 1][true];
                        dp[i][j][aliceTurn] = min(pickStart, pickEnd);
                    }
                }
            }
        }

        return dp[0][n - 1][true];
    }

    // O(N^2) & O(N)
    int solveBy2DTable(const vector<int>& nums) {
        int next[500][2], curr[500][2];
        memset(next, 0, sizeof(next));
        memset(curr, 0, sizeof(curr));

        for(int i = n - 1; i >= 0; --i) {
            for(int j = i + 1; j <= n - 1; ++j) {
                for(int aliceTurn = 0; aliceTurn <= 1; ++aliceTurn) {
                    if(aliceTurn) {
                        int pickStart = nums[i] + next[j][false];
                        int pickEnd   = nums[j] + curr[j - 1][false];
                        curr[j][aliceTurn] = max(pickStart, pickEnd);
                    }
                    else {
                        int pickStart = next[j][true];
                        int pickEnd   = curr[j - 1][true];
                        curr[j][aliceTurn] = min(pickStart, pickEnd);
                    }
                }
            }
            swap(next, curr);
        }

        return next[n - 1][true];
    }

public:
    bool stoneGame(vector<int>& nums) {
        n = nums.size();
        const int aliceScore = solveBy2DTable(nums);
        const int bobScore   = accumulate(begin(nums), end(nums), 0) - aliceScore;
        return aliceScore >= bobScore;
    }
}; 

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Maths {
public:
    // O(1) & O(1)
    bool stoneGame(vector<int>& piles) {
        /* 
            Alice always wins the game : Read the reason with below example

            1. We know both Alice and Bob have two possibility - Is that the player with its turn can take the entire pile of stones either from the beginning or from the end of the row

            2. If you notice the player who starts the game have two possibilities:-
                - If he chooses the possibility of taking the entire piles from extreme left then this player will absolutely be moving in odd fashion (1-based indexing)
                - If he chooses the possibility of taking the entire piles from extreme right then this player will absolutely be moving in even fashion (1-based indexing)

            3. So, Lets understand with the Example : [5, 2, 3, 3]
                                            Position - 1  2  3  4

                -> We know Alice always starts the game, then the odd fashion result of Alice will be :-
                        Alice Stones - [5, 3] (Maximum is 8)
                        Bob Stones   - [2, 3] (Maximum is 5)

                -> We know Alice always starts the game, then the even fashion result of Alice will be :-
                        Alice Stones - [3, 2] (Maximum is 5) 
                        Bob Stones   - [3, 5] (Maximum is 8)


            Imp: If you notice, you can see both the players have choosen all positions from both the possibility,
                 that means Alice and Bob both got the maximum results, So both are going to Win? No, Its not like that. Both the players are playing optimally and we know that Alice will start the game, so Alice knows at any point of time to consider which pile of stone and which not. So if she's getting maximum stones by starting from the extreme left then she will choose this possibility or if she's getting maximum from the extreme right then she will choose this possibility. 
                 In conclusion, Alice will always pick the possibility which will lead to the maximum stones or could say Alice will always start the game from the possibility which will lead to the maximum stones. So this how Alice always win the game
        */

        return true;
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Math | Dynamic Programming | Game Theory
Link  : https://leetcode.com/problems/stone-game/
