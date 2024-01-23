// Program to find the level order traversal of the nodes value of a binary tree ~ coded by Hiren
#include <iostream>
#include <vector>
#include <queue>

// Tree template
class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;

    // Init constructor
    TreeNode(int data, TreeNode* left = nullptr, TreeNode* right = nullptr)
    :
    data(data), left(left), right(right) {}
};

// #1 Solution class:
class Solution_V1 {
public:
    // Method to find the level order traversal of the nodes value, using dfs - O(N) & O(N) : Where N is the total number of nodes of the tree
    std::vector<std::vector<int>> getLevelOrder(TreeNode* rootNode) {
        std::vector<std::vector<int>> nodesLevelWise;
        dfs(rootNode, 0, nodesLevelWise);
        return nodesLevelWise;
    }

private:
    // Method helper
    void dfs(TreeNode* rootNode, int currentDepth, std::vector<std::vector<int>>& nodesLevelWise) {
        if(rootNode) {
            if(currentDepth == nodesLevelWise.size()) {
                nodesLevelWise.emplace_back(std::vector<int>());
            }
            nodesLevelWise[currentDepth].emplace_back(rootNode->data);
            dfs(rootNode->left, currentDepth+1, nodesLevelWise);
            dfs(rootNode->right, currentDepth+1, nodesLevelWise);
        } 
    } 
};

// #2 Solution class:
class Solution_V2 {
public:
    // Method to find the level order traversal of the nodes value, using bfs - O(N) & O(N) : Where N is the total number of nodes of the tree
    std::vector<std::vector<int>> getLevelOrder(TreeNode* rootNode) {
        if(!rootNode)
            return {};

        std::queue<TreeNode*> q;
        q.push(rootNode);
        std::vector<std::vector<int>> nodesLevelWise;

        while(!q.empty()) {
            int qSize = q.size();
            std::vector<int> currLevel;
            while(qSize--) {
                TreeNode* currNode = q.front(); q.pop();
                currLevel.emplace_back(currNode->data);
                if(currNode->left) 
                    q.push(currNode->left);
                if(currNode->right)
                    q.push(currNode->right);
            }
            nodesLevelWise.emplace_back(currLevel);
        }

        return nodesLevelWise;
    }
};

// Class to wrap all the basic methods of the tree:
class TreeCommonMethods {
public:
    // Method to insert a node in the tree, using constant auxiliary space - O(N) & O(1)
    TreeNode* insertNodeInTree(TreeNode* rootNode, int key) {
        if(!rootNode)
            return new TreeNode(key);

        TreeNode* parentNode = nullptr;
        TreeNode* currNode   = rootNode;

        while(currNode) {
            parentNode = currNode;
            currNode = (currNode->data < key) ? currNode->right : currNode->left;
        }

        TreeNode* newNode = new TreeNode(key);

        (parentNode->data < key) ? parentNode->right = newNode : parentNode->left = newNode;

        return rootNode;
    }

    // Method to delete the tree, using dfs only - O(N) & O(H)
    TreeNode* deleteTree(TreeNode* rootNode) {
        if(!rootNode)
            return nullptr;

        rootNode->left  = deleteTree(rootNode->left);
        rootNode->right = deleteTree(rootNode->right);

        delete rootNode;

        return nullptr;
    }
};

// Driver code
int main() {
    bool userWantsOperation = true;

    while(userWantsOperation) {
        system("cls || clear");
        int N;
        std::cout<<"Enter the number of nodes for the tree: ";
        std::cin>>N;

        TreeNode* rootNode = nullptr;
        TreeCommonMethods commonMethods;

        // Input the nodes value of the tree
        for(int node = 1; node <= N; ++node) {
            int key;
            std::cout<<"Enter the value of the "<<node<<"th node: ";
            std::cin>>key;
            rootNode = commonMethods.insertNodeInTree(rootNode, key);
        }

        // Print call
        Solution_V2 solution;
        auto nodesLevelWise = solution.getLevelOrder(rootNode);

        // Print values
        std::cout<<"\nLevel order traversal of the tree is:\n";
        for(auto& currLevel : nodesLevelWise) {
            int size = currLevel.size();
            std::cout<<"[";
            for(int node = 0; node < size; ++node) {
                (node < size-1) ? std::cout<<currLevel[node]<<", " : std::cout<<currLevel[node];
            }
            std::cout<<"]\n";
        }

        // Deletion call
        rootNode = commonMethods.deleteTree(rootNode);

        // Input section to handle the flow of iterations
        char userChoise;
        std::cout<<"\nDo you want to perform the same operation on an another tree? (Write Y for \"Yes\" else application will exit automatically): ";
        std::cin>>userChoise;
        userWantsOperation = (userChoise == 'Y') ? true : false;
    }

    return 0;
}
// Link: https://leetcode.com/problems/binary-tree-level-order-traversal/description/
