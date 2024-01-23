// Program to insert a node into a sorted circular linked list ~ coded by Hiren
#include <iostream>
#include <vector>
#include <algorithm>

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

// #1 Solution class:
class Solution_V1 {
    // Method helper
    static bool comparator(ListNode* node1, ListNode* node2) {
        return node1->val < node2->val;
    }

public:
    // Method to insert the node into the list, using sorting with buffer - O(NLogN) & O(N) : Where N is the size of the list.
    ListNode* sortedInsertToList(ListNode* headNode, int key) {
        // Edge case: When the list is empty.
        if(!headNode) {
            ListNode* newHead = new ListNode(key, nullptr);
            newHead->next = newHead;
            return newHead;
        }

        // Stores the nodes of the list.
        std::vector<ListNode*> nodes;
        nodes.push_back(new ListNode(key, nullptr));

        // Tracks the nodes of the list.
        ListNode* currNode = headNode;

        // Iterate and store all the nodes to the buffer.
        while(currNode->next != headNode) {
            nodes.push_back(currNode);
            currNode = currNode->next;
        }
        // Store the last node of the list to the buffer.
        nodes.push_back(currNode);

        // Sort all the nodes based on their values.
        std::sort(begin(nodes), end(nodes), comparator);

        // Iterate and link all the nodes.
        for(int i=1; i<nodes.size(); i++) {
            nodes[i-1]->next = nodes[i];
        }
        // Lastly, set the circular point of the list.
        nodes[nodes.size()-1]->next = nodes[0];

        // Return the head node of the list.
        return nodes[0];
    }
};

// #2 Solution class:
class Solution_V2 {
public:
    // Method to insert the node into the list, using buffer only - O(N) & O(N) : Where N is the size of the list.
    ListNode* sortedInsertToList(ListNode* headNode, int key) {
        // Edge case: When the list is empty.
        if(!headNode) {
            ListNode* newHead = new ListNode(key, nullptr);
            newHead->next = newHead;
            return newHead;
        }

        std::vector<ListNode*> nodes;  // Stores the nodes of the list in sorted order.
        ListNode* currNode = headNode; // Tracks the nodes of the list.
        bool keyIsInserted = false;    // Tracks the node with value "key" is inserted or not.

        while(currNode->next != headNode) {
            // If the node with value "key" is not inserted yet and has to be inserted before the current node.
            if(key <= currNode->val && !keyIsInserted) {  
                // Create it and store it to the buffer.
                nodes.push_back(new ListNode(key, nullptr));
                // Mark it inserted for the next time to avoid the duplicate creations.
                keyIsInserted = true; 
            }
            nodes.push_back(currNode); // Store the current node of the list to the buffer.
            currNode = currNode->next; // Move to the next node in the list.
        }

        // If the node with value "key" is not inserted yet and has to be inserted before the last node.
        if(key <= currNode->val && !keyIsInserted) {
            // Create it and store it to the buffer.
            nodes.push_back(new ListNode(key, nullptr));
            // Now, store the last node of the list to ensure the sorted order.
            nodes.push_back(currNode);
            // Mark the new node with value key as inserted for the next time to avoid the duplicate creations.
            keyIsInserted = true;
        }
        // If the node with value "key" is not inserted yet and has to be inserted after the last node.
        if(key >= currNode->val && !keyIsInserted) {
            // Create it and store it to the buffer.
            nodes.push_back(currNode);
            // Now, store the last node of the list to ensure the sorted order.
            nodes.push_back(new ListNode(key, nullptr));
            // Mark the new node with value key as inserted for the next time to avoid the duplicate creations.
            keyIsInserted = true;
        }
        // If the node with value "key" is inserted ever-before, then just store the last node to the buffer.
        if(keyIsInserted) {
            nodes.push_back(currNode);
        }

        // Iterate and link all the nodes.
        for(int i=1; i<nodes.size(); i++) {
            nodes[i-1]->next = nodes[i];
        }
        // Lastly, set the circular point of the list.
        nodes[nodes.size()-1]->next = nodes[0];

        // Return the head node of the list.
        return nodes[0];
    }
};

// #3 Solution class:
class Solution_V3 {
public:
    // Method to insert the node into the list, using constant auxiliary space - O(N) & O(1) : Where N is the size of the list.
    ListNode* sortedInsertToList(ListNode* headNode, int key) {
        // Edge case: When the list is empty.
        if(!headNode) {
            ListNode* newHead = new ListNode(key, nullptr);
            newHead->next = newHead;
            return newHead;
        }
        
        // Tracks the nodes of the list.
        ListNode* currNode = headNode;

        // Edge case: When the node with value "key" has to be inserted before the head node.
        if(key < headNode->val) {
            while(currNode->next != headNode) currNode = currNode->next;
            ListNode* tmp = headNode;
            headNode = new ListNode(key, tmp);
            currNode->next = headNode;
            return headNode;
        }
        
        // Tracks the previous node of any node in the list.
        ListNode* prevNode = nullptr; currNode = headNode;
        
        // Iterate and find the node with its previous node, in which the node with value "key" has to be inserted.
        while(currNode->next != headNode && key > currNode->val) {
            prevNode = currNode;
            currNode = currNode->next;
        }
        
        // If the current node is not the last node of the list, then insert the new node with value "key" before the current node.
        if(currNode->next != headNode) {
            prevNode->next = new ListNode(key, currNode);
        }
        // Else when the current node is the last node of the list, then insert the new node with value "key" after the current node.
        else {
            ListNode* tmp = currNode->next;
            currNode->next = new ListNode(key, tmp);
        }

        // Return the head node of the updated list.  
        return headNode;
    }
};

// Class to wrap all the common methods of the list:
class ListBasicMethods {
public:
    // Method to insert a node in the list - O(1) & O(1)
    void insertNode(ListNode*& headNode, ListNode*& tailNode, int val) {
        ListNode* newNode = new ListNode(val);

        if(!headNode)
            headNode = newNode, tailNode = newNode;
        else    
            tailNode->next = newNode, tailNode = tailNode->next;

        tailNode->next = headNode;
    }

    // Method to delete the list - O(N) & O(1)
    void deleteList(ListNode*& currNode) {
        if(currNode) {
            ListNode* headNode = currNode;
            currNode = currNode->next;
            while(currNode != headNode) {
                ListNode* nextNode = currNode->next;
                delete currNode;
                currNode = nextNode;
            }
            delete currNode; currNode = nullptr;            
        }
    }

    // Method to print the list - O(N) & O(1)
    void printList(ListNode* headNode) {
        if(headNode) {
            ListNode* currNode = headNode;
            while(currNode->next != headNode) {
                std::cout<<currNode->val<<' ';
                currNode = currNode->next;
            }
            std::cout<<currNode->val;
        }
        std::cout<<'\n';
    }
};

// Driver code
int main() {
    bool userWantsOperation = true;

    while(userWantsOperation) {
        system("cls || clear");
        int n;
        std::cout<<"Enter the number of nodes for the list: ";
        std::cin>>n;

        ListNode *headNode = nullptr, *tailNode = nullptr;
        ListBasicMethods basicMethods;

        // Input section for the nodes of the list.
        for(int node=1; node<=n; ++node) {
            int val;
            std::cout<<"Enter the value of the "<<node<<"the node: ";
            std::cin>>val;
            basicMethods.insertNode(headNode, tailNode, val);
        }

        // Input section for "key value"
        int key;
        std::cout<<"\nEnter the value which you want to insert in the list: ";    
        std::cin>>key;

        // Print call
        std::cout<<"List before node insertion: ";
        basicMethods.printList(headNode);

        // Insertion call
        Solution_V3 obj;
        headNode = obj.sortedInsertToList(headNode, key);

        // Print call
        std::cout<<"List after node insertion: ";
        basicMethods.printList(headNode);

        // Deletion call
        basicMethods.deleteList(headNode);

        // Input section to handle the flow of iterations of the application.
        char userChoise;
        std::cout<<"\nPress \'Y\' if you want to perform the same operation on another \"circular linked list\": ";
        std::cin>>userChoise;
        userWantsOperation = (userChoise == 'Y') ? true : false ;
    }

    return 0;
}
/*
Links:
      https://leetcode.com/discuss/interview-question/435345/Google-or-Phone-or-Insert-into-a-Sorted-Circular-Linked-List
      https://leetcode.com/discuss/interview-question/429160/Facebook-or-Phone-Screen-or-Insert-into-a-Sorted-Circular-Linked-list
      https://leetcode.com/problems/insert-into-a-sorted-circular-linked-list/description/
*/
