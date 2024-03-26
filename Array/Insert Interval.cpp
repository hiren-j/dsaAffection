// Program to insert "newInterval" into "intervals" such that "intervals" is still sorted in ascending order by their start time and "intervals" still does not have any overlapping intervals (merge overlapping intervals if necessary) ~ coded by Hiren
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

// Solution class:
class Solution {
public:
    // #1 Method to insert "newInterval" into "intervals", using sorting - O(NLogN) & O(1) : Where N let be the size of "intervals"
    vector<vector<int>> insert_V1(vector<vector<int>>& intervals, vector<int>& newInterval) {
        // Insert the "newInterval" into the "intervals" and sort the "intervals" so it remains sorted in ascending order
        intervals.push_back(newInterval);
        sort(begin(intervals), end(intervals));
        int n = intervals.size();

        // Stores the "result intervals"
        vector<vector<int>> answer;

        // Iterate the "intervals"
        for(int index = 0; index < n; ++index) {
            int currStartTime = intervals[index][0]; // Represents the start time of the current interval
            int currEndTime   = intervals[index][1]; // Represents the end time of the current interval
            // If the result array is empty or the last interval of the result array is ending before the start time of the current interval, then store the current interval to the result array
            if(answer.empty() || answer.back()[1] < currStartTime) {
                answer.push_back(intervals[index]);
            }
            // Else, merge the overlapping intervals by updating the end time of the last interval by the maximum value
            else {
                answer.back()[1] = max(answer.back()[1], currEndTime);
            }
        }

        // Return the "result intervals"
        return answer;
    }

    // #2 Method to insert "newInterval" into "intervals", using no sorting - O(N) & O(1) : Where N let be the size of "intervals"
    vector<vector<int>> insert_V2(vector<vector<int>>& intervals, vector<int>& newInterval) {
        int n = intervals.size();
        
        // Iterate and find the interval which is the maximum according to the start time
        for(int index = 0; index < n; ++index) {
            if(newInterval[0] < intervals[index][0]) {
                swap(newInterval, intervals[index]);
            }
        }

        // Store this interval (which is the maximum according to the start time) at the end of the "intervals"
        intervals.push_back(newInterval); 
        n++;

        // Stores the "result intervals"
        vector<vector<int>> answer;

        // Iterate the "intervals"
        for(int index = 0; index < n; ++index) {
            int currStartTime = intervals[index][0]; // Represents the start time of the current interval
            int currEndTime   = intervals[index][1]; // Represents the end time of the current interval
            // If the result array is empty or the last interval of the result array is ending before the start time of the current interval, then store the current interval to the result array
            if(answer.empty() || answer.back()[1] < currStartTime) {
                answer.push_back(intervals[index]);
            }
            // Else, merge the overlapping intervals by updating the end time of the last interval by the maximum value
            else {
                answer.back()[1] = max(answer.back()[1], currEndTime);
            }
        }

        // Return the "result intervals"
        return answer;
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userWantsOperation = true;

    while(userWantsOperation) {
        // Controls console clearance for both "windows" and "linux" user
        system("cls || clear");

        cout<<"Note: The application only accepts non-decimal numeric type value, unless specified!\n";

        // Input the size of intervals
        int n;
        cout<<"\nEnter the total number of intervals: ";
        cin>>n;

        // Check the given size is lying within the problem constraints or not
        if(n <= 0 || n >= 10001) {
            cout<<"You must enter a size which lies between 1 and 10^4!\n";
        }
        else {                
            // Stores the "intervals"
            vector<vector<int>> intervals(n, vector<int>(2, 0));

            // Input the information of each interval
            cout<<"\nNote: Each interval considers two information: [startTime, endTime]\n";
            for(int index = 0; index < n;) {
                cout<<"Enter the information of the "<<index<<"th interval: ";
                cin>>intervals[index][0];
                cin>>intervals[index][1];
                if(intervals[index][0] <= 0 || intervals[index][0] >= 100001 || intervals[index][1] <= 0 || intervals[index][1] >= 100001)
                    cout<<"You must enter the [startTime, endTime] which lies between 1 and 10^5!\n";
                else
                    ++index;
            }

            // Stores the values of "newInterval"
            vector<int> newInterval(2, 0);

            // Input the values of "newInterval"
            while(true) {
                cout<<"\nEnter the information of the new-interval: ";
                cin>>newInterval[0];
                cin>>newInterval[1];
                if(newInterval[0] <= 0 || newInterval[0] >= 100001 || newInterval[1] <= 0 || newInterval[1] >= 100001)
                    cout<<"You must enter the [startTime, endTime] which lies between 1 and 10^5!\n";
                else
                    break;
            }

            // Sort the "intervals" to meet the problem requirement
            sort(begin(intervals), end(intervals));            

            // Call to insert the "newInterval" into "intervals"
            Solution solution;
            intervals = solution.insert_V2(intervals, newInterval);

            // Print the result values ("intervals" of after insertion)
            cout<<"\nIntervals after insertion:\n";
            for(auto& interval : intervals) {
                cout<<"["<<interval[0]<<", "<<interval[1]<<"]\n";
            }
        }

        // Input section to control the flow of iterations of the application
        char userChoice;
        cout<<"\nPress \'R\' to restart the application, else it will exit: ";
        cin>>userChoice;
        userWantsOperation = (userChoice == 'R');
    }

    return 0;
}
/*
    Topics: Array
    Link: https://leetcode.com/problems/insert-interval/?envType=daily-question&envId=2024-03-17
*/
