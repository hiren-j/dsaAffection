// Code to answer whether for a query, course u is a prerequisite of course v or not. You must do this for all the queries ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    vector<vector<int>> adjList;
    vector<vector<int>> dp;

    // O(Q*V*V) & O(V) : Where V = numCourses, Q = queries.size
    bool canReachDestination(int src, int dest) {
        if(src == dest)
            return true;

        for(const int neighbor : adjList[src]) 
            if(canReachDestination(neighbor, dest)) 
                return true;

        return false;
    }

    // O(Q+V*V) & O(V*V) : Where V = numCourses, Q = queries.size
    bool canReachDestination_DP(int src, int dest) {
        if(src == dest)
            return true;

        if(dp[src][dest] != -1)
            return dp[src][dest];

        for(const int neighbor : adjList[src]) 
            if(canReachDestination_DP(neighbor, dest)) 
                return dp[src][dest] = true;

        return dp[src][dest] = false;
    }

public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        adjList.resize(numCourses);
        
        for(const auto& p : prerequisites) {
            const int courseA = p[0];
            const int courseB = p[1];
            adjList[courseA].push_back(courseB);
        }

        dp.resize(numCourses, vector<int>(numCourses, -1)); // Memoization DP
        vector<bool> answer;
        for(const auto& q : queries) {
            const int src  = q[0];
            const int dest = q[1];
            answer.push_back(canReachDestination_DP(src, dest));
        }
        return answer;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    vector<vector<int>> adjList;

    void markReachableCourses_DFS(int courseA, int mainCourse, vector<vector<bool>>& isPrequisite) {
        for(const int courseB : adjList[courseA]) {
            if(isPrequisite[mainCourse][courseB]) // If precomputed
                continue; 
            isPrequisite[mainCourse][courseB] = true;
            markReachableCourses_DFS(courseB, mainCourse, isPrequisite);
        }
    }

    void markReachableCourses_BFS(int courseA, int mainCourse, vector<vector<bool>>& isPrequisite) {
        queue<int> q;
        q.push(courseA);

        while(!q.empty()) {
            const int courseA = q.front(); q.pop();

            for(const int courseB : adjList[courseA]) {
                if(isPrequisite[mainCourse][courseB]) // If precomputed
                    continue; 
                isPrequisite[mainCourse][courseB] = true;
                q.push(courseB);
            }
        }
    }

public:
    // O(V*(V+E)) & O(V*V) : Where V = numCourses, E = prequisites.size, Q = queries.size
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        adjList.resize(numCourses);
        for(const auto& p : prerequisites) {
            const int courseA = p[0];
            const int courseB = p[1];
            adjList[courseA].push_back(courseB);
        }

        vector<vector<bool>> isPrequisite(numCourses, vector<bool>(numCourses, false)); // Tabulative DP
        for(int course = 0; course < numCourses; ++course) {
            markReachableCourses_BFS(course, course, isPrequisite);
        }
        vector<bool> answer;
        for(const auto& q : queries) {
            const int u = q[0];
            const int v = q[1];
            answer.push_back(isPrequisite[u][v]);
        }
        return answer;
    }
};  

---------------------------------------------------------------------------------------------------------------------------------------------------

/*
    NOTE: The time complexity of Bottom-up : O(V*(V+E))
          is for the worst case, but on an average It's taking very less time, 
          due to avoiding rechecking of pairs [isPrequisite[mainCourse][courseB]]. 
          But still considering the majors I still need to consider the mentioned time.
*/
    
---------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Graph | Dynamic Programming | Depth-first-search | Breadth-first-search | Greedy
Link : https://leetcode.com/problems/course-schedule-iv/
