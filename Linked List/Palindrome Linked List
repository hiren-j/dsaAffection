// Program to check whether a singly linked list is a palindrome or not ~ coded by Hiren
#include <iostream>
#include <stack>

// List template
struct ListNode {
    int val;
    ListNode* next;

    // Init constructor
    ListNode(int val, ListNode* next)
    :
    val(val), next(next) {}

    // Init destructor
    ~ListNode() {
        if(next) {
            delete next;
        }
    }
};

// #1 Method to check whether the list is a palindrome or not, using 1 stack - O(N) & O(N) : Where N is the size of the list.
bool isPalindrome(ListNode* headNode) {
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
// Note: A brute force solution can be made using a new list.

// #2 Method to check whether the list is a palindrome or not, using constant auxiliary space - O(N) & O(1) : Where N is the size of the list.
bool isPalindrome_(ListNode* headNode) {
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

// Method to print the list - O(N) & O(1)
void printList(ListNode* headNode) {
    while(headNode) {
        std::cout<<headNode->val<<' ';
        headNode = headNode->next;
    }
    std::cout<<'\n';
}

// Driver code
int main() {
    // Creating, connecting nodes and initializing their data.
    ListNode* headNode = new ListNode(1, new ListNode(2, new ListNode(8, new ListNode(1, nullptr))));

    // Print call
    printList(headNode); 

    // Verification call
    if(isPalindrome_(headNode))
        std::cout<<"Given list is a palindrome!";
    else
        std::cout<<"Given list is not a palindrome!";

    // Deletion call
    delete headNode;

    return 0;
}
// Link: https://leetcode.com/problems/palindrome-linked-list/description/
