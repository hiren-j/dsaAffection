// Code to find the maximum amount of money the thief can rob without alerting the police ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------

class DynamicProgramming {
    int solveWithoutMemo(TreeNode* node) {
        if(!node)
            return 0;   

        int skip = solveWithoutMemo(node->left) + solveWithoutMemo(node->right); 
        int rob  = node->val;                                                        

        if(node->left) 
            rob += solveWithoutMemo(node->left->left) + solveWithoutMemo(node->left->right);
        if(node->right) 
            rob += solveWithoutMemo(node->right->left) + solveWithoutMemo(node->right->right);

        return max(rob, skip);
    }

    int solveWithMemo(TreeNode* node, unordered_map<TreeNode*, int>& dp) {
        if(!node)
            return 0;   

        if(dp.count(node))
            return dp[node];

        int skip = solveWithMemo(node->left, dp) + solveWithMemo(node->right, dp); 
        int rob  = node->val;                

        if(node->left) 
            rob += solveWithMemo(node->left->left, dp) + solveWithMemo(node->left->right, dp);
        if(node->right) 
            rob += solveWithMemo(node->right->left, dp) + solveWithMemo(node->right->right, dp);

        return dp[node] = max(rob, skip);
    }

public:
    int robMaxMoney(TreeNode* node) {
        unordered_map<TreeNode*, int> dp;
        return solveWithMemo(node, dp);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
Topics: Dynamic Programming | Tree | Depth-First Search | Binary Tree
Link  : https://leetcode.com/problems/house-robber-iii/description/
