// Code to count the total number of partitions in which sum1 is greater than or equal to sum2 and the difference between sum1 and sum2 is equal to given difference ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n, arrSum;
    
    // O(N*K) & O(N*K)
    int solveWithMemo(vector<vector<int>>& dp, const vector<int>& arr, int i, int k) {
        if(k < 0)
            return 0;
        
        if(i == n)
            return (k == 0) ? 1 : 0;
            
        if(dp[i][k] != -1)
            return dp[i][k];
            
        int currTake = solveWithMemo(dp, arr, i + 1, k - arr[i]);
        int currSkip = solveWithMemo(dp, arr, i + 1, k);
        
        return dp[i][k] = (currTake + currSkip);
    }  
    
public:
    // O(N*AS) & O(N*AS) : Where AS = arrSum
    int countPartitions(vector<int>& arr, int D) {
        n = arr.size();
        arrSum = accumulate(begin(arr), end(arr), 0);
        
        vector<vector<int>> dp(n, vector<int>(arrSum + 1, -1));
        int result = 0;
        
        for(int subset1Sum = arrSum; subset1Sum >= arrSum / 2; --subset1Sum) {
            int countSubsets = solveWithMemo(dp, arr, 0, subset1Sum);
            int subset2Sum   = arrSum - subset1Sum;
            if(subset1Sum - subset2Sum == D) {
                result += countSubsets;
            }
        }
        
        return result;
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n, arrSum;
    
    void precomputeCountOfSubsetsSumK(vector<vector<int>>& dp, const vector<int>& arr) {
        dp.resize(n + 1, vector<int>(arrSum + 1, -1));
        
        for(int k = 0; k <= arrSum; ++k)
            dp[n][k] = (k == 0) ? 1 : 0;
        
        for(int i = n - 1; i >= 0; --i) {
            for(int k = 0; k <= arrSum; ++k) {
                int currTake = (k - arr[i] < 0) ? 0 : dp[i + 1][k - arr[i]];
                int currSkip = dp[i + 1][k];
                dp[i][k] = (currTake + currSkip);
            }
        }
    }
    
public:
    // O(N*AS) & O(N*AS) : Where AS = arrSum
    int countPartitions(vector<int>& arr, int D) {
        n = arr.size();
        arrSum = accumulate(begin(arr), end(arr), 0);
        
        vector<vector<int>> dp;
        precomputeCountOfSubsetsSumK(dp, arr);
        
        int result = 0;
        
        for(int subset1Sum = arrSum; subset1Sum >= arrSum / 2; --subset1Sum) {
            int countSubsets = dp[0][subset1Sum];
            int subset2Sum   = arrSum - subset1Sum;
            if(subset1Sum - subset2Sum == D) {
                result += countSubsets;
            }
        }
        
        return result;
    }
};
// Note: To optimize bottom up then you could fetch solveBy1DTable() code from problem - Subset Sum Equal To K

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/partitions-with-given-difference/1 
