// Program to build the result list by removing the list1's nodes from the ath node to the bth node, and put list2 in their place and then return the head node of the result list ~ coded by Hiren
#include <iostream>
#include <cstdlib>

// List template
class ListNode {
public:
    int val;
    ListNode* next;

    // Init constructor
    ListNode(int val, ListNode* next = nullptr)
    :
    val(val), next(next) {}

    // Method to create a list - O(N) & O(1)
    std::pair<ListNode*, int> createList(int listNumber) {
        // Input the length of the list
        int length;
        std::cout<<"Enter the total number of nodes of list"<<listNumber<<": ";
        std::cin>>length; 

        // Check the given length is lying within the problem constraints or not
        if(length <= 0 || length >= 1e4 + 1) {
            std::cout<<"You must enter a length which lies between 1 and 10000!\n";
            return {nullptr, 0};
        }

        ListNode* headNode = nullptr; // Tracks the head node of the list
        ListNode* tailNode = nullptr; // Tracks the last node of the list

        // Input the nodes value
        for(int node = 0; node < length; ++node) {
            int key;
            std::cout<<"Enter value of the "<<node<<"th node: ";
            std::cin>>key;   
            headNode->insertNode(headNode, tailNode, key);
        }

        // Return the head node along with the length of the list
        return {headNode, length};
    }

    // Method to insert a node in the list - O(1) & O(1)
    void insertNode(ListNode*& headNode, ListNode*& tailNode, int key) {
        ListNode* newNode = new ListNode(key);
        if(!headNode)
            headNode = newNode, tailNode = newNode;
        else
            tailNode->next = newNode, tailNode = tailNode->next;
        tailNode->next = nullptr;
    }

    // Method to delete the list - O(N) & O(1)
    void deleteList(ListNode*& headNode) {
        while(headNode) {
            ListNode* nextNode = headNode->next;
            delete headNode;
            headNode = nullptr;
            headNode = nextNode;
        }
    }

    // Method to print the list - O(N) & O(1)
    void printList(ListNode* headNode) {
        std::cout<<"[";
        while(headNode) {
            std::cout<<headNode->val;
            (headNode->next) ? std::cout<<", " : std::cout<<"";
            headNode = headNode->next;
        }
        std::cout<<"]\n";
    }
};

// #1 Solution class:
class Solution_A {
public:
    // Method to build the result list by performing the specified instructions, using constant auxiliary space - O(N+M) & O(1) : Where N let be the length of "list1" and M of "list2"
    ListNode* mergeInBetween(ListNode* headNode1, int a, int b, ListNode* headNode2) {
        ListNode* resHead    = nullptr; // Tracks the head node of the result list
        ListNode* resCurrent = nullptr; // Tracks any node of the result list
        
        int index = 0;

        // Iterate till the previous node of the ath node of the "list1" and set the nodes in the result list
        while(headNode1 && index < a) {
            ListNode* nextNode = headNode1->next;
            updateLinks(resHead, resCurrent, headNode1);
            headNode1 = nextNode; index++;
        }

        // Iterate the "list2" and set the nodes in the result list
        while(headNode2) {
            ListNode* nextNode = headNode2->next;
            updateLinks(resHead, resCurrent, headNode2);
            headNode2 = nextNode;
        }

        // Iterate from the ath node of the "list1" and delete the nodes lying between ath and the bth node and then set the rest of the nodes in the result list
        while(headNode1) {
            ListNode* nextNode = headNode1->next;
            if(index > b)
                updateLinks(resHead, resCurrent, headNode1);
            else    
                delete headNode1;
            headNode1 = nextNode; index++;
        }

        // Return the head node of the result list
        return resHead;
    }

private:
    // Method to update and set the nodes of the result list - O(1) & O(1)
    void updateLinks(ListNode*& resHead, ListNode*& resCurrent, ListNode* givenNode) {
        if(!resHead)
            resHead = givenNode, resCurrent = givenNode;
        else
            resCurrent->next = givenNode, resCurrent = resCurrent->next;
        resCurrent->next = nullptr;
    }
};

// #2 Solution class:
class Solution_B {
public:
    // Method to build the result list by performing the specified instructions, using constant auxiliary space - O(N+M) & O(1) : Where N let be the length of "list1" and M of "list2"
    ListNode* mergeInBetween(ListNode* headNode1, int a, int b, ListNode* headNode2) {
        ListNode* currNode1  = headNode1; // Tracks the nodes of the "list1"
        ListNode* prevNode_a = nullptr;   // Tracks the previous node of the ath node of the "list1"
        ListNode* nextNode_b = nullptr;   // Tracks the next node of the bth node of the "list1"

        int index = 0;

        // Iterate the "list1" and find the previous node of the ath node and the next node of the bth node and also delete the nodes lying between ath and the bth node 
        while(currNode1) {
            ListNode* nextNode = currNode1->next;
            if(index == a-1)
                prevNode_a = currNode1;
            if(index == b+1)
                nextNode_b = currNode1;
            if(index >= a && index <= b)
                delete currNode1;
            currNode1 = nextNode; index++;
        }

        // If the previous node of the ath node exists then link it with the head node of the "list2"
        if(prevNode_a)
            prevNode_a->next = headNode2;

        // Tracks the last node of the "list2"
        ListNode* nodeLast2 = headNode2;

        // If the next node of the bth node exists then find the last node of the "list2" and then link the last node with the next node of the bth node
        if(nextNode_b) {
            while(nodeLast2 && nodeLast2->next) nodeLast2 = nodeLast2->next;
            nodeLast2->next = nextNode_b;
        }

        // If the "list1" is empty then directly return the head node of the "list2", else return the head node of the "list1"
        return (!prevNode_a) ? headNode2 : headNode1;
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userNeedOperation = true;

    while(userNeedOperation) {
        // Controls console clearance for both "windows" and "linux" user
        system("cls || clear");

        std::cout<<"Note: The application only accepts non-decimal numeric type value, unless specified!\n\n";

        // Create the lists and store the head node along with the length of them
        ListNode* pointer = nullptr;
        auto [headNode1, length1] = pointer->createList(1); std::cout<<"\n";
        auto [headNode2, length2] = pointer->createList(2);
        
        // If the "list2" length is a positive integer then execute the statements
        if(length2 >= 1) {
            // Input the value of 'a' and 'b'
            int a, b;
            std::cout<<"\nEnter the value of \'a\' and \'b\': ";
            std::cin>>a>>b;

            // Check the given values are lying within the problem constraints or not
            if(a <= -1 || b >= length1 || a > b) {
                if(length1 >= 1) 
                    std::cout<<"You must enter the value of \'a\' and \'b\' which lies between [0 : "<<length1 - 1<<"] or can say [0 : list1length - 1]\n";
                if(a > b)
                    std::cout<<"Note: \'a\' must be lesser than or equal to \'b\'!\n"; 
            }

            // If 'a' is lesser than or equal to 'b' then execute the statements
            if(a <= b) {
                // Print call
                std::cout<<"\nList1: ";
                headNode1->printList(headNode1);

                // Print call
                std::cout<<"List2: ";
                headNode2->printList(headNode2);

                // Merge call
                Solution_B solution;
                ListNode* resHead = solution.mergeInBetween(headNode1, a, b, headNode2);

                // Print call
                std::cout<<"Result list: ";
                resHead->printList(resHead);

                // Deletion call
                resHead->deleteList(resHead);
            }
        }

        // Input section to control the flow of iterations of the application
        char userChoice;
        std::cout<<"\nPress \'R\' to restart the application, else it will exit: ";
        std::cin>>userChoice;
        userNeedOperation = (userChoice == 'R');
    }

    return 0;
}
/*
    Topics: Linked List
    Link: https://leetcode.com/problems/merge-in-between-linked-lists/description/
*/
