// Program to partition the list such that all the nodes less than x come before nodes greater than or equal to x while maintaing the relative order ~ coded by Hiren
#include <iostream>
#include <vector>

// List template
class ListNode {
public:
    int data;
    ListNode* next;

    // Initialize constructor
    ListNode(int data, ListNode* next = nullptr) {
        this->data = data;
        this->next = next;
    }

    // Method to insert a node in the list - O(1) & O(1)
    void insertNode(ListNode*& headNode, ListNode*& tailNode, int key) {
        ListNode* newNode = new ListNode(key);
        if(!headNode)
            headNode = newNode, tailNode = newNode;
        else
            tailNode->next = newNode, tailNode = tailNode->next;
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
            std::cout<<headNode->data<<' ';
            headNode = headNode->next;
        }
        std::cout<<'\n';
    }
};

// #1 Solution class
class Solution_A {
public:
    // Method to partition the list, using dynamic node creation - O(N) & O(N)
    ListNode* partitionList(ListNode* headNode, int x) {
        // Edge case: When the list is empty or single noded
        if(!headNode || !headNode->next)
            return headNode;

        ListNode* dummyLesser  = new ListNode(-1); // Tracks the group "having nodes value lesser than x"
        ListNode* dummyGreater = new ListNode(-1); // Tracks the group "having nodes value greater than or equal to x"
        ListNode* currLesser   = dummyLesser ;     // Tracks the nodes of the "lesser's list" 
        ListNode* currGreater  = dummyGreater;     // Tracks the nodes of the "greater's list"

        // Iterate the list
        while(headNode) {
            // Create a new node of value equal to the current node
            ListNode* newNode = new ListNode(headNode->data);
            
            if(headNode->data < x)
                // If the current node value is "lesser than x", then set the new node in the "lesser's list"
                currLesser->next = newNode, currLesser = currLesser->next;
            else    
                // Else when the current node value is "greater than or equal to x", then set the new node in the "greater's list"
                currGreater->next = newNode, currGreater = currGreater->next;

            // Move to the next node in the original list
            headNode = headNode->next;
        }

        ListNode* lesserHead  = dummyLesser->next ; // Tracks the head node of the "lesser's list"
        ListNode* greaterHead = dummyGreater->next; // Tracks the head node of the "greater's list"

        // Delete to avoid the "memory leak issues"
        delete dummyLesser ; dummyLesser  = nullptr; 
        delete dummyGreater; dummyGreater = nullptr;

        // If the head node of "lesser's list" does not exist, then return the head node of the "greater's list"
        if(!lesserHead)
            return greaterHead;

        // Link the last node of "lesser's list" with the head node of the "greater's list"
        currLesser->next = greaterHead;

        // Return the head node of the "lesser's list"
        return lesserHead;
    }
};
// Note: The solution can lead to "memory leak issues" as the new list is created dynamically but never freed

// #2 Solution class
class Solution_B {
public:
    // Method to partition the list, using buffer only - O(N) & O(N)
    ListNode* partitionList(ListNode* headNode, int x) {
        // Edge case: When the list is empty or single noded
        if(!headNode || !headNode->next)
            return headNode;

        // Stores the nodes of the list
        std::vector<ListNode*> buffer;

        pushNodes(headNode, x, true, buffer);  // Store all the nodes having value "lesser than x"
        pushNodes(headNode, x, false, buffer); // Store all the nodes having value "greater than or equal to x" 

        int size = buffer.size();

        // Iterate and link all the nodes
        for(int node=0; node<size-1; ++node) {
            buffer[node]->next   = buffer[node+1];
        }

        // Set the last node of the list
        buffer[size-1]->next = nullptr;

        // Return the head node of the list
        return buffer[0];
    }

private:
    // Method to store the nodes of the list - O(N) & O(1)
    void pushNodes(ListNode* headNode, int x, bool pushLesser, std::vector<ListNode*>& buffer) {
        // Iterate the list
        while(headNode) {
            // When to push the nodes with "value lesser than x"
            if(pushLesser && headNode->data < x)
                buffer.push_back(headNode);

            // Else when to push the nodes with "value greater than or equal to x" 
            else if(!pushLesser && headNode->data >= x)
                buffer.push_back(headNode);

            // Move to the next node in the list
            headNode = headNode->next;
        }
    }
};

// #3 Solution class
class Solution_C {
public:
    // Method to partition the list, using recursion only - O(N) & O(N)
    ListNode* partitionList(ListNode* headNode, int x) {
        // Edge case: When the list is empty or single noded
        if(!headNode || !headNode->next)
            return headNode;    

        // Recurse to the list and partition it into two different lists 
        partitionInRec(headNode, x);

        ListNode* lesserHead  = dummyLesser->next ; // Tracks the head node of the "lesser's list"
        ListNode* greaterHead = dummyGreater->next; // Tracks the head node of the "greater's list"

        // Delete to avoid the memory leak issuses
        delete dummyLesser ; dummyLesser  = nullptr;  
        delete dummyGreater; dummyGreater = nullptr; 

        // If the "lesser's list" is empty, then return the head node of the "greater's list"
        if(!lesserHead)
            return greaterHead;

        // Link the last node of the "lesser's list" with the head node of the "greater's list"
        currLesser->next = greaterHead;

        // Return the head node of the "lesser's list"
        return lesserHead;
    }

private:
    ListNode* dummyLesser  = new ListNode(-1); // Tracks the group "having nodes value lesser than x"
    ListNode* dummyGreater = new ListNode(-1); // Tracks the group "having nodes value greater than or equal to x"
    ListNode* currLesser   = dummyLesser ;     // Tracks the nodes of the "lesser's list" 
    ListNode* currGreater  = dummyGreater;     // Tracks the nodes of the "greater's list"

    // Method to partition the list into two different lists - O(N) & O(N)
    void partitionInRec(ListNode* headNode, int x) {
        // When the current node exist
        if(headNode) {
            // Tracks the next node of the current node
            ListNode* nextNode = headNode->next;

            // If the current node value is "lesser than x", then set the node in the "lesser's list"
            if(headNode->data < x) {
                currLesser->next = headNode, currLesser = currLesser->next;
                currLesser->next = nullptr;
            }
            // Else when the current node value is "greater than or equal to x", then set the node in the "greater's list"
            else {
                currGreater->next = headNode, currGreater = currGreater->next;
                currGreater->next = nullptr;
            }

            // Recurse to the next node and perform the same task
            partitionInRec(nextNode, x);
        }
    }
};

// #4 Solution class
class Solution_D {
public:
    // Method to partition the list, using constant auxiliary space - O(N) & O(1)
    ListNode* partitionList(ListNode* headNode, int x) {
        // Edge case: When the list is empty or single noded
        if(!headNode || !headNode->next)
            return headNode;
        
        ListNode* lesserHead  = nullptr, *lesserCurrent  = nullptr; // Tracks the "head node" and "any node" of the "lesser's list"
        ListNode* greaterHead = nullptr, *greaterCurrent = nullptr; // Tracks the "head node" and "any node" of the "greater's list"

        // Iterate the list
        while(headNode) {
            // Tracks the next node of the current node
            ListNode* nextNode = headNode->next;

            if(headNode->data < x)
                // If the current node value is "lesser than x", then set the node in the "lesser's list"
                updateLinks(lesserHead, lesserCurrent, headNode);
            else 
                // Else when the current node value is "greater than or equal to x", then set the node in the "greater's list"
                updateLinks(greaterHead, greaterCurrent, headNode);
            
            // Move to the next node in the list
            headNode = nextNode;
        }

        // If the "lesser's list" is not empty, then link the last node of the "lesser's list" with the head node of the "greater's list"
        if(lesserHead)
            lesserCurrent->next = greaterHead;

        // If the "lesser's list" is not empty, then return the head node of it, else return the head node of the "greater's list"
        return (lesserHead) ? lesserHead : greaterHead ;
    }

private:
    // Method to update and set the links of the given node in the result list - O(1) & O(1)
    void updateLinks(ListNode*& resHead, ListNode*& resCurrent, ListNode*& givenNode) {
        if(!resHead)
            // If the "result list" is empty then set the head node of it
            resHead = givenNode, resCurrent = givenNode;
        else
            // Else then set the current node in the "result list"
            resCurrent->next = givenNode, resCurrent = resCurrent->next;

        // Set the current node as the last node of the "result list"
        resCurrent->next = nullptr; 
    }    
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool canPerformOp = true;

    while(canPerformOp) {
        // Controls console clearance for both "windows" and "linux" user
        system("cls || clear");

        // Input the size of the list
        int size;
        std::cout<<"Enter the size of the list: ";
        std::cin>>size;

        // Check the given size is valid or not
        if(size <= 0) {
            std::cout<<"Enter a valid size, application expects a positive integer!";
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

        // Input the value of x
        int x;
        std::cout<<"\nEnter the value of x: ";
        std::cin>>x;

        // Print call
        std::cout<<"\nList before partition: ";
        headNode->printList(headNode);

        // Partition call
        Solution_D solution;
        headNode = solution.partitionList(headNode, x);

        // Print call
        std::cout<<"List after partition: ";
        headNode->printList(headNode);

        // Deletion call
        headNode->deleteList(headNode);

        // Input section to control the flow of iterations of the application
        char userChoise;
        std::cout<<"\nPress \'R\' to restart the application, else it will exit automatically: ";
        std::cin>>userChoise;
        canPerformOp = (userChoise == 'R' ? true : false);        
    }

    return 0;
}
/*
    Topics: Linked List | Two Pointers
    Link: https://leetcode.com/problems/partition-list/
*/
