// Code to find the maximum score that Alice can get ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int dp[500][500];
    int n;

    int getIntervalSum(const vector<int>& nums, int i, int j) {
        int sum = 0;
        while(i <= j) sum += nums[i++];
        return sum;
    }

    int solveWithMemo(const vector<int>& nums, int i, int j) {
        if(i >= j)
            return 0;
        
        if(dp[i][j] != -1)
            return dp[i][j];

        int totalSum = getIntervalSum(nums, i, j);
        int part1Sum = 0;
        int maxScore = 0;

        for(int ptr = i; ptr <= j; ++ptr) {
            part1Sum += nums[ptr];
            const int part2Sum = totalSum - part1Sum;

            if(part1Sum > part2Sum) {
                const int next = solveWithMemo(nums, ptr + 1, j);
                maxScore = max(maxScore, next + part2Sum);
            }
            else if(part2Sum > part1Sum) {
                const int next = solveWithMemo(nums, i, ptr);
                maxScore = max(maxScore, next + part1Sum);
            }
            else {
                const int next1 = solveWithMemo(nums, i, ptr);
                const int next2 = solveWithMemo(nums, ptr + 1, j);
                maxScore = max(maxScore, next1 + part1Sum);
                maxScore = max(maxScore, next2 + part2Sum);
            }
        }

        return dp[i][j] = maxScore;
    }

public:
    int stoneGameV(vector<int>& nums) {
        n = nums.size();
        memset(dp, -1, sizeof(dp));
        return solveWithMemo(nums, 0, n - 1);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  
class BottomUp {
    int getIntervalSum(const vector<int>& nums, int i, int j) {
        int sum = 0;
        while(i <= j) sum += nums[i++];
        return sum;
    }

public:
    int stoneGameV(vector<int>& nums) {
        const int n = nums.size();

        int dp[501][501];
        memset(dp, 0, sizeof(dp));

        for(int i = n - 1; i >= 0; --i) {
            for(int j = i + 1; j <= n - 1; ++j) {
                int totalSum = getIntervalSum(nums, i, j);
                int part1Sum = 0;
                int maxScore = 0;

                for(int ptr = i; ptr <= j; ++ptr) {
                    part1Sum += nums[ptr];
                    const int part2Sum = totalSum - part1Sum;

                    if(part1Sum > part2Sum) {
                        const int next = dp[ptr + 1][j];
                        maxScore = max(maxScore, next + part2Sum);
                    }
                    else if(part2Sum > part1Sum) {
                        const int next = dp[i][ptr];
                        maxScore = max(maxScore, next + part1Sum);
                    }
                    else {
                        const int next1 = dp[i][ptr];
                        const int next2 = dp[ptr + 1][j];
                        maxScore = max(maxScore, next1 + part1Sum);
                        maxScore = max(maxScore, next2 + part2Sum);
                    }
                }

                dp[i][j] = maxScore;
            }
        }

        return dp[0][n - 1];
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Game Theory
Link  : https://leetcode.com/problems/stone-game-v/description/
