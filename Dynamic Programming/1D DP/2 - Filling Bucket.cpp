// Code to find in how many ways we could fill the given bucket. Given a Bucket having a capacity of N litres and the task is to determine that by how many ways you can fill it using two bottles of capacity of 1 Litre and 2 Litre only. Find the answer using modulo 1e8 ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int MOD = 1e8;
    
    // O(2^N) & O(N)
    int solveWithoutMemo(int N) {
        if(N == 0) // Edge case: If you've filled the whole bucket then you've 1 way 
            return 1;
        
        if(N < 0) // Edge case: If the bucket is overfilled then its not valid
            return 0;
            
        // There are always two possibilities to perform
        int fill1Litre = solveWithoutMemo(N - 1); // Is to fill bucket with 1 litre
        int fill2Litre = solveWithoutMemo(N - 2); // Is to fill bucket with 2 litre
            
        return (fill1Litre + fill2Litre) % MOD;
    }

    // O(2*N) & O(2*N)
    int solveWithMemo(vector<int>& dp, int N) {
        if(N == 0) // Edge case: If you've filled the whole bucket then you've got 1 way 
            return 1;
        
        if(N < 0) // Edge case: If the bucket is overfilled then its not valid
            return 0;
            
        if(dp[N] != -1)
            return dp[N];
            
        // There are always two possibilities to perform 
        int fill1Litre = solveWithMemo(dp, N - 1); // Is to fill bucket with 1 litre
        int fill2Litre = solveWithMemo(dp, N - 2); // Is to fill bucket with 2 litre
            
        return dp[N] = (fill1Litre + fill2Litre) % MOD;
    }
    
public:
    int numWaysToFillBucket(int N) {
        vector<int> dp(N + 1, -1);
        return solveWithMemo(dp, N);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e8;
    
    // O(1*N) & O(1*N)
    int solveWith1DTable(int N) {
        vector<int> dp(N + 1, 0);
        dp[0] = 1; // Initialize the edge case
        
        for(int capacity = 1; capacity <= N; ++capacity) {
            int fill1Litre = (capacity - 1 >= 0) ? dp[capacity - 1] : 0;
            int fill2Litre = (capacity - 2 >= 0) ? dp[capacity - 2] : 0;
            dp[capacity]   = (fill1Litre + fill2Litre) % MOD;
        }
        
        return dp[N];
    }

    // O(1*N) & O(1)
    int solveWithoutTable(int N) {
        int fill1Litre = 1;
        int fill2Litre = 0;
        int numWays    = 0;

        for(int capacity = 1; capacity <= N; ++capacity) {
            numWays    = (fill1Litre + fill2Litre) % MOD;
            fill2Litre = fill1Litre;
            fill1Litre = numWays;
        }

        return numWays;
    }

public:
    int numWaysToFillBucket(int N) {
        return solveWithoutTable(N);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/filling-bucket0529/0
