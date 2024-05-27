// Program to return an array "answer" such that "answer[i]" is the number of days we have to wait after the ith day to get a warmer temperature ~ coded by Hiren
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Solution class:
class Solution {
public:
    // #1 Method to return an array "answer" such that "answer[i]" contains the specified value, using nested loop - O(N*N) & O(N)
    vector<int> dailyTemperatures_V1(vector<int>& temps) {
        int n = temps.size();

        // Stores the result values
        vector<int> answer(n);
        
        // Iterate the array
        for(int i=0; i<n; i++) {
            // Stores the number of days the "ith temperature / ith element" have to wait to get a warmer temperature 
            int daysToWait = 1;
            // Find the "next greater element / immediate greater temperature" of the "ith temperature" and then update the "result count / result value" for it
            for(int j=i+1; j<n; j++) {
                if(temps[j] > temps[i]) {
                    answer[i] = daysToWait;
                    break;
                }
                daysToWait++;
            }
        }

        // Return the result array
        return answer;
    }

    // #2 Method to return an array "answer" such that "answer[i]" contains the specified value, using buffer with 1 stack - O(N) & O(N)
    vector<int> dailyTemperatures_V2(vector<int>& temps) {
        int n = temps.size();

        // Stores the result values
        vector<int> answer(n);

        // Stores the values in monotonic fashion (decreasing order)
        stack<int> s;

        for(int i = n-1; i >= 0; --i) {
            // Pop all the elements until the "ith element / with temperature" don't get a "greater element / warmer temperature" on its "right side"
            while(!s.empty() && temps[s.top()] <= temps[i])
                s.pop();

            // If the stack is not empty then store the number of days the "ith temperature / ith element" have to wait to get a warmer temperature, else then no future day is possible for it
            if(!s.empty())
                answer[i] = s.top() - i;

            // Store the index of the "ith temperature / ith element" to the stack
            s.push(i);
        } 

        // Return the result array
        return answer;
    }

    // #3 Method to return an array "answer" such that "answer[i]" contains the specified value, using 1 stack - O(N) & O(N)
    vector<int> dailyTemperatures_V3(vector<int>& temps) {
        int n = temps.size();

        // Stores the "values with their index" in monotonic fashion (decreasing order)
        stack<pair<int, int>> s;

        for(int i = n-1; i >= 0; --i) {
            // Pop all the elements until the "ith element / with temperature" don't get a "greater element / warmer temperature" on its "right side"
            while(!s.empty() && s.top().first <= temps[i])
                s.pop();

            int num = temps[i];

            // If the stack is not empty then store the number of days the "ith temperature / ith element" have to wait to get a warmer temperature, else then no future day is possible for it
            temps[i] = (!s.empty() ? s.top().second - i : 0); 

            // Store the value of the "ith temperature with its index" to the stack
            s.push({num, i}); 
        } 

        // Return the "modified array / result array"
        return temps;
    }
};

// Method to print the array - O(N) & O(1)
void printArray(vector<int>& nums) {
    for(int num : nums) {
        cout<<num<<' ';
    }
    cout<<'\n';
}

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool canPerformOp = true;

    while(canPerformOp) {
        // Handles console clearance for both "windows" and "linux" user
        system("cls || clear");

        // Input the size of the array
        int size;
        cout<<"Enter the size of the array: ";
        cin>>size;

        // Check the given size is valid or not
        if(size <= 0) {
            cout<<"Enter a valid size, application expects a positive integer!";
            return 0;
        }

        // Stores the array values
        vector<int> nums(size);

        // Input the array values
        for(int i=0; i<size; ++i) {
            cout<<"Enter the value for "<<i<<"th index: ";
            cin>>nums[i];
        }

        // Print call
        cout<<"\nYour array: ";
        printArray(nums);

        // Call to get the "answer" array
        Solution solution;
        solution.dailyTemperatures_V3(nums);

        // Print call
        cout<<"Result array: ";
        printArray(nums);

        // Input section to control the flow of iterations
        char userChoise;
        cout<<"\nPress \'R\' restart the application, else it will exit automatically: ";
        cin>>userChoise;
        canPerformOp = (userChoise == 'R' ? true : false);
    }

    return 0;
}
/*
    Topics: Array | Stack | Monotonic Stack
    Link: https://leetcode.com/problems/daily-temperatures/description/?envType=daily-question&envId=2024-01-31
*/
