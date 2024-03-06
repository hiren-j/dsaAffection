// Program to find the leftmost value of the last row of a binary tree ~ coded by Hiren
#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;

// Tree template
class Node {
public:
    int data;
    Node* left; Node* right;

    // Init constructor
    Node(int data, Node* left = nullptr, Node* right = nullptr)
    :
    data(data), left(left), right(right) {}

    // Method to construct the tree - O(N) & O(H) : Where N is the total number of nodes and H is the height of the tree
    Node* constructTree(vector<int>& nodes, int start, int end) {
        if(start > end)
            return nullptr;

        int mid = start + (end - start) / 2;

        Node* rootNode = new Node(nodes[mid]);
        rootNode->left  = constructTree(nodes, start, mid-1);
        rootNode->right = constructTree(nodes, mid+1, end);

        return rootNode;
    }

    // Method to delete the tree - O(N) & O(H) : Where N is the total number of nodes and H is the height of the tree
    Node* deleteTree(Node* rootNode) {
        if(!rootNode)
            return nullptr;

        rootNode->left  = deleteTree(rootNode->left);
        rootNode->right = deleteTree(rootNode->right);

        delete rootNode;

        return nullptr;
    }

    // Method to print the tree - O(N) & O(N) : Where N is the total number of nodes of the tree
    void printTree(Node* rootNode) {
        queue<Node*> q;
        q.push(rootNode);

        while(!q.empty()) {
            int qSize = q.size();
            cout<<"[";
            while(qSize--) {
                Node* currNode = q.front(); q.pop();
                (!qSize) ? cout<<currNode->data : cout<<currNode->data<<", ";
                if(currNode->left)   
                    q.push(currNode->left);
                if(currNode->right)
                    q.push(currNode->right);
            }
            cout<<"]\n";
        }
    }
};

// #1 Solution class:
class Solution_V1 {
public:
    // Method to find the leftmost value of the last row, using dfs with buffer - O(N) & O(H)
    int getBottomLeftValue(Node* rootNode) {
        std::vector<int> buffer;        // Stores the leftmost value of each row
        dfs(rootNode, 0, buffer);       // Traverse and get the leftmost value of each row
        return buffer[buffer.size()-1]; // Return the leftmost value of the last row
    }
    
private:
    // Method to get the value of the first node of each row - O(N) & O(H)
    void dfs(Node* rootNode, int currentDepth, std::vector<int>& buffer) {
        // If the node exist
        if(rootNode) {
            // If the current row is seen for the first time, then store the value of the first node
            if(currentDepth == buffer.size()) {
                buffer.push_back(rootNode->data);
            }
            // Recurse to each row and get the value of the first node
            dfs(rootNode->left, currentDepth+1, buffer);
            dfs(rootNode->right, currentDepth+1, buffer);
        }
    }
};

// #2 Solution class:
class Solution_V2 {
public:
    // Method to find the leftmost value of the last row, using dfs only - O(N) & O(H)
    int getBottomLeftValue(Node* rootNode) {
        int extremeLeftValue = rootNode->data;            // Stores the leftmost value of the last row
        int maximumDepth = 0;                            // Tracks for the height of the tree
        dfs(rootNode, 0, maximumDepth, extremeLeftValue); // Traverse and look for the leftmost value of each row
        return extremeLeftValue;                          // Return the leftmost value of the last row
    }

private:
    void dfs(Node* rootNode, int currentDepth, int& maximumDepth, int& extremeLeftValue) {
        // If the node exist
        if(rootNode) {
            // If the current row is seen for the first time, then store the value of the first node
            (currentDepth > maximumDepth) ? extremeLeftValue = rootNode->data, maximumDepth = currentDepth : 0;
            // Recurse to each row and look for the value of the first node
            dfs(rootNode->left, currentDepth+1, maximumDepth, extremeLeftValue);
            dfs(rootNode->right, currentDepth+1, maximumDepth, extremeLeftValue);
        }
    }
};

// #3 Solution class:
class Solution_V3 {
public:
    // Method to find the leftmost value of the last row, using bfs only - O(N) & O(N)
    int getBottomLeftValue(Node* rootNode) {
        // Requires to visit the nodes row wise
        std::queue<Node*> q;
        q.push(rootNode);

        // Stores the leftmost value of the last row
        int extremeLeftValue = -1;

        while(!q.empty()) {
            int qSize = q.size();
            // Visit the nodes of the current row
            for(int node=1; node<=qSize; ++node) {
                Node* currNode = q.front(); q.pop();
                // If its the first node of the current row, then store the value of it
                if(node == 1)
                    extremeLeftValue = currNode->data;
                // If the left child of the node exist, then store it to the queue
                if(currNode->left)
                    q.push(currNode->left);
                // If the right child of the node exist, then store it to the queue
                if(currNode->right)
                    q.push(currNode->right);
            }
        }

        // Return the leftmost value of the last row
        return extremeLeftValue;
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userWantsOp = true;

    while(userWantsOp) {
        // Controls console clearance for both "windows" and "linux" user
        system("cls || clear");

        // Input the size of the nodes
        int n;
        cout<<"Enter the number of nodes of the tree: ";
        cin>>n;

        // Check the given size is valid or not
        if(n <= 0 || n >= 10001) {
            cout<<"Enter a value which lies within the problem contraints, application expects a positive integer!";
            return 0;
        }

        // Store the nodes value
        vector<int> nodes(n);

        // Input the nodes value
        for(int node=1; node<=n; ++node) {
            cout<<"Enter the value of the "<<node<<"th node: ";
            cin>>nodes[node];
        }

        // Tree construction call
        Node* rootNode = rootNode->constructTree(nodes, 0, n-1);
        
        // Print call (print each level of the tree)
        cout<<"\nLevel order traversal of the tree:\n";
        rootNode->printTree(rootNode);

        // Call to find the leftmost value of the last row
        Solution_V3 solution;
        int extremeLeftValue = solution.getBottomLeftValue(rootNode);
        cout<<"\nThe leftmost value of the last row is: "<<extremeLeftValue;

        // Deletion call
        rootNode = rootNode->deleteTree(rootNode);

        // Input section to control the flow of iterations of the application
        char userChoice;
        cout<<"\n\nPress \'R\' to restart the application, else it will exit automatically: ";
        cin>>userChoice;
        userWantsOp = (userChoice == 'R' ? true : false);
    }

    return 0;
}
/*
    Topics: Tree | Depth-First Search | Breadth-First Search | Binary Tree
    Link: https://leetcode.com/problems/find-bottom-left-tree-value/description/
*/
