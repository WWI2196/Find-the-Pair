#include <iostream>
#include <sstream>
using namespace std;

class LinkedListNode { // Node of the linked list
public:
    int data;
    LinkedListNode* next;

    LinkedListNode(int data) {
        this->data = data;
        this->next = nullptr;
    }
};

class LinkedList {
private:
    LinkedListNode* head;

public:
    LinkedList() {
        head = nullptr;
    }

    void addData_toEnd(int data) { // Add data to the end of the linked list
        LinkedListNode* newNode = new LinkedListNode(data);

        if (head == nullptr) {
            head = newNode;
        }
        else {
            LinkedListNode* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    bool search(int data) const { // Search for the given data in the linked list and return true if found
        LinkedListNode* temp = head;
        while (temp != nullptr) {
            if (temp->data == data) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    void deleteValue(int data) { // Delete the given data from the linked list
        if (!search(data)) {
            return;
        }

        LinkedListNode* tempPrv = nullptr;
        LinkedListNode* temp = head;

        while (temp != nullptr && temp->data != data) {
            tempPrv = temp;
            temp = temp->next;
        }

        if (temp == head) { // If the data to be deleted is the first element
            head = temp->next; // Update the head to the next element
            delete temp; // Delete the first element
        }
        else {
            tempPrv->next = temp->next;
            delete temp;
        }
    }

    LinkedListNode* getHead() const { // Return the head of the linked list
        return head;
    }

    void deleteLinkedList() { // Delete the entire linked list
		LinkedListNode* temp = head;
		while (head != nullptr) {
			temp = head;
			head = head->next;
			delete temp;
		}
	}
};

class TreeNode { // Node of the binary search tree
public:
    int data;
    TreeNode* leftChild;
    TreeNode* rightChild;

    TreeNode(int data) {
        this->data = data;
        leftChild = nullptr;
        rightChild = nullptr;
    }
};

class BinarySearchTree {
private:
    TreeNode* root;

public:
    BinarySearchTree() {
        root = nullptr;
    }

    void insert(TreeNode*& current, int data) { // Insert the data into the binary search tree
        if (current == nullptr) {
            TreeNode* node = new TreeNode(data);
            current = node;
            return;
        }

        if (data < current->data) {
            insert(current->leftChild, data);
        }
        else if (data > current->data) {
            insert(current->rightChild, data);
        }
    }

    void insert(int data) {
        insert(root, data);
    }

    TreeNode* search(TreeNode* current, int data) const { // Search for the given data in the binary search tree
        while (current != nullptr) {
            if (data < current->data) {
                current = current->leftChild;
            }
            else if (data > current->data) {
                current = current->rightChild;
            }
            else {
                return current; // Return the node if the data is found
            }
        }
        return nullptr; // Return nullptr if the data is not found
    }

    TreeNode* search(int data) const {
        return search(root, data);
    }

    void findPair(int value) { // Find the pairs of elements in the binary search tree that sum up to the given value
        if (root == nullptr) { // If the tree is empty
            cout << "No pairs found" << endl;
            return;
        }

        LinkedList firstElement, secondElement; // To store the first and second elements of the pairs
        LinkedList useNode; // LinkedList to go through the tree
        useNode.addData_toEnd(root->data); // Start with the root node

        while (useNode.getHead() != nullptr) { // While there are elements to process in the linked list
            TreeNode* current = search(useNode.getHead()->data); // Get the current node from the linked list

            int difference = value - current->data; // Calculate the difference needed to reach the target value
            if (difference > current->data) { // Check the difference is greater than the current node's data 
                TreeNode* differenceNode = search(difference); // Search for the node with the difference value
                if (differenceNode != nullptr) { // If such a node is found
                    firstElement.addData_toEnd(current->data); // Add the current node's data to the first element list
                    secondElement.addData_toEnd(difference); // Add the difference to the second element list
                }
            }

            // Add the left and right children of the current node to the linked list
            if (current->leftChild != nullptr) { // If the left child exists
                useNode.addData_toEnd(current->leftChild->data); // Add the left child's data to the linked list
            }
            if (current->rightChild != nullptr) { // If the right child exists
                useNode.addData_toEnd(current->rightChild->data); // Add the right child's data to the linked list
            }

            LinkedListNode* temp = useNode.getHead(); // Remove the processed node from the linked list
            useNode.deleteValue(temp->data);
        }

        if (firstElement.getHead() == nullptr) { // If no pairs are found, inform the user
            cout << "No pairs found";
        }
        else { // Print the pairs found
            cout << "Pairs: ";
            LinkedListNode* first = firstElement.getHead();
            LinkedListNode* second = secondElement.getHead();
            while (first != nullptr && second != nullptr) { // Go through both linked lists and print the pairs
                cout << "(" << first->data << ", " << second->data << ") ";
                first = first->next;
                second = second->next;
            }
        }
        cout << endl;

        firstElement.deleteLinkedList(); // Delete the linked lists
        secondElement.deleteLinkedList();
        useNode.deleteLinkedList();
    }


    void deleteTree(TreeNode* current) { // Delete the binary search tree
        if (current == nullptr) {
            return;
        }
        deleteTree(current->leftChild);
        deleteTree(current->rightChild);
        delete current;
    }

    void deleteTree() {
        deleteTree(root);
    }
};

int main()
{
    
    int numberOfTreeNodes, choice,value;

    cout << "Enter the number of Nodes: ";
    cin >> numberOfTreeNodes;
    cin.ignore();  // To ignore the newline character after the number of TreeTreeTreeNodes

    BinarySearchTree tree;

    cout << "Enter the values separated by space: ";

    string input;
    getline(cin, input);  // Read the entire line of input

    stringstream inputStream(input);

    for (int i = 0; i < numberOfTreeNodes; i++) {
        inputStream >> choice;  // Extract each number from the stringstream
        tree.insert(choice);
    }

    cout << "Enter a value: ";
    cin >> value;

    tree.findPair(value);

    tree.deleteTree();


    return 0;
}
