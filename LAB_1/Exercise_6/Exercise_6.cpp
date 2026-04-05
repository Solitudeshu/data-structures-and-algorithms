#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
};

struct Queue {
    Node* front;
    Node* rear;
};

void enqueue(Queue &q, int data) {
    Node* newNode = new Node{data, nullptr};
    if (!q.rear) {
        q.front = q.rear = newNode;
        return;
    }
    q.rear->next = newNode;
    q.rear = newNode;
}

void dequeue(Queue &q) {
    if (!q.front) return;
    Node* p = q.front;
    q.front = q.front->next;
    if (!q.front) q.rear = nullptr;
    delete p;
}

int front(Queue &q) {
    if (!q.front) return -1;
    return q.front->data;
}

void traversal(Queue &q) {
    for (Node* p = q.front; p; p = p->next)
        cout << p->data << ' ';
    cout << '\n';
}

void deleteQueue(Queue &q) {
    while (q.front) 
        dequeue(q);
}

int main() {
    Queue q;
    q.front = q.rear = nullptr;

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int data; 
        cin >> data;
        enqueue(q, data);
    }
    
    cout << "Dequeue the front item from the queue: ";
    dequeue(q);
    traversal(q);

    cout << "The value of the front item: ";
    cout << front(q);

    deleteQueue(q);
    return 0;
}