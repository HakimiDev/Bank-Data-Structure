#include <iostream>
#include <string>

// By Shadi AL-Hakimi - AI

using namespace std;

const string nodeName = "Bank Account";

struct Data {
    string accountNumber = "", username = "";
    double balance = 0.0;
};

struct Node {
    Node *prev = nullptr, *next = nullptr;
    Data data;
};

typedef Node *nodePtr;

template<typename... Args>
void print (Args... args) {
    ((cout << args << " "), ...);
    cout << "\033[0m"; // Reset color
    cout << endl;
};

template<typename T>
T input (string msg) {
    T in;
    cout << msg;
    cin >> in;

    return in;
};

template<typename... Args>
void printSuccess (Args... args) {
    print("\033[1;32m", args...); // Set color to bright green
};

template<typename... Args>
void printError (Args... args) {
    print("\033[1;31m", args...); // Set color to bright red
};

template<typename... Args>
void printWarning (Args... args) {
    print("\033[1;33m", args...); // Set color to bright yellow
};

nodePtr createNode () {
    string accountNumber = input<string>("Enter the account number: ");
    string username = input<string>("Enter the account username: ");

    nodePtr node = new Node;
    Data data = {
        accountNumber: accountNumber,
        username: username,
        balance: 0.0
    };
    node->data = data;

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

    printSuccess("The", nodeName, "Is Successfully Added!");
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

    printSuccess("The", nodeName, "Is Successfully Added!");
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

    printSuccess("The", nodeName, "Is Successfully Added!");
};

void shift (nodePtr &firstNode) {
    if (firstNode == NULL) printError("The LinkedList Is Empty!");
    else {
        nodePtr node = firstNode; 
        firstNode = firstNode->next;
        if (firstNode != NULL) firstNode->prev = NULL;

        printSuccess("The", nodeName, "Is Successfully Deleted!");
        delete node;
    }
};

void pop (nodePtr &firstNode) {
    if (firstNode == NULL) printError("The LinkedList Is Empty!");
    else {
        nodePtr node = firstNode; 
        while (node->next != NULL) {
            node = node->next;
        }

        if (node->prev != NULL) node->prev->next = NULL;
        else firstNode = NULL;

        printSuccess("The", nodeName, "Is Successfully Deleted!");
        delete node;
    }
};

void popOne (nodePtr &firstNode, int nodeNumber) {
    if (firstNode == NULL) printError("The LinkedList Is Empty!");
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

        printSuccess("The", nodeName, "Is Successfully Deleted!");
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

int getIndexByAccountNumber (nodePtr &firstNode, string accountNumber) { // Unused Function
    int index = -1, counter = 1;
    nodePtr node = firstNode;        
    while (node != NULL) {
        if (node->data.accountNumber == accountNumber) {
            index = counter;
            break;
        }

        node = node->next;
        counter++;
    }

    return index;
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

void addBalance (nodePtr &firstNode) {
    string username = input<string>("Enter the username of user: ");
    int index = getIndexByUsername(firstNode, username);
    if (index == -1) printError("This Username Is Not Found!");
    else {
        nodePtr node = getNodeByIndex(firstNode, index);
        double amount = input<double>("Enter the amount: ");
        if (amount <= 0) {
            printError("You Should Enter A Number Greater Than Zero!");
        } else {
            node->data.balance += amount;
            printSuccess("Balance Successfully Added!");
        }
    }
};

void withrowMoney (nodePtr &firstNode) {
    string username = input<string>("Enter the username of user: ");
    int index = getIndexByUsername(firstNode, username);
    if (index == -1) printError("This Username Is Not Found!");
    else {
        nodePtr node = getNodeByIndex(firstNode, index);
        double amount = input<double>("Enter the amount: ");
        if (amount <= 0) {
            printError("You Should Enter A Number Greater Than Zero!");
        } else {
            if (amount > node->data.balance) {
                printError("You Don't Have Enough Balance ):");
            } else {
                node->data.balance -= amount;
                printSuccess("Thanks For Using Our Bank!");
                printWarning("Your Current Balance Is:", node->data.balance);
            }
        }
    }
};

void transferMoney (nodePtr &firstNode) {
    string username1 = input<string>("Enter the username of user number one: ");
    int index1 = getIndexByUsername(firstNode, username1);
    if (index1 == -1) { 
        printError("This Username Is Not Found!");
        return;
    }
    string username2 = input<string>("Enter the username of user number two: ");
    int index2 = getIndexByUsername(firstNode, username2);
    if (index2 == -1) {
        printError("This Username Is Not Found!");
        return;
    }

    nodePtr node1 = getNodeByIndex(firstNode, index1);
    nodePtr node2 = getNodeByIndex(firstNode, index2);
    double amount = input<double>("Enter the amount: ");
    if (amount <= 0) {
        printError("You Should Enter A Number Greater Than Zero!");
    } else {
        if (amount > node1->data.balance) {
            printError("You Don't Have Enough Balance ):");
        } else {
            node1->data.balance -= amount;
            node2->data.balance += amount;

            printSuccess("Thanks For Using Our Bank!");
            printWarning("Your Current Balance Is:", node1->data.balance);
        }
    }
};

void showNodeData (nodePtr &node) {
    if (node == NULL) return;
    Data data = node->data;
    print("\tAccount Number: \033[1;33m", data.accountNumber);
    print("\tAccount Username: \033[1;33m", data.username);
    print("\tAccount Balance: \033[1;33m", data.balance);
    print("\t--------------------------------");
};

void displayNodes (nodePtr &firstNode) {
    if (firstNode == NULL) printError("The LinkedList Is Empty!");
    else {
        nodePtr node = firstNode;
        while (node != NULL) {
            showNodeData(node);
            node = node->next;
        }
    }
};

void displayMainMenu () {
    print("---------------------------");
    printSuccess("1 -> Create Account");
    printError("2 -> Delete Account");
    printSuccess("3 -> Show Accounts");
    printWarning("4 -> More Options");
    print("\n \033[0;31m5 -> Exit Program");
    print("---------------------------");
};

void displayAddMenu () {
    print("---------------------------");
    printSuccess("1 -> Add Account From The Begin");
    printSuccess("2 -> Add Account From The Last");
    printSuccess("3 -> Add Account From The Middle");
    print("---------------------------");
};

void displayDeleteMenu () {
    print("---------------------------");
    printError("1 -> Delete Account From The Begin");
    printError("2 -> Delete Account From The Last");
    printError("3 -> Delete Account From The Middle");
    print("---------------------------");
};

void displayOptionsMenu () {
    print("---------------------------");
    printSuccess("1 -> Add Balance");
    printError("2 -> Withrow Money");
    printWarning("3 -> Transfer");
    print("---------------------------");
};

int main () {
    nodePtr firstNode = nullptr;

    print("--- \033[1;32mWelcome To Our \033[1;33mBank\033[0m ---");

    char choice;
    int choice2;
    while (true) {
        displayMainMenu();

        choice = input<char>("Choose: ");
        switch (choice) {
            case '1':
                displayAddMenu();
                choice = input<char>("Choose: ");
                switch (choice) {
                    case '1':
                        unShift(firstNode);
                        break;
                    case '2':
                        push(firstNode);
                        break;
                    case '3':
                        choice2 = input<int>("Enter the node number that you want to push after it: ");
                        pushMiddle(firstNode, choice2);
                        break;
                }
                break;
            case '2':
                displayDeleteMenu();
                choice = input<char>("Choose: ");
                switch (choice) {
                    case '1':
                        shift(firstNode);
                        break;
                    case '2':
                        pop(firstNode);
                        break;
                    case '3':
                        choice2 = input<int>("Enter the node number that you want to delete: ");
                        popOne(firstNode, choice2);
                        break;
                }
                break;
            case '3':
                displayNodes(firstNode);
                break;
            case '4':
                displayOptionsMenu();
                choice = input<char>("Choose: ");
                switch (choice) {
                    case '1':
                        addBalance(firstNode);
                        break;
                    case '2':
                        withrowMoney(firstNode);
                        break;
                    case '3':
                        transferMoney(firstNode);
                        break;
                }
                break;
            case '5':
                printWarning("Good Bye (:");
                exit(0);
                break;
            default:
                printWarning("Invalid choice!");
                break;
        }
    }

    return 0;
};