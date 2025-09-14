// Program to find largest value of each row of the binary tree ~ coded by Hiren
#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;

class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;

    // Init constructor
    TreeNode(int val, TreeNode* left = nullptr, TreeNode* right = nullptr)
    :
    val(val), left(left), right(right) {}
};

class ConstructBinaryTree {
    char getUserChoice(char ch, string side, string& rootPath) {
        char choice;
        cout << "Press '" << ch << "' to move to " << side << " side of (" << rootPath  << "): ";
        cin >> choice;
        return choice;
    }

public:
    // O(N) & O(N*N)
    TreeNode* createTree(string rootPath) {
        int val;
        cout << "Enter value of " << rootPath << " (-1 for endpoint): ";
        cin >> val;

        if(val == -1) {
            return nullptr;
        }

        TreeNode* rootNode = new TreeNode(val);

        // Left side
        string leftPath = rootPath + " -> left";
        if(getUserChoice('L', "left", leftPath) == 'L' ) {
            rootNode->left = createTree(leftPath);
        }

        // Right side
        string rightPath = rootPath + " -> right";
        if(getUserChoice('R', "right", rightPath) == 'R' ) {
            rootNode->right = createTree(rightPath);
        }

        return rootNode;
    }

    // O(N) & O(N)
    TreeNode* createTreeOptimized(string& rootPath) {
        int val;
        cout << "Enter value of " << rootPath << " (-1 for endpoint): ";
        cin >> val;

        if(val == -1) {
            return nullptr;
        }

        // Left side
        TreeNode* rootNode = new TreeNode(val);
        rootPath += " -> left";
        if(getUserChoice('L', "left", rootPath) == 'L' ) {
            rootNode->left = createTreeOptimized(rootPath);
        }
        int charToRemove = 8;
        while(charToRemove-- > 0) rootPath.pop_back();

        // Right side
        rootPath += " -> right";
        if(getUserChoice('R', "right", rootPath) == 'R' ) {
            rootNode->right = createTreeOptimized(rootPath);
        }
        charToRemove = 9;
        while(charToRemove-- > 0) rootPath.pop_back();

        return rootNode;
    }
};

class LargestValueEachRow {
    // O(N) & O(N)
    vector<int> BFS(TreeNode* rootNode) {
        if(!rootNode)
            return {};

        queue<TreeNode*> q;
        q.push(rootNode);

        vector<int> maxLeveLWise;

        while(!q.empty()) {
            int qSize = q.size();
            int currLeveLMax = INT_MIN;
            
            while(qSize--) {
                rootNode = q.front(); q.pop();
                if(rootNode->left)  q.push(rootNode->left);
                if(rootNode->right) q.push(rootNode->right);
                currLeveLMax = max(currLeveLMax, rootNode->val);
            }

            maxLeveLWise.push_back(currLeveLMax);
        }

        return maxLeveLWise;
    }

    // O(N) & O(H)
    void DFS(TreeNode* rootNode, int depth, vector<int>& maxLeveLWise) {
        if(rootNode) {
            if(maxLeveLWise.size() == depth) {
                maxLeveLWise.push_back(INT_MIN);
            }
            maxLeveLWise[depth] = max(maxLeveLWise[depth], rootNode->val);
            DFS(rootNode->left, depth + 1, maxLeveLWise);
            DFS(rootNode->right, depth + 1, maxLeveLWise);
        }
    }

public:
    vector<int> largestValues(TreeNode* rootNode) {
        vector<int> maxLeveLWise;
        DFS(rootNode, 0, maxLeveLWise);
        return maxLeveLWise;
    }
};

// O(N) & O(N)
void printLeveLOrder(TreeNode* rootNode) {
    if(!rootNode)
        return;

    queue<TreeNode*> q;
    q.push(rootNode);

    while(!q.empty()) {
        int qSize = q.size();
        cout << "[";

        for(int i = 1; i <= qSize; ++i) {    
            rootNode = q.front(); q.pop();
            cout << rootNode->val;
            if(i < qSize) cout << ", ";
            if(rootNode->left)  q.push(rootNode->left);
            if(rootNode->right) q.push(rootNode->right);
        }

        cout << "]\n";
    }
}

// O(N) & O(H)
TreeNode* deleteTree(TreeNode* rootNode) {
    if(!rootNode)
        return nullptr;

    rootNode->left  = deleteTree(rootNode->left);
    rootNode->right = deleteTree(rootNode->right);

    delete rootNode; 
    return nullptr;
}

// Driver code
int main() {
    bool userRunApp = true;

    while(userRunApp) {
        system("cls || clear");

        // Tree creation call
        ConstructBinaryTree cbt;
        string rootPath = "root";
        TreeNode* rootNode = cbt.createTreeOptimized(rootPath);

        // Print call
        cout << "\nThe BFS order of tree is: \n";
        printLeveLOrder(rootNode);

        // Find largest value of each row
        LargestValueEachRow solution;
        vector<int> maxLeveLWise = solution.largestValues(rootNode);

        // Print largest values
        cout << "\nThe largest values of each row of the tree:\n";
        for(const int& val : maxLeveLWise) {
            cout << val << '\n';
        }

        // Deletion call
        rootNode = deleteTree(rootNode);

        char userChoice;
        cout << "\nPress 'R' to restart application, else application will exit: ";
        cin >> userChoice;
        userRunApp = (userChoice == 'R');
    }

    return 0;
}
/*
    Topics: Tree | Depth-First Search | Breadth-First Search | Binary Tree
    Link: https://leetcode.com/problems/find-largest-value-in-each-tree-row/
*/
