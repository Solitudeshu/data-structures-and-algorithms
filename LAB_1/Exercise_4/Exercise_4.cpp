#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
};

void traversalNodes(Node* head) {
    for (Node* p = head; p; p = p->next) 
        cout << p->data << " -> ";
    cout << "NULL\n";
}

int countNodes(Node* head) {
    int count = 0;
    for (Node* p = head; p; p = p->next) count++;
    return count;
}

Node* createNode(int val) {
    Node* newNode = new Node();
    newNode->data = val;
    newNode->next = nullptr;
    return newNode;
}

void addHead(Node* &head, int data) {
    head = new Node{data, head};
}

void addTail(Node* &head, int data) {
    if (!head) addHead(head, data);
    else {
        for (Node* p = head; p; p = p->next) 
            if (!p->next) {
                p->next = createNode(data);
                return;
            }
    }
}

void removeHead(Node* &head) {
    if (!head) return;
    Node* p = head;
    head = head->next;
    delete p;
}

void removeTail(Node* &head) {
    if (!head) return;
    if (!head->next) return removeHead(head);
    for (Node* p = head; p; p = p->next) 
        if (!p->next->next) {
            Node* tmp = p->next;
            p->next = nullptr; 
            delete tmp;
        }
}

void removeDuplicate(Node* &head) {
    if (!head || !head->next) return;
    for (Node* p = head; p; p = p->next) {
        Node* prev = p;
        Node* q = p->next;
        while (q) {
            if (p->data == q->data) {
                prev->next = q->next;
                delete q;
                q = prev->next;
            }
            else {
                prev = q;
                q = q->next;
            }
        }

    }
}

void deleteList(Node* &head) {
    while (head) 
        removeHead(head);
}

int main() {
    Node* head = nullptr;

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int data;
        cin >> data;
        addTail(head, data);
    }

    cout << "Linked list: ";
    traversalNodes(head);

    cout << "The total number of nodes in the linked list: ";
    cout << countNodes(head) << '\n';

    int x;
    cout << "Add an element x to the head: ";
    cin >> x;    
    addHead(head, x);
    traversalNodes(head);

    cout << "Add an element x to the tail: ";
    cin >> x;    
    addTail(head, x);
    traversalNodes(head);

    cout << "Remove head: ";
    removeHead(head);
    traversalNodes(head);

    cout << "Remove tail: ";
    removeTail(head);
    traversalNodes(head);

    cout << "Remove duplicate: ";
    removeDuplicate(head);
    traversalNodes(head);

    deleteList(head);
    return 0;
}