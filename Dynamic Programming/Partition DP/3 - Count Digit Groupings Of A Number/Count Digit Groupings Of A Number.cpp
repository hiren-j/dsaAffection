// Code to find the count of all `n` digit numbers whose sum of digits is `sum`. Leading 0’s are not counted as digits ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int sumLimit = 900;
    int n;
    
    // O(N^N) & O(N)
    int solveWithoutMemo(const string& s, int start, int prevSum) {
        if(start == n)
            return 1;
        
        int count = 0;
        int subarrSum = 0;
        
        for(int i = start; i < n; ++i) {
            subarrSum += s[i] - '0';
            
            if(prevSum <= subarrSum) {
                count += solveWithoutMemo(s, i + 1, subarrSum);
            } 
        }
        
        return count;
    }
    
    // O(N*N*SL) & O(N*N) : Where SL = sumLimit
    int solveWithMemo(vector<vector<int>>& dp, const string& s, int start, int prevSum) {
        if(start == n)
            return 1;
            
        if(dp[start][prevSum] != -1)
            return dp[start][prevSum];
        
        int count = 0;
        int subarrSum = 0;
        
        for(int i = start; i < n; ++i) {
            subarrSum += s[i] - '0';
            
            if(prevSum <= subarrSum) {
                count += solveWithMemo(dp, s, i + 1, subarrSum);
            } 
        }
        
        return dp[start][prevSum] = count;
    }

public:
    int validGroups(string& s) {
        n = s.size();
        vector<vector<int>> dp(n, vector<int>(sumLimit + 1, -1));
        return solveWithMemo(dp, s, 0, 0);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // O(N*SL*N) & O(N*N) : Where SL = sumLimit
    int validGroups(string& s) {
        const int n = s.size();
        const int sumLimit = 900;
        
        vector<vector<int>> dp(n + 1, vector<int>(sumLimit + 1, -1));
        
        for(int prevSum = 0; prevSum <= sumLimit; ++prevSum)
            dp[n][prevSum] = 1;
        
        for(int start = n - 1; start >= 0; --start) {
            for(int prevSum = sumLimit; prevSum >= 0; --prevSum) {
                int count = 0;
                int subarrSum = 0;
                
                for(int i = start; i < n; ++i) {
                    subarrSum += s[i] - '0';
                    
                    if(prevSum <= subarrSum) {
                        count += dp[i + 1][subarrSum];
                    } 
                }
                
                dp[start][prevSum] = count;
            }
        }
        
        return dp[0][0];
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: String | Dynamic Programming 
Link  : https://www.geeksforgeeks.org/problems/count-digit-groupings-of-a-number1520/1
