// Program to check whether a singly linked list is a palindrome or not ~ coded by Hiren
#include <iostream>
#include <stack>
#include <chrono>
#include <thread>

// List template
class ListNode {
public:
    int val;
    ListNode* next;

    // Init constructor
    ListNode(int val, ListNode* next = nullptr)
    :
    val(val), next(next) {}
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

// Class to wrap all the basic methods of the list:
class ListCommonMethods {
public:
    // Method to insert a node in the list - O(1) & O(1)
    void insertNode(ListNode*& headNode, ListNode*& currNode, int val) {
        ListNode* newNode = new ListNode(val);
        if(!headNode)
            headNode = newNode, currNode = newNode;
        else    
            currNode->next = newNode, currNode = currNode->next;
        currNode->next = nullptr;
    }

    // Method to delete the list - O(N) & O(1)
    void deleteList(ListNode*& headNode) {
        while(headNode) {
            ListNode* nextNode = headNode->next;
            delete headNode;
            headNode = nextNode;
        }
    }

    // Method to print the list - O(N) & O(1)
    void printList(ListNode* headNode) {
        while(headNode) {
            std::cout<<headNode->val<<' ';
            headNode = headNode->next;
        }
        std::cout<<'\n';
    }
};

// Driver code
int main() {
    int testCases;
    std::cout<<"Enter the number of testcases you want: ";
    std::cin>>testCases;

    if(testCases <= 0) {
        std::cout<<"Enter an valid number for the testcases, application expects a positive integer!";
        return 0;
    }

    while(testCases--) {
        system("cls || clear");
        int n;
        std::cout<<"Enter the number of nodes for the list: ";
        std::cin>>n;

        ListNode *headNode = nullptr, *currNode = nullptr;
        ListCommonMethods cm;

        for(int node=1; node<=n; ++node) {
            int val;
            std::cout<<"Enter the value for the "<<node<<"th node: ";
            std::cin>>val;
            cm.insertNode(headNode, currNode, val);
        }

        std::cout<<"\nList: ";
        cm.printList(headNode);

        Solution solution;
        (solution.isPalindrome_V2(headNode)) ? std::cout<<"Given list is a palindrome!" : std::cout<<"Given list is not a palindrome!";

        cm.deleteList(headNode);

        if(testCases) {
            int userSeconds;
            std::cout<<"\n\nEnter the number of seconds which after you want to restart the application: ";
            std::cin>>userSeconds;
            std::this_thread::sleep_for(std::chrono::seconds(userSeconds));
        }
        else {
            std::cout<<"\n\nThe application will close in 10 seconds!";
            std::this_thread::sleep_for(std::chrono::seconds(10));
        }
    }

    return 0;
}
// Link: https://leetcode.com/problems/palindrome-linked-list/description/
