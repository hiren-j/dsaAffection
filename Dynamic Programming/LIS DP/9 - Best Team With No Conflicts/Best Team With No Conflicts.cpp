// Code to find the highest overall score of all possible basketball teams. You are the manager of a basketball team. For the upcoming tournament, you want to choose the team with the highest overall score. The score of the team is the sum of scores of all the players in the team. However, the basketball team is not allowed to have conflicts. A conflict exists if a younger player has a strictly higher score than an older player. A conflict does not occur between players of the same age ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    vector<pair<int, int>> ageToScore; // {age, score} of ith player
    int n;

    // O(N*N) & O(N*N)
    int solveWithMemo(vector<vector<int>>& dp, int i, int prev) {
        if(i == n)
            return 0;
            
        if(dp[i][prev] != -1)
            return dp[i][prev];
        
        int currSkip = solveWithMemo(dp, i + 1, prev);
        int currTake = 0;

        if(prev == n || ageToScore[prev].second <= ageToScore[i].second)
            currTake = solveWithMemo(dp, i + 1, i) + ageToScore[i].second;

        return dp[i][prev] = max(currSkip, currTake);
    }

public:
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        n = scores.size();
        ageToScore.resize(n); 

        for(int i = 0; i < n; ++i) {
            ageToScore[i] = {ages[i], scores[i]};
        }
        sort(ageToScore.begin(), ageToScore.end());

        vector<vector<int>> dp(n, vector<int>(n + 1, -1));
        return solveWithMemo(dp, 0, n);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    vector<pair<int, int>> ageToScore; 
    int n;

    // O(N*N) & O(N*N)
    int solveBy2DTable() {
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        for(int i = n - 1; i >= 0; --i) {
            for(int prev = 0; prev <= n; ++prev) {
                int currSkip = dp[i + 1][prev];
                int currTake = 0;

                if(prev == n || ageToScore[prev].second <= ageToScore[i].second)
                    currTake = dp[i + 1][i] + ageToScore[i].second;

                dp[i][prev] = max(currSkip, currTake);
            }
        }

        return dp[0][n];
    }  

    // O(N*N) & O(N)
    int solveBy1DTable() {
        vector<int> nextRow(n + 1, 0), idealRow(n + 1, 0);

        for(int i = n - 1; i >= 0; --i) {
            for(int prev = 0; prev <= n; ++prev) {
                int currSkip = nextRow[prev];
                int currTake = 0;

                if(prev == n || ageToScore[prev].second <= ageToScore[i].second)
                    currTake = nextRow[i] + ageToScore[i].second;

                idealRow[prev] = max(currSkip, currTake);
            }
            swap(nextRow, idealRow);
        }

        return nextRow[n];
    }   

public:
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        n = scores.size();
        ageToScore.resize(n); 

        for(int i = 0; i < n; ++i) {
            ageToScore[i] = {ages[i], scores[i]};
        }
        sort(ageToScore.begin(), ageToScore.end());

        return solveBy1DTable();
    }
};
    
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUpClean {
public:
    // O(N*N) & O(N)
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        const int n = scores.size();

        vector<pair<int, int>> ageToScore(n);
        for(int i = 0; i < n; ++i) {
            ageToScore[i] = {ages[i], scores[i]};
        }
        sort(ageToScore.begin(), ageToScore.end());

        vector<int> dp(n);
        int res = 0;

        for(int i = 0; i < n; ++i) {
            dp[i] = ageToScore[i].second;

            for(int prev = 0; prev < i; ++prev) {
                if(ageToScore[prev].second <= ageToScore[i].second) {
                    dp[i] = max(dp[i], ageToScore[i].second + dp[prev]);
                }
            }
            
            res = max(res, dp[i]);
        } 

        return res;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Sorting
Link  : https://leetcode.com/problems/best-team-with-no-conflicts/description/
