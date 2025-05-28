// Code to find the maximum points the geek can earn by performing the aforementioned activites ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int N;
    
    int solveWithoutMemo(vector<vector<int>>& points, int R, int skipColumn) {
        if(R == N)
            return 0;
        
        int maxPoints = 0;
        
        for(int C = 0; C < 3; ++C)
            if(C != skipColumn)
                maxPoints = max(maxPoints, points[R][C] + solveWithoutMemo(points, R + 1, C));
            
        return maxPoints;
    }

    int solveWithMemo(vector<vector<int>>& dp, vector<vector<int>>& points, int R, int skipColumn) {
        if(R == N)
            return 0;
        
        if(dp[R][skipColumn] != -1) 
            return dp[R][skipColumn];
        
        int maxPoints = 0;
        
        for(int C = 0; C < 3; ++C)
            if(C != skipColumn)
                maxPoints = max(maxPoints, points[R][C] + solveWithMemo(dp, points, R + 1, C));
            
        return dp[R][skipColumn] = maxPoints;
    }
        
public:
    int gainMaximumPoints(vector<vector<int>>& points) {
        N = points.size();
        vector<vector<int>> dp(N, vector<int>(4, -1));
        return solveWithMemo(dp, points, 0, 3);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int N;

    int solveWith2DTable(vector<vector<int>>& points) {
        vector<vector<int>> dp(N, vector<int>(4, -1));
        
        for(int R = N-1; R >= 0; --R) {
            for(int skipColumn = 0; skipColumn <= 3; ++skipColumn) {
                int maxPoints = 0;
                
                for(int C = 0; C < 3; ++C) {
                    if(C != skipColumn) {
                        int nextPoints = (R + 1 < N) ? dp[R + 1][C] : 0;
                        maxPoints = max(maxPoints, points[R][C] + nextPoints);
                    }
                }
                
                dp[R][skipColumn] = maxPoints;
            }
        }
        
        return dp[0][3];
    }
    
    int solveWith2DEnhanced(vector<vector<int>>& points) {
        vector<vector<int>> dp(N + 1, vector<int>(4, 0));
        
        for(int R = N-1; R >= 0; --R) {
            for(int skipColumn = 0; skipColumn <= 3; ++skipColumn) {
                int maxPoints = 0;
                
                for(int C = 0; C < 3; ++C) {
                    if(C != skipColumn) {
                        int nextPoints = dp[R + 1][C];
                        maxPoints = max(maxPoints, points[R][C] + nextPoints);
                    }
                }
                
                dp[R][skipColumn] = maxPoints;
            }
        }
        
        return dp[0][3];
    }
    
    int solveWith1DTable(vector<vector<int>>& points) {
        vector<int> nextRow(4, 0), idealRow(4, 0);
        
        for(int R = N-1; R >= 0; --R) {
            for(int skipColumn = 0; skipColumn <= 3; ++skipColumn) {
                int maxPoints = 0;
                
                for(int C = 0; C < 3; ++C) {
                    if(C != skipColumn) {
                        int nextPoints = nextRow[C];
                        maxPoints = max(maxPoints, points[R][C] + nextPoints);
                    }
                }
                
                idealRow[skipColumn] = maxPoints;
            }
            nextRow = idealRow;
        }
        
        return nextRow[3];
    }

public:
    int gainMaximumPoints(vector<vector<int>>& points) {
        N = points.size();
        return solveWith1DTable(points);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUpIntuitive {
    int N;

    int solveWithoutTable_V1(vector<vector<int>>& points) {
        for(int R = N-2; R >= 0; --R) {
            for(int C = 0; C < 3; ++C) {
                int maxPoints = 0; // To earn maximum points, get maximum value from from next row but the only cell which you shouldn't consider is the same cell from the next row
                
                for(int skipColumn = 0; skipColumn < 3; ++skipColumn) { 

                    if(C != skipColumn) { 
                        maxPoints = max(maxPoints, points[R + 1][skipColumn]); 
                    }
                }
                
                points[R][C] += maxPoints;
            }
        }
        
        return *max_element(begin(points[0]), end(points[0]));
    }

    int solveWithoutTable_V2(vector<vector<int>>& points) {
        // Suppose you're on a cell so to earn maximum points, get maximum value from from previous row but the only cell which you shouldn't consider is the same cell from the previous row
        for(int R = 1; R < N; ++R) {
            for(int C = 0; C < 3; ++C) {
                if(C == 0)
                    points[R][C] += max(points[R - 1][C + 1], points[R - 1][C + 2]);

                else if(C == 1)
                    points[R][C] += max(points[R - 1][C - 1], points[R - 1][C + 1]);

                else
                    points[R][C] += max(points[R - 1][C - 1], points[R - 1][C - 2]);
            }
        }

        return *max_element(begin(points[N - 1]), end(points[N - 1]));
    }

public:
    int gainMaximumPoints(vector<vector<int>>& points) {
        N = points.size();
        return solveWithoutTable_V2(points);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Matrix | Dynamic Programming
Links : https://www.geeksforgeeks.org/problems/geeks-training/1
