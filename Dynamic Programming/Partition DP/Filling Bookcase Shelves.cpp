// Code to find the minimum possible height that the total bookshelf can be after placing shelves in this manner ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to find the minimum possible height, using recursion with memoization - O(N*N) & O(N)
    int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
        int n = books.size();
        vector<int> memory(n, -1);
        return solveWithMemo(books, shelfWidth, n, 0, memory);
    }

private:   
    // O(N*N) & O(N+N)
    int solveWithMemo(vector<vector<int>>& books, int shelfWidth, int n, int startPoint, vector<int>& memory) {
        if(startPoint == n)
            return 0;

        if(memory[startPoint] != -1)
            return memory[startPoint];

        int sumThickness = 0, maxHeight = 0, resultHeight = INT_MAX;

        for(int book = startPoint; book < n; ++book) {
            sumThickness += books[book][0];
            if(sumThickness > shelfWidth) {
                break;
            }
            maxHeight      = max(maxHeight, books[book][1]);
            int nextResult = solveWithMemo(books, shelfWidth, n, book + 1, memory);
            resultHeight   = min(resultHeight, nextResult + maxHeight);
        }

        return memory[startPoint] = resultHeight;
    }

    // O(N^N) & O(N)
    int solveWithoutMemo(vector<vector<int>>& books, int shelfWidth, int n, int startPoint) {
        if(startPoint == n)
            return 0;

        int sumThickness = 0, maxHeight = 0, resultHeight = INT_MAX;

        for(int book = startPoint; book < n; ++book) {
            sumThickness += books[book][0];
            if(sumThickness > shelfWidth) {
                break;
            }
            maxHeight      = max(maxHeight, books[book][1]);
            int nextResult = solveWithoutMemo(books, shelfWidth, n, book + 1);
            resultHeight   = min(resultHeight, nextResult + maxHeight);
        }

        return resultHeight;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to find the minimum possible height, using 1D tabulation - O(N*N) & O(N)
    int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
        int n = books.size();

        vector<int> dp(n+1, INT_MAX);
        dp[n] = 0;

        for(int startPoint = n-1; startPoint >= 0; --startPoint) {
            int sumThickness = 0, maxHeight = 0, resultHeight = INT_MAX;

            for(int book = startPoint; book < n; ++book) {
                sumThickness += books[book][0];
                if(sumThickness > shelfWidth) {
                    break;
                }
                maxHeight      = max(maxHeight, books[book][1]);
                int nextResult = dp[book + 1];
                resultHeight   = min(resultHeight, nextResult + maxHeight);
            }

            dp[startPoint] = resultHeight;
        }

        return dp[0];
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/filling-bookcase-shelves/description/?envType=daily-question&envId=2024-07-31
