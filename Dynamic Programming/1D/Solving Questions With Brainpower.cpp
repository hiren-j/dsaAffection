// Program to find the maximum points you can earn for the exam ~ coded by Hiren
#include <iostream>
#include <cstdlib>
#include <vector>
#define ll long long
using namespace std;

// Class to implement the Top-down approach:
class TopDown {
public:
    // Method to find the maximum points you can earn for the exam, using recursion with memoization - O(N) & O(N)
    ll mostPoints(vector<vector<int>>& ques) {
        int N = ques.size();
        vector<ll> memory(N+1, -1);
        return solveWithMemo(ques, memory, N, 0);
    }

private:
    // O(N) & O(N)
    ll solveWithMemo(vector<vector<int>>& ques, vector<ll>& memory, int N, int J) {
        // Edge case: If all the questions are exhausted, then you can earn no more points
        if(J >= N)
            return 0;
         
        // Memoization table: If the current state is already computed, then return the computed value
        if(memory[J] != -1)
            return memory[J];

        // There are always two possibilities at each question
        ll solveQuestion = ques[J][0] + solveWithMemo(ques, memory, N, J + ques[J][1] + 1); // Is to solve the current question
        ll skipQuestion  = solveWithMemo(ques, memory, N, J+1);                             // Is to skip the current question 

        // Store the value of the maximum points to the memoization table and then return it
        return memory[J] = max(solveQuestion, skipQuestion);
    }

    // O(2^N) & O(N)
    ll solveWithoutMemo(vector<vector<int>>& ques, int N, int J) {
        // Edge case: If all the questions are exhausted, then you can earn no more points
        if(J >= N)
            return 0;

        // There are always two possibilities at each question
        ll solveQuestion = ques[J][0] + solveWithoutMemo(ques, N, J + ques[J][1] + 1); // Is to solve the current question
        ll skipQuestion  = solveWithoutMemo(ques, N, J+1);                             // Is to skip the current question

        // Return the value of the maximum points
        return max(solveQuestion, skipQuestion);
    }
};

// Class to implement the Bottom-up approach:
class BottomUp {
public:
    // Method to find the maximum points you can earn for the exam, using 1D buffer for tabulation - O(N) & O(N)
    ll mostPoints(vector<vector<int>>& ques) {
        int N = ques.size();     

        // Tabulation buffer: dp[J] represents the maximum points you can earn till the Jth question
        vector<ll> dp(N+1);

        // Iterate from the back side and compute the maximum points you can earn till the Jth question
        for(int J=N-1; J>=0; J--) {
            int nextQuestion = J + ques[J][1] + 1;
            // There are always two possibilities at each question
            ll skipQuestion  = dp[J+1];                                                // Stores the maximum points you can earn by skiping the Jth question
            ll solveQuestion = ques[J][0] + (nextQuestion < N ? dp[nextQuestion] : 0); // Stores the maximum points you can earn by solving the Jth question 
            // Stores the value of the maximum points you can earn till the Jth question
            dp[J] = max(skipQuestion, solveQuestion);
        }

        // Return the maximum points you can earn for the exam 
        return dp[0];
    }
};

// Driver code
int main() {
    // Controls the user wants to perform the operation or not
    bool userWantsOperation = true;

    while(userWantsOperation) {
        // Controls console clearance for both "windows" and "linux" user
        system("cls || clear");

        // Input the array size
        int N;
        cout<<"Enter the total number of questions: ";
        cin>>N;

        // Check the given size is valid or not
        if(N <= 0 || N >= 100001) {
            cout<<"Application expects a size which lies within the problem constraints!";
            return 0;
        }

        // Stores the array values
        vector<vector<int>> questions(N, vector<int>(2, 0));

        // Input the array values
        cout<<"\nNote: Each question considers two values - [points, brainpower]\n";
        for(int J=0; J<N; J++) {
            cout<<"Enter the values of the "<<J<<"th question: ";
            cin>>questions[J][0]>>questions[J][1];
        }

        // Call to find the maximum points you can for the exam
        BottomUp bottomUp;
        ll maxPoints = bottomUp.mostPoints(questions);
        cout<<"\nThe maximum points you can earn for the exam is: "<<maxPoints;

        // Input section to control the flow of iterations of the application
        char userChoice;
        cout<<"\n\nPress \'R\' to restart the application, else it will exist: ";
        cin>>userChoice;
        userWantsOperation = (userChoice == 'R' ? true : false);
    }

    return 0;
}
/*
    Topics: Array | Dynamic Programming
    Link: https://leetcode.com/problems/solving-questions-with-brainpower/description/
*/
