// Program to delete all the nodes with a value in "to_delete" array, then we are left with a forest (a disjoint union of trees). The aim is to return the roots of the trees in the remaining forest (each node in the tree has a distinct value) ~ coded by Hiren
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

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

    // Method to construct the binary tree using dfs with binary search technique - O(N) & O(H)
    TreeNode* constructTree(vector<int>& nums, int start, int end) {
        if(start > end)
            return nullptr;

        int mid = start + (end - start) / 2;

        TreeNode* rootNode = new TreeNode(nums[mid]);
        rootNode->left     = constructTree(nums, start, mid-1);
        rootNode->right    = constructTree(nums, mid+1, end);

        return rootNode;
    }

    // Method to delete the tree using dfs - O(N) & O(H)
    TreeNode* deleteTree(TreeNode* rootNode) {
        if(!rootNode)
            return nullptr;

        rootNode->left  = deleteTree(rootNode->left);
        rootNode->right = deleteTree(rootNode->right);

        rootNode = nullptr;
        delete rootNode;

        return rootNode;
    }

    // Method to print the tree using bfs - O(N) & O(N)
    void printTree(TreeNode* rootNode) {
        if(!rootNode) {
            cout<<"Note: The tree is empty!\n";   
            return;
        }

        queue<TreeNode*> q;
        q.push(rootNode);

        while(!q.empty()) {
            int qSize = q.size();
            cout<<"[";
            while(qSize--) {
                rootNode = q.front(); q.pop();
                cout<<rootNode->val;
                if(qSize != 0) 
                    cout<<", ";
                if(rootNode->left)  
                    q.push(rootNode->left);
                if(rootNode->right)  
                    q.push(rootNode->right);
            }
            cout<<"]\n";
        }
    }
};

// Solution class
class Solution {
    unordered_map<TreeNode*, bool> isParentPresent;
    unordered_set<int> nodesToDelete;

    TreeNode* deleteNodesAndUpdateParentInfo(TreeNode* rootNode) {
        // Edge case: When the tree is empty
        if(!rootNode)
            return nullptr;

        rootNode->left  = deleteNodesAndUpdateParentInfo(rootNode->left);
        rootNode->right = deleteNodesAndUpdateParentInfo(rootNode->right);

        // If the node is going to be deleted
        if(nodesToDelete.count(rootNode->val)) {
            // Mark the left child as orphan
            if(rootNode->left)
                isParentPresent[rootNode->left] = false;

            // Mark the right child as orphan
            if(rootNode->right)
                isParentPresent[rootNode->right] = false;

            // Delete the node
            rootNode = nullptr;
            delete rootNode;
        }
        // Else mark the existence of the parent node as true
        else {
            isParentPresent[rootNode] = true;
        }
        
        return rootNode;
    }

public:
    // Method to delete the nodes and return the forest using hashmap, hashset and dfs - O(N) & O(N)
    vector<TreeNode*> deleteNodesReturnForest(TreeNode* rootNode, vector<int>& to_delete) {
        for(int node : to_delete)
            nodesToDelete.insert(node);

        deleteNodesAndUpdateParentInfo(rootNode); 

        // If the root node of the tree is not for deletion then reset it as the root node of the tree
        if(!nodesToDelete.count(rootNode->val))
            isParentPresent[rootNode] = false;

        vector<TreeNode*> forest;
        
        // Iterate and store the roots (a node with no parent is called the root node)
        for(auto [node, haveParent] : isParentPresent) 
            if(!haveParent)
                forest.push_back(node);

        return forest;
    }
};

// Class to handle the program operations
class ProgramManager {
public:
    // Method to create the tree and handle it's operations - O(N) & O(N) 
    void createAndManageTree() {
        vector<int> nodes     = createAndManageArray(true);
        vector<int> to_delete = createAndManageArray(false);

        // Tree construction call
        TreeNode* rootNode = rootNode->constructTree(nodes, 0, nodes.size() - 1);

        // Print call
        cout<<"\nThe level order traversal of the original tree is:\n";
        rootNode->printTree(rootNode);

        // Call to get the list containing the roots of the trees remaining in the forest
        Solution solution;
        vector<TreeNode*> forest = solution.deleteNodesReturnForest(rootNode, to_delete);

        // Print each component
        int comp = 1;
        for(auto& currRoot : forest) {
            cout<<"\nThe level order traversal of the "<<comp<<"th component is:\n";
            currRoot->printTree(currRoot);
            currRoot = currRoot->deleteTree(currRoot);
            comp++;
        }
    }

private:
    // Method to create the array - O(N) & O(N)
    vector<int> createAndManageArray(bool toCreateTree) {
        // Input the array size
        int n;
        if(toCreateTree)
            cout<<"\nEnter the total number of nodes (tree size): ";
        else
            cout<<"\nEnter the size of \"to_delete\" array: ";
        cin>>n;

        // Check the array size is lying within the problem constraints or not
        while(n < 1 || n > 1000) {
            cout<<"\nYou must enter a size which lies between 1 and 1000!\nKindly! Enter the size again: ";
            cin>>n;
        }

        // Stores the distinct values. It's just to ensure the problem requirement
        unordered_set<int> st;

        // Input the array values
        cout<<"Enter the values: ";
        for(int index = 0; index < n;) {
            int val;
            cin>>val;

            // Check the given value is lying within the problem constraints or not
            if(val < 1 || val > 1000) {
                cout<<"You must enter a value which lies between 1 and 1000!\n";
            }
            else {
                st.insert(val);
                ++index;
            }
        }

        vector<int> result(begin(st), end(st));

        return result;
    }
};

// Driver code
int main() {
    bool userRunsApp = true;

    while(userRunsApp) {
        // Controls console clearance for both windows and linux user
        system("cls || clear");

        cout<<"The application only accepts non-decimal numeric type value, unless specified!\n";
        
        ProgramManager programManager;
        programManager.createAndManageTree();

        // Input section to control the use of application
        char userChoice;
        cout<<"\nPress \'R\' to restart the application else it will exit: ";
        cin>>userChoice;
        userRunsApp = (userChoice == 'R');
    }

    return 0;
}
/*
    Topics: Array | Hash Table | Tree | Depth-First Search | Binary Tree
    Link  : https://leetcode.com/problems/delete-nodes-and-return-forest/
*/
