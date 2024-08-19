// Code to find the maximum coins you can collect by bursting the balloons wisely. If you burst the ith balloon, you will get nums[i - 1] * nums[i] * nums[i + 1] coins. If i - 1 or i + 1 goes out of bounds of the array, then treat it as if there is a balloon with a 1 painted on it ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
    DON'T IGNORE MUST READ (REGARDING THE INTUITION BEHIND THE CODE SEGMENT):

        for(int k = i; k <= j; ++k) {
            int currCoins = nums[i - 1] * nums[k] * nums[j + 1]
                         + solveWithMemo(memory, nums, i, k - 1)
                         + solveWithMemo(memory, nums, k + 1, j);
        }

        Initially assume that you have no balloon. When you consider the kth balloon for the first time then logically if it's the first balloon then for it there should be no balloon on the left and the right side of it. 
        So the insertion of 1 that we did at the front and end of the array will help us in this case.
        
        The multiplication with nums[i - 1] and nums[j + 1] indicates the cost of the left and right balloon respectively. 
        As i said that when we choose the kth balloon, more clearly the first balloon of the sequence and from it when we call the next recursion then in it whichever the balloon we'll pick will be treated as the second balloon of the sequence, 
        so then based on the sequence you've to consider the cost of correct left and right balloon and for it the multiplication with nums[i - 1] and nums[j + 1] is required.
*/

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to find the maximum coins you can get by bursting balloons, using recursion with memoization - O(N^3) & O(N^2)
    int getMaximumCoins(vector<int>& nums) {
        nums.insert(begin(nums), 1);
        nums.push_back(1);
        int n = nums.size();
        vector<vector<int>> memory(n-1, vector<int>(n-1, -1));
        return solveWithMemo(memory, nums, 1, n-2);
    }

private:
    // O(N * 2*N*N) & O(N*N + N)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& nums, int i, int j) {
        // Edge case: If there are no balloons left then you can't burst more
        if(i > j)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[i][j] != -1)
            return memory[i][j];

        int maxCoins = 0;

        // Consider each balloon as an unique start point and from a particular consideration find the total coins to burst all the balloons. Among all the considerations choose the one which gives the maximum coins 
        for(int k = i; k <= j; ++k) {
            int currCoins = nums[i - 1] * nums[k] * nums[j + 1]
                          + solveWithMemo(memory, nums, i, k - 1)
                          + solveWithMemo(memory, nums, k + 1, j);
            maxCoins = max(maxCoins, currCoins);
        }

        // Store the result value to the memoization table and then return it
        return memory[i][j] = maxCoins;
    }

    // O(N * 2^N) & O(N)
    int solveWithoutMemo(vector<int>& nums, int i, int j) {
        // Edge case: If there are no balloons left then you can't burst more
        if(i > j)
            return 0;

        int maxCoins = 0;

        // Consider each balloon as an unique start point and from a particular consideration find the total coins to burst all the balloons. Among all the considerations choose the one which gives the maximum coins 
        for(int k = i; k <= j; ++k) {
            int currCoins = nums[i - 1] * nums[k] * nums[j + 1]
                          + solveWithoutMemo(nums, i, k - 1)
                          + solveWithoutMemo(nums, k + 1, j);
            maxCoins = max(maxCoins, currCoins);
        }

        return maxCoins;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // #1 Method to find the maximum coins you can get by bursting balloons, using 2D tabulation - O(N^3) & O(N^2)
    int getMaximumCoins_V1(vector<int>& nums) {
        nums.insert(begin(nums), 1);
        nums.push_back(1);

        int n = nums.size();

        // 2D DP table
        vector<vector<int>> dp(n, vector<int>(n, INT_MAX));

        // Fill the table
        for(int i = n-2; i >= 1; --i) {
            for(int j = 1; j <= n-2; ++j) {
                // Initialize the edge case
                if(i > j) {
                    dp[i][j] = 0;
                }
                else {
                    int maxCoins = 0;

                    for(int k = i; k <= j; ++k) {
                        int currCoins = nums[i - 1] * nums[k] * nums[j + 1];
                        int costLeft  = dp[i][k - 1];
                        int costRight = dp[k + 1][j];
                        if(costLeft != INT_MAX) currCoins += costLeft;
                        if(costRight != INT_MAX) currCoins += costRight;
                        maxCoins = max(maxCoins, currCoins);
                    }

                    dp[i][j] = maxCoins;
                }
            }
        }

        // Return the result value
        return dp[1][n - 2];
    }

    // #2 Method to find the maximum coins you can get by bursting balloons, using 2D tabulation - O(N^3) & O(N^2)
    int getMaximumCoins_V2(vector<int>& nums) {
        nums.insert(begin(nums), 1);
        nums.push_back(1);

        int n = nums.size();

        // 2D DP table
        vector<vector<int>> dp(n, vector<int>(n, 0));

        // Fill the table
        for(int i = n-2; i >= 1; --i) {
            for(int j = 1; j <= n-2; ++j) {
                // Ensure to handle the edge case
                if(i > j) 
                    continue;

                for(int k = i; k <= j; ++k) {
                    int currCoins = nums[i - 1] * nums[k] * nums[j + 1]
                                  + dp[i][k - 1]
                                  + dp[k + 1][j];
                    dp[i][j] = max(dp[i][j], currCoins);
                }
            }
        }

        // Return the result value
        return dp[1][n - 2];
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/burst-balloons/description/
