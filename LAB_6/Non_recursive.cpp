#include <iostream>
#include <queue>
#include <stack>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
};

Node* newNode(int data) {
    Node* p = new Node{data, nullptr, nullptr};
    return p;
}

void LevelOrder(Node* root) {
    if (root == nullptr) return;

    queue<Node*> q;
    q.push(root);
    while (q.size()) {
        Node* temp = q.front();
        q.pop();
        
        cout << temp->key << ' ';
        if (temp->left) q.push(temp->left);
        if (temp->right) q.push(temp->right);
    }
    cout << '\n';
}

void NLR_(Node* root) {
    if (root == nullptr) return;
    stack<Node*> s;
    s.push(root);
    while (s.size()) {
        Node* p = s.top();
        s.pop();
        cout << p->key << ' ';
        if (p->right) s.push(p->right);
        if (p->left) s.push(p->left);
    }
}

void LNR_(Node* root) {
    if (root == nullptr) return;
    stack<Node*> s;
    Node* p = root;
    while (p || s.size()) {
        if (p) {
            s.push(p);
            p = p->left;
        }
        else {
            p = s.top();
            cout << p->key << ' ';
            s.pop();
            p = p->right;
        }
    }
}

void LRN_(Node* root) {
    if (root == nullptr) return;

    stack<Node*> s1, s2;
    s1.push(root);
    while (s1.size()) {
        Node* p = s1.top(); s1.pop();
        s2.push(p);
        
        if (p->left) s1.push(p->left);
        if (p->right) s1.push(p->right);
    }

    while (s2.size()) {
        cout << s2.top()->key << ' ';
        s2.pop();
    }
    cout << '\n';
}

void Insert(Node* &root, int data) {
    if (root == nullptr) {
        root = newNode(data);
        return;
    }
    Node* cur = root;
    Node* par = nullptr;
    while (cur) {
        par = cur;
        if (data < cur->key) cur = cur->left;
        else if (data > cur->key) cur = cur->right;
        else return;
    }
    if (data > par->key) par->right = newNode(data);
    else par->left = newNode(data);
}

void Delete_(Node* &root, int data) {
    if (root == nullptr) return;

    Node* cur = root;
    Node* par = nullptr;
    while (cur && cur->key != data) {
        par = cur;
        if (data < cur->key) cur = cur->left;
        else if (data > cur->key) cur = cur->right;
    }

    if (cur == nullptr) return; // ko tim thay

    //truong hop ko co hoac co 1 con
    if (cur->left == nullptr || cur->right == nullptr) {
        Node* child = (cur->left) ? cur->left : cur->right;

        if (par == nullptr) root = child; // xoa root
        else if (par->left == cur) par->left = child;
        else par->right = child;

        delete cur;
    }
    //truong hop co 2 con
    else {
        Node* parr = cur;
        Node* curr = cur->left;
        while (curr->right) {
            parr = curr;
            curr =  curr->right;
        }
        cur->key = curr->key;
        Node* child = curr->left;
        if (parr->left == curr) parr->left = child;
        else parr->right = child;

        delete curr;
    }
}

int main() {
    Node* root = nullptr;
    
    Insert(root, 8);
    Insert(root, 6);
    Insert(root, 5);
    Insert(root, 7);
    Insert(root, 10);
    Insert(root, 9);

    // NLR_(root);
    // LNR_(root);
    LRN_(root);              
    
    Delete_(root, 8);
    LevelOrder(root);
}