// Code to find the maximum amount of money the thief can rob without alerting the police ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    // O(2^N) & O(N)
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

    // O(N) & O(N)
    int solveWithMemo(unordered_map<TreeNode*, int>& dp, TreeNode* node) {
        if(!node)
            return 0;   

        if(dp.count(node))
            return dp[node];

        int skip = solveWithMemo(dp, node->left) + solveWithMemo(dp, node->right); 
        int rob  = node->val;                

        if(node->left) 
            rob += solveWithMemo(dp, node->left->left) + solveWithMemo(dp, node->left->right);
        if(node->right) 
            rob += solveWithMemo(dp, node->right->left) + solveWithMemo(dp, node->right->right);

        return dp[node] = max(rob, skip);
    }

public:
    int robMaxMoney(TreeNode* root) {
        unordered_map<TreeNode*, int> dp;
        return solveWithMemo(dp, root);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // O(N) & O(N)
    int robMaxMoney(TreeNode* root) {
        unordered_map<TreeNode*, int> dp;
        stack<pair<TreeNode*, bool>> stk;

        stk.push({root, false});

        while(!stk.empty()) {
            auto [node, canBuy] = stk.top(); stk.pop();

            if(!node)
                continue;

            else if(!canBuy) {
                stk.push({node, true});
                stk.push({node->right, false});
                stk.push({node->left, false});
            }
            else {
                int skip = dp[node->left] + dp[node->right];
                int rob = node->val;

                if(node->left)
                    rob += dp[node->left->left]
                         + dp[node->left->right];

                if(node->right)
                    rob += dp[node->right->left]
                         + dp[node->right->right];

                dp[node] = max(rob, skip);
            }
        }

        return dp[root];
    }
};
    
----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
Topics: Dynamic Programming | Tree | Depth-First Search | Binary Tree
Link  : https://leetcode.com/problems/house-robber-iii/description/
