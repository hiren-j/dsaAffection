// Code to find the longest ZigZag path contained in that tree. Zigzag length is defined as the number of nodes visited - 1. (A single node has a length of 0) ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
    DON'T IGNORE MUST READ (REGARDING TIME AND AUXILIARY SPACE OF THE FUNCTION):

        `getLongestPath() without memoization` 
            - Time complexity: O(N*N) 
              Explanation: Let the total number of nodes is N. The auxiliary time of the `getLongestPath()` is O(N) here and as we're calling the function from each node of the tree hence the overall time complexity becomes O(N*N).
               
            - Auxiliary space : O(H)
              Explanation: Where H let be the height of the tree. It represents the maximum depth of the recursion stack.

        `getLongestPath() with memoization` 
            - Time complexity: O(NLogN) 
              Explanation: The memoization table will end up storing results for N*2 states in the worst case. As the table is an ordered map and we've performed operations such as insertion and searching which could take `Log(sizeofmap)` time. 
              More clearly Log(N) time. The results will be calculated once after that the memoization table will be used to return the result in Log(N) time, and
              as we're calling the `getLongestPath()` from each node then the overall time complexity becomes O(NLogN). 
                          
            - Auxiliary space : O(N*2 + H)
              Explanation: The first term N*2 represents the space taken by the memoization table. Why 2? It's because the second parameter could be either true or false. So this how it will end up storing results for N*2 states in the worst case.
              Where H let be the height of the tree. It represents the maximum depth of the recursion stack.
*/

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Class to implement the Top-down approach:
class DynamicProgramming {
    map<pair<TreeNode*, bool>, int> dp;
    int result = 0;

    int getLongestPath(TreeNode* rootNode, bool goLeft) {
        // Edge case: If the tree is empty then there's no path hence return 0
        if(!rootNode)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(dp.count({rootNode, goLeft})) 
            return dp[{rootNode, goLeft}];

        int maxLength = 0;

        if(goLeft)
            maxLength = max(maxLength, getLongestPath(rootNode->left, false));
        else
            maxLength = max(maxLength, getLongestPath(rootNode->right, true));      

        // Store the result value to the memoization table and then return it
        return dp[{rootNode, goLeft}] = 1 + maxLength;
    }    

    void DFS(TreeNode* rootNode) {
        // Edge case: If the tree is empty then there's no path
        if(!rootNode)
            return;

        result = max(result, getLongestPath(rootNode, true));  // Get the length of the longest ZigZag path from the left subtree of the node
        result = max(result, getLongestPath(rootNode, false)); // Get the length of the longest ZigZag path from the right subtree of the node 

        // Recursively explore all the ZigZag paths lying in the subtrees
        DFS(rootNode->left);
        DFS(rootNode->right);
    }

public:
    // Method to find the longest ZigZag path contained in the tree, using recursion with memoization :- 
    int longestZigZag(TreeNode* rootNode) {
        DFS(rootNode);
        return result - 1;
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming | Tree | Depth-First Search | Binary Tree
Link  : https://leetcode.com/problems/longest-zigzag-path-in-a-binary-tree/description/
