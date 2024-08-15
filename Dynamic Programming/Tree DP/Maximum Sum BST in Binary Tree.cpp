// Code to find the maximum sum of all keys of any sub-tree which is also a Binary Search Tree (BST) ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
    DON'T IGNORE MUST READ (REGARDING THE FIRST SOLUTION):
        This solution will lead to time limit exceed due to the frequent checks performed in logarithmic time. 
        The primary issue is the use of a `map`, which takes `log(sizeofmap)` time for insertion and searching, 
        resulting in inefficiencies. Both recursion and memoization will result in TLE.

        Including the recursive solution alone, the time complexity is O(N*N). With memoization, it seems to be 
        improved but still suffers from the `map`'s logarithmic complexity, leading to TLE.

        However, this approach illustrates how memoization can be applied. The brute-force method checks if 
        each subtree is a BST, which is inefficient. Memoization attempts to optimize by storing results 
        to avoid redundant checks, but due to the `map`'s logarithmic complexity, it still results in TLE.
*/

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
    DON'T IGNORE MUST READ (REGARDING THE SECOND SOLUTION):
        This solution isn't a complete DP solution because it doesn't have overlapping subproblems. 
        I refer to it as a bottom-up DFS approach because, in DP, we create future results from past information, 
        which is similar here. However, since a true DP problem with a recursive solution must have both multiple options 
        and overlapping subproblems, the absence of one means I still don't consider this solution to be a DP solution.
*/

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Class to implement the Top-down approach:
class DynamicProgramming {
    map<pair<TreeNode*, int>, int> dp;
    int maximumSum = INT_MIN;

    bool solveWithMemo(TreeNode* rootNode, int& prevValue, int& sum) {
        // Edge case: If the tree is empty then it's also a valid BST
        if(!rootNode)
            return true;

        // Memoization table: If the current state is already computed then return the computed value
        if(dp.count({rootNode, prevValue})) 
            return dp[{rootNode, prevValue}];

        bool isBSTLeft = solveWithMemo(rootNode->left, prevValue, sum);

        // If the previous node value is not strictly lesser than the current node's value then the subtree is not a valid BST
        if(prevValue >= rootNode->val)
            return dp[{rootNode, prevValue}] = false;

        prevValue = rootNode->val; sum += rootNode->val;

        bool isBSTRight = solveWithMemo(rootNode->right, prevValue, sum);

        // Store the result value to the memoization table and then return it
        return dp[{rootNode, prevValue}] = (isBSTLeft && isBSTRight);
    }

    void exploreAllBST(TreeNode* rootNode) {
        // Edge case: If the tree is empty then
        if(!rootNode)
            return;

        int prevValue = INT_MIN; // Tracks the previous node of any node in the inorder fashion
        int sum = 0;             // Stores the sum of a BST

        // If the current subtree is a valid BST then update the result by the maximum value
        if(solveWithMemo(rootNode, prevValue, sum))
            maximumSum = max(maximumSum, sum);

        // Recursively explore all the BST's
        exploreAllBST(rootNode->left);
        exploreAllBST(rootNode->right);
    }

public:
    // Method to find the maximum sum of all keys of any sub-tree which is also a BST, using recursion with memoization :- 
    int maxSumBST(TreeNode* rootNode) {
        exploreAllBST(rootNode);
        return (maximumSum < 0) ? 0 : maximumSum;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Class to implement the second solution:
class Solution_V2 {
    // Stores the result value
    int maximumSum = INT_MIN;

    vector<int> findMaxSumBST(TreeNode* rootNode) {
        // Edge case: If the tree is empty then it's also a valid BST
        if(!rootNode)
            // Return {information of being a BST or not, sum of the BST, minimum value of the BST, maximum value of the BST}
            return {true, 0, INT_MAX, INT_MIN}; 

        auto BSTInfoLeft  = findMaxSumBST(rootNode->left);  // Stores the BST information of the left subtree
        auto BSTInfoRight = findMaxSumBST(rootNode->right); // Stores the BST information of the right subtree  

        bool isLeftBST  = (BSTInfoLeft[0]  && BSTInfoLeft[3] < rootNode->val);  // If the maximum value of the left subtree is lesser than the current node's value then left subtree is a BST 
        bool isRightBST = (BSTInfoRight[0] && BSTInfoRight[2] > rootNode->val); // If the minimum value of the right subtree is greater than the current node's value then right subtree is a BST

        int subtreeSum = BSTInfoLeft[1] + rootNode->val + BSTInfoRight[1];
        
        // If the left and right subtree of the current node is a BST then update the result by the maximum value
        if(isLeftBST && isRightBST)
            maximumSum = max(maximumSum, subtreeSum);

        int minVal = min(rootNode->val, BSTInfoLeft[2]);  // Stores the minimum value of the current BST
        int maxVal = max(rootNode->val, BSTInfoRight[3]); // Stores the maximum value of the current BST

        // Return the BST information of the current node
        return {isLeftBST && isRightBST, subtreeSum, minVal, maxVal};
    }

public:
    // Method to find the maximum sum of all keys of any sub-tree which is also a BST, using postorder traversal - O(N) & O(H)
    int maxSumBST(TreeNode* rootNode) {
        findMaxSumBST(rootNode);
        return (maximumSum <= 0) ? 0 : maximumSum;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming | Tree | Depth-First Search | Binary Search Tree | Binary Tree
Link  : https://leetcode.com/problems/maximum-sum-bst-in-binary-tree/?envType=list&envId=50v8rtm7
