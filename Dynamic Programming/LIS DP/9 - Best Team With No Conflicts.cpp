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
    // O(N*N) & O(N*N)
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

class BottomUp_V2 {
public:
    // Method to find the highest overall score of all possible basketball teams, using 1D tabulation - O(N^2) & O(N)
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        int n = scores.size(), maxScore = 0;

        // Create the list of players mapped with their age and score information
        vector<pair<int, int>> players;
        for(int index = 0; index < n; ++index) {
            players.push_back({ages[index], scores[index]});
        }
        sort(begin(players), end(players));

        // 1D DP table: dp[i] represents the maximum score you can get by considering the players from index 0 to i
        vector<int> dp(n, 0);

        // Fill the table
        for(int index = 0; index < n; ++index) {
            dp[index] = players[index].second;
            for(int prevIndex = 0; prevIndex < index; ++prevIndex) {
                if(players[prevIndex].second <= players[index].second) {
                    dp[index] = max(dp[index], players[index].second + dp[prevIndex]);
                }
            }
            maxScore = max(maxScore, dp[index]);
        } 

        // Return the result value
        return maxScore;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Sorting
Link  : https://leetcode.com/problems/best-team-with-no-conflicts/description/
