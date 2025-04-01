// Code to find the maximum points you can earn for the exam ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
    DON'T IGNORE MUST READ: Starting from the 10th problem, you’ll notice a shift in the approach. The bottom-up solutions will now be direct conversions from the memoized ones. 
                            This change aims to reduce time and avoid the need for pen and paper, making the process more efficient. As you work through the bottom-up solutions, switch tabs to view the memoized solution side-by-side. 
                            This will help you see how the values passed as parameters in the memoized solution correspond to what we calculate and store in the bottom-up approach. 
                            With practice, you’ll be able to create bottom-up solutions within minutes or even seconds, as I have developed the habit of doing. 
                            This conversion technique will be applied to the remaining problems across all DP patterns.
*/    
    
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class TopDown {
    typedef long long LL;

public:
    // Method to find the maximum points you can earn for the exam, using recursion with memoization - O(N) & O(N)
    LL mostPoints(vector<vector<int>>& ques) {
        int N = ques.size();
        vector<LL> memory(N+1, -1);
        return solveWithMemo(ques, memory, N, 0);
    }

private:
    // O(2*N) & O(N+N)
    LL solveWithMemo(vector<vector<int>>& ques, vector<LL>& memory, int N, int J) {
        // Edge case: If all the questions are exhausted then you can't earn more points
        if(J >= N)
            return 0;
         
        // Memoization table: If the current state is already computed then return the computed value
        if(memory[J] != -1)
            return memory[J];

        // There are always two possibilities to perform at each question
        LL skipQuestion  = solveWithMemo(ques, memory, N, J+1);                             // Is to skip it
        LL solveQuestion = ques[J][0] + solveWithMemo(ques, memory, N, J + ques[J][1] + 1); // Is to solve it

        // Store the result value to the memoization table and then return it
        return memory[J] = max(solveQuestion, skipQuestion);
    }

    // O(2^N) & O(N)
    LL solveWithoutMemo(vector<vector<int>>& ques, int N, int J) {
        // Edge case: If all the questions are exhausted then you can't earn more points
        if(J >= N)
            return 0;

        // There are always two possibilities to perform at each question
        LL skipQuestion  = solveWithoutMemo(ques, N, J+1);                             // Is to skip it
        LL solveQuestion = ques[J][0] + solveWithoutMemo(ques, N, J + ques[J][1] + 1); // Is to solve it

        // As we're striving for the maximum points hence return the maximum value
        return max(solveQuestion, skipQuestion);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    typedef long long LL;

public:
    // Method to find the maximum points you can earn for the exam, using 1D tabulation - O(N) & O(N)
    LL mostPoints(vector<vector<int>>& ques) {
        int N = ques.size();     

        // 1D table: dp[J] represents the maximum points you can earn till the Jth question
        vector<LL> dp(N+1, 0);

        // Iterate from the back side and compute the maximum points you can earn till the Jth question
        for(int J=N-1; J>=0; J--) {
            int nextQuestion = J + ques[J][1] + 1;
            LL solveQuestion = ques[J][0] + (nextQuestion <= N ? dp[nextQuestion] : 0); 
            LL skipQuestion  = dp[J+1];                                               
            dp[J] = max(skipQuestion, solveQuestion);
        }

        // Return the result value
        return dp[0];
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/solving-questions-with-brainpower/description/
