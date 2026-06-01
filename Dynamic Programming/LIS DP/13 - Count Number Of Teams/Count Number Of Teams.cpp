// Code to find the number of teams you can form under the given conditions ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int dp[1000][1001][4]; // Use static array to reduce time overhead of vectors (dynamic array)
    bool findInc = false;
    int n;

    int solveWithMemo(const vector<int>& rating, int i, int prev, int k) {
        if(k < 0)
            return 0;
        
        if(i == n)
            return (k == 0) ? 1 : 0;
        
        if(dp[i][prev][k] != -1)
            return dp[i][prev][k];
        
        int currSkip = solveWithMemo(rating, i + 1, prev, k);
        int currTake = 0;

        if(prev == n || (findInc && rating[prev] < rating[i]) 
                     || (!findInc && rating[prev] > rating[i])) 
            currTake = solveWithMemo(rating, i + 1, i, k - 1);

        return dp[i][prev][k] = (currSkip + currTake);
    }

public:
    // O(N^2) & O(N^2)
    int numTeams(vector<int>& rating) {
        n = rating.size();
        const int k = 3;

        // For Increasing Subseq Len 3
        findInc = true;
        memset(dp, -1, sizeof(dp));
        int countIncLen3 = solveWithMemo(rating, 0, n, k);

        // For Decreasing Subseq Len 3
        findInc = false;
        memset(dp, -1, sizeof(dp));
        int countDecLen3 = solveWithMemo(rating, 0, n, k);

        return countIncLen3 + countDecLen3;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int dp[1001][1001][4];
    bool findInc = false;
    int n;

    int solveBy3DTable(const vector<int>& rating, int given_k) {
        for(int prev = 0; prev <= n; ++prev)
            dp[n][prev][0] = 1;
        
        for(int i = n - 1; i >= 0; --i) {
            for(int prev = 0; prev <= n; ++prev) {
                for(int k = 0; k <= given_k; ++k) {
                    int currSkip = dp[i + 1][prev][k];
                    int currTake = 0;

                    if(prev == n || (findInc && rating[prev] < rating[i]) 
                                 || (!findInc && rating[prev] > rating[i])) 
                        currTake = (k - 1 < 0) ? 0 : dp[i + 1][i][k - 1];

                    dp[i][prev][k] = (currSkip + currTake);
                }
            }
        }

        return dp[0][n][given_k];
    }

public:
    // O(N^2) & O(N^2)
    int numTeams(vector<int>& rating) {
        n = rating.size();
        const int k = 3;

        // For Increasing Subseq Len 3
        findInc = true;
        memset(dp, 0, sizeof(dp));
        int countIncLen3 = solveBy3DTable(rating, 3);

        // For Decreasing Subseq Len 3
        findInc = false;
        memset(dp, 0, sizeof(dp));
        int countDecLen3 = solveBy3DTable(rating, 3);

        return countIncLen3 + countDecLen3;
    }
};
    
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUpSpaceOptimized {
    bool findInc = false;
    int n;

    int solveBy2DTable(const vector<int>& rating, int given_k) {
        int next[1001][4];
        memset(next, 0, sizeof(next));

        for(int prev = 0; prev <= n; ++prev)
            next[prev][0] = 1;
        
        for(int i = n - 1; i >= 0; --i) {
            int curr[1001][4];
            memset(curr, 0, sizeof(curr));

            for(int prev = 0; prev <= n; ++prev) {
                for(int k = 0; k <= given_k; ++k) {
                    int currSkip = next[prev][k];
                    int currTake = 0;

                    if(prev == n || (findInc && rating[prev] < rating[i]) 
                                 || (!findInc && rating[prev] > rating[i])) 
                        currTake = (k - 1 < 0) ? 0 : next[i][k - 1];

                    curr[prev][k] = (currSkip + currTake);
                }
            }

            swap(next, curr);
        }

        return next[n][given_k];
    }

public:
    // O(N^2) & O(N)
    int numTeams(vector<int>& rating) {
        n = rating.size();
        const int k = 3;

        // For Increasing Subseq Len 3
        findInc = true;
        int countIncLen3 = solveBy2DTable(rating, 3);

        // For Decreasing Subseq Len 3
        findInc = false;
        int countDecLen3 = solveBy2DTable(rating, 3);

        return countIncLen3 + countDecLen3;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/count-number-of-teams/description/
