// Program to find the zigzag level order traversal of the node's value of a binary tree ~ coded by Hiren
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>

// Tree template
class TreeNode {
public:
    int data;
    TreeNode* left; TreeNode* right;

    // Init constructor
    TreeNode(int data, TreeNode* left = nullptr, TreeNode* right = nullptr)
    :
    data(data), left(left), right(right) {}

    // Method to insert a node in the tree, using constant auxiliary space - O(N) & O(1) : Where N let be the total number of nodes of the tree
    TreeNode* insertNode(TreeNode* rootNode, int key) {
        if(!rootNode)
            return new TreeNode(key);

        TreeNode* parentNode = nullptr;
        TreeNode* currNode   = rootNode;

        while(currNode) {
            parentNode = currNode;
            currNode = (currNode->data > key) ? currNode->left : currNode->right;
        }

        TreeNode* newNode = new TreeNode(key);
        (parentNode->data > key) ? parentNode->left = newNode : parentNode->right = newNode;

        return rootNode;
    }

    // Method to delete the tree, using dfs - O(N) & O(H) : Where N let be the total number of nodes and H let be the height of the tree
    TreeNode* deleteTree(TreeNode* rootNode) {
        if(!rootNode)
            return nullptr;

        rootNode->left  = deleteTree(rootNode->left);
        rootNode->right = deleteTree(rootNode->right);

        delete rootNode; rootNode = nullptr;

        return rootNode;
    } 

    // Method to print the tree, using bfs - O(N) & O(N) : Where N let be the total number of nodes of the tree
    void printTree(TreeNode* rootNode) {
        if(!rootNode)
            return;

        std::queue<TreeNode*> q;
        q.push(rootNode);

        while(!q.empty()) {
            int qSize = q.size();
            std::cout<<"[";
            while(qSize--) {
                rootNode = q.front(); q.pop();
                if(rootNode->left)
                    q.push(rootNode->left);
                if(rootNode->right)
                    q.push(rootNode->right);
                (!qSize) ? std::cout<<rootNode->data : std::cout<<rootNode->data<<", ";
            }
            std::cout<<"]\n";
        }
    }
};

// Class to implement the Breadth-first-search approach:
class BFS {
public:
    // Method to find the zigzag level order traversal of the tree, using bfs - O(N) & O(N) : Where N let be the total number of nodes of the tree
    std::vector<std::vector<int>> zigZagLeveLOrder(TreeNode* rootNode) {
        if(!rootNode)
            return {};

        std::queue<TreeNode*> q;
        q.push(rootNode);
        std::vector<std::vector<int>> nodesZigZagWise;

        bool isOddLeveL = false;

        while(!q.empty()) {
            int qSize = q.size();
            std::vector<int> currLeveLNodes;
            while(qSize--) {
                TreeNode* currNode = q.front(); q.pop();
                if(currNode->left)
                    q.push(currNode->left);
                if(currNode->right)
                    q.push(currNode->right);
                currLeveLNodes.push_back(currNode->data);
            }
            if(isOddLeveL) {
                std::reverse(begin(currLeveLNodes), end(currLeveLNodes));
            }
            nodesZigZagWise.push_back(currLeveLNodes);
            isOddLeveL = !isOddLeveL;
        }

        return nodesZigZagWise;
    }
};

// Class to implement the Depth-first-search approach:
class DFS {
public:
    // Method to find the zigzag level order traversal of the tree, using dfs - O(N) & O(N) : Where N let be the total number of nodes of the tree
    std::vector<std::vector<int>> zigZagLeveLOrder(TreeNode* rootNode) {
        std::vector<std::vector<int>> nodesLeveLwise;
        dfs(rootNode, 0, nodesLeveLwise);
        bool isOddLeveL = false;
        for(auto& currLeveL : nodesLeveLwise) {
            if(isOddLeveL) {
                std::reverse(begin(currLeveL), end(currLeveL));
            }
            isOddLeveL = !isOddLeveL;
        }
        return nodesLeveLwise;
    }

private:
    // Method to find the level order traversal of the tree, using dfs - O(N) & O(N)
    void dfs(TreeNode* rootNode, int currentDepth, std::vector<std::vector<int>>& nodesLeveLwise) {
        if(rootNode) {
            if(currentDepth == nodesLeveLwise.size()) 
                nodesLeveLwise.push_back(std::vector<int>());
            nodesLeveLwise[currentDepth].push_back(rootNode->data);
            dfs(rootNode->left, currentDepth + 1, nodesLeveLwise);
            dfs(rootNode->right, currentDepth + 1, nodesLeveLwise);
        }
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

        // Input the size of the tree
        int n;
        std::cout<<"Enter the total number of nodes: ";
        std::cin>>n;

        // Check the given size is lying within the problem constraints or not
        if(n <= -1 || n >= 2001) {
            std::cout<<"You must enter a size, which lies between 0 and 2000!\n";
        }
        else {
            // Tracks the root node of the tree
            TreeNode* rootNode = nullptr;

            // Input the value of the nodes
            for(int node = 1; node <= n;) {
                int key;
                std::cout<<"Enter the value of the "<<node<<"th node: ";
                std::cin>>key;
                if(key <= -101 || key >= 101) {
                    std::cout<<"You must enter a value, which lies between -100 and 100!\n";
                }
                else {
                    rootNode = rootNode->insertNode(rootNode, key);
                    node++;
                }
            }

            // Call to get the list containing the zigzag level order traversal of the tree 
            BFS bfs;
            std::vector<std::vector<int>> nodesZigZagWise = bfs.zigZagLeveLOrder(rootNode);

            // Print call (print each level of the tree)
            std::cout<<"\nLevel order traversal of the tree:\n";
            rootNode->printTree(rootNode);

            // Print the zigzag order of each level of the tree
            std::cout<<"\nZigzag level order traversal of the tree:\n";
            for(auto& currLeveL : nodesZigZagWise) {
                std::cout<<"[";
                int size = currLeveL.size();                    
                for(int node = 0; node < size; ++node) {
                    (node < size-1) ? std::cout<<currLeveL[node]<<", " : std::cout<<currLeveL[node];
                }                
                std::cout<<"]\n";
            }

            // Deletion call
            rootNode = rootNode->deleteTree(rootNode);
        }

        // Input section to control the flow of iterations of the application
        char userChoice;
        std::cout<<"\nPress \'R\' to restart the application, else it will exit: ";
        std::cin>>userChoice;
        userNeedOperation = (userChoice == 'R');
    }

    return 0;
}
/*
    Topics: Tree | Breadth-first-search | Depth-first-search | Binary Tree
    Link: https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/description/
*/
