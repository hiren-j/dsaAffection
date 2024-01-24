// Program to return the average value of the nodes on each level in the form of an array ~ coded by Hiren
#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <thread>
#include <chrono>

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

    // Method to insert a node in the tree, using constant auxiliary space - O(N) & O(1) : Where N is total number of nodes of the tree
    TreeNode* insertNodeInBT(TreeNode* rootNode, int val) {
        if(!rootNode)
            return new TreeNode(val); 

        TreeNode* parentNode = nullptr;
        TreeNode* currNode   = rootNode;

        while(currNode) {
            parentNode = currNode;
            currNode   = (currNode->val > val) ? currNode->left : currNode->right;
        }

        TreeNode* newNode = new TreeNode(val);

        (parentNode->val > val) ? parentNode->left = newNode : parentNode->right = newNode;

        return rootNode;
    }

    // Method to print the tree, using preOrder traversal - O(N) & O(H) : Where N is total number of nodes and H is height of the tree
    void printTree(TreeNode* rootNode) {
        if(rootNode) {
            std::cout<<rootNode->val<<' ';
            printTree(rootNode->left);
            printTree(rootNode->right);
        }
    }
};

// #1 Solution class:
class Solution_V1 {
public:
    // Method to find the average of each level, using bfs - O(N) & O(N) : Where N is total number of nodes of the tree
    std::vector<double> averageOfLevels(TreeNode* currNode) {
        // Stores the levels one by one
        std::queue<TreeNode*> q;
        // Store the node of the first level of the tree
        q.push(currNode);
        // Stores the average of each level
        std::vector<double> avgLevelWise;

        while(!q.empty()) {
            int qSize = q.size();
            // Stores the sum of nodes and the count of nodes of current level
            double currLevelSum = 0, currNodesCount = 0;
            // Explore the current level
            while(qSize--) {
                // Extract the current node of the current level from the "queue"
                currNode = q.front(); q.pop();
                // Current node of the current level is seen for the first time thus update the nodes count and sum the node value to the sum of nodes
                currLevelSum += currNode->val, currNodesCount++;
                // If exists then store the left child of the current node to the "queue"
                if(currNode->left) 
                    q.push(currNode->left);
                // If exists then store the right child of the current node to the "queue"
                if(currNode->right) 
                    q.push(currNode->right);
            }
            // Calculate the average of the current level and store it to the "list"
            avgLevelWise.push_back(currLevelSum / currNodesCount);
        }

        // Return the list of averages
        return avgLevelWise;
    }
};

// #2 Solution class:
class Solution_V2 {
public:
    // Method to find the average of each level, using buffer with dfs - O(N) & O(H) : Where N is total number of nodes and H is height of the tree
    std::vector<double> averageOfLevels(TreeNode* rootNode) {
        // Stores the count of nodes and the sum of nodes of each level
        std::vector<std::pair<double, double>> countAndSum; 
        // Stores the average of each level
        std::vector<double> avgLevelWise; 
        // Calculate average of each level
        calcAvgOfLevels(rootNode, 0, countAndSum, avgLevelWise);
        // Return the list of averages
        return avgLevelWise;
    }

private:
    // Method helper
    void calcAvgOfLevels(TreeNode* currNode, int currDepth, std::vector<std::pair<double, double>>& countAndSum, std::vector<double>& avgLevelWise) {
        // When the current node is present
        if(currNode) {
            // When the current level is seen for the first time
            if(countAndSum.size() == currDepth) {
                // Store the number of nodes visited as 1, with the current node value
                countAndSum.push_back({1, currNode->val});
                // For now store the average of current level as zero in the "list" 
                avgLevelWise.push_back(0);
            }
            // Else when the current level is seen again
            else {
                // Extract the count of nodes and the sum of nodes of current level
                auto& [currLevelCount, currLevelSum] = countAndSum[currDepth];
                // Current node of the current level is seen for the first time thus update the nodes count and sum the node value to the sum of nodes
                currLevelCount += 1, currLevelSum += currNode->val;
            }
            // Extract the count of nodes and the sum of nodes of current level
            auto [currLevelCount, currLevelSum] = countAndSum[currDepth];
            // Calculate the average of current level each time and update it in the "list"
            avgLevelWise[currDepth] = currLevelSum / currLevelCount;
            // Recurse to the nodes one by one in both the subtrees of the current node
            calcAvgOfLevels(currNode->left, currDepth+1, countAndSum, avgLevelWise);
            calcAvgOfLevels(currNode->right, currDepth+1, countAndSum, avgLevelWise);
        }
    }
};

// Driver code
int main() {
    int testCases;
    std::cout<<"Enter the number of testcases you want: ";
    std::cin>>testCases;

    if(testCases <= 0) {
        std::cout<<"Enter a valid number for the testcases, application expects a positive integer!";
        return 0;
    }

    while(testCases--) {
        system("clear || cls");
        int n;
        std::cout<<"Enter the number of nodes for the binary tree: ";
        std::cin>>n;

        TreeNode* rootNode = nullptr;

        for(int node = 1; node <= n; ++node) {
            int val;
            std::cout<<"Enter the value of the "<<node<<"th node: ";
            std::cin>>val;
            rootNode = rootNode->insertNodeInBT(rootNode, val);
        }

        // Print call
        std::cout<<"\nTree: ";
        rootNode->printTree(rootNode); 

        // Call to find the average of each level
        Solution_V2 obj;
        std::vector<double> avgLevelWise = obj.averageOfLevels(rootNode);

        // Print values
        std::cout<<"\nList of averages: ";
        for(double currLevelAvg : avgLevelWise)
            std::cout<<std::fixed<<std::setprecision(3)<<currLevelAvg<<"  ";

        // Delete the root node (and recursively the entire tree)
        delete rootNode;

        (testCases) ? std::cout<<"\n\nThe application will restart in 10 seconds!" : std::cout<<"\n\nThe application will close in 10 seconds!";

        // Add 10-seconds of delay before the next iteration   
        std::this_thread::sleep_for(std::chrono::seconds(10));
    } 

    return 0;
}
// Link: https://leetcode.com/problems/average-of-levels-in-binary-tree/
