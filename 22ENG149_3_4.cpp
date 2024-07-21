#include <iostream>
#include <sstream>
using namespace std;


#include <iostream>
using namespace std;

class LinkedListNode {
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

    void addData_toEnd(int data) {
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

    bool search(int data) const {
        LinkedListNode* temp = head;
        while (temp != nullptr) {
            if (temp->data == data) return true;
            temp = temp->next;
        }
        return false;
    }

    void deleteValue(int data) {
        if (!search(data)) {
            return;
        }

        LinkedListNode* tempPrv = nullptr;
        LinkedListNode* temp = head;

        while (temp != nullptr && temp->data != data) {
            tempPrv = temp;
            temp = temp->next;
        }

        if (temp == head) {
            head = temp->next;
            delete temp;
        }
        else {
            tempPrv->next = temp->next;
            delete temp;
        }
    }

    LinkedListNode* getHead() const {
        return head;
    }

    void deleteLinkedList() {
		LinkedListNode* temp = head;
		while (head != nullptr) {
			temp = head;
			head = head->next;
			delete temp;
		}
	}
};

class TreeNode {
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

    void insert(TreeNode*& current, int data) {
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

    TreeNode* search(TreeNode* current, int data) const {
        while (current != nullptr) {
            if (data < current->data) {
                current = current->leftChild;
            }
            else if (data > current->data) {
                current = current->rightChild;
            }
            else {
                return current;
            }
        }
        return nullptr;
    }

    TreeNode* search(int data) const {
        return search(root, data);
    }

    void findPair(int value) {
        if (root == nullptr) {
            cout << "No pairs found" << endl;
            return;
        }

        LinkedList firstElement, secondElement;
        LinkedList useNode;
        useNode.addData_toEnd(root->data); // Initialize with root

        while (useNode.getHead() != nullptr) {
            TreeNode* current = search(useNode.getHead()->data);

            int difference = value - current->data;
            if (difference > current->data) {
                TreeNode* differenceNode = search(difference);
                if (differenceNode != nullptr) {
                    firstElement.addData_toEnd(current->data);
                    secondElement.addData_toEnd(difference);
                }
            }

            if (current->leftChild != nullptr) {
                useNode.addData_toEnd(current->leftChild->data);
            }
            if (current->rightChild != nullptr) {
                useNode.addData_toEnd(current->rightChild->data);
            }

            LinkedListNode* temp = useNode.getHead();
            useNode.deleteValue(temp->data);
        }

        if (firstElement.getHead() == nullptr) {
            cout << "No pairs found";
        }
        else {
            cout << "Pairs: ";
            LinkedListNode* first = firstElement.getHead();
            LinkedListNode* second = secondElement.getHead();
            while (first != nullptr && second != nullptr) {
                cout << "(" << first->data << ", " << second->data << ") ";
                first = first->next;
                second = second->next;
            }
        }
        cout << endl;

        firstElement.deleteLinkedList();
        secondElement.deleteLinkedList();
        useNode.deleteLinkedList();
    }

    void deleteTree(TreeNode* current) {
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
