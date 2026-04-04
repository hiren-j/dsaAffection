// Code to find the maximum value obtainable by cutting up the rod and selling the pieces ~ coded by vHiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;
    
    int solveWithoutMemo(const vector<int>& price, int cutLen, int rodLen) {
        if(rodLen == 0 || cutLen > price.size())
            return 0;
            
        int skipCut    = solveWithoutMemo(price, cutLen + 1, rodLen);
        int performCut = cutLen <= rodLen 
                            ? price[cutLen - 1] + solveWithoutMemo(price, cutLen, rodLen - cutLen)
                            : 0;
        
        return max(performCut, skipCut);
    }
    
    int solveWithMemo(vector<vector<int>>& memory, const vector<int>& price, int cutLen, int rodLen) {
        if(cutLen > n || rodLen == 0)
            return 0;
            
        if(memory[cutLen][rodLen] != -1)
            return memory[cutLen][rodLen];
            
        int skipCut    = solveWithMemo(memory, price, cutLen + 1, rodLen);
        int performCut = cutLen <= rodLen 
                            ? price[cutLen - 1] + solveWithMemo(memory, price, cutLen, rodLen - cutLen)
                            : 0;
        
        return memory[cutLen][rodLen] = max(performCut, skipCut);
    }
    
    int solveWithMemoLoop(vector<vector<int>>& memory, const vector<int>& price, int start, int rodLen) {
        if(start > n || rodLen == 0)
            return 0;
            
        if(memory[start][rodLen] != -1)
            return memory[start][rodLen];

        int maxValue = 0;
        
        for(int cutLen = start; cutLen <= n; ++cutLen) {
            int performCut = cutLen <= rodLen 
                                ? price[cutLen - 1] + solveWithMemoLoop(memory, price, cutLen, rodLen - cutLen)
                                : 0;
            maxValue = max(maxValue, performCut);
        }
        
        return memory[start][rodLen] = maxValue;
    }

public:
    int cutRod(vector<int>& price) {
        n = price.size();
        vector<vector<int>> memory(n + 1, vector<int>(n + 1, -1));
        return solveWithMemo(memory, price, 1, n);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    int solveBy2DTable(const vector<int>& price) {
        vector<vector<int>> dp(n + 2, vector<int>(n + 1, 0));
        
        for(int cutLen = n; cutLen >= 1; --cutLen) {
            for(int rodLen = 1; rodLen <= n; ++rodLen) {
                int skipCut    = dp[cutLen + 1][rodLen];
                int performCut = cutLen <= rodLen 
                                    ? price[cutLen - 1] + dp[cutLen][rodLen - cutLen]
                                    : 0;
                dp[cutLen][rodLen] = max(performCut, skipCut);
            }
        }
        
        return dp[1][n];
    }
    
    int solveBy1DTable(const vector<int>& price) {
        vector<int> nextRow(n + 1, 0), currRow(n + 1, 0);
        
        for(int cutLen = n; cutLen >= 1; --cutLen) {
            for(int rodLen = 1; rodLen <= n; ++rodLen) {
                int skipCut    = nextRow[rodLen];
                int performCut = cutLen <= rodLen 
                                    ? price[cutLen - 1] + currRow[rodLen - cutLen]
                                : 0;
                currRow[rodLen] = max(performCut, skipCut);
            }
            swap(nextRow, currRow);
        }
        
        return nextRow[n];
    }

public:
    int cutRod(vector<int>& price) {
        n = price.size();
        return solveBy1DTable(price);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/rod-cutting0840/1
