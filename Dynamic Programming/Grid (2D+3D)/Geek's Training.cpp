// Program to find the maximum points the geek can earn by performing the aforementioned activites ~ coded by Hiren
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <climits>
#include <vector>
using namespace std;

// Class to implement the "Top Down Approach":
class TopDown {
public: 
    // Method to find the maximum points the geek can earn, using recursion with memoization - O(N) & O(N)
    int maximumPoints(vector<vector<int>>& points, int N) {
        vector<vector<int>> memory(N, vector<int>(4, -1));
        return solveWithMemo(points, memory, N, 0, -1);
    }
    
private:
    // O(N) & O(N)
    int solveWithMemo(vector<vector<int>>& points, vector<vector<int>>& memory, int N, int day, int activityToSkip) {
        // Edge case: If all the days are exhausted, then it's not possible to perform any more activity
        if(day >= N)
            return 0;
        
        // Memoization table: If the current state is already computed then return the computed value
        if(memory[day][activityToSkip + 1] != -1)
            return memory[day][activityToSkip + 1]; 
        
        // Stores the value of maximum points the geek can earn (result value)
        int maxPoints = 0;
        
        // Traverse and perform each activity once and update the maximum points the geek can earn
        for(int activity=0; activity<3; activity++) {
            // Make sure the geek does not perform the same activity on two consecutive days
            if(activity != activityToSkip) {
                // Compute and store the maximum points the geek can earn by performing the current activity
                int currPoints = solveWithMemo(points, memory, N, day+1, activity);
                // As we're striving for the maximum points hence update the value by maximum points each time
                maxPoints = max(maxPoints, currPoints + points[day][activity]);
            }
        }
        
        // Store the result value to the memoization table and then return it
        return memory[day][activityToSkip + 1] = maxPoints;
    }

    // O(3^(3*N)) & O(N)
    int solveWithoutMemo(vector<vector<int>>& points, int N, int day, int activityToSkip) {
        // Edge case: If all the days are exhausted, then it's not possible to perform any activity more
        if(day >= N)
            return 0;

        // Stores the value of maximum points the geek can earn (result value)
        int maxPoints = 0;
        
        // Traverse and perform each activity once and update the maximum points the geek can earn
        for(int activity=0; activity<3; activity++) {
            // Make sure the geek does not perform the same activity on two consecutive days
            if(activity != activityToSkip) {
                // Compute and store the maximum points the geek can earn by performing the current activity
                int currPoints = solveWithoutMemo(points, N, day+1, activity);
                // As we're striving for the maximum points hence update the value by maximum points each time
                maxPoints = max(maxPoints, currPoints + points[day][activity]);
            }
        }

        // Return the maximum points the geek can earn (result value) 
        return maxPoints;
    }
};

// Class to implement the "Bottom Up Approach":
class BottomUp {
public: 
    // #1 Method to find the maximum points the geek can earn, using 2d buffer for tabulation - O(N) & O(N)
    int maximumPoints_V1(vector<vector<int>>& points, int N) {
        // Tabulation buffer: dp[day][activity] stores the maximum points the geek can earn till this day including the activity of this day 
        vector<vector<int>> dp(N, vector<int>(3, 0));

        // Stores the points of all the activities of the first day
        dp[0] = points[0];
        
        // Visit the rest of the days one by one
        for(int day=1; day<N; day++) {
            // Visit each activity of the current day and compute the maximum points the geek can earn till each day by including the activity of that day
            for(int activity=0; activity<3; activity++) {
                if(activity == 0)
                    dp[day][activity] = points[day][activity] + max(dp[day-1][activity+1], dp[day-1][activity+2]);

                else if(activity == 1)
                    dp[day][activity] = points[day][activity] + max(dp[day-1][activity-1], dp[day-1][activity+1]);

                else
                    dp[day][activity] = points[day][activity] + max(dp[day-1][activity-1], dp[day-1][activity-2]);
            }
        }
        
        // Return the maximum points the geek can earn (result value) 
        return *max_element(begin(dp[N-1]), end(dp[N-1]));
    }

    // #2 Method to find the maximum points the geek can earn, using 1d buffer for tabulation - O(N) & O(1)
    int maximumPoints_V2(vector<vector<int>>& points, int N) {
        vector<int> currDay(3); // Stores the points of each activity of the day which is currently being seen
        vector<int> prevDay(3); // Stores the points of each activity of the previous day of any current day

        // Stores the points of all the activities of the first day
        prevDay = points[0];
        
        // Visit the rest of the days one by one
        for(int day=1; day<N; day++) {
            // Visit each activity of the current day and compute the maximum points the geek can earn till each day by including the activity of that day
            for(int activity=0; activity<3; activity++) {
                if(activity == 0)
                    currDay[activity] = points[day][activity] + max(prevDay[activity+1], prevDay[activity+2]);

                else if(activity == 1)
                    currDay[activity] = points[day][activity] + max(prevDay[activity-1], prevDay[activity+1]);

                else
                    currDay[activity] = points[day][activity] + max(prevDay[activity-1], prevDay[activity-2]);
            }
            // Update the information of the previous day for the upcoming day
            prevDay = currDay;
        }
        
        // Return the maximum points the geek can earn (result value) 
        return *max_element(begin(prevDay), end(prevDay));
    }

    // #3 Method to find the maximum points the geek can earn, using constant auxiliary space - O(N) & O(1)
    int maximumPoints_V3(vector<vector<int>>& points, int N) {
        // Visit the days one by one
        for(int day=1; day<N; day++) {
            // Visit each activity of the current day and compute the maximum points the geek can earn till each day by including the activity of that day
            for(int activity=0; activity<3; activity++) {
                if(activity == 0)
                    points[day][activity] += max(points[day-1][activity+1], points[day-1][activity+2]);

                else if(activity == 1)
                    points[day][activity] += max(points[day-1][activity-1], points[day-1][activity+1]);

                else
                    points[day][activity] += max(points[day-1][activity-1], points[day-1][activity-2]);
            }
        }
        
        // Return the maximum points the geek can earn (result value) 
        return *max_element(begin(points[N-1]), end(points[N-1]));
    }
};

// Driver code
int main() {
    // Controls the user wants to perform the operation or not
    bool userWantsOperation = true;

    while(userWantsOperation) {
        // Controls console clearance for both "windows" and "linux" user
        system("cls || clear");

        // Input the number of days
        int N;
        cout<<"Enter the total number of days: ";
        cin>>N;

        // Check the given value is valid or not
        if(N < 1 || N > 100000) {
            cout<<"Enter a value which lies within the problem constraints, application expects a positive integer!";
            return 0;
        }

        // Stores the points of each activity of each day
        vector<vector<int>> points(N, vector<int>(3, 0));

        // Input the points of each activity
        cout<<"\nEnter the points of each activity (Note: 3 activities are considered for each day):\n";
        for(int day=0; day<N; day++) {
            for(int activity=0; activity<3; activity++) {
                cin>>points[day][activity];
            }
        }

        // Call to find the maximum points the geek can earn
        BottomUp bottomUp;
        int maxPoints = bottomUp.maximumPoints_V3(points, N);
        cout<<"The maximum points the geek can earn is: "<<maxPoints;

        // Input section to control the flow of iterations of the application
        char userChoice;
        cout<<"\n\nPress \'R\' to restart the application, else it will exit: ";
        cin>>userChoice;
        userWantsOperation = (userChoice == 'R' ? true : false);
    }

    return 0;
}
/*
    Topics: Array | Matrix | Dynamic Programming
    Links: https://www.geeksforgeeks.org/problems/geeks-training/1
           https://www.codingninjas.com/studio/problems/ninja-s-training_3621003d?source=youtube&campaign=striver_dp_videos&utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_dp_videos&leftPanelTabValue=PROBLEM
*/
