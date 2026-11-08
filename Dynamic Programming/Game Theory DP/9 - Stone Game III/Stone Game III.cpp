// Code to check whether Alice can win the game or not. Alice play against Bob in an alternating way. Alice and Bob take turns, with Alice starting first. On each player's turn, that player can take 1, 2, or 3 stones from the first remaining stones in the row. The score of each player is the sum of the values of the stones taken. The objective of the game is to end with the highest score, and the winner is the player with the highest score and there could be a tie. The score of each player is 0 initially. Note that both the players are playing optimally ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    // O(3^N) & O(N)
    int solveWithoutMemo(const vector<int>& nums, int start, bool aliceTurn) {
        if(start == n)
            return 0;
        
        int result = aliceTurn ? INT_MIN : INT_MAX;
        int sum = 0;  

        for(int i = start; i < min(start + 3, n); ++i) {
            if(aliceTurn) {
                sum += nums[i];
                int next = solveWithoutMemo(nums, i + 1, false);
                result = max(result, next + sum);
            }
            else {
                int next = solveWithoutMemo(nums, i + 1, true);
                result = min(result, next);
            }
        }

        return result;
    }

    // O(N) & O(N)
    int solveWithMemo(vector<vector<int>>& dp, const vector<int>& nums, int start, bool aliceTurn) {
        if(start == n)
            return 0;

        if(dp[start][aliceTurn] != -1)
            return dp[start][aliceTurn];
        
        int result = aliceTurn ? INT_MIN : INT_MAX;
        int sum = 0;  

        for(int i = start; i < min(start + 3, n); ++i) {
            if(aliceTurn) {
                sum += nums[i];
                int next = solveWithMemo(dp, nums, i + 1, false);
                result = max(result, next + sum);
            }
            else {
                int next = solveWithMemo(dp, nums, i + 1, true);
                result = min(result, next);
            }
        }

        return dp[start][aliceTurn] = result;
    }

public:
    string stoneGameIII(vector<int>& nums) {
        n = nums.size(); 
        vector<vector<int>> dp(n, vector<int>(2, -1));
        int aliceScore = solveWithMemo(dp, nums, 0, true);
        int bobScore   = accumulate(begin(nums), end(nums), 0) - aliceScore;
        return aliceScore >= bobScore ? (aliceScore == bobScore ? "Tie" : "Alice") : "Bob";
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    // O(N) & O(N)
    int solveBy2DTable(const vector<int>& nums) {
        vector<vector<int>> dp(n + 1, vector<int>(2, -1));
        dp[n][0] = 0;
        dp[n][1] = 0;

        for(int start = n - 1; start >= 0; --start) {
            for(int aliceTurn = 0; aliceTurn <= 1; ++aliceTurn) {
                int result = aliceTurn ? INT_MIN : INT_MAX;
                int sum = 0;  

                for(int i = start; i < min(start + 3, n); ++i) {
                    if(aliceTurn) {
                        sum += nums[i];
                        int next = dp[i + 1][false];
                        result = max(result, next + sum);
                    }
                    else {
                        int next = dp[i + 1][true];
                        result = min(result, next);
                    }
                }

                dp[start][aliceTurn] = result;
            }
        }

        return dp[0][true];
    }

public:
    string stoneGameIII(vector<int>& nums) {
        n = nums.size(); 
        int aliceScore = solveBy2DTable(nums);
        int bobScore   = accumulate(begin(nums), end(nums), 0) - aliceScore;    
        return aliceScore >= bobScore ? (aliceScore == bobScore ? "Tie" : "Alice") : "Bob";
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Math | Dynamic Programming | Game Theory
Link  : https://leetcode.com/problems/stone-game-iii/description/?envType=problem-list-v2&envId=game-theory
