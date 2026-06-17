// Code to find the longest common substring of given two strings ~ coded by Hiren 

----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class BottomUp {
public:
    // O(N*M) & O(M)
    int PrintLongCommSubstr(string& s1, string& s2) {
        const int n = s1.size();
        const int m = s2.size();
        int maxLen = 0;
        int start  = 0;
        
        vector<int> nextRow(m + 1, 0); 
         
        for(int i = n - 1; i >= 0; --i) {
            vector<int> currRow(m + 1, 0); 
            
            for(int j = m - 1; j >= 0; --j) {
                if(s1[i] == s2[j])
                    currRow[j] = 1 + nextRow[j + 1];
                else
                    currRow[j] = 0;
                    
                if(currRow[j] > maxLen) {
                    maxLen = currRow[j];
                    start  = i;
                }
            }
            
            swap(nextRow, currRow);
        }
    
        cout << s1.substr(start, maxLen);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
Topics: String | Dynamic Programming 
Link  : https://www.geeksforgeeks.org/print-longest-common-substring/
        https://github.com/hiren-j/dsaAffection/blob/C%2B%2B/Dynamic%20Programming/String%20DP/2%20-%20Longest%20Common%20Substring/Longest%20Common%20Substring.cpp
