// Code to find the maximum number of cut segments possible. Given an integer n denoting the Length of a line segment. You need to cut the line segment in such a way that the cut length of a line segment each time is either x , y or z. Here x, y, and z are integers. After performing all the cut operations, your total number of cut segments must be maximum ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class TopDown {
    // O(3^N) & O(N)
    int solveWithoutMemo(int n, int x, int y, int z) {
        if(n == 0) // Edge case: If you've cut the whole line segment then return 0 as an indication
            return 0;

        if(n < 0) // Edge case: If you've can't cut the whole line segment then return INT_MIN as an indication
            return INT_MIN;

        if(memory[n] != -1)
            return memory[n];

        // There are three cut operations to perform
        int cutInLenX = solveWithoutMemo(n - x, x, y, z); // Is to cut line segment in length x
        int cutInLenY = solveWithoutMemo(n - y, x, y, z); // Is to cut line segment in length y
        int cutInLenX = solveWithoutMemo(n - z, x, y, z); // Is to cut line segment in length z

        int maxCuts = max({cutInLenX, cutInLenY, cutInLenX});                
        return (maxCuts != INT_MIN) ? maxCuts + 1 : INT_MIN;
    }

    // O(3*N) & O(2*N)
    int solveWithMemo(vector<int>& memory, int n, int x, int y, int z) {
        if(n == 0) // Edge case: If you've cut the whole line segment then return 0 as an indication
            return 0;

        if(n < 0) // Edge case: If you've can't cut the whole line segment then return INT_MIN as an indication
            return INT_MIN;

        if(memory[n] != -1)
            return memory[n];

        // There are three cut operations to perform
        int cutInLenX = solveWithMemo(memory, n - x, x, y, z); // Is to cut line segment in length x
        int cutInLenY = solveWithMemo(memory, n - y, x, y, z); // Is to cut line segment in length y
        int cutInLenX = solveWithMemo(memory, n - z, x, y, z); // Is to cut line segment in length z

        int maxCuts = max({cutInLenX, cutInLenY, cutInLenX});                
        return memory[n] = (maxCuts != INT_MIN) ? maxCuts + 1 : INT_MIN;
    }

public:
    int maximizeTheCuts(int n, int x, int y, int z) {
        vector<int> memory(n + 1, -1);
        int maxCutSegments = solveWithMemo(memory, n, x, y, z);
        return (maxCutSegments == INT_MIN) ? 0 : maxCutSegments;
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // O(1*N) & O(1*N)
    int maximizeTheCuts(int n, int x, int y, int z) {
        vector<int> dp(n + 1, -1);
        dp[0] = 0; // Initialize first edge case
        
        for(int length = 1; length <= n; ++length) {
            int cutInLenX = (length - x >= 0) ? dp[length - x] : INT_MIN;
            int cutInLenY = (length - y >= 0) ? dp[length - y] : INT_MIN;
            int cutInLenZ = (length - z >= 0) ? dp[length - z] : INT_MIN;
            int maxCuts   = max({cutInLenX, cutInLenY, cutInLenZ});
            dp[length] = (maxCuts == INT_MIN) ? INT_MIN : maxCuts + 1;
        }
        
        int maxCutSegments = dp[n];
        return (maxCutSegments == INT_MIN) ? 0 : maxCutSegments;
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/cutted-segments1642/1   
