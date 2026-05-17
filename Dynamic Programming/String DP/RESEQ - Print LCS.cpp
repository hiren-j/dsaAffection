// Code to print longest common subsequence of two strings ~ coded by vHiren

---------------------------------------------------------------------------------------------------------------------------------------------------

// O(N*M) & O(N*M)
string findLCS(int n, int m, string& s1, string& s2) {
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

    for(int i = n-1; i >= 0; --i) {
        for(int j = m-1; j >= 0; --j) {
            if(s1[i] == s2[j])
                dp[i][j] = 1 + dp[i+1][j+1];
            else
                dp[i][j] = max(dp[i+1][j], dp[i][j+1]);   
        }
    }

	int i = 0, j = 0;
	string answer;

	while(i <= n-1 && j <= m-1) {
        if(s1[i] == s2[j]) {
            answer.push_back(s1[i]);
            i++;
            j++;
        }
        else {
            if(dp[i+1][j] > dp[i][j+1]) {
                i++;
            }
            else {
                j++;
            }  
        }
	}

	return answer;
}

---------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming | String
Link  : https://www.naukri.com/code360/problems/print-longest-common-subsequence_8416383?leftPanelTabValue=PROBLEM
