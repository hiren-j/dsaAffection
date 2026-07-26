// Code to find the minimum possible height that the total bookshelf can be after placing shelves in this manner ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class TopDown {
    int n, shelfWidth;

    // O(N^N) & O(N)
    int solveWithoutMemo(const vector<vector<int>>& books, int start) {
        if(start == n)
            return 0;

        int sumOfThickness = 0;
        int maxHeight = 0;
        int res = INT_MAX;

        for(int i = start; i < n; ++i) {
            const int t = books[i][0];
            const int h = books[i][1];
            sumOfThickness += t;
            maxHeight = max(maxHeight, h);
            if(sumOfThickness > shelfWidth) 
                break;
            const int next = solveWithoutMemo(books, i + 1);
            res = min(res, maxHeight + next);
        }

        return res;
    }

    // O(N*N) & O(N)
    int solveWithMemo(vector<int>& dp, const vector<vector<int>>& books, int start) {
        if(start == n)
            return 0;

        if(dp[start] != -1) 
            return dp[start]; 

        int sumOfThickness = 0;
        int maxHeight = 0;
        int res = INT_MAX;

        for(int i = start; i < n; ++i) {
            const int t = books[i][0];
            const int h = books[i][1];
            sumOfThickness += t;
            maxHeight = max(maxHeight, h);
            if(sumOfThickness > shelfWidth) 
                break;
            const int next = solveWithMemo(dp, books, i + 1);
            res = min(res, maxHeight + next);
        }

        return dp[start] = res;
    }

public:
    int minHeightShelves(vector<vector<int>>& books, int SW) {
        n = books.size(), shelfWidth = SW;
        vector<int> dp(n, -1);
        return solveWithMemo(dp, books, 0);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // O(N*N) & O(N)
    int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
        const int n = books.size();
        
        vector<int> dp(n + 1, -1);
        dp[n] = 0;

        for(int start = n - 1; start >= 0; --start) {
            int sumOfThickness = 0;
            int maxHeight = 0;
            int res = INT_MAX;

            for(int i = start; i < n; ++i) {
                const int t = books[i][0];
                const int h = books[i][1];
                sumOfThickness += t;
                maxHeight = max(maxHeight, h);
                if(sumOfThickness > shelfWidth) 
                    break;
                const int next = dp[i + 1];
                res = min(res, maxHeight + next);
            }

            dp[start] = res;   
        }

        return dp[0];
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/filling-bookcase-shelves/description/?envType=daily-question&envId=2024-07-31
