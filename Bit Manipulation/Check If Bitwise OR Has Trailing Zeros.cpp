// Program to check if it is possible to select two or more elements whose bitwise OR has trailing zeros or not ~ coded by Hiren
#include <bits/stdc++.h>
using namespace std;
#define loop(i,n,k) for(int i=(k?k:0); i<n; i++)
#define even(n) (!(n % 2))

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

// Driver code
int main() {
    cout<<"Enter the number of testcases you want: ";
    int testCases; cin>>testCases;

    if(testCases <= 0) {
        std::cout<<"Enter a valid number for the testcases, application expects a positive integer!";
        return 0;
    }

    while(testCases--) {
        system("clear || cls");
        
        cout<<"Enter the size of the array: ";
        int n; cin>>n;

        vector<int> nums(n);

        cout<<"\nEnter the array elements: ";

        for(int i=0; i<n; i++) {
            cin>>nums[i];
        }

        // Verification call
        if(hasTrailingZeros_V2(nums))
            cout<<"\nIt is possible to select two or more elements whose bitwise OR has trailing zeros!";
        else
            cout<<"\nIt is not possible to select two or more elements whose bitwise OR has trailing zeros!";
        
        if(testCases != 0)
            cout<<"\n\nApplication will restart in 10 seconds!";
        else
            cout<<"\n\nApplication will close in 10 seconds!";
            
        // Add a 10-second delay before the next iteration
        this_thread::sleep_for(chrono::seconds(10));
    }

    return 0;
}
// Link: https://leetcode.com/problems/check-if-bitwise-or-has-trailing-zeros/
