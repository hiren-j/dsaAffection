// Code to find in how many ways we could fill the given bucket. Given a Bucket having a capacity of N litres and the task is to determine that by how many ways you can fill it using two bottles of capacity of 1 Litre and 2 Litre only. Find the answer modulo 10e8 ~ coded by Hiren

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int MOD = 1e8;
    
    int solveWithoutMemo(int N) {
        if(N == 0)
            return 1;
        
        if(N < 0)
            return 0;
            
        int fill1Litre = solveWithoutMemo(N - 1);
        int fill2Litre = solveWithoutMemo(N - 2);
            
        return (fill1Litre + fill2Litre) % MOD;
    }

    int solveWithMemo(vector<int>& dp, int N) {
        if(N == 0)
            return 1;
        
        if(N < 0)
            return 0;
            
        if(dp[N] != -1)
            return dp[N];
            
        int fill1Litre = solveWithMemo(dp, N - 1);
        int fill2Litre = solveWithMemo(dp, N - 2);
            
        return dp[N] = (fill1Litre + fill2Litre) % MOD;
    }
    
public:
    int fillingBucket(int N) {
        vector<int> dp(N + 1, -1);
        return solveWithMemo(dp, N);
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e8;
    
public:
    int fillingBucket_V1(int N) {
        vector<int> dp(N + 1, 0);
        dp[0] = 1;
        
        for(int capacity = 1; capacity <= N; ++capacity) {
            int fill1Litre = (capacity - 1 >= 0) ? dp[capacity - 1] : 0;
            int fill2Litre = (capacity - 2 >= 0) ? dp[capacity - 2] : 0;
            dp[capacity] = (fill1Litre + fill2Litre) % MOD;
        }
        
        return dp[N];
    }

    int fillingBucket_V2(int N) {
        int prev_1 = 1; 
        int prev_2 = 0;
        int curr   = 1;
        
        for(int capacity = 1; capacity <= N; ++capacity) {
            int fill1Litre = (capacity - 1 >= 0) ? prev_1 : 0;
            int fill2Litre = (capacity - 2 >= 0) ? prev_2 : 0;
            curr = (fill1Litre + fill2Litre) % MOD;
            prev_2 = prev_1;
            prev_1 = curr;
        }
        
        return curr;
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/filling-bucket0529/0
