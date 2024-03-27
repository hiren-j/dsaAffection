#include <unordered_map>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <stack>

// List template
class ListNode {
public:
    int data;
    ListNode* next;

    // Init constructor
    ListNode(int data, ListNode* next = nullptr)
    :
    data(data), next(next) {}

    // Method to insert a node in the list, using constant auxiliary space - O(1) & O(1)
    void insertNode(ListNode*& headNode, ListNode*& tailNode, int key) {
        ListNode* newNode = new ListNode(key);
        if(!headNode)
            headNode = newNode, tailNode = newNode;
        else    
            tailNode->next = newNode, tailNode = tailNode->next;
        tailNode->next = nullptr;
    }

    // Method to print the list - O(N) & O(1)
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
            std::cout<<headNode->data;
            if(headNode->next) std::cout<<", ";
            headNode = headNode->next;
        }
        std::cout<<"]";
    }
};

// Solution class:
class Solution {
public:
    // #1 Method to find the maximum twin sum of the list, using map as buffer - O(N) & O(N)
    int maximumTwinSum_V1(ListNode* headNode) {
        // Tracks the nodes of the list
        ListNode* currNode = headNode;
        
        std::unordered_map<int, int> mp; // Maps the indeces of the nodes
        int listLength = 0;              // Stores the length of the list

        // Iterate and map the index of each node
        while(currNode) {
            mp[listLength++] = currNode->data;
            currNode = currNode->next;
        }

        int maxTwinSum = 0;       // Stores the "maximum twin sum / result value"    
        int index = 0;            // Tracks the index of any node                    
        int mid = listLength / 2; // Tracks the "mid index / mid point" of the list 

        // Iterate till the mid point and update the result value by the maximum value each time 
        while(headNode && index < mid) {
            int currTwinSum = headNode->data + mp[listLength - 1 - index];
            maxTwinSum = std::max(maxTwinSum, currTwinSum);
            headNode = headNode->next;
            index++;
        }

        // Return the result value
        return maxTwinSum;
    }

    // #2 Method to find the maximum twin sum of the list, using vector as buffer - O(N) & O(N)
    int maximumTwinSum_V2(ListNode* headNode) {
        // Stores the nodes value
        std::vector<int> buffer;

        // Iterate and store the value of each node to the buffer
        while(headNode) {
            buffer.push_back(headNode->data);
            headNode = headNode->next;
        }

        int maxTwinSum = 0;             // Stores the "maximum twin sum / result value"  
        int listLength = buffer.size(); // Stores the length of the list
        int mid = listLength / 2;       // Tracks the "mid index / mid point" of the list 

        // Iterate till the mid point and update the result value by the maximum value each time 
        for(int node = 0; node < mid; ++node) {
            maxTwinSum = std::max(maxTwinSum, buffer[node] + buffer[listLength - 1 - node]);
        }

        // Return the result value
        return maxTwinSum;
    } 

    // #3 Method to find the maximum twin sum of the list, using stack as buffer - O(N) & O(N)
    int maximumTwinSum_V3(ListNode* headNode) {
        std::stack<int> s;             // Stores the values of the list in reverse order
        ListNode* currNode = headNode; // Tracks the nodes of the list

        while(currNode) {
            s.push(currNode->data);
            currNode = currNode->next;
        }

        int maxTwinSum = 0;     // Stores the "maximum twin sum / result value"
        int mid = s.size() / 2; // Tracks the "mid index / mid point" of the list 

        // Iterate till the mid point and update the result value by the maximum value each time 
        while(s.size() > mid) {
            int currSum = headNode->data + s.top(); 
            s.pop();
            maxTwinSum = std::max(maxTwinSum, currSum);
            headNode = headNode->next;
        }

        // Return the result value
        return maxTwinSum;
    }

    // #4 Method to find the maximum twin sum of the list, using constant auxiliary space - O(N) & O(1)
    int maximumTwinSum_V4(ListNode* headNode) {
        ListNode* prevMiddleNode   = nullptr;  // Tracks the previous node of the middle node of the list
        ListNode* middleNode       = headNode; // Tracks the middle node of the list
        ListNode* secondMostNode   = headNode; // Tracks the second most node of any node

        // Iterate and find the middle node along with the previous node of it 
        while(secondMostNode && secondMostNode->next) {
            prevMiddleNode   = middleNode;
            middleNode       = middleNode->next;
            secondMostNode   = secondMostNode->next->next;
        }

        // Seperate the first half of the list
        prevMiddleNode->next = nullptr;

        // Iterate and reverse the second half of the list
        while(middleNode) {
            ListNode* nextNode = middleNode->next;
            middleNode->next   = prevMiddleNode;
            prevMiddleNode     = middleNode;
            middleNode         = nextNode;
        }
        
        // Stores the "maximum twin sum / result value" 
        int maxTwinSum = 0;

        // Iterate both the halves together and update the result value by the maximum value each time 
        while(headNode) {
            maxTwinSum     = std::max(maxTwinSum, headNode->data + prevMiddleNode->data);
            headNode       = headNode->next; 
            prevMiddleNode = prevMiddleNode->next;
        }
        
        // Return the result value
        return maxTwinSum;
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userWantsOperation = true;

    while(userWantsOperation) {
        // Controls console clearance for both "windows" and "linux" user
        system("cls || clear");
        
        std::cout<<"The application only accepts non-decimal numeric type value, unless specified!\n\n";

        // Input the length of the list
        int length;
        std::cout<<"Enter the total number of nodes: ";
        std::cin>>length;

        // Check the given length is lying within the problem constraints or not
        if(length <= 1 || length >= 100001) {
            std::cout<<"Enter a length which lies between 2 and 10^5!";
        }
        else if(length % 2 != 0) {
            std::cout<<"Length must be an even value!";
        }
        else {
            ListNode* headNode = nullptr; // Tracks the head node of the list
            ListNode* tailNode = nullptr; // Tracks the last node of the list

            // Input the value of the nodes
            for(int node = 1; node <= length;) {
                int key;
                std::cout<<"Enter value of the "<<node<<"th node: ";
                std::cin>>key;
                if(key <= 0 || key >= 100001) {
                    std::cout<<"You must enter a value which lies between 1 and 10^5!\n";
                }
                else {
                    headNode->insertNode(headNode, tailNode, key);
                    node++;
                }
            }

            // Print call
            std::cout<<"\nList: ";
            headNode->printList(headNode);

            // Call to find the maximum twin sum of the list
            Solution solution;
            int maxTwinSum = solution.maximumTwinSum_V4(headNode);
            std::cout<<"\nThe maximum twin sum of the linked list is: "<<maxTwinSum;

            // Deletion call
            headNode->deleteList(headNode);
        }

        // Input section to control the flow of iterations of the application
        char userChoice;
        std::cout<<"\n\nPress \'R\' to restart the application, else it will exit: ";
        std::cin>>userChoice;
        userWantsOperation = (userChoice == 'R');
    }

    return 0;
}
/*
    Topics: Linked List | Two Pointers | Stack
    Link: https://leetcode.com/problems/maximum-twin-sum-of-a-linked-list/
*/
