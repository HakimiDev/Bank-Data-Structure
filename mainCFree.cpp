#include <iostream>
#include <string>

using namespace std;

const string nodeName = " Bank Account ";

struct Data {
    string accountNumber, username;
    double balance;
};

struct Node {
    Node *prev, *next;
    Data data;
};

typedef Node *nodePtr;

nodePtr createNode () {
    string accountNumber;
    string username;
    
    cout << "Enter the account number: ";
    cin >> accountNumber;

    cout << "Enter the account username: ";
    cin >> username;

    nodePtr node = new Node;
    Data data = {
        accountNumber,
        username,
        balance: 0.0
    };

    node->data = data;
    node->prev = NULL;
    node->next = NULL;

    return node;
};

void unShift (nodePtr &firstNode) {
    nodePtr newNode = createNode();
    if (firstNode == NULL) firstNode = newNode;
    else {
        newNode->next = firstNode;
        firstNode->prev = newNode;
        firstNode = newNode;
    }

    cout << "The" << nodeName << "Is Successfully Added!" << endl;
};

void push (nodePtr &firstNode) {
    nodePtr newNode = createNode();
    if (firstNode == NULL) firstNode = newNode;
    else {
        nodePtr node = firstNode;
        while (node->next != NULL) {
            node = node->next;
        }

        newNode->prev = node;
        node->next = newNode;
    }

    cout << "The" << nodeName << "Is Successfully Added!" << endl;
};

void pushMiddle (nodePtr &firstNode, int nodeNumber) {
    nodePtr newNode = createNode();
    if (firstNode == NULL) firstNode = newNode;
    else {
        int counter = 1;

        nodePtr node = firstNode;        
        while (node->next != NULL && counter < nodeNumber) {
            node = node->next;
            counter++;
        }

        newNode->prev = node;
        newNode->next = node->next;
        if (node->next != NULL) node->next->prev = newNode;
        node->next = newNode;
    }

    cout << "The" << nodeName << "Is Successfully Added!" << endl;
};

void shift (nodePtr &firstNode) {
    if (firstNode == NULL) cout << "The LinkedList Is Empty!" << endl;
    else {
        nodePtr node = firstNode; 
        firstNode = firstNode->next;
        if (firstNode != NULL) firstNode->prev = NULL;

        cout << "The" << nodeName << "Is Successfully Deleted!" << endl;
        delete node;
    }
};

void pop (nodePtr &firstNode) {
    if (firstNode == NULL) cout << "The LinkedList Is Empty!" << endl;
    else {
        nodePtr node = firstNode; 
        while (node->next != NULL) {
            node = node->next;
        }

        if (node->prev != NULL) node->prev->next = NULL;
        else firstNode = NULL;

        cout << "The" << nodeName << "Is Successfully Deleted!" << endl;
        delete node;
    }
};

void popOne (nodePtr &firstNode, int nodeNumber) { // If the 'nodeNumber' is not exist then its gonna delete the last node.
    if (firstNode == NULL) cout << "The LinkedList Is Empty!" << endl;
    else {
        int counter = 1;

        nodePtr node = firstNode;        
        while (node->next != NULL && counter < nodeNumber) {
            node = node->next;
            counter++;
        }

        if (node->prev == NULL && node->next == NULL) firstNode = NULL;
        else {
            if (node->prev != NULL) node->prev->next = node->next;
            if (node->next != NULL) node->next->prev = node->prev;

            if (node->prev == NULL) firstNode = node->next;
        }

        cout << "The" << nodeName << "Is Successfully Deleted!" << endl;
        delete node;
    }
};

nodePtr getNodeByIndex (nodePtr &firstNode, int index) { // Index start form 1
    int counter = 1;
    nodePtr node = firstNode;        
    while (node->next != NULL && counter < index) {
        node = node->next;
        counter++;
    }

    return index == counter ? node : NULL;
};

int getIndexByUsername (nodePtr &firstNode, string username) {
    int index = -1, counter = 1;
    nodePtr node = firstNode;        
    while (node != NULL) {
        if (node->data.username == username) {
            index = counter;
            break;
        }

        node = node->next;
        counter++;
    }

    return index;
};

void addBalance (nodePtr& firstNode) {
    cout << "Enter the username of the user: ";
    string username;
    cin >> username;

    int index = getIndexByUsername(firstNode, username);
    if (index == -1)
        cout << "This Username Is Not Found!" << endl;
    else {
        nodePtr node = getNodeByIndex(firstNode, index);
        cout << "Enter the amount: ";
        double amount;
        cin >> amount;

        if (amount <= 0) {
            cout << "You Should Enter A Number Greater Than Zero!" << endl;
        } else {
            node->data.balance += amount;
            cout << "Balance Successfully Added!" << endl;
        }
    }
};

void withdrawMoney (nodePtr& firstNode) {
    cout << "Enter the username of the user: ";
    string username;
    cin >> username;

    int index = getIndexByUsername(firstNode, username);
    if (index == -1)
        cout << "This Username Is Not Found!" << endl;
    else {
        nodePtr node = getNodeByIndex(firstNode, index);
        cout << "Enter the amount: ";
        double amount;
        cin >> amount;

        if (amount <= 0) {
            cout << "You Should Enter A Number Greater Than Zero!" << endl;
        } else {
            if (amount > node->data.balance) {
                cout << "You Don't Have Enough Balance :(" << endl;
            } else {
                node->data.balance -= amount;
                cout << "Thanks For Using Our Bank!" << endl;
                cout << "Your Current Balance Is: " << node->data.balance << endl;
            }
        }
    }
};

void transferMoney (nodePtr& firstNode) {
    cout << "Enter the username of user number one: ";
    string username1;
    cin >> username1;

    int index1 = getIndexByUsername(firstNode, username1);
    if (index1 == -1) {
        cout << "This Username Is Not Found!" << endl;
        return;
    }

    cout << "Enter the username of user number two: ";
    string username2;
    cin >> username2;

    int index2 = getIndexByUsername(firstNode, username2);
    if (index2 == -1) {
        cout << "This Username Is Not Found!" << endl;
        return;
    }

    nodePtr node1 = getNodeByIndex(firstNode, index1);
    nodePtr node2 = getNodeByIndex(firstNode, index2);

    cout << "Enter the amount: ";
    double amount;
    cin >> amount;

    if (amount <= 0) {
        cout << "You Should Enter A Number Greater Than Zero!" << endl;
    } else {
        if (amount > node1->data.balance) {
            cout << "You Don't Have Enough Balance :(" << endl;
        } else {
            node1->data.balance -= amount;
            node2->data.balance += amount;

            cout << "Thanks For Using Our Bank!" << endl;
            cout << "Your Current Balance Is: " << node1->data.balance << endl;
        }
    }
};

void showNodeData (nodePtr& node) {
    if (node == NULL) return;
    Data data = node->data;
    cout << "\tAccount Number: " << data.accountNumber << endl;
    cout << "\tAccount Username: " << data.username << endl;
    cout << "\tAccount Balance: " << data.balance << endl;
    cout << "\t--------------------------------" << endl;
};

void displayNodes (nodePtr& firstNode) {
    if (firstNode == NULL) cout << "The LinkedList Is Empty!" << endl;
    else {
        nodePtr node = firstNode;
        while (node != NULL) {
            showNodeData(node);
            node = node->next;
        }
    }
};

void displayMainMenu () {
    cout << "---------------------------" << endl;
    cout << "1 -> Create Account" << endl;
    cout << "2 -> Delete Account" << endl;
    cout << "3 -> Show Accounts" << endl;
    cout << "4 -> More Options" << endl;
    cout << endl << "5 -> Exit Program" << endl;
    cout << "---------------------------" << endl;
};

void displayAddMenu () {
    cout << "---------------------------" << endl;
    cout << "1 -> Add Account From The Begin" << endl;
    cout << "2 -> Add Account From The Last" << endl;
    cout << "3 -> Add Account From The Middle" << endl;
    cout << "---------------------------" << endl;
};

void displayDeleteMenu () {
    cout << "---------------------------" << endl;
    cout << "1 -> Delete Account From The Begin" << endl;
    cout << "2 -> Delete Account From The Last" << endl;
    cout << "3 -> Delete Account From The Middle" << endl;
    cout << "---------------------------" << endl;
};

void displayOptionsMenu () {
    cout << "---------------------------" << endl;
    cout << "1 -> Add Balance" << endl;
    cout << "2 -> Withdraw Money" << endl;
    cout << "3 -> Transfer" << endl;
    cout << "---------------------------" << endl;
};

int main () {
    nodePtr firstNode = NULL;

    cout << "--- Welcome To Our Bank ---" << endl;

    char choice;
    int choice2;
    while (true) {
        displayMainMenu();

        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
            case '1':
                displayAddMenu();
                cout << "Choose: ";
                cin >> choice;

                switch (choice) {
                    case '1':
                        unShift(firstNode);
                        break;
                    case '2':
                        push(firstNode);
                        break;
                    case '3':
                        cout << "Enter the node number that you want to push after it: ";
                        cin >> choice2;
                        pushMiddle(firstNode, choice2);
                        break;
                }
                break;
            case '2':
                displayDeleteMenu();
                cout << "Choose: ";
                cin >> choice;

                switch (choice) {
                    case '1':
                        shift(firstNode);
                        break;
                    case '2':
                        pop(firstNode);
                        break;
                    case '3':
                        cout << "Enter the node number that you want to delete: ";
                        cin >> choice2;
                        popOne(firstNode, choice2);
                        break;
                }
                break;
            case '3':
                displayNodes(firstNode);
                break;
            case '4':
                displayOptionsMenu();
                cout << "Choose: ";
                cin >> choice;

                switch (choice) {
                    case '1':
                        addBalance(firstNode);
                        break;
                    case '2':
                        withdrawMoney(firstNode);
                        break;
                    case '3':
                        transferMoney(firstNode);
                        break;
                }
                break;
            case '5':
                cout << "Good Bye (:" << endl;
                exit(0);
                break;
            default:
                cout << "Invalid choice!" << endl;
                break;
        }
    }

    return 0;
};