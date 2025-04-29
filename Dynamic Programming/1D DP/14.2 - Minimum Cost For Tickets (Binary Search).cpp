
// Code to find the minimum number of dollars you need to travel every day in the given list of days ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    int getNextStartDay(vector<int>& days, int target, int start) {
        int end = n-1, answer = n;

        while(start <= end) {
            int mid = start + (end - start) / 2;

            if(days[mid] >= target) {
                answer = mid;
                end = mid - 1;
            } else {
                start = mid + 1;
            }
        }

        return answer;
    } 

    // O(3^N * LogN) & O(N)
    int solveWithoutMemo(vector<int>& days, vector<int>& costs, int idx) {
        if(idx == n)
            return 0;

        // There are three possibilities to perform at each day
        int oneDayPass    = costs[0] + solveWithoutMemo(days, costs, getNextStartDay(days, days[idx] + 1, idx + 1));  // To buy 1-day pass
        int sevenDayPass  = costs[1] + solveWithoutMemo(days, costs, getNextStartDay(days, days[idx] + 7, idx + 1));  // To buy 7-day pass
        int thirtyDayPass = costs[2] + solveWithoutMemo(days, costs, getNextStartDay(days, days[idx] + 30, idx + 1)); // To buy 30-day pass

        return min({oneDayPass, sevenDayPass, thirtyDayPass}); 
    }

    // O(3*NLogN) & O(2*N)
    int solveWithMemo(vector<int>& dp, vector<int>& days, vector<int>& costs, int idx) {
        if(idx == n)
            return 0;

        if(dp[idx] != -1)
            return dp[idx];

        // There are three possibilities to perform at each day
        int oneDayPass    = costs[0] + solveWithMemo(dp, days, costs, getNextStartDay(days, days[idx] + 1, idx + 1));  // To buy 1-day pass
        int sevenDayPass  = costs[1] + solveWithMemo(dp, days, costs, getNextStartDay(days, days[idx] + 7, idx + 1));  // To buy 7-day pass
        int thirtyDayPass = costs[2] + solveWithMemo(dp, days, costs, getNextStartDay(days, days[idx] + 30, idx + 1)); // To buy 30-day pass

        return dp[idx] = min({oneDayPass, sevenDayPass, thirtyDayPass}); 
    }

public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        n = days.size();
        vector<int> dp(n, -1);
        return solveWithMemo(dp, days, costs, 0);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    int getNextStartDay(vector<int>& days, int target, int start) {
        int end = n-1, answer = n;

        while(start <= end) {
            int mid = start + (end - start) / 2;

            if(days[mid] >= target) {
                answer = mid;
                end = mid - 1;
            } else {
                start = mid + 1;
            }
        }

        return answer;
    } 

public:
    // O(NLogN) & O(N)
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        n = days.size();

        vector<int> dp(n + 1, -1);
        dp[n] = 0;

        for(int idx = n-1; idx >= 0; --idx) {
            int oneDayPass    = costs[0] + dp[getNextStartDay(days, days[idx] + 1, idx + 1)];
            int sevenDayPass  = costs[1] + dp[getNextStartDay(days, days[idx] + 7, idx + 1)];
            int thirtyDayPass = costs[2] + dp[getNextStartDay(days, days[idx] + 30, idx + 1)];
            dp[idx] = min({oneDayPass, sevenDayPass, thirtyDayPass}); 
        }

        return dp[0];
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/minimum-cost-for-tickets/description/ 
