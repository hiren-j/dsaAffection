// Program to find the boolean result of evaluating the root node of the binary tree ~ coded by Hiren
#include <iostream>

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
};

// Method to evaluate the root node of the binary tree, using dfso only - O(N) & O(H)
bool evaluateTree(TreeNode* rootNode) {
    // Edge case: Return true if the tree is empty.
    if(!rootNode)
        return true;

    // Edge case: If it's a leaf node then return the node's value.
    if(!rootNode->left && !rootNode->right)
        return rootNode->val;
    
    // Recursively evaluate the left and right subtrees.
    bool sideLeft  = evaluateTree(rootNode->left);
    bool sideRight = evaluateTree(rootNode->right);

    // If the node's value is 2 then evaluate the OR operation.
    if(rootNode->val == 2 && (sideLeft || sideRight))
        return true;
    
    // If the node's value is 3 then evaluate the AND operation.
    if(rootNode->val == 3 && sideLeft && sideRight)
        return true;

    // Return false, if no conditions mets.
    return false;
}

// Method to print the tree using postOrder traversal - O(N) & O(H)
void printTree(TreeNode* rootNode) {
    if(rootNode) {
        printTree(rootNode->left);
        printTree(rootNode->right);
        std::cout<<rootNode->val<<' ';
    }
}

// Driver code
int main() {
    // Creating, connecting nodes and initializing their data.
    TreeNode* rootNode = new TreeNode(2);
    rootNode->left = new TreeNode(1);
    rootNode->right = new TreeNode(3);
    rootNode->right->left = new TreeNode(0);
    rootNode->right->right = new TreeNode(1);

    // Print call
    printTree(rootNode);

    // Verification call
    if(evaluateTree(rootNode))
        std::cout<<"\nEvaluation result is \"True\"!";
    else
        std::cout<<"\nEvaluation result is \"False\"!";

    // Deallocation call
    delete rootNode;

    return 0;
}
// Link: https://leetcode.com/problems/evaluate-boolean-binary-tree/description/
