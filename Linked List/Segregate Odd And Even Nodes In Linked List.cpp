// Program to segregate odd and even nodes in a linked list ~ coded by Hiren
#include <iostream>
#include <cstdlib>
#include <vector>

// List template
class ListNode {
public:
    int val;
    ListNode* next;

    // Init constructor
    ListNode(int val, ListNode* next = nullptr)
    :
    val(val), next(next) {}

    // Init destructor
    ~ListNode() {
        if(next) {
            delete next;
        }
    }

    // Method to insert a node in the list - O(1) & O(1) : Where N is the size of the list.
    void insertNode(ListNode*& headNode, ListNode*& tailNode, int key) {
        ListNode* newNode = new ListNode(key);
        if(!headNode)
            headNode = newNode, tailNode = newNode;
        else    
            tailNode->next = newNode, tailNode = tailNode->next;
        tailNode->next = nullptr;
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

// #1 Solution class
class Solution_V1 {
public:
    // Method to segregate odd and even nodes, using dynamic node creation - O(N) & O(N) : Where N is the size of the list.
    ListNode* segregateOddEven(ListNode* headNode) {
        // Edge case: When the list is empty or single noded.
        if(!headNode || !headNode->next)
            return headNode;
    
        ListNode* newCurrent = nullptr; // Tracks the nodes of the new list.
        ListNode* newHead    = nullptr; // Tracks the head node node of the new list.

        createNewNodes(headNode, newHead, newCurrent, true);  // Create new nodes from odd-valued-nodes.
        createNewNodes(headNode, newHead, newCurrent, false); // Create new nodes from even-valued-nodes.
    
        // Set the last node of the new list.
        newCurrent->next = nullptr;
    
        // Return the head node node of the new list.
        return newHead;
    }

private:
    // Method helper
    void createNewNodes(ListNode* origCurrent, ListNode*& newHead, ListNode*& newCurrent, bool lookingForOdd) {
        while(origCurrent) {
            // If we're looking for odd then check for the odd-valued-nodes, else check for the even-valued-nodes.
            if(origCurrent->val % 2 && lookingForOdd || !(origCurrent->val % 2) && !lookingForOdd) {
                // If its the first node of the new list, then create the head node of it. 
                if(!newCurrent) {
                    newHead = new ListNode(origCurrent->val, nullptr);
                    newCurrent = newHead;
                }
                // Else then create the current node in the new list. 
                else {
                    newCurrent->next = new ListNode(origCurrent->val, nullptr);
                    newCurrent = newCurrent->next;
                }
            }
            // Move to the next node in the original list.
            origCurrent = origCurrent->next;
        }
    }
};
// Note: This solution can lead to the "memory leak issues", as the new list is created dynamically but never freed.

// #2 Solution class
class Solution_V2 {
public:
    // Method to segregate odd and even nodes, using buffer - O(N) & O(N) : Where N is the size of the list.
    ListNode* segregateOddEven(ListNode* headNode) {
        // Edge case: When the list is empty or single noded.
        if(!headNode || !headNode->next)
            return headNode;

        ListNode* origCurrent = headNode; // Tracks the nodes of the original list.
        std::vector<ListNode*> oddEven;   // Stores the nodes of the original list in odd and even group.

        // Iterate and store all the odd-valued-nodes to the "buffer".
        while(origCurrent) {
            if(origCurrent->val % 2)
                oddEven.push_back(origCurrent);
    
            origCurrent = origCurrent->next;
        }

        origCurrent = headNode;

        // Iterate and store all the even-valued-nodes to the "buffer".
        while(origCurrent) {
            if(!(origCurrent->val % 2))
                oddEven.push_back(origCurrent);

            origCurrent = origCurrent->next;
        }

        int size = oddEven.size();

        // Iterate and link all the nodes of the "buffer".
        for(int i=1; i<size; i++) { 
            oddEven[i-1]->next = oddEven[i];
        }

        // Set the last node of the segregated list.
        oddEven[size-1]->next = nullptr;

        // Return the head node of the segregated list.
        return oddEven[0];
    }
};

// #3 Solution class
class Solution_V3 {
public:
    // Method to segregate odd and even nodes, using recursion - O(N) & O(N) : Where N is the size of the list.
    ListNode* segregateOddEven(ListNode* headNode) {
        // Tracks the last node of the odd-grouped list.
        ListNode* oddLast = nullptr; 
        
        // Recursively search and store the head node of both the groups.
        std::vector<ListNode*> oddEvenHead = segregateUsingRecursion(headNode, oddLast);

        // Return the head node of the even-grouped list, if the odd-grouped list doesn't exist.
        if(!oddEvenHead[0]) 
            return oddEvenHead[1];

        // Link the last node of the odd-grouped list to the head node of the even-grouped list.
        oddLast->next = oddEvenHead[1];
        
        // Return the head node of the odd-grouped list.
        return oddEvenHead[0];
    }

private:
    // Method helper
    std::vector<ListNode*> segregateUsingRecursion(ListNode* headNode, ListNode*& oddLast) {
        // Edge case: When the list is empty.
        if(!headNode)
            return {nullptr, nullptr};

        // Recursively move and set the odd and even grouped list. 
        std::vector<ListNode*> oddEven = segregateUsingRecursion(headNode->next, oddLast);

        // If the value of the current node is odd.
        if(headNode->val % 2) {
            // Set the last node of the odd-grouped list.
            if(!oddLast) oddLast = headNode;
            // link the current node to the node of the odd-grouped list
            headNode->next = oddEven[0];
            // Update it as the head node of the odd-grouped list.
            oddEven[0] = headNode;
        }
        // Else when the value of the current node is even.
        else {
            // link the current node to the node of the even-grouped list
            headNode->next = oddEven[1];
            // Update it as the head node of the even-grouped list.
            oddEven[1] = headNode;
        }

        // Return the "buffer" of updated nodes of both the groups.
        return oddEven;
    }
};
// Note: If constraints are greater than 10^4, then this solution can lead to "segmentation-fault" due to "stack-overflow".

// #4 Solution class
class Solution_V4 {
public:    
    // Method to segregate odd and even nodes, using constant auxiliary space - O(N) & O(1) : Where N is the size of the list.
    ListNode* segregateOddEven(ListNode* headNode) {
        // Edge case: When the list is empty or single noded.
        if(!headNode || !headNode->next)
            return headNode;

        ListNode* oddHead     = nullptr; // Tracks the head node of the odd-grouped list.
        ListNode* evenHead    = nullptr; // Tracks the head node of the even-grouped list.
        ListNode* oddCurrent  = nullptr; // Tracks the nodes of the odd-grouped list.
        ListNode* evenCurrent = nullptr; // Tracks the nodes of the even-grouped list.

        while(headNode) {
            // If the value of the current node is odd.
            if(headNode->val % 2) {
                // If its the first node of the odd-grouped list, then set the head node of it. 
                if(!oddHead)
                    oddHead = headNode, oddCurrent = oddHead;
                // Else then set the current node in the odd-grouped list. 
                else
                    oddCurrent->next = headNode, oddCurrent = oddCurrent->next;
            }
            // Else when the value of the current node is even.
            else {
                // If its the first node of the even-grouped list, then set the head node of it. 
                if(!evenHead)
                    evenHead = headNode, evenCurrent = evenHead;
                // Else then set the current node in the even-grouped list. 
                else
                    evenCurrent->next = headNode, evenCurrent = evenCurrent->next;
            }
            headNode = headNode->next;
        }

        // If the odd-grouped list is not empty, then link the last node of it to the head of the even-grouped list.
        (oddHead) ? oddCurrent->next = evenHead : 0;

        // If the even-grouped list is not empty, then set the last node of it.
        (evenHead) ? evenCurrent->next = nullptr : 0;

        // If the odd-grouped list is not empty then return the head node of it, else return the head node of the even-grouped list.
        return (oddHead) ? oddHead : evenHead;
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userWantsOperation = true;

    while(userWantsOperation) {
        // Handles console clearance for both "windows" and "linux" user
        system("cls || clear");

        // Input the size of the list
        int size;
        std::cout<<"Enter the number of nodes for the list: ";
        std::cin>>size;

        // Check the given size is valid or not
        if(size <= 0) {
            std::cout<<"Enter a valid size, application expects a postive integer!";
            return 0;
        }

        ListNode* headNode = nullptr; // Tracks the head node of the list
        ListNode* tailNode = nullptr; // Tracks the last node of the list

        // Input the nodes value of the list
        for(int node=1; node<=size; ++node) {
            int key;
            std::cout<<"Enter the value of the "<<node<<"th node: ";
            std::cin>>key;
            headNode->insertNode(headNode, tailNode, key);
        }

        // Print call
        std::cout<<"\nList before segregation: ";
        headNode->printList(headNode);

        // Segregation call
        std::cout<<"List after segregation: ";
        Solution_V4 solution;
        headNode = solution.segregateOddEven(headNode);

        // Print call
        headNode->printList(headNode);

        // Deletion call (delete the head node and recursively the entire list)
        delete headNode; headNode = nullptr;

        // Input section to handle the flow of iterations of the application
        char userChoise;
        std::cout<<"\nPress \'R\' to restart the application, else it will exit automatically: ";
        std::cin>>userChoise;
        userWantsOperation = (userChoise == 'R') ? true : false ;

    }   

    return 0;
}
/*
    Topics: Linked List | Recursion
    Links: https://leetcode.com/discuss/interview-question/668896/Google-or-Phone-or-Group-odd-valued-and-even-valued-nodes-in-Linked-List
           https://practice.geeksforgeeks.org/problems/segregate-even-and-odd-nodes-in-a-linked-list5035/1
*/
