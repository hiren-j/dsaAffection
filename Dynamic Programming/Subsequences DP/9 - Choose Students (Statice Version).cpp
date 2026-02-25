// Code to find the number of ways you can choose `chooseLimit` students from a class of `totalStudents` students ~ coded by vHiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int totalStudents;

    // O(2^TS) & O(TS) : Where TS = totalStudents
    int solveWithoutMemo(int student, int chooseLimit) {
        if(chooseLimit == 0) 
            return 1; // Edge case when you've chosen students with specified chooseLimit then return 1
    
        if(student == totalStudents)
            return 0; // Edge case when no more students left then return 0

        // There are always two possibilities at each student
        int currSkip   = solveWithoutMemo(student + 1, chooseLimit);     // Is to skip it
        int currChoose = solveWithoutMemo(student + 1, chooseLimit - 1); // Is to choose it
    
        return (currSkip + currChoose);
    }
    
    // O(TS*CL) & O(TS*CL) : Where CL = chooseLimit
    int solveWithMemo(vector<vector<int>>& dp, int student, int chooseLimit) {
        if(chooseLimit == 0) 
            return 1;
    
        if(student == totalStudents)
            return 0; 

        if(dp[student][chooseLimit] != -1)
            return dp[student][chooseLimit];

        int currSkip   = solveWithMemo(dp, student + 1, chooseLimit);     
        int currChoose = solveWithMemo(dp, student + 1, chooseLimit - 1); 
    
        return dp[student][chooseLimit] = (currSkip + currChoose);
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

    // O(TS*GL) & O(TS*GL) : Where TS = totalStudents, CL = givenLimit
    int solveBy2DTable(int givenLimit) {
        vector<vector<int>> dp(totalStudents + 1, vector<int>(givenLimit + 1, -1));
        dp[totalStudents][0] = 1;

        for(int chooseLimit = 1; chooseLimit <= givenLimit; ++chooseLimit)
            dp[totalStudents][chooseLimit] = 0;

        for(int student = totalStudents - 1; student >= 0; --student) {
            dp[student][0] = 1;
            for(int chooseLimit = 1; chooseLimit <= givenLimit; ++chooseLimit) {
                int currSkip   = dp[student + 1][chooseLimit];     
                int currChoose = dp[student + 1][chooseLimit - 1]; 
                dp[student][chooseLimit] = (currSkip + currChoose);
            }
        }

        return dp[0][givenLimit];
    }

    // O(TS*GL) & O(TS*GL) : Where TS = totalStudents, CL = givenLimit
    int solveBy2DEnhanced(int givenLimit) {
        vector<vector<int>> dp(totalStudents + 1, vector<int>(givenLimit + 1, 0));
        dp[totalStudents][0] = 1;

        for(int student = totalStudents - 1; student >= 0; --student) {
            dp[student][0] = 1;
            for(int chooseLimit = 1; chooseLimit <= givenLimit; ++chooseLimit) {
                int currSkip   = dp[student + 1][chooseLimit];     
                int currChoose = dp[student + 1][chooseLimit - 1]; 
                dp[student][chooseLimit] = (currSkip + currChoose);
            }
        }

        return dp[0][givenLimit];
    }

    // O(TS*GL) & O(GL) : Where TS = totalStudents, CL = givenLimit
    int solveBy1DTable(int givenLimit) {
        vector<int> nextRow(givenLimit + 1, 0); 
        nextRow[0] = 1;
        
        for(int student = totalStudents - 1; student >= 0; --student) {
            vector<int> idealRow(givenLimit + 1, 0); 
            idealRow[0] = 1;
            for(int chooseLimit = 1; chooseLimit <= givenLimit; ++chooseLimit) {
                int currSkip   = nextRow[chooseLimit];     
                int currChoose = nextRow[chooseLimit - 1]; 
                idealRow[chooseLimit] = (currSkip + currChoose);
            }
            swap(nextRow, idealRow);
        }

        return nextRow[givenLimit];
    }

public:
    int numWays(int n, int chooseLimit) {
        totalStudents = n;
        return solveBy1DTable(chooseLimit);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming
Link  : https://www.naukri.com/code360/problems/choose-students_1062724?topList=top-dynamic-programming-questions&problemListRedirection=true&page=4&leftPanelTabValue=PROBLEM
