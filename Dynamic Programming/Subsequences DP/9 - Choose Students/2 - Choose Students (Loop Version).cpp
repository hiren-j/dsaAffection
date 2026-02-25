// Code to find the number of ways you can choose `chooseLimit` students from a class of `totalStudents` students ~ coded by vHiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int totalStudents;

    // O(2^TS) & O(TS) : Where TS = totalStudents
    int solveWithoutMemo(int start, int chooseLimit) {
        if(chooseLimit == 0) 
            return 1;
    
        if(start == totalStudents)
            return 0;

        int count = 0;

        for(int student = start; student < totalStudents; ++student) {
            int chooseStudent = solveWithoutMemo(student + 1, chooseLimit - 1); 
            count += chooseStudent;
        }

        return count;
    }    

    // O(TS*TS*CL) & O(TS*CL) : Where TS = totalStudents, CL = chooseLimit
    int solveWithMemo(vector<vector<int>>& dp, int start, int chooseLimit) {
        if(chooseLimit == 0) 
            return 1;
    
        if(start == totalStudents)
            return 0;

        if(dp[start][chooseLimit] != -1)
            return dp[start][chooseLimit];

        int count = 0;

        for(int student = start; student < totalStudents; ++student) {
            int chooseStudent = solveWithMemo(dp, student + 1, chooseLimit - 1); 
            count += chooseStudent;
        }

        return dp[start][chooseLimit] = count;
    }
    
public:
    int numWays(int n, int chooseLimit) {
        totalStudents = n;
        vector<vector<int>> dp(totalStudents + 1, vector<int>(chooseLimit + 1, -1));
        return solveWithMemo(dp, 0, chooseLimit);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int totalStudents;

    // O(TS*GL*TS) & O(TS*GL) : Where TS = totalStudents, GL = givenLimit
    int solveBy2DTable(int givenLimit) {
        vector<vector<int>> dp(totalStudents + 1, vector<int>(givenLimit + 1, -1));
        dp[totalStudents][0] = 1;

        for(int chooseLimit = 1; chooseLimit <= givenLimit; ++chooseLimit)
            dp[totalStudents][chooseLimit] = 0;

        for(int start = totalStudents - 1; start >= 0; --start) {
            dp[start][0] = 1;
            for(int chooseLimit = 1; chooseLimit <= givenLimit; ++chooseLimit) {
                int count = 0;
                for(int student = start; student < totalStudents; ++student) {
                    int chooseStudent = dp[student + 1][chooseLimit - 1]; 
                    count += chooseStudent;
                }
                dp[start][chooseLimit] = count;
            }
        }

        return dp[0][givenLimit];
    }

    // O(TS*GL*TS) & O(TS*GL) : Where TS = totalStudents, GL = givenLimit
    int solveBy2DEnhanced(int givenLimit) {
        vector<vector<int>> dp(totalStudents + 1, vector<int>(givenLimit + 1, 0));
        dp[totalStudents][0] = 1;

        for(int start = totalStudents - 1; start >= 0; --start) {
            dp[start][0] = 1;
            for(int chooseLimit = 1; chooseLimit <= givenLimit; ++chooseLimit) {
                int count = 0;
                for(int student = start; student < totalStudents; ++student) {
                    int chooseStudent = dp[student + 1][chooseLimit - 1]; 
                    count += chooseStudent;
                }
                dp[start][chooseLimit] = count;
            }
        }

        return dp[0][givenLimit];
    }

public:
    int numWays(int n, int chooseLimit) {
        totalStudents = n;
        return solveBy2DEnhanced(chooseLimit);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming
Link  : https://www.naukri.com/code360/problems/choose-students_1062724?topList=top-dynamic-programming-questions&problemListRedirection=true&page=4&leftPanelTabValue=PROBLEM
