// Program to find the maximum value of each row of a tree ~ coded by Hiren
#include <iostream>
#include <climits>
#include <cstdlib>
#include <vector>
#include <queue>

// Tree template
class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;

    // Init constructor
    TreeNode(int val, TreeNode* left = nullptr, TreeNode* right = nullptr)
    :
    val(val), left(left), right(right) {}

    // Init destructor
    ~TreeNode() {
        if(left) {
            delete left;
        }
        if(right) {
            delete right;
        }
    }

    // Method to construct the tree - O(N) & O(H) : Where N is the total number of nodes and H is the height of the tree
    TreeNode* constructTree(std::vector<int>& nums, int start, int end) {
        if(start > end)
            return nullptr;

        int mid = start + (end - start) / 2;

        TreeNode* rootNode = new TreeNode(nums[mid]);
        rootNode->left  = constructTree(nums, start, mid-1);
        rootNode->right = constructTree(nums, mid+1, end);

        return rootNode;
    }

    // Method to print the tree - O(N) & O(N) : Where N is the total number of nodes of the tree
    void printTree(TreeNode* rootNode) {
        if(!rootNode)
            return;

        std::queue<TreeNode*> q;
        q.push(rootNode);

        while(!q.empty()) {
            int qSize = q.size();
            std::cout<<"[";
            while(qSize--) {
                TreeNode* currNode = q.front(); q.pop();
                (!qSize ? std::cout<<currNode->val : std::cout<<currNode->val<<", ");
                if(currNode->left)
                    q.push(currNode->left);
                if(currNode->right)
                    q.push(currNode->right);
            }
            std::cout<<"]\n";
        }
    }
};

// #1 Solution class
class Solution_A {
public:
    // Method to find the maximum value of each row, using bfs - O(N) & O(N) : Where N is the total number of nodes of the tree
    std::vector<int> getMaxEachRow(TreeNode* rootNode) {
        // Edge case: When the tree is empty
        if(!rootNode)
            return {};

        // Requires to visit the nodes level wise
        std::queue<TreeNode*> q;
        q.push(rootNode);

        // Buffer to store the maximum value of each level
        std::vector<int> maxLevelWise;

        // Explore the nodes level wise
        while(!q.empty()) {
            int qSize = q.size();
            int currLevelMax = INT_MIN; // Stores the maximum value of the current level
            // Explore the nodes of the current level
            while(qSize--) {
                TreeNode* currNode = q.front(); q.pop();
                // If the left child of the current node exist, then store it to the queue
                if(currNode->left)
                    q.push(currNode->left);
                // If the right child of the current node exist, then store it to the queue
                if(currNode->right)
                    q.push(currNode->right);
                // Update the maximum value each time
                currLevelMax = std::max(currLevelMax, currNode->val);
            }
            // Store the maximum value of the current level to the buffer
            maxLevelWise.push_back(currLevelMax);
        }
        
        // Return the buffer containing the result values
        return maxLevelWise;
    }
};

// #2 Solution class
class Solution_B {
public:
    // Method to find the maximum value of each row, using dfs - O(N) & O(H) : Where N is the total number of nodes and H is the height of the tree
    std::vector<int> getMaxEachRow(TreeNode* rootNode) {
        // Buffer to store the maximum value of each level
        std::vector<int> maxLevelWise;
        // Explore the nodes of the tree
        dfs(rootNode, 0, maxLevelWise);
        // Return the buffer containing the result values
        return maxLevelWise;
    }

private:
    // Method to get the maximum value of each row - O(N) & O(H)
    void dfs(TreeNode* currNode, int currDepth, std::vector<int>& maxLevelWise) {
        // When the node exist
        if(currNode) {
            // When the current level is seen for the first time 
            if(currDepth == maxLevelWise.size()) {
                maxLevelWise.push_back(INT_MIN);
            }
            // Update the maximum value at the corresponding level in the buffer
            maxLevelWise[currDepth] = std::max(maxLevelWise[currDepth], currNode->val);
            // Recurse to both the subtrees and look for the maximum value at each level
            dfs(currNode->left, currDepth+1, maxLevelWise);
            dfs(currNode->right, currDepth+1, maxLevelWise);
        }
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userWantsOperation = true;

    while(userWantsOperation) {
        // Controls console clearance for both "windows" and "linux" user 
        system("cls || clear");

        // Input the size of the nodes
        int size;
        std::cout<<"Enter the number of nodes for the tree: ";
        std::cin>>size;

        // Check the given size is valid or not
        if(size <= 0) {
            std::cout<<"Enter a valid size, application expects a positive integer!";
            return 0;
        }

        // Stores the nodes value
        std::vector<int> nums(size, 0);

        // Input the nodes value
        for(int node=0; node<size; ++node) {
            std::cout<<"Enter the value of the "<<node+1<<"th node: ";
            std::cin>>nums[node];
        } 

        // Call to construct the tree
        TreeNode* rootNode = rootNode->constructTree(nums, 0, size-1);

        // Print call (print each row of the tree)
        std::cout<<"\nTree:\n";
        rootNode->printTree(rootNode);

        // Call to find the maximum value of each row
        Solution_B solution;
        std::vector<int> maxLevelWise = solution.getMaxEachRow(rootNode);

        // Print values (print the maximum value of each row)
        std::cout<<"\nLargest value of each row: ";
        for(int maxNumber : maxLevelWise)
            std::cout<<maxNumber<<"  ";

        // Deletion call (delete the root node and recursively the entire tree)
        delete rootNode; rootNode = nullptr;

        // Input section to control the flow of iterations of the application
        char userChoise;
        std::cout<<"\n\nPress \'R\' to restart the application, else it will exit automatically: ";
        std::cin>>userChoise;
        userWantsOperation = (userChoise == 'R' ? true : false);
    }

    return 0;
}
/*
    Topics: Tree | Depth-First Search | Breadth-First Search | Binary Tree
    Link: https://leetcode.com/problems/find-largest-value-in-each-tree-row/
*/
