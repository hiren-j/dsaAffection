// Program to check if it is possible to select two or more elements whose bitwise OR has trailing zeros or not ~ coded by Hiren
#include <bits/stdc++.h>
using namespace std;

#define loop(i,n,k) for(int i=(k?k:0); i<n; i++)
#define itr(it,arr) for(auto it = begin(arr); it != end(arr); it++)
#define sortThe(arr) sort(begin(arr), end(arr));
#define ct cout
#define cn cin
#define pb push_back
#define pp pop_back
#define F first
#define S second
#define ll long long
#define even(n) if(!(n % 2))
#define odd(n) if(n % 2)
typedef pair<int, int> p;
typedef vector<int> vec;
typedef vector<vector<int>> vec2d;
typedef map<int, int> omap;
typedef unordered_map<int, int> umap;
typedef set<int> oset;
typedef unordered_set<int> uset;
typedef queue<int> q;

// #1 Method to check if bitwise OR has trailing zeros or not, using brute force - O(N*N) & O(1)
bool hasTrailingZeros(vector<int>& nums) {
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
bool hasTrailingZeros_(vector<int>& nums) {
    int n = nums.size();

    // Stores any "even element" with its index
    int evenNum = -1, evenNumIdx = -1;
    
    // Iterate the array
    loop(i, n, 0) {
        // If the ith element is "even" then mark the element with its index
        if(!(nums[i] % 2)) {
            evenNum = nums[i], evenNumIdx = i; 
            break;
        }
    }
    
    // Iterate the array and look for an another "even element"
    loop(i, n, 0) {
        // If the ith element is "even" and its at unique index then check for the trailing zeros by OR operation
        if((i != evenNumIdx) && !(nums[i] % 2) && (evenNum | nums[i]) % 2 == 0) {
            return true;
        }
    }

    // Return false, if reached here 
    return false;
}

// Driver code
int main() {
    vector<int> nums = {2,4,8,16};

    // Print values
    for(int num : nums)
        cout<<num<<' ';

    // Verification call
    if(hasTrailingZeros_(nums))
        cout<<"\nIt is possible to select two or more elements whose bitwise OR has trailing zeros!";
    else
        cout<<"\nIt is not possible to select two or more elements whose bitwise OR has trailing zeros!";

    return 0;
}
// Link: https://leetcode.com/problems/check-if-bitwise-or-has-trailing-zeros/
