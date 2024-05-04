// Program to segregate all the nodes with odd position together followed by the nodes with even position and then return the reordered list (Note that the relative order inside both the even and odd groups should remain as it) ~ coded by Hiren
#include <iostream>
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

    // Method to insert a node in the list, using constant auxiliary space - O(1) & O(1)
    void insertNode(ListNode*& headNode, ListNode*& tailNode, int key) {
        ListNode* newNode = new ListNode(key);
        if(!headNode)
            headNode = newNode, tailNode = newNode;
        else    
            tailNode->next = newNode, tailNode = tailNode->next;
    } 

    // Method to delete the list, using constant auxiliary space - O(N) & O(1)
    void deleteList(ListNode*& headNode) {
        while(headNode) {
            ListNode* nextNode = headNode->next;
            delete headNode; 
            headNode = nullptr;
            headNode = nextNode;
        }
    }

    // Method to print the list, using constant auxiliary space - O(N) & O(1)
    void printList(ListNode* headNode) {
        std::cout<<"[";
        while(headNode) {
            (headNode->next) ? std::cout<<headNode->val<<", " : std::cout<<headNode->val;
            headNode = headNode->next;
        }
        std::cout<<"]";
    }
};

// #1 Solution class:
class Solution_A {
public:
    // Method to segregate all the nodes with odd position together followed by the nodes with even position, using buffer - O(N) & O(N)
    ListNode* oddEvenList(ListNode* headNode) {
        // Edge case: When the list is empty or single noded
        if(!headNode || !headNode->next)
            return headNode;

        std::vector<ListNode*> oddNodes;  // Stores the nodes of odd group
        std::vector<ListNode*> evenNodes; // Stores the nodes of even group        

        // Tracks any position is even or not
        bool isEvenPosition = false;        

        // Iterate the list
        while(headNode) {
            // Tracks the next node of the current node
            ListNode* nextNode = headNode->next; 
            headNode->next = nullptr;
            // If it's the even position then store the current node to the even group else store it to the odd group
            (isEvenPosition) ? evenNodes.push_back(headNode) : oddNodes.push_back(headNode);
            // Toggle the position to odd if it's even or to even if it's odd
            isEvenPosition = !isEvenPosition;
            // Move to the next node
            headNode = nextNode;
        }

        int size1 = oddNodes.size(), size2 = evenNodes.size();

        // Iterate and link all the nodes of the odd group
        for(int node = 1; node < size1; ++node) {
            oddNodes[node - 1]->next = oddNodes[node];
        }

        // Iterate and link all the nodes of the even group
        for(int node = 1; node < size2; ++node) {
            evenNodes[node - 1]->next = evenNodes[node];
        }

        // Link the last node of the odd group with the head node of the even group
        oddNodes[size1 - 1]->next = evenNodes[0];

        // Return the head node of the odd group
        return oddNodes[0];
    }
};

// #2 Solution class:
class Solution_B {
public:
    // Method to segregate all the nodes with odd position together followed by the nodes with even position, using constant auxiliary space - O(N) & O(1)
    ListNode* oddEvenList(ListNode* headNode) {
        // Edge case: When the list is empty or single noded
        if(!headNode || !headNode->next)
            return headNode;

        ListNode* dummyOdd  = new ListNode(0); // Tracks the nodes of the odd group
        ListNode* dummyEven = new ListNode(0); // Tracks the nodes of the even group
        ListNode* currOdd   = dummyOdd;        // Tracks any node of the odd group
        ListNode* currEven  = dummyEven;       // Tracks any node of the even group

        // Tracks any position is even or not
        bool isEvenPosition = false;

        // Iterate the list
        while(headNode) {
            // Tracks the next node of the current node
            ListNode* nextNode = headNode->next;
            headNode->next = nullptr; 
            // If it's the even position then set the current node in the even group 
            if(isEvenPosition)
                currEven->next = headNode, currEven = currEven->next;
            // Else then set the current node in the odd group
            else
                currOdd->next = headNode, currOdd = currOdd->next;
            // Toggle the position to odd if it's even or to even if it's odd
            isEvenPosition = !isEvenPosition;
            // Move to the next node
            headNode = nextNode; 
        }

        ListNode* oddHead  = dummyOdd->next;  // Tracks the head node of the odd group
        ListNode* evenHead = dummyEven->next; // Tracks the head node of the even group
        
        // Delete the dummy nodes to avoid the memory leak issues
        delete dummyOdd; delete dummyEven; 
        
        // Link the last node of the odd group with the head node of the even group
        currOdd->next = evenHead;

        // Return the head node of the odd group
        return oddHead; 
    }
};

// #3 Solution class:
class Solution_C {
public:
    // Method to segregate all the nodes with odd position together followed by the nodes with even position, using constant auxiliary space - O(N) & O(1)
    ListNode* oddEvenList(ListNode* headNode) {
        // Edge case: When the list is empty or single noded
        if(!headNode || !headNode->next)
            return headNode;

        ListNode *oddHead = nullptr, *currOdd = nullptr;   // Tracks the head node and the nodes of the odd group    
        ListNode *evenHead = nullptr, *currEven = nullptr; // Tracks the head node and the nodes of the even group
        
        // Tracks any position is even or not
        bool isEvenPosition = false;

        // Iterate the list
        while(headNode) {
            // Tracks the next node of the current node
            ListNode* nextNode = headNode->next;
            // If it's the even position then set the current node in the even group 
            if(isEvenPosition)
                updateLinks(evenHead, currEven, headNode);
            // Else then set the current node in the odd group
            else
                updateLinks(oddHead, currOdd, headNode);
            // Toggle the position to odd if it's even or to even if it's odd
            isEvenPosition = !isEvenPosition; 
            // Move to the next node
            headNode = nextNode; 
        }

        // Link the last node of the odd group with the head node of the even group
        currOdd->next = evenHead;

        // Return the head node of the odd group
        return oddHead;
    }

private:
    // Method to set the given node in the result list, using constant auxiliary space - O(1) & O(1)
    void updateLinks(ListNode*& resHead, ListNode*& resCurrent, ListNode* givenNode) {
        // If the result list is empty then set the given node as the head node of it
        if(!resHead)
            resHead = givenNode, resCurrent = givenNode;
        // Else then set it as the last node of the result list
        else
            resCurrent->next = givenNode, resCurrent = resCurrent->next;
        resCurrent->next = nullptr;
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userNeedOperation = true;

    while(userNeedOperation) {
        // Controls console clearance for both "windows" and "linux" user
        system("cls || clear");

        std::cout<<"The application only accepts non-decimal numeric type value, unless specified!\n\n";

        // Input the length of the list
        int length;
        std::cout<<"Enter the total number of nodes of the list: ";
        std::cin>>length;

        // Check the given length is lying within the problem constraints or not
        if(length <= -1 || length >= 1e4 + 1) {
            std::cout<<"You must enter a length which lies between 0 and 10^4!";
        }
        else {
            ListNode* headNode = nullptr; // Tracks the head node of the list
            ListNode* tailNode = nullptr; // Tracks the last node of the list

            // Input the value of the nodes
            for(int node = 1; node <= length;) {
                int key;
                std::cout<<"Enter value of the "<<node<<"th node: ";
                std::cin>>key;
                // Check the given value is lying within the problem constraints or not
                if(key <= -1e6 - 1 || key >= 1e6 + 1) {
                    std::cout<<"You must enter a value which lies between -10^6 and 10^6!\n";
                }
                else {
                    headNode->insertNode(headNode, tailNode, key);
                    ++node;
                }
            }

            // Print call
            std::cout<<"\nList before segregation: ";
            headNode->printList(headNode);

            // Segregation call
            Solution_B solution;
            headNode = solution.oddEvenList(headNode);

            // Print call
            std::cout<<"\nList after segregation: ";
            headNode->printList(headNode);

            // Deletion call
            headNode->deleteList(headNode);
        }

        // Input section to control the flow of iterations of the appliacation
        char userChoice;
        std::cout<<"\n\nPress \'R\' to restart the application, else it will exit: ";
        std::cin>>userChoice;
        userNeedOperation = (userChoice == 'R');
    }

    return 0;
}
/*
    Topics: Linked List
    Link: https://leetcode.com/problems/odd-even-linked-list/description/
*/
