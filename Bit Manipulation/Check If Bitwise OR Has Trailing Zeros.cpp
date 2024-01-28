// Program to check if it is possible to select two or more elements whose bitwise OR has trailing zeros or not ~ coded by Hiren
#include <bits/stdc++.h>
#define loop(i,n,k) for(int i=(k?k:0); i<n; i++)
#define even(n) (!(n % 2))
using namespace std;

// Solution class:
class Solution {
public:
    // #1 Method to check if bitwise OR has trailing zeros or not, using brute force - O(N*N) & O(1)
    bool hasTrailingZeros_V1(vector<int>& nums) {
        int n = nums.size();

        loop(i, n, 0) 
            loop(j, n, i+1) 
                // Its observed that the "even elements" always contain trailing zero, hence check for the trailing zeros by OR operation
                if((nums[i] | nums[j]) % 2 == 0)
                    return true;

        // Return false, if reached here 
        return false;
    }

    // #2 Method to check if bitwise OR has trailing zeros or not, using constant auxiliary space - O(N) & O(1)
    bool hasTrailingZeros_V2(vector<int>& nums) {
        int n = nums.size();

        // Stores any "even element" with its index
        int evenNum = -1, evenNumIdx = -1;

        // Iterate the array
        loop(i, n, 0) {
            // If the ith element is "even" then mark the element with its index
            if(even(nums[i])) {
                evenNum = nums[i], evenNumIdx = i; 
                break;
            }
        }

        // Iterate the array and look for an another "even element"
        loop(i, n, 0) {
            // If the ith element is "even" and its at unique index then check for the trailing zeros by OR operation
            if((i != evenNumIdx) && (even(nums[i])) && (evenNum | nums[i]) % 2 == 0) {
                return true;
            }
        }

        // Return false, if reached here 
        return false;
    }
};

// Driver code
int main() {
    // Tracks for the user wants to perform the operation or not
    bool canPerformOperation = true;

    while(canPerformOperation) {
        // Handles console clearance for both "windows" and "linux" user
        system("cls || clear");
        
        // Input section for the size of the array
        cout<<"Enter the size of the array: ";
        int n; cin>>n;  

        // Check for the given size is valid or not
        if(n <= 0) {
            cout<<"Enter a valid size, application expects a positive integer!";
            return 0;
        }

        vector<int> nums(n);

        cout<<"Enter the array elements: ";

        // Input section for the array elements
        for(int i=0; i<n; i++) {
            cin>>nums[i];
        }

        // Verification call
        Solution solution;
        if(solution.hasTrailingZeros_V2(nums))
            cout<<"Its possible to select two or more elements whose bitwise OR has trailing zeros!";
        else
            cout<<"Its not possible to select two or more elements whose bitwise OR has trailing zeros!";

        // Input section to handle the flow of iterations of the application
        char userChoise;
        cout<<"\n\nPress \'R\' to restart the application, else application will exit automatically: ";
        cin>>userChoise;
        canPerformOperation = (userChoise == 'R' ? true : false);        
    }

    return 0;
}
// Link: https://leetcode.com/problems/check-if-bitwise-or-has-trailing-zeros/
