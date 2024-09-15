// Code to check is if all the elements in the linked list starting from the head correspond to some downward path connected in the binary tree, otherwise return false. In this context downward path means a path that starts at some node and goes downwards ~ coded by Hiren

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Class to implement the Top-down approach:
class DynamicProgramming {
    map<pair<ListNode*, TreeNode*>, bool> dp;
    ListNode* origHead = nullptr;

    // O(N^4) & O(H) : Where N and H is the number of nodes and height of the tree
    bool solveWithoutMemo(ListNode* headNode, TreeNode* rootNode) {
        // Edge case: If the list is empty then return true
        if(!headNode)
            return true;

        // Edge case: At this point if the tree is empty then return false
        if(!rootNode)
            return false;

        // If the value of tree node and list node is equal
        if(rootNode->val == headNode->val) {
            // If its the last node of the list then return true
            if(!headNode->next)
                return true;

            // If the value of left child is equal to the next node of list then check the existence of the remaining list at the left subtree
            if(rootNode->left && headNode->next->val == rootNode->left->val && solveWithoutMemo(headNode->next, rootNode->left))
                return true;

            // If the value of right child is equal to the next node of list then check the existence of the remaining list at the right subtree
            if(rootNode->right && headNode->next->val == rootNode->right->val && solveWithoutMemo(headNode->next, rootNode->right)) 
                return true;
        }
        
        // Check the existence of the list from its first node at the left and right side of the tree node
        bool isPathFromLeft  = solveWithoutMemo(origHead, rootNode->left);
        bool isPathFromRight = solveWithoutMemo(origHead, rootNode->right);

        // If the list is present as a path in any of the subtrees then return true
        return isPathFromLeft || isPathFromRight;
    }

    // O((M*N)Log(M*N)) & O(M*N + H) : Where M is the length of the list. N and H is the number of nodes and height of the tree
    bool solveWithMemo(ListNode* headNode, TreeNode* rootNode) {
        // Edge case: If the list is empty then return true
        if(!headNode)
            return true;

        // Edge case: At this point if the tree is empty then return false
        if(!rootNode)
            return false;

        // Memoization table: If the current state is already computed then return the computed value
        if(dp.count({headNode, rootNode}))
            return dp[{headNode, rootNode}];    

        // If the value of tree node and list node is equal
        if(rootNode->val == headNode->val) {
            // If its the last node of the list then return true
            if(!headNode->next)
                return dp[{headNode, rootNode}] = true;

            // If the value of left child is equal to the next node of list then check the existence of the remaining list at the left subtree
            if(rootNode->left && headNode->next->val == rootNode->left->val && solveWithMemo(headNode->next, rootNode->left))
                return dp[{headNode, rootNode}] = true;

            // If the value of right child is equal to the next node of list then check the existence of the remaining list at the right subtree
            if(rootNode->right && headNode->next->val == rootNode->right->val && solveWithMemo(headNode->next, rootNode->right))
                return dp[{headNode, rootNode}] = true;
        }
        
        // Check the existence of the list from its first node at the left and right side of the tree node
        bool isPathFromLeft  = solveWithMemo(origHead, rootNode->left);
        bool isPathFromRight = solveWithMemo(origHead, rootNode->right);

        // Store the result value to the memoization table and then return it
        return dp[{headNode, rootNode}] = isPathFromLeft || isPathFromRight;
    }

public:
    // Method to check is if linked list present in the binary tree, using recursion with memoization :-
    bool isSubPath(ListNode* headNode, TreeNode* rootNode) {
        origHead = headNode;
        return solveWithMemo(headNode, rootNode);
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Linked List | Tree | Depth-First Search | Binary Tree | Dynamic Programming
Link  : https://leetcode.com/problems/linked-list-in-binary-tree/description/
