// Code to find the maximum points you can earn for the exam ~ coded by Hiren
    
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class TopDown {
    typedef long long LL;
    int n;

    // O(2^N) & O(N)
    LL solveWithoutMemo(vector<vector<int>>& questions, int i) {
        if(i >= n)
            return 0;

        LL solveQuestion = questions[i][0] + solveWithoutMemo(questions, i + questions[i][1] + 1);
        LL skipQuestion  = solveWithoutMemo(questions, i + 1);

        return max(solveQuestion, skipQuestion);
    }
    
    // O(2*N) & O(2*N)
    LL solveWithMemo(vector<LL>& dp, vector<vector<int>>& questions, int i) {
        if(i >= n)
            return 0;

        if(dp[i] != -1)
            return dp[i];

        LL solveQuestion = questions[i][0] + solveWithMemo(dp, questions, i + questions[i][1] + 1);
        LL skipQuestion  = solveWithMemo(dp, questions, i + 1);

        return dp[i] = max(solveQuestion, skipQuestion);
    }

public:
    LL mostPoints(vector<vector<int>>& questions) {
        n = questions.size();
        vector<LL> dp(n, -1);
        return solveWithMemo(dp, questions, 0);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    using LL = long long;

public:
    // O(1*N) & O(1*N)
    LL mostPoints(vector<vector<int>>& questions) {
        int n = questions.size();

        vector<LL> dp(n + 1, -1);
        dp[n] = 0;

        for(int i = n-1; i >= 0; --i) {
            LL nextQuestion  = i + questions[i][1] + 1;
            LL solveQuestion = questions[i][0] + (nextQuestion <= n ? dp[nextQuestion] : 0); 
            LL skipQuestion  = dp[i + 1];
            dp[i] = max(solveQuestion, skipQuestion);
        }

        return dp[0];
    }
    // Note: We can't do space optimization in this, as you could see dp[nextQuestion], the value of `nextQuestion` could be anything, overall its not constant
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/solving-questions-with-brainpower/description/
