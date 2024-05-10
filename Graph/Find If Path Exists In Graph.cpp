// Program to check is if there exists a valid path from the source to destination or not ~ coded by Hiren
#include <iostream>
#include <vector>
#include <queue>
#include <set>

// Solution class:
class Solution {
public:
    // Method to check is if there exists a valid path from the source to destination or not - O(V+E) & O(V+E) : Where V let be the total number vertices and E let be the total number of edges
    bool validPath(int n, std::vector<std::vector<int>>& edges, int source, int destination) {
        // Early exit: If the source is equal to the destination then return true
        if(source == destination)
            return true;

        // Stores the list of neighbours of each vertex
        std::vector<std::vector<int>> adjList(n);

        // Iterate and create the adjacency list
        for(auto& edge : edges) {
            adjList[edge[0]].push_back(edge[1]);
            adjList[edge[1]].push_back(edge[0]);
        }

        // Tracks the vertices which are visited
        std::vector<int> visited(n);
        
        // Traverse from the source node and check for the existence of the path
        return BFS(n, adjList, visited, source, destination);
    }

private:
    // Method to to check is if there exists a valid path from source to destination or not, using bfs - O(V+E) & O(V)
    bool BFS(int n, std::vector<std::vector<int>>& adjList, std::vector<int>& visited, int vertex, int destination) {
        // Mark the source node as visited
        visited[vertex]++;

        // Requires to visit the neighbours of any vertex in correct order
        std::queue<int> q;
        q.push(vertex);

        while(!q.empty()) {
            vertex = q.front(); q.pop();
            // Iterate the neighbors of the vertex
            for(auto neighbor : adjList[vertex]) {
                // If the neighbour is the destination then return true
                if(destination == neighbor) {
                    return true;
                }
                // If the neighbour is not visited then mark it visited and then store it to the queue
                if(!visited[neighbor]) {
                    visited[neighbor]++;
                    q.push(neighbor);
                }
            }
        }

        // If reached here then there's no path from the source to destination
        return false;
    }

    // Method to to check is if there exists a valid path from source to destination or not, using dfs - O(V+E) & O(V)
    bool DFS(int n, std::vector<std::vector<int>>& adjList, std::vector<int>& visited, int vertex, int destination) {
        // Early exit: If the vertex is equal to the destination then return true
        if(vertex == destination)
            return true;

        // Mark the vertex as visited
        visited[vertex]++;

        // Tracks the information of the existence of the path
        bool flag = false;

        // Iterate the neighbours of the vertex
        for(auto neighbor : adjList[vertex]) {
            // If the neighbour is not visited then traverse it and check the existence of the path from it
            if(!visited[neighbor]) {
                flag |= DFS(n, adjList, visited, neighbor, destination);
            }
        }
        
        // Return the information of the path existence
        return flag;
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userNeedOperation = true;

    while(userNeedOperation) {
        // Controls console clearance for both "windows" and "linux" user
        std::system("cls || clear");

        std::cout<<"The application only accepts non-decimal numeric type value, unless specified!\n\n";

        // Input the size of the graph
        int n;
        std::cout<<"Enter the total number of vertices: ";
        std::cin>>n;

        // Input the size of the edges
        int size;
        std::cout<<"Enter the total number of edges: ";
        std::cin>>size;

        // Input the source value
        int source;
        std::cout<<"Enter the value of source vertex: ";
        std::cin>>source;

        // Input the destination value
        int destination;
        std::cout<<"Enter the value of destination vertex: ";
        std::cin>>destination;

        // Check the given values are lying within the problem constraints or not
        if(n <= 0 || n >= 2 * 1e5 + 1) {
            std::cout<<"You must enter the vertices value, which lies between 1 and 20^5!";
        }
        else if(size <= -1 || size >= 2 * 1e5 + 1) {
            std::cout<<"You must enter the edge size, which lies between 0 and 20^5!";
        }
        else if(source <= -1 || source >= n || destination <= -1 || destination >= n) {
            std::cout<<"You must enter the value of source and destination, which lies between 0 and "<<n - 1<<"!";
        }
        else {
            // Stores the edges
            std::vector<std::vector<int>> edges(size);

            // Requires to avoid the duplication of edges
            std::set<std::vector<int>> uniqEdges;

            // Input the edges
            std::cout<<"\nNote: An edge consist of two vertex [u, v]. It denotes a bi-directional edge between vertex (u) and vertex (v):-\n";
            for(int edge = 0; edge < size;) {
                // Input the vertices of the edge
                int u, v;
                std::cout<<"Enter the "<<edge<<"th edge [u, v]: ";
                std::cin>>u>>v;
                // Check the given values are lying within the problem constraints or not
                if(uniqEdges.count({u, v})) {
                    std::cout<<"The edge ["<<u<<", "<<v<<"] already exists! Kindly enter unique edges, no duplicates allowed!\n";
                }
                else if(u == v) {
                    std::cout<<"You must enter the different values, vertices can't be same!\n";
                }
                else if(u <= -1 || u >= n || v <= -1 || v >= n) {
                    std::cout<<"You must enter the edge [u, v] which lies between 0 and "<<n - 1<<"!\n";
                }
                else {
                    edges[edge] = {u, v};
                    uniqEdges.insert({u, v});
                    edge++;
                }
            }

            // Call to check is if there exists a valid path from the source to destination or not
            Solution solution;
            if(solution.validPath(n, edges, source, destination)) {
                std::cout<<"\nThere exists a path from the source "<<source<<" to "<<"destination "<<destination<<"!";
            }
            else {
                std::cout<<"\nThere's no path from the source "<<source<<" to "<<"destination "<<destination<<"!";
            }
        }

        // Input section to control the flow of iteration of the appliation
        char userChoice;
        std::cout<<"\n\nPress \'R\' to restart the application, else it will exit: ";
        std::cin>>userChoice;
        userNeedOperation = (userChoice == 'R');
    }

    return 0;
}
/*
    Topics: Depth-First Search | Breadth-First Search | Graph
    Link: https://leetcode.com/problems/find-if-path-exists-in-graph/description/?envType=daily-question&envId=2024-04-21
*/
