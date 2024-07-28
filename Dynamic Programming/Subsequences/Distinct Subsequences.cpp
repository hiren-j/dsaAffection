// Program to count the total number of subsequences of string "s1" equal to string "s2" ~ coded by Hiren
#include <iostream>
#include <vector>
using namespace std;

// #1 Class to implement the Top-down approach:
class TopDown_A {
    int n, m;

    // O(2^N) & O(max(N,M)) 
    int solveWithoutMemo(string& s1, string& s2, int i, int j) {
        // Edge case: If all the letters of "s2" are exhausted then you've one valid way 
        if(j == m)
            return 1;
            
        // Edge case: If all the letters of "s1" are exhausted then you've no valid way 
        if(i == n)
            return 0;
            
        // There are always two possibilites to perform at each index
        int currSkip = solveWithoutMemo(s1, s2, i + 1, j); // Is to skip the ith letter of "s1"
        int currTake = 0;                                  // Is to take the ith letter of "s1"
        
        // If the ith and jth letter of both the strings are equal then take the ith letter of "s1"
        if(s1[i] == s2[j])
            currTake = solveWithoutMemo(s1, s2, i + 1, j + 1);
            
        // Return ther result value
        return (currSkip + currTake);
    }
    
    // O(N*M) & O(N*M)
    int solveWithMemo(vector<vector<int>>& memory, string& s1, string& s2, int i, int j) {
        // Edge case: If all the letters of "s2" are exhausted then you've one valid way 
        if(j == m)
            return 1;
        
        // Edge case: If all the letters of "s1" are exhausted then you've no valid way 
        if(i == n)
            return 0;
        
        // Memoization table: If the current state is already computed then return the computed value
        if(memory[i][j] != -1)
            return memory[i][j];
        
        // There are always two possibilites to perform at each index
        int currSkip = solveWithMemo(memory, s1, s2, i + 1, j); // Is to skip the ith letter of "s1"
        int currTake = 0;                                       // Is to take the ith letter of "s1"      
        
        // If the ith and jth letter of both the strings are equal then take the ith letter of "s1"
        if(s1[i] == s2[j])
            currTake = solveWithMemo(memory, s1, s2, i + 1, j + 1);
        
        // Store the result value to the memoization table and then return it
        return memory[i][j] = (currSkip + currTake);
    }
    
public:
    // Method to count the total number of subsequences of string "s1" equal to string "s2", using recursion with memoization - O(N*M) & O(N*M)
    int numDistinct(string& s1, string& s2) {
        n = s1.size(), m = s2.size();
        vector<vector<int>> memory(n, vector<int>(m, -1));
        return solveWithMemo(memory, s1, s2, 0, 0);
    }
};

// #2 Class to implement the Top-down approach:
class TopDown_B {
    int n, m;

    // O(2^N) & O(max(N,M))
    int solveWithoutMemo(string& s1, string& s2, int startIndex, int j) {
        // Edge case: If all the letters of "s2" are exhausted then you've one valid way 
        if(j == m)
            return 1;
            
        // Edge case: If all the letters of "s1" are exhausted then you've no valid way 
        if(startIndex == n)
            return 0;

        // Stores the result value
        int resCount = 0;

        // Iterate "s1" and if the ith and jth letter of both the strings are equal then take the ith letter of "s1"
        for(int i = startIndex; i < n; ++i) {
            if(s1[i] == s2[j]) {
                resCount += solveWithoutMemo(s1, s2, i + 1, j + 1);
            }
        }
        
        // Return the result value
        return resCount;
    }

    // O(N*M) & O(N*M)
    int solveWithMemo(vector<vector<int>>& memory, string& s1, string& s2, int startIndex, int j) {
        // Edge case: If all the letters of "s2" are exhausted then you've one valid way 
        if(j == m)
            return 1;
            
        // Edge case: If all the letters of "s1" are exhausted then you've no valid way 
        if(startIndex == n)
            return 0;
        
        // Edge case: If the current state is already computed then return the computed value
        if(memory[startIndex][j] != -1)
            return memory[startIndex][j];

        // Stores the result value
        int resCount = 0;

        // Iterate "s1" and if the ith and jth letter of both the strings are equal then take the ith letter of "s1"
        for(int i = startIndex; i < n; ++i) {
            if(s1[i] == s2[j]) {
                resCount += solveWithMemo(memory, s1, s2, i + 1, j + 1);
            }
        }
        
        // Store the result value to the memoization table and then return it
        return memory[startIndex][j] = resCount;
    }
    
public:
    // Method to count the total number of subsequences of string "s1" equal to string "s2", using recursion with memoization - O(N*M) & O(N*M)
    int numDistinct(string& s1, string& s2) {
        n = s1.size(), m = s2.size();
        vector<vector<int>> memory(n, vector<int>(m, -1));
        return solveWithMemo(memory, s1, s2, 0, 0);
    }
};

// Class to implement the Bottom-up approach:
class BottomUp {
public:
    // #1 Method to count the total number of subsequences of string "s1" equal to string "s2", using 2D tabulation - O(N*M) & O(N*M)
    int numDistinct_A(string& s1, string& s2) {
        int n = s1.size(), m = s2.size();
        
        // 2D table for tabulation: dp[i][j] stores the count of total number of subsequences of "s1" equal to "s2" such that by considering the first i letters of "s1" and j letters of "s2"
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        
        // Edge case: If "s2" is empty then for any size of "s1" you've one valid way
        for(int i = 0; i < n; ++i) {
            dp[i][0] = 1;
        }
        
        // Fill the rest of the table
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                unsigned int currSkip = dp[i - 1][j];
                unsigned int currTake = 0; 
                if(s1[i - 1] == s2[j - 1]) {
                    currTake = dp[i - 1][j - 1];
                }
                dp[i][j] = (currSkip + currTake);
            }
        }
        
        // Return the count of total number of subsequences of "s1" equal to "s2" such that by considering the whole "s1" and "s2"
        return dp[n][m];
    }

    // #2 Method to count the total number of subsequences of string "s1" equal to string "s2", using 1D tabulation - O(N*M) & O(M)
    int numDistinct_B(string& s1, string& s2) {
        int n = s1.size(), m = s2.size();
        
        // 1D table for tabulation: "prevRow[j] or currRow[j]" stores the count of total number of subsequences of "s1" equal to "s2" such that by considering the first i letters of "s1" and j letters of "s2"
        vector<int> prevRow(m + 1, 0), currRow(m + 1, 0);
        
        // Fill the 2D table
        for(int i = 1; i <= n; ++i) {
            // If "s2" is empty then for any size of "s1" you've one valid way
            prevRow[0] = 1;
            for(int j = 1; j <= m; ++j) {
                unsigned int currSkip = prevRow[j];
                unsigned int currTake = 0; 
                if(s1[i - 1] == s2[j - 1]) {
                    currTake = prevRow[j - 1];
                }
                currRow[j] = (currSkip + currTake);
            }
            // Update the previous row of the upcoming row
            prevRow = currRow;
        }
        
        // Return the count of total number of subsequences of "s1" equal to "s2" such that by considering the whole "s1" and "s2"
        return prevRow[m];
    }
};

// Driver code
int main() {
    int testCases;
    cout<<"Enter the total number of cases to test: ";
    cin>>testCases;

    while(testCases--) {
        string s1, s2;
        cout<<"\nEnter the first string: "; cin>>s1;
        cout<<"Enter the seconod string: "; cin>>s2;
        int n = s1.size(), m = s2.size();

        // Check the string size is lying within the problem constraints or not
        if(n < 1 || n > 500 || m < 1 || m > 500) {
            cout<<"You must enter the string of size which lies between 1 and 500!\n";
        }
        else {
            BottomUp bottomUp;
            cout<<"The total number of subsequences is: "<<bottomUp.numDistinct_B(s1, s2)<<'\n';    
        }
    }

    return 0;
}
/*
    Topics: String | Dynamic Programming
    Links: https://leetcode.com/discuss/interview-question/433901/Google-or-Phone-or-Distinct-subsequences
           https://leetcode.com/problems/distinct-subsequences/description/
*/
