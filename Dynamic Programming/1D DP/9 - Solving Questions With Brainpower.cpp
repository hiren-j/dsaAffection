// Code to find the maximum points you can earn for the exam ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Class to implement the Top-down approach:
class TopDown {
    typedef long long ll;

public:
    // Method to find the maximum points you can earn for the exam, using recursion with memoization - O(N) & O(N)
    ll mostPoints(vector<vector<int>>& ques) {
        int N = ques.size();
        vector<ll> memory(N+1, -1);
        return solveWithMemo(ques, memory, N, 0);
    }

private:
    // O(2*N) & O(N+N)
    ll solveWithMemo(vector<vector<int>>& ques, vector<ll>& memory, int N, int J) {
        // Edge case: If all the questions are exhausted then you can't earn more points
        if(J >= N)
            return 0;
         
        // Memoization table: If the current state is already computed then return the computed value
        if(memory[J] != -1)
            return memory[J];

        // There are always two possibilities to perform at each question
        ll skipQuestion  = solveWithMemo(ques, memory, N, J+1);                             // Is to skip it
        ll solveQuestion = ques[J][0] + solveWithMemo(ques, memory, N, J + ques[J][1] + 1); // Is to solve it

        // Store the result value to the memoization table and then return it
        return memory[J] = max(solveQuestion, skipQuestion);
    }

    // O(2^N) & O(N)
    ll solveWithoutMemo(vector<vector<int>>& ques, int N, int J) {
        // Edge case: If all the questions are exhausted then you can't earn more points
        if(J >= N)
            return 0;

        // There are always two possibilities to perform at each question
        ll skipQuestion  = solveWithoutMemo(ques, N, J+1);                             // Is to skip it
        ll solveQuestion = ques[J][0] + solveWithoutMemo(ques, N, J + ques[J][1] + 1); // Is to solve it

        // As we're striving for the maximum points hence return the maximum value
        return max(solveQuestion, skipQuestion);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Class to implement the Bottom-up approach:
class BottomUp {
    typedef long long ll;

public:
    // Method to find the maximum points you can earn for the exam, using 1D tabulation - O(N) & O(N)
    ll mostPoints(vector<vector<int>>& ques) {
        int N = ques.size();     

        // 1D table: dp[J] represents the maximum points you can earn till the Jth question
        vector<ll> dp(N+1, 0);

        // Iterate from the back side and compute the maximum points you can earn till the Jth question
        for(int J=N-1; J>=0; J--) {
            int nextQuestion = J + ques[J][1] + 1;
            ll solveQuestion = ques[J][0] + (nextQuestion <= N ? dp[nextQuestion] : 0); 
            ll skipQuestion  = dp[J+1];                                               
            dp[J] = max(skipQuestion, solveQuestion);
        }

        // Return the result value
        return dp[0];
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/solving-questions-with-brainpower/description/
