#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
};

struct Stack {
    Node* head;
};

void push(Stack &st, int data) {
    st.head = new Node{data, st.head};
}

void pop(Stack &st) {
    if (!st.head) return;
    Node* p = st.head->next;
    delete st.head;
    st.head = p;   
}

int top(Stack &st) {
    if (!st.head) return -1;
    return st.head->data;
}

void traversal(Stack &st) {
    for (Node* p = st.head; p; p = p->next) 
        cout << p->data << ' ';
    cout << '\n';
}

void deleteStack(Stack &st) {
    while (st.head) 
        pop(st);
}

int main() {
    Stack st;
    st.head = nullptr;

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int data;
        cin >> data;
        push(st, data);
    }

    cout << "Pop the top item from the stack: ";
    pop(st);
    traversal(st);


    cout << "The value of the top item: ";
    cout << top(st) << '\n';

    deleteStack(st);
    return 0;
}
