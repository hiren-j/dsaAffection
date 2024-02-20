// Program to return an integer array answer where answer[i] is the final price we will pay for the ith item of the shop, considering the special discount ~ coded by Hiren
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Solution class
class Solution {
public:
    // #1 Method to return an array answer where answer[i] contains the specified value, using nested loop - O(N*N) & O(1)
    vector<int> finalPrices_V1(vector<int>& prices) {
        int n = prices.size();

        for(int i=0; i<n; i++) {
            // Stores the next smaller element of the ith element
            int nextSmaller = -1;
            // Iterate and find the next smaller element from the right side of the ith element
            for(int j=i+1; j<n; j++) {
                if(prices[j] <= prices[i]) {
                    nextSmaller = prices[j];
                    break;
                }
            }
            // Replace the ith element by its next smaller element (considering the special discount) or -1 if not found
            prices[i] = (nextSmaller == -1) ? prices[i] : prices[i] - nextSmaller;
        }

        // Return the "modified array / result array"
        return prices;
    }

    // #2 Method to return an array answer where answer[i] contains the specified value, using buffer and 1 stack - O(N) & O(N)
    vector<int> finalPrices_V2(vector<int>& prices) {
        int n = prices.size();

        // Stores the result values
        vector<int> answer(n);

        // Stores the elements in monotonic fashion (increasing order)
        stack<int> s;

        // Iterate the array from the back side
        for(int i=n-1; i>=0; --i) {
            // Pop all the elements greater than the ith element
            while(!s.empty() && s.top() > prices[i]) {   
                s.pop();
            }
            // If the stack is not empty then replace the ith element by its next smaller element (considering the special discount)
            answer[i] = (!s.empty() ? prices[i] - s.top() : prices[i]);
            s.push(prices[i]);
        }

        // Return the result array
        return answer;
    }

    // #3 Method to return an array answer where answer[i] contains the specified value, using 1 stack - O(N) & O(N)
    vector<int> finalPrices_V3(vector<int>& prices) {
        int n = prices.size();

        // Stores the elements in monotonic fashion (increasing order)
        stack<int> s;

        // Iterate the array from the back side
        for(int i=n-1; i>=0; --i) {
            // Pop all the elements greater than the ith element
            while(!s.empty() && s.top() > prices[i]) {   
                s.pop();
            }

            int currNum = prices[i];

            // If the stack is not empty then replace the ith element by its next smaller element (considering the special discount)
            prices[i] = (!s.empty() ? prices[i] - s.top() : prices[i]);

            // Store the ith element to the stack
            s.push(currNum);
        }

        // Return the "modified array / result array"
        return prices;
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
        cout<<"Enter total number of items for the shop: ";
        cin>>n;

        // Check the given size is valid or not
        if(n <= 0) {
            cout<<"Enter a valid size, applicatin expects a positive integer!";
            return 0;
        }

        // Stores the array values
        vector<int> prices(n, 0);

        // Input the array values
        cout<<"\nEnter prices of the items:\n";
        for(int i=0; i<n; i++) {
            cout<<"-> Enter price for the "<<i<<"th item: ";
            cin>>prices[i];
        }

        // Call to find the next smallest element of each element of the array
        Solution obj;   
        prices = obj.finalPrices_V3(prices);

        // Print values
        cout<<"\nFinal prices (considering the special discount): ";
        for(int num : prices) 
            cout<<num<<' ';

        // Input section to control the flow of iterations of the application
        char userChoise;
        cout<<"\n\nPress \'R\' to restart the application, else it will exit automatically: ";
        cin>>userChoise;
        userWantsOperation = (userChoise == 'R' ? true : false);
    }

    return 0;
}
/*
    Topics: Array | Stack | Monotonic Stack
    Link: https://leetcode.com/problems/final-prices-with-a-special-discount-in-a-shop/description/
*/
