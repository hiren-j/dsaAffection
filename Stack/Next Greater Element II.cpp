// Program to find the next largest element of each element of a circular integer array ~ coded by Hiren
#include <iostream>
#include <cstdlib>
#include <climits>
#include <vector>
#include <stack>
using namespace std;

// #1 Solution class
class Solution_V1 {
public:
    // Method to find the next largest element of each element, using nested loop - O(N*N) & O(N)
    vector<int> nextLargestElement(vector<int>& nums) {
        int n = nums.size();

        // Stores the result values
        vector<int> output(n, INT_MAX);

        // Iterate the array
        for(int i=0; i<n; i++) {
            // Find the "next largest element" of the "ith element" at the "right side" of it
            for(int j=i+1; j<n; j++) {
                if(nums[j] > nums[i]) {
                    output[i] = nums[j];
                    break;
                }
            }

            // If not found then find it at the "left side" of the "ith element"
            if(output[i] == INT_MAX) {
                output[i] = -1;
                for(int k=0; k<i; k++) {
                    if(nums[k] > nums[i]) {
                        output[i] = nums[k];
                        break;
                    }
                }
            }
        }

        // Return the result array
        return output;
    }
};
// Note: The auxiliary space is considered for the "output array", its because even if its not the user's demand but we still need the array

// #2 Solution class
class Solution_V2 {
public: 
    // Method to find the next largest element of each element, using 1 stack - O(N) & O(N)
    vector<int> nextLargestElement(vector<int>& nums) {
        // Stores the result values
        vector<int> output(nums.size(), -1);

        // Stores the elements in monotonic fashion (decreasing order)
        stack<int> s;
        
        // Replace each element of the array by its "next largest element" twice times
        updateNLE(nums, output, s);
        updateNLE(nums, output, s);

        // Return the result array
        return output;
    }

private:
    // Method to replace all the elements of the array by their next largest element - O(N) & O(N)
    void updateNLE(vector<int>& nums, vector<int>& output, stack<int>& s) {
        // Iterate the array from the back side
        for(int i=nums.size()-1; i>=0; i--) {
            // Pop all the elements "lesser than or equal" to the "ith element"
            while(!s.empty() && nums[s.top()] <= nums[i])
                s.pop();

            // If the stack is not empty then replace the "ith element" by its "next largest element"
            if(!s.empty())
                output[i] = nums[s.top()];

            // Store the "index of the ith element" to the stack
            s.push(i);
        }
    }
};

// #3 Solution class
class Solution_V3 {
public: 
    // Method to find the next largest element of each element, using 1 stack - O(N) & O(N)
    vector<int> nextLargestElement(vector<int>& nums) {
        int n = nums.size();
        vector<int> output(n, -1);
        updateNLE(nums, output, n);
        return output;
    }

private:
    // Method to replace all the elements of the array by their next largest element - O(N) & O(N)
    void updateNLE(vector<int>& nums, vector<int>& output, int n) {
        // Stores the elements in monotonic fashion (decreasing order)
        stack<int> s;

        // Iterate "twice of the size of the array" from the back side
        for(int i = 2*n-1; i >= 0; --i) {
            // Pop all the elements "lesser than or equal" to the "element of the proper index"
            while(!s.empty() && s.top() <= nums[i%n])
                s.pop();

            // If the stack is not empty then replace the "element of proper index" by its "next largest element"
            if(!s.empty())
                output[i%n] = s.top();

            // Store the element of the "proper index" to the stack
            s.push(nums[i%n]);
        }
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool canPerformOperation = true;

    while(canPerformOperation) {
        // Handles console clearance for both "windows" and "linux" user
        system("cls || clear");

        // Input the size of the "circular array"
        int n;
        cout<<"Enter size of the circular array: ";
        cin>>n;

        // Check the given size is valid or not
        if(n <= 0) {
            cout<<"Enter a valid size, applicatin expects a positive integer!";
            return 0;
        }

        // Stores the values of the "circular array"
        vector<int> nums(n, 10);

        // Input the array values
        cout<<"Enter values of the circular array: ";
        for(int i=0; i<n; i++)
            cin>>nums[i];

        // Call to find the "next largest element" of "each element" of the array
        Solution_V3 solution;
        nums = solution.nextLargestElement(nums);

        // Print values
        cout<<"Result array: ";
        for(int num : nums) 
            cout<<num<<' ';

        // Input section to handle the flow of iterations of the application
        char userChoise;
        cout<<"\n\nPress \'R\' to restart the application, else it will exit automatically: ";
        cin>>userChoise;
        canPerformOperation = (userChoise == 'R' ? true : false);
    }

    return 0;
}
/*
    Topics: Array | Stack | Monotonic Stack
    Link: https://leetcode.com/problems/next-largest-element-ii/description/
*/
