// Code to find the minimum number of months needed to complete all the courses such that by following the mentioned rules ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Class to implement the Top-down approach:
class DynamicProgramming {
    vector<vector<int>> adjList;
    vector<int> visited;  

    // O(N * M^N) & O(N)
    int solveWithoutMemo(int course, vector<int>& time) {
        // Stores the total time required to complete the course
        int maximumTime = 0;

        // Explore each neighbour courses and find the maximum remaining time to complete the course
        for(int neighbor : adjList[course]) 
            maximumTime = max(maximumTime, solveWithoutMemo(neighbor, time));

        // Return the result value
        return (maximumTime == 0) ? time[course - 1] : time[course - 1] + maximumTime;
    }
    
    // O(N + M*N) & O(N+N)
    int solveWithMemo(int course, vector<int>& time) {
        // Stores the total time required to complete the course
        int maximumTime = 0;

        for(int neighbor : adjList[course]) {
            // If the current state is not computed then find the maximum remaining time to complete the course
            if(!visited[neighbor]) {
                maximumTime = max(maximumTime, solveWithMemo(neighbor, time));
            }
            // If the current state is already computed then update the result by the maximum value
            else {
                maximumTime = max(maximumTime, visited[neighbor]);
            }
        }

        // Store the result value to the memoization table and then return it
        return visited[course] = (maximumTime == 0) ? time[course - 1] : time[course - 1] + maximumTime;
    }

public:
    // Method to find minimum number of months needed to complete all the courses, using recursion with memoization - O(M*N) & O(N) : Where M let be the maxmium number of neighbours of any course
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
        // Edge case: If there are no relations then return the maximum time  
        if(relations.size() == 0)
            return *max_element(begin(time), end(time));

        adjList.resize(n + 1); // Stores the list of neighbour courses of each course
        visited.resize(n + 1); // Memoization table

        // Create the adjacency list
        for(auto& r : relations) {
            int prevCourse = r[1];
            int nextCourse = r[0];
            adjList[prevCourse].push_back(nextCourse);
        }

        // Stores the result value
        int minMonths = 0;
        
        // Start doing the courses and find the total time required to complete all the courses through each of them and update the result by the maximum value
        for(int course = 1; course <= n; ++course) 
            if(!visited[course]) 
                minMonths = max(minMonths, solveWithMemo(course, time));

        // Return the result value
        return minMonths;
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Graph | Topological Sort
Link  : https://leetcode.com/problems/parallel-courses-iii/description/
