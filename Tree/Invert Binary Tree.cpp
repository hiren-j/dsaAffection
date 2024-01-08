// Program to invert a binary tree ~ coded by Hiren
#include <iostream>
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
};

// Method to invert the binary tree using dfs only - O(N) & O(H)
TreeNode* invertTree(TreeNode* rootNode) {
    // Edge case: When the tree is empty
    if(!rootNode)
        return nullptr;

    TreeNode* nodeLeft  = rootNode->left;  // Tracks the left node of the current node
    TreeNode* nodeRight = rootNode->right; // Tracks the right node of the current node

    rootNode->left  = invertTree(nodeRight); // Recurse and set the right node to the left side of the current node
    rootNode->right = invertTree(nodeLeft);  // Recurse and set the left node to the right side of the current node

    // Return the current node
    return rootNode;
}

// Method to delete the binary tree using dfs - O(N) & O(H)
TreeNode* deleteTree(TreeNode* rootNode) {
    if(!rootNode)
        return nullptr;

    rootNode->left  = deleteTree(rootNode->left);
    rootNode->right = deleteTree(rootNode->right);

    delete rootNode;

    return nullptr;
}

// Method to print the tree using inOrder traversal - O(N) & O(H)
void printTree(TreeNode* rootNode) {
    if(rootNode) {
        printTree(rootNode->left);
        cout<<rootNode->val<<' ';
        printTree(rootNode->right);
    }
}

// Driver code
int main() {
    // Creating, connecting nodes and initializing their data
    TreeNode* c3 = new TreeNode(8);
    TreeNode* c2 = new TreeNode(6, nullptr, c3);
    TreeNode* c1 = new TreeNode(5);
    TreeNode* rootNode = new TreeNode(10, c1, c2);

    // Print call
    printTree(rootNode); 
    cout<<'\n';

    // Invert call
    rootNode = invertTree(rootNode);

    // Print call
    printTree(rootNode);
    
    // Deletion call
    rootNode = deleteTree(rootNode);
    
    return 0;
}
// Link: https://leetcode.com/problems/invert-binary-tree/
