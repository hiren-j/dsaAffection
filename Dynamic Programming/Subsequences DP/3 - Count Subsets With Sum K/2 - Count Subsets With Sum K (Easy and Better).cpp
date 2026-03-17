// Code to find the count of all the subsets of the given array with a sum equal to the given sum ~ coded by vHiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;
    
    // O(2^N) & O(N)
    int solveWithoutMemo(const vector<int>& arr, int i, int k) {
        if(k < 0)
            return 0;
        
        if(i == n)
            return (k == 0) ? 1 : 0;
            
        int currSkip = solveWithoutMemo(arr, i + 1, k);
        int currTake = solveWithoutMemo(arr, i + 1, k - arr[i]);
        
        return (currSkip + currTake);
    }
    
    // O(N*K) & O(N*K)
    int solveWithMemo(vector<vector<int>>& dp, const vector<int>& arr, int i, int k) {
        if(k < 0)
            return 0;
        
        if(i == n)
            return (k == 0) ? 1 : 0;
            
        if(dp[i][k] != -1)
            return dp[i][k];
            
        int currSkip = solveWithMemo(dp, arr, i + 1, k);
        int currTake = solveWithMemo(dp, arr, i + 1, k - arr[i]);
        
        return dp[i][k] = (currSkip + currTake);
    }  
    
    // O(N*N*K) & O(N*K)
    int solveWithMemoLoop(vector<vector<int>>& dp, const vector<int>& arr, int start, int k) {
        if(k < 0)
            return 0;
        
        if(start == n)
            return (k == 0) ? 1 : 0;
            
        if(dp[start][k] != -1)
            return dp[start][k];
            
        int count = (k == 0) ? 1 : 0;
        
        for(int i = start; i < n; ++i) {
            int currTake = solveWithMemoLoop(dp, arr, i + 1, k - arr[i]);
            count += currTake;
        }
        
        return dp[start][k] = count;
    }  
    
public:
    int perfectSum(vector<int>& arr, int k) {
        n = arr.size();
        vector<vector<int>> dp(n, vector<int>(k + 1, -1));
        return solveWithMemo(dp, arr, 0, k);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;
    
    // O(N*GK) & O(N*GK) : Where GK = given_k
    int solveBy2DTable(const vector<int>& arr, int given_k) {
        vector<vector<int>> dp(n + 1, vector<int>(given_k + 1, -1));
        
        for(int k = 0; k <= given_k; ++k)
            dp[n][k] = (k == 0) ? 1 : 0;
        
        for(int i = n - 1; i >= 0; --i) {
            for(int k = 0; k <= given_k; ++k) {
                int currSkip = dp[i + 1][k];
                int currTake = (k - arr[i] < 0) ? 0 : dp[i + 1][k - arr[i]];
                dp[i][k] = (currSkip + currTake);
            }
        }
        
        return dp[0][given_k];
    }
    
    // O(N*GK) & O(GK) : Where GK = given_k
    int solveBy1DTable(const vector<int>& arr, int given_k) {
        vector<int> nextRow(given_k + 1, -1); // i + 1th row
        
        for(int k = 0; k <= given_k; ++k)
            nextRow[k] = (k == 0) ? 1 : 0;
        
        for(int i = n - 1; i >= 0; --i) {
            vector<int> idealRow(given_k + 1, -1); // ith row
            
            for(int k = 0; k <= given_k; ++k) {
                int currSkip = nextRow[k];
                int currTake = (k - arr[i] < 0) ? 0 : nextRow[k - arr[i]];
                idealRow[k] = (currSkip + currTake);
            }
            
            swap(nextRow, idealRow);
        }
        
        return nextRow[given_k];
    }
    
public:
    int perfectSum(vector<int>& arr, int k) {
        n = arr.size();
        return solveBy1DTable(arr, k);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/perfect-sum-problem5633/1
        https://www.naukri.com/code360/problems/count-subsets-with-sum-k_3952532
