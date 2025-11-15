// Code to find the maximum number of cut segments possible. Given an integer n denoting the Length of a line segment. You need to cut the line segment in such a way that the cut length of a line segment each time is either x , y or z. Here x, y, and z are integers. After performing all the cut operations, your total number of cut segments must be maximum ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class TopDown {
    // O(3^N) & O(N)
    int solveWithoutMemo(int n, int x, int y, int z) {
        if(n == 0) // Edge case: If you've cut the whole line segment then return 0 as indication
            return 0;

        if(n < 0) // Edge case: If you've can't cut the whole line segment then return INT_MIN as indication
            return INT_MIN;

        if(memory[n] != -1)
            return memory[n];

        // There are three cut operations to perform
        int cutInLenX = solveWithoutMemo(n - x, x, y, z); // Is to cut line segment in length x
        int cutInLenY = solveWithoutMemo(n - y, x, y, z); // Is to cut line segment in length y
        int cutInLenZ = solveWithoutMemo(n - z, x, y, z); // Is to cut line segment in length z

        int maxSegments = max({cutInLenX, cutInLenY, cutInLenZ});                
        return (maxSegments == INT_MIN) ? INT_MIN : maxSegments + 1;
    }

    // O(3*N) & O(2*N)
    int solveWithMemo(vector<int>& memory, int n, int x, int y, int z) {
        if(n == 0) // Edge case: If you've cut the whole line segment then return 0 as indication
            return 0;

        if(n < 0) // Edge case: If you've can't cut the whole line segment then return INT_MIN as indication
            return INT_MIN;

        if(memory[n] != -1)
            return memory[n];

        // There are three cut operations to perform
        int cutInLenX = solveWithMemo(memory, n - x, x, y, z); // Is to cut line segment in length x
        int cutInLenY = solveWithMemo(memory, n - y, x, y, z); // Is to cut line segment in length y
        int cutInLenZ = solveWithMemo(memory, n - z, x, y, z); // Is to cut line segment in length z

        int maxSegments = max({cutInLenX, cutInLenY, cutInLenZ});                
        return memory[n] = (maxSegments == INT_MIN) ? INT_MIN : maxSegments + 1;
    }

public:
    // Method to find maximum segments can cut, using recursion with memoization - O(N) & O(N)
    int maximizeTheCuts(int n, int x, int y, int z) {
        vector<int> memory(n + 1, -1);
        int result = solveWithMemo(memory, n, x, y, z);
        return (result == INT_MIN) ? 0 : result;
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // O(1*N) & O(1*N)
    int maximizeTheCuts(int given_n, int x, int y, int z) {
        vector<int> dp(given_n + 1, -1);
        dp[0] = 0; // Initialize first edge case
        
        for(int n = 1; n <= given_n; ++n) {
            int cutInLenX = (n - x < 0) ? INT_MIN : dp[n - x];
            int cutInLenY = (n - y < 0) ? INT_MIN : dp[n - y];
            int cutInLenZ = (n - z < 0) ? INT_MIN : dp[n - z];
            int maxSegments = max({cutInLenX, cutInLenY, cutInLenZ});
            dp[n] = (maxSegments == INT_MIN) ? INT_MIN : maxSegments + 1;
        }
        
        int result = dp[given_n];
        return (result == INT_MIN) ? 0 : result;
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/cutted-segments1642/1   
