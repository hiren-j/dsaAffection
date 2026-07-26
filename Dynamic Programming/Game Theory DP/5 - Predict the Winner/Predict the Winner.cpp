// Code to check if player1 can win the game by assuming both player1 and player2 play optimally, if player1 can't then return false ~ coded by Hiren

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int dp[20][20][2];

    int solveWithMemo(const vector<int>& nums, int i, int j, bool p1Turn) {
        if(i > j)
            return 0;
        
        if(dp[i][j][p1Turn] != -1)
            return dp[i][j][p1Turn];

        if(p1Turn) {
            int pickStart = nums[i] + solveWithMemo(nums, i + 1, j, false);
            int pickEnd   = nums[j] + solveWithMemo(nums, i, j - 1, false);
            return dp[i][j][p1Turn] = max(pickStart, pickEnd);
        }
        else {
            int pickStart = solveWithMemo(nums, i + 1, j, true);
            int pickEnd   = solveWithMemo(nums, i, j - 1, true);
            return dp[i][j][p1Turn] = min(pickStart, pickEnd);
        }
    }

public:
    // O(N^2) & O(N^2)
    bool predictTheWinner(vector<int>& nums) {
        memset(dp, -1, sizeof(dp));
        const int p1Score = solveWithMemo(nums, 0, nums.size() - 1, true);
        const int p2Score = accumulate(begin(nums), end(nums), 0) - p1Score;
        return p1Score >= p2Score;
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    // O(N^2) & O(N^2)
    int solveBy3DTable(const vector<int>& nums) {
        int dp[21][20][2];
        memset(dp, -1, sizeof(dp));

        for(int i = n - 1; i >= 0; --i) {
            for(int j = 0; j <= n - 1; ++j) {
                for(int p1Turn = 0; p1Turn <= 1; ++p1Turn) {
                    if(i > j) {
                        dp[i][j][p1Turn] = 0;
                    }
                    else if(p1Turn) {
                        int pickStart = nums[i] + dp[i + 1][j][false];
                        int pickEnd   = nums[j] + (j - 1 < 0 ? 0 : dp[i][j - 1][false]);
                        dp[i][j][p1Turn] = max(pickStart, pickEnd);
                    }
                    else {
                        int pickStart = dp[i + 1][j][true];
                        int pickEnd   = j - 1 < 0 ? 0 : dp[i][j - 1][true];
                        dp[i][j][p1Turn] = min(pickStart, pickEnd);
                    }
                }
            }
        }

        return dp[0][n - 1][true];
    }

    // O(N^2) & O(N^2)
    int solveBy3DEnhanced(const vector<int>& nums) {
        int dp[21][20][2];
        memset(dp, 0, sizeof(dp));

        for(int i = n - 1; i >= 0; --i) {
            for(int j = i; j <= n - 1; ++j) {
                for(int p1Turn = 0; p1Turn <= 1; ++p1Turn) {
                    if(p1Turn) {
                        int pickStart = nums[i] + dp[i + 1][j][false];
                        int pickEnd   = nums[j] + (j - 1 < 0 ? 0 : dp[i][j - 1][false]);
                        dp[i][j][p1Turn] = max(pickStart, pickEnd);
                    }
                    else {
                        int pickStart = dp[i + 1][j][true];
                        int pickEnd   = (j - 1 < 0) ? 0 : dp[i][j - 1][true];
                        dp[i][j][p1Turn] = min(pickStart, pickEnd);
                    }
                }
            }
        }

        return dp[0][n - 1][true];
    }

    // O(N^2) & O(N)
    int solveBy2DTable(const vector<int>& nums) {
        int next[20][2], curr[20][2];
        memset(next, 0, sizeof(next));
        memset(curr, 0, sizeof(curr));

        for(int i = n - 1; i >= 0; --i) {
            for(int j = i; j <= n - 1; ++j) {
                for(int p1Turn = 0; p1Turn <= 1; ++p1Turn) {
                    if(p1Turn) {
                        int pickStart = nums[i] + next[j][false];
                        int pickEnd   = nums[j] + (j - 1 < 0 ? 0 : curr[j - 1][false]);
                        curr[j][p1Turn] = max(pickStart, pickEnd);
                    }
                    else {
                        int pickStart = next[j][true];
                        int pickEnd   = (j - 1 < 0) ? 0 : curr[j - 1][true];
                        curr[j][p1Turn] = min(pickStart, pickEnd);
                    }
                }
            }
            swap(next, curr);
        }

        return next[n - 1][true];
    }

public:
    bool predictTheWinner(vector<int>& nums) {
        n = nums.size();
        const int p1Score = solveBy2DTable(nums);
        const int p2Score = accumulate(begin(nums), end(nums), 0) - p1Score;
        return p1Score >= p2Score;
    }
};
    
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Math | Dynamic Programming | Recursion | Game Theory
Link  : https://leetcode.com/problems/predict-the-winner/
