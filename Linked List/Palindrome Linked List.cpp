// Program to check whether a singly linked list is a palindrome or not ~ coded by Hiren
#include <iostream>
#include <cstdlib>
#include <stack>

// List template
class ListNode {
public:
    int val;
    ListNode* next;

    // Init constructor
    ListNode(int val, ListNode* next = nullptr)
    :
    val(val), next(next) {}

    // Method to insert a node in the list - O(1) & O(1)
    void insertNode(ListNode*& headNode, ListNode*& currNode, int val) {
        ListNode* newNode = new ListNode(val);
        if(!headNode)
            headNode = newNode, currNode = newNode;
        else    
            currNode->next = newNode, currNode = currNode->next;
        currNode->next = nullptr;
    }

    // Method to delete the list - O(N) & O(1) : Where N is the size of the list.
    void deleteList(ListNode*& headNode) {
        while(headNode) {
            ListNode* nextNode = headNode->next;
            delete headNode;
            headNode = nextNode;
        }
    }

    // Method to print the list - O(N) & O(1) : Where N is the size of the list.
    void printList(ListNode* headNode) {
        while(headNode) {
            std::cout<<headNode->val<<' ';
            headNode = headNode->next;
        }
        std::cout<<'\n';
    }
};

// Solution class:
class Solution {
public:
    // #1 Method to check whether the list is a palindrome or not, using 1 stack - O(N) & O(N) : Where N is the size of the list.
    bool isPalindrome_V1(ListNode* headNode) {
        // Edge case: When the list is empty or single noded.
        if(!headNode || !headNode->next)
            return true;

        std::stack<ListNode*> stack;   // Stores the nodes in the reverse order.
        ListNode* currNode = headNode; // Tracks the nodes of the list.

        // Iterate and store all the nodes to the stack.
        while(currNode) {
            stack.push(currNode);
            currNode = currNode->next;
        }

        // Iterate and check for the palindromeness.
        while(headNode) {
            // Return false, if the value of both the nodes is not same.
            if(headNode->val != stack.top()->val) {
                return false;
            }
            headNode = headNode->next;
            stack.pop();
        }

        // Return true, if reached here.
        return true;
    }

    // #2 Method to check whether the list is a palindrome or not, using constant auxiliary space - O(N) & O(1) : Where N is the size of the list.
    bool isPalindrome_V2(ListNode* headNode) {
        // Edge case: When the list is empty or single noded.
        if(!headNode || !headNode->next)
            return true;

        ListNode *slowPointer = headNode, *fastPointer = headNode;
        ListNode *tmpPointer  = nullptr;

        // Iterate and find the previous node of the middle node and itself.
        while(fastPointer && fastPointer->next) {
            tmpPointer  = slowPointer;
            slowPointer = slowPointer->next;
            fastPointer = fastPointer->next->next;
        }   

        // Seperate the sublist by setting the previous node of the middle node.
        tmpPointer->next = nullptr; 
        tmpPointer = nullptr;
        ListNode* currNode = slowPointer; 

        // Reverse the second half (which begins from the middle node) of the list.
        while(currNode) {
            ListNode* nextNode = currNode->next; 
            currNode->next = tmpPointer;
            tmpPointer = currNode;
            currNode = nextNode;
        }

        // Iterate and check for the palindromeness.
        while(headNode) {
            // Return false, if the value of both the nodes is not same.
            if(headNode->val != tmpPointer->val) {
                return false;
            }
            headNode = headNode->next;
            tmpPointer = tmpPointer->next;
        }

        // Return true, if reached here.
        return true;
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not.
    bool canPerformOperation = true;

    while(canPerformOperation) {
        // Handles console clearance for both "windows" and "linux" user.
        system("cls || clear");

        // Input the number of nodes for the list.
        int size;
        std::cout<<"Enter the number of nodes for the list: ";
        std::cin>>size;
        
        // Check the given size is valid or not.
        if(size <= 0) {
            std::cout<<"Enter a valid size, application expects a positive integer!";
            return 0;
        }

        ListNode* headNode = nullptr; // Tracks the head node of the list.
        ListNode* tailNode = nullptr; // Tracks the last node of the list.

        // Input the nodes value of the list.
        for(int node=1; node<=size; ++node) {
            int key;
            std::cout<<"Enter the value of the "<<node<<"th node: ";
            std::cin>>key;
            headNode->insertNode(headNode, tailNode, key);
        }

        // Print call
        std::cout<<"\nList: ";
        headNode->printList(headNode);

        // Verification call
        Solution solution;
        if(solution.isPalindrome_V2(headNode))
            std::cout<<"Given list is a palindrome!";
        else
            std::cout<<"Given list is not a palindrome!";

        // Deletion call (delete the head node and recursively the entire list)
        delete headNode; headNode = nullptr;

        // Input section to handle the flow of iterations.
        char userChoise;
        std::cout<<"\n\nPress \'Y\' to perform the same operation on an another list, else application will exit automatically: ";
        std::cin>>userChoise;
        canPerformOperation = (userChoise == 'Y') ? true : false; 
    }

    return 0;
}
/*
    Topics: Linked List | Stack | Two Pointers
    Link: https://leetcode.com/problems/palindrome-linked-list/description/
*/
