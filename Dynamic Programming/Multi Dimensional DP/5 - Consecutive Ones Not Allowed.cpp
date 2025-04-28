// Code to count all the possible distinct binary strings of length n such that there are no consecutive 1’s ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    // O(2^N) & O(N)
    int solveWithoutMemo(int n, int prevPick) {
        // Edge case: If you've created a string of length n then you've 1 way
        if(n == 0)
            return 1;
            
        // There are two possibilities to perform
        int pick0 = solveWithoutMemo(n - 1, 0);                       // To append 0 to string, regardless of the previous value
        int pick1 = (prevPick != 1) ? solveWithoutMemo(n - 1, 1) : 0; // To append 1 to string, if and only if previous value is not 1
        
        return pick0 + pick1;
    }
    
    // O(2*N*2) & O(N*2+N)
    int solveWithMemo(vector<vector<int>>& dp, int n, int prevPick) {
        // Edge case: If you've created a string of length n then you've 1 way
        if(n == 0)
            return 1;
            
        if(dp[n][prevPick] != -1)
            return dp[n][prevPick];

        // There are two possibilities to perform
        int pick0 = solveWithMemo(dp, n - 1, 0);                       // To append 0 to string, regardless of the previous value
        int pick1 = (prevPick != 1) ? solveWithMemo(dp, n - 1, 1) : 0; // To append 1 to string, if and only if previous value is not 1
        
        return dp[n][prevPick] = (pick0 + pick1);
    }
    
public:
    // Method to count all distinct binary strings of length n, using recursion with memoization - O(N) & O(N)
    int countDistinctBinaryStrs(int n) {
        vector<vector<int>> dp(n + 1, vector<int>(2, -1));
        return solveWithMemo(dp, n, 0);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    // O(N*2) & O(N*2)
    int solveWith2DTable(int given_n) {
        vector<vector<int>> dp(given_n + 1, vector<int>(2, -1));

        // Init the edge case
        dp[0][0] = 1;
        dp[0][1] = 1;
        
        for(int n = 1; n <= given_n; ++n) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                int pick0 = dp[n - 1][0];
                int pick1 = (prevPick != 1) ? dp[n - 1][1] : 0;
                dp[n][prevPick] = (pick0 + pick1);   
            }
        }
        
        return dp[given_n][0];
    }

    // O(N*2) & O(2*2)
    int solveWith1DTable(int given_n) {
        vector<int> prevRow(2, -1), idealRow(2, -1);

        // Init the edge case
        prevRow[0] = 1;
        prevRow[1] = 1;
        
        for(int n = 1; n <= given_n; ++n) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                int pick0 = prevRow[0];
                int pick1 = (prevPick != 1) ? prevRow[1] : 0;
                idealRow[prevPick] = (pick0 + pick1);   
            }
            prevRow = idealRow;
        }
        
        return prevRow[0];
    }

    // O(N*2) & O(1)
    int solveWithoutTable(int given_n) {
        int prevRow_0  = 1; // Init the edge case
        int prevRow_1  = 1; // Init the edge case
        int idealRow_0 = 0;
        int idealRow_1 = 0;

        for(int n = 1; n <= given_n; ++n) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                int pick0  = prevRow_0;
                int pick1  = (prevPick != 1) ? prevRow_1 : 0;
                int result = pick0 + pick1; 
                (prevPick == 1) ? idealRow_1 = result :  idealRow_0 = result;
            }
            prevRow_0 = idealRow_0;
            prevRow_1 = idealRow_1;
        }
        
        return prevRow_0;
    }

public:
    // Method to count all distinct binary strings of length n, using tabulation :-
    int countDistinctBinaryStrs(int n) {
        return solveWith1DTable(n);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
    NOTE: This same question is also in the 1D-Dimensional DP Folder, but there I solved it using 1D DP approach that came to my mind.
*/
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/consecutive-1s-not-allowed1912/1
