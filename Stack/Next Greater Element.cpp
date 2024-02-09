// Program to find the the next largest element of each element of an array ~ coded by Hiren
#include <iostream>
#include <cstdlib>
#include <vector>
#include <stack>
typedef long long ll;
using namespace std;

// Solution class
class Solution {
public:
    // #1 Method to find the next largest element of each element, using nested loop - O(N*N) & O(1)
    vector<ll> nextLargestElement_V1(vector<ll>& nums, int n) {
        // Iterate the array
        for(int i=0; i<n; i++) {
            // Stores the next largest element of the ith element
            ll nextLargest = -1;
            // Iterate and find the next largest element
            for(int j=i+1; j<n; j++) {
                if(nums[j] > nums[i]) {
                    nextLargest = nums[j];
                    break;
                }
            }
            // Replace the ith element by its next largest element or -1 if not found
            nums[i] = nextLargest;
        }
        // Return the result array
        return nums;
    }

    // #2 Method to find the next greater element of each element, using buffer and 1 stack - O(N) & O(N)
    vector<ll> nextLargestElement_V2(vector<ll>& nums, int n) {
        // Buffer to store the result values
        vector<ll> output(n, -1);

        // Stores the elements in monotonic fashion (decreasing order)
        stack<ll> st;

        // Iterate the array from the back side
        for(int i=n-1; i>=0; i--) {
            // Pop all the elements lesser than or equal to the ith element
            while(!st.empty() && nums[st.top()] <= nums[i])
                st.pop();

            // If the stack is not empty then replace the ith element by its next greater element
            if(!st.empty())
                output[i] = nums[st.top()];

            // Store the index of the ith element to the stack
            st.push(i);
        }

        // Return the result array
        return output;
    }

    // #3 Method to find the next largest element of each element, using 1 stack - O(N) & O(N)
    vector<ll> nextLargestElement_V3(vector<ll>& nums, int n) {
        // Stores the elements in monotonic fashion (decreasing order)
        stack<ll> st;
        
        // Iterate the array from the back side
        for(int i=n-1; i>=0; --i) {
            // Pop all the elements lesser than or equal to the ith element
            while(!st.empty() && st.top() <= nums[i]) {
                st.pop();
            }
            // If the stack is not empty then replace the ith element by its next largest element
            ll tmp = nums[i];
            nums[i] = (!st.empty() ? st.top() : -1);
            st.push(tmp);
        }
        
        // Return the result array
        return nums;
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
        cout<<"Enter the size of the array: ";
        cin>>n;

        // Check the given size is valid or not
        if(n <= 0) {
            cout<<"Enter a valid size, applicatin expects a positive integer!";
            return 0;
        }

        // Stores the array values
        vector<ll> nums(n, 0);
        cout<<"Enter values of the array: ";

        // Input the array values
        for(int i=0; i<n; i++)
            cin>>nums[i];

        // Call to find the next largest element of each element of the array
        Solution solution;
        nums = solution.nextLargestElement_V3(nums, n);

        // Print values
        cout<<"Result array: ";
        for(int num : nums) 
            cout<<num<<' ';

        // Input section to handle the flow of iterations of the application
        char userChoise;
        cout<<"\n\nPress \'Y\' to perform the same operation on an another array, else application will exit automatically: ";
        cin>>userChoise;
        userWantsOperation = (userChoise == 'Y') ? true : false ;
    }

    return 0;
}
/*
    Topics: Array | Stack | Monotonic Stack
    Link: https://www.geeksforgeeks.org/problems/next-larger-element-1587115620/1
*/
