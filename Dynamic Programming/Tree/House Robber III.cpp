// Code to find the maximum amount of money the thief can rob without alerting the police ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------

// Class to implement the Top-down approach:
class TopDown {
public:
    // Method to find the maximum amount of money the thief can rob, using recursion with memoization - O(N) & O(N)
    int robMaxMoney(TreeNode* rootNode) {
        unordered_map<TreeNode*, int> memory;
        return solveWithMemo(rootNode, memory);
    }

private:
    // O(6*N) & O(N+N)
    int solveWithMemo(TreeNode* rootNode, unordered_map<TreeNode*, int>& memory) {
        // Edge case: If there's no node then there's no money to rob
        if(!rootNode)
            return 0;   

        // Memoization table: If the current state is already computed then return the computed value
        if(memory.count(rootNode))
            return memory[rootNode];

        // There are always two possibilities to perform at each node
        int currSkip = solveWithMemo(rootNode->left, memory) + solveWithMemo(rootNode->right, memory); // Is to skip the rob and move to it's child nodes
        int currRob  = rootNode->val;                                                                  // Is to rob and take the value of it                

        // If you rob at the node then you can't rob at it's left child / adjacent node
        if(rootNode->left) 
            currRob += solveWithMemo(rootNode->left->left, memory) + solveWithMemo(rootNode->left->right, memory);
            
        // If you rob at the node then you can't rob at it's right child / adjacent node
        if(rootNode->right) 
            currRob += solveWithMemo(rootNode->right->left, memory) + solveWithMemo(rootNode->right->right, memory);

        // Store the result value to the memoization table and then return it
        return memory[rootNode] = max(currRob, currSkip);
    }

    // O(6^N) & O(N)
    int solveWithoutMemo(TreeNode* rootNode) {
        // Edge case: If there's no node then there's no money to rob
        if(!rootNode)
            return 0;   

        // There are always two possibilities to perform at each node
        int currSkip = solveWithoutMemo(rootNode->left) + solveWithoutMemo(rootNode->right); // Is to skip the rob and move to it's child nodes
        int currRob  = rootNode->val;                                                        // Is to rob and take the value of it                

        // If you rob at the node then you can't rob at it's left child / adjacent node
        if(rootNode->left) 
            currRob += solveWithoutMemo(rootNode->left->left) + solveWithoutMemo(rootNode->left->right);
            
        // If you rob at the node then you can't rob at it's right child / adjacent node
        if(rootNode->right) 
            currRob += solveWithoutMemo(rootNode->right->left) + solveWithoutMemo(rootNode->right->right);

        // As we're striving for the maximum money hence return the maximum value
        return max(currRob, currSkip);
    }
};

--------------------------------------------------------------------------------------------------------------------
    
Topics: Dynamic Programming | Tree | Depth-First Search | Binary Tree
Link  : https://leetcode.com/problems/house-robber-iii/description/
