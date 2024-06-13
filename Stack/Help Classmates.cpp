// Program to find each student's classmate with lower marks and a higher roll number ~ coded by Hiren
#include <iostream>
#include <vector>
#include <stack>
typedef long long ll;
using namespace std;

// Solution class
class Solution {
public:
    // #1 Method to find each student's classmate with lower marks and a higher roll number, using nested loop - O(N*N) & O(1)
    vector<ll> helpClassmates_V1(vector<ll>& students, int n) {
        // Iterate the array
        for(int i=0; i<n; i++) {
            // Stores the marks (marks less than the ith student) of the student having higher roll number 
            ll immediateLowerMarks = -1;
            // Iterate and find the marks of such student
            for(int j=i+1; j<n; j++) {
                if(students[j] < students[i]) {
                    immediateLowerMarks = students[j];
                    break;
                }
            }
            // Replace the marks of the ith student by the lower marks or -1 if not found
            students[i] = immediateLowerMarks;
        }
        // Return the result array
        return students;
    }

    // #2 Method to find each student's classmate with lower marks and a higher roll number, using buffer and 1 stack - O(N) & O(N)
    vector<ll> helpClassmates_V2(vector<ll>& students, int n) {
        // Buffer to store the result values
        vector<ll> output(n, -1);

        // Stores the marks of the students in monotonic fashion (increasing order)
        stack<ll> st;

        // Iterate the array from the back side
        for(int i=n-1; i>=0; i--) {
            // Pop all the elements (marks) greater than or equal to the "marks" of the ith student
            while(!st.empty() && students[st.top()] >= students[i])
                st.pop();

            // If the stack is not empty then replace the marks of the ith student by immediate lower marks 
            if(!st.empty())
                output[i] = students[st.top()];

            // Store the index of the ith student to the stack
            st.push(i);
        }

        // Return the result array
        return output;
    }

    // #3 Method to find each student's classmate with lower marks and a higher roll number, using 1 stack - O(N) & O(N)
    vector<ll> helpClassmates_V3(vector<ll>& students, int n) {
        // Stores the marks of the students in monotonic fashion (increasing order)
        stack<ll> st;
        
        // Iterate the array from the back side
        for(int i=n-1; i>=0; i--) {
            // Pop all the elements (marks) greater than or equal to the "marks" of ith student
            while(!st.empty() && st.top() >= students[i]) {
                st.pop();
            }
            // If the stack is not empty then replace the marks of the ith student by immediate lower marks 
            ll currStudentMarks = students[i];
            students[i] = (!st.empty() ? st.top() : -1);
            st.push(currStudentMarks);
        }
        
        // Return the result array
        return students;
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userWantsOperation = true;

    while(userWantsOperation) {
        // Handles console clearance for both "windows" and "linux" user
        system("cls || clear");

        // Input the size of the array
        int n;
        cout<<"Enter the total number of students: ";
        cin>>n;

        // Check the given size is valid or not
        if(n <= 0) {
            cout<<"Enter a valid size, applicatin expects a positive integer!";
            return 0;
        }

        // Stores the array values
        vector<ll> students(n, 0);

        // Input the array values
        for(int i=0; i<n; i++) {
            cout<<"Enter marks for the "<<i+1<<"th student: ";
            cin>>students[i];
        }

        // Call to find each student's classmate with lower marks and a higher roll number
        Solution solution;
        students = solution.helpClassmates_V3(students, n);

        cout<<"\nMarks after helping classmates: ";

        // Print values
        for(int marks : students) {   
            cout<<marks<<' ';
        }

        // Input section to handle the flow of iterations of the application
        char userChoise;
        cout<<"\n\nPress \'R\' to restart the application, else it will exit automatically: ";
        cin>>userChoise;
        userWantsOperation = (userChoise == 'R');
    }

    return 0;
}
/*
    Topics: Array | Stack | Monotonic Stack
    Link: https://www.geeksforgeeks.org/problems/help-classmates--141631/1
*/
