// Program to find the earliest hour at which the shop must be closed to incur a minimum penalty ~ coded by Hiren
#include <iostream>
#include <cstdlib>
#include <climits>
#include <vector>

// Solution class
class Solution {
public:
    // #1 Method to find the earliest hour, using nested loop - O(N*N) & O(1) : Where N is the size of the "cust" array
    int bestClosingTime_V1(const std::string& cust) {
        int n = cust.size();

        int minPenalty = INT_MAX; // Stores the value of the "minimum penalty"
        int minHour    = INT_MAX; // Stores the value of the "earliest hour / minimum hour" at which the "minimum penalty" occurs

        // Iterate the array
        for(int i=0; i<=n; i++) {
            // Stores the "total penalty" by considering to close the shop at this ith hour
            int penaltyTotal = 0;

            // Calculate the penalty from the left side of the ith hour
            for(int j=0; j<i; j++) {
                // If the shop is open and no customer comes then the penalty increases by one
                if(cust[j] == 'N') {
                    penaltyTotal++;
                }
            }

            // Calculate the penalty from the right side of the ith hour
            for(int j=i; j<n; j++) {
                // If the shop is closed and the customer comes, then the penalty increases by one
                if(cust[j] == 'Y') {
                    penaltyTotal++;
                }
            }

            // If the penalty calculated for the "ith hour" is lesser than the "minimum penalty", then update the value of the "earliest hour"
            if(penaltyTotal < minPenalty) {
                minPenalty = penaltyTotal;
                minHour = i;
            }
        }

        // Return the value of the "earliest hour / minimum hour" 
        return minHour;
    }

    // #2 Method to find the earliest hour, using two buffers - O(N) & O(N) : Where N is the size of the "cust" array
    int bestClosingTime_V2(const std::string& cust) {
        int n = cust.size();

        std::vector<int> penaltyLeft(n);  // Stores the penalty (calculated from the left side) for "each of the hour"
        std::vector<int> penaltyRight(n); // Stores the penalty (calculated from the right side) for "each of the  hour"

        // Stores the "total penalty" for a specific hour by considering to close the shop at that hour
        int penaltyTotal = 0;

        // Iterate and calculate the penalty from the "left side" for "each of the hour" 
        for(int hour=0; hour<n; hour++) {
            // Store the "total penalty" for this specific hour
            penaltyLeft[hour] = penaltyTotal;
            // If the shop is open and no customer comes, then the penalty increases by one
            penaltyTotal += (cust[hour] == 'N') ? 1 : 0; 
        }

        // Set the "total penalty" to zero
        penaltyTotal = 0;

        // Iterate and calculate the penalty from the "right side" for "each of the hour" 
        for(int hour=n-1; hour>=0; hour--) {
            // If the shop is closed and a customer comes, then the penalty increases by one
            penaltyTotal += (cust[hour] == 'Y') ? 1 : 0;
            // Store the "total penalty" for this specific hour
            penaltyRight[hour] = penaltyTotal; 
        }

        // Set the "total penalty" to zero
        penaltyTotal = 0;

        // Mark the penalty of the "nth hour" as the "minimum penalty" and update the value of the "earliest hour" by the "nth hour"
        int minPenalty = penaltyLeft[n-1], minHour = n;
        
        // Iterate from the back side of the array
        for(int hour=n-1; hour>=0; hour--) {
            // Calculate and store the "total penalty" for this specific hour
            penaltyTotal = penaltyLeft[hour] + penaltyRight[hour];

            // If the penalty calculated for this hour is "lesser than or equal" to the "minimum penalty", then update the value of the "earliest hour"
            if(penaltyTotal <= minPenalty) {
                minPenalty = penaltyTotal;
                minHour = hour;
            }
        }

        // Return the value of the "earliest hour / minimum hour"
        return minHour;
    }

    // #3 Method to find the earliest hour, using two buffers - O(N) & O(N) : Where N is the size of the "cust" array
    int bestClosingTime_V3(const std::string& cust) {
        int n = cust.size();

        std::vector<int> penaltyLeft(n);  // Stores the penalty (calculated from the left side) for "each of the hour"
        std::vector<int> penaltyRight(n); // Stores the penalty (calculated from the right side) for "each of the  hour"

        int currPenaltyL = 0; // Tracks the penalty (calculated from the left side) for a specific hour
        int currPenaltyR = 0; // Tracks the penalty (calculated from the right side) for a specific hour

        // Iterate and calculate the penalty from the "left side" and "right side" for "each of the hour" 
        for(int hour=0; hour<n; hour++) {
            penaltyLeft[hour] = currPenaltyL;
            currPenaltyL += (cust[hour] == 'N') ? 1 : 0;
            currPenaltyR += (cust[n-1-hour] == 'Y') ? 1 : 0;
            penaltyRight[n-1-hour] = currPenaltyR;
        }

        // Mark the penalty of the "nth hour" as the "minimum penalty" and update the value of the "earliest hour" by the "nth hour"
        int minPenalty = penaltyLeft[n-1], minHour = n;

        // Iterate from the back side of the array
        for(int hour=n-1; hour>=0; hour--) {
            // Calculate and store the "total penalty" for this specific hour
            int penaltyTotal = penaltyLeft[hour] + penaltyRight[hour];
            
            // If the penalty calculated for this hour is "lesser than or equal" to the "minimum penalty", then update the value of the "earliest hour"
            if(penaltyTotal <= minPenalty) {
                minPenalty = penaltyTotal;
                minHour = hour;
            }
        }

        // Return the value of the "earliest hour / minimum hour"
        return minHour;
    }

    // #4 Method to find the earliest hour, using single buffer - O(N) & O(N) : Where N is the size of the "cust" array
    int bestClosingTime_V4(const std::string& cust) {
        int n = cust.size();
        
        // Stores the penalty (calculated from the left side) for "each of the hour"
        std::vector<int> penaltyLeft(n);
        
        // Stores the "total penalty" for a specific hour by considering to close the shop at that hour
        int penaltyTotal = 0;

        // Iterate and calculate the penalty from the "left side" for "each of the hour" 
        for(int hour=0; hour<n; hour++) {
            // Store the "total penalty" for this specific hour
            penaltyLeft[hour] = penaltyTotal;
            // If the shop is open and no customer comes, then the penalty increases by one
            penaltyTotal += (cust[hour] == 'N') ? 1 : 0;
        }

        // Set the "total penalty" to zero
        penaltyTotal = 0;

        // Mark the penalty of the "nth hour" as the "minimum penalty" and update the value of the "earliest hour" by the "nth hour"
        int minPenalty = penaltyLeft[n-1], minHour = n;

        for(int hour=n-1; hour>=0; hour--) {
            // Calculate and store the "penalty from the right side" for this specific hour
            penaltyTotal += (cust[hour] == 'Y') ? 1 : 0;
            int penaltyRight_i = penaltyTotal;

            // Calculate and store the "total penalty" for this specific hour
            int penaltyTotal = penaltyLeft[hour] + penaltyRight_i;
            
            // If the penalty calculated for this hour is "lesser than or equal" to the "minimum penalty", then update the value of the "earliest hour"
            if(penaltyTotal <= minPenalty) {
                minPenalty = penaltyTotal;
                minHour = hour;
            }
        }

        // Return the value of the "earliest hour / minimum hour"
        return minHour;
    }
};

// Driver code
int main() {
    int testCases;
    std::cout<<"Enter the number of testcases you want: ";
    std::cin>>testCases;

    if(testCases > 0) {
        std::cout<<"\n-> \'Y\' represents the customer comes!";
        std::cout<<"\n-> \'N\' represents no customer comes!";
    }

    while(testCases-- > 0) {
        std::string customers;
        std::cout<<"\n\nEnter a string: "; 
        std::cin>>customers;
        Solution obj;
        int minHour = obj.bestClosingTime_V4(customers);
        std::cout<<"The earliest hour at which the shop must be closed to incur a minimum penalty is: "<<minHour;
    }

    return 0;
}
/*
    Topics: String | Prefix Sum
    Link: https://leetcode.com/problems/minimum-penalty-for-a-shop/description/
*/
