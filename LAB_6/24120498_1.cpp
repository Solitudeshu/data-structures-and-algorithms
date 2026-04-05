#include <iostream>
#include <queue>

using namespace std;

struct Node {
    int key;
    Node *left;
    Node *right;
};

Node* newNode(int data) {
    Node* p = new Node{data, nullptr, nullptr};
    return p;
}

Node* insert(Node* root, int data) {
    if (root == nullptr) 
        return newNode(data);
    if (data < root->key) 
        root->left = insert(root->left, data);
    else if (data > root->key) 
        root->right = insert(root->right, data);
    return root;
}

Node* search(Node* root, int data) {
    if (root == nullptr || root->key == data) 
        return root;
    if (data < root->key) return search(root->left, data);
    return search(root->right, data);
}

Node* Delete(Node* root, int data) {
    if (root == nullptr) 
        return root;
    if (data < root->key) 
        root->left = Delete(root->left, data);
    else if (data > root->key) 
        root->right = Delete(root->right, data);
    else {
        if (root->left == nullptr) {
            Node* p = root->right;
            delete root;
            return p;
        }
        else if (root->right == nullptr) {
            Node* p = root->left;
            delete root;
            return p;
        }
        Node* temp = root->left;
        while (temp->right) temp = temp->right;
        root->key = temp->key;
        root->left = Delete(root->left, temp->key);
    }
    return root;
}

void NLR(Node* root) {
    if (root) {
        cout << root->key << ' ';
        NLR(root->left);
        NLR(root->right);
    }
}

void LNR(Node* root) {
    if (root) {
        LNR(root->left);
        cout << root->key << ' ';
        LNR(root->right);
    }
}

void LRN(Node* root) {
    if (root) {
        LRN(root->left);
        LRN(root->right);
        cout << root->key << ' ';
    }
}

void LevelOrder(Node* root) {
    if (root == nullptr) return;

    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();

        cout << temp->key << ' ';
        if (temp->left) q.push(temp->left);
        if (temp->right) q.push(temp->right);
    }
}

int height(Node* root) {
    if (root == nullptr) 
        return 0;
    int heightLeft = height(root->left);
    int heightRight = height(root->right);
    return max(heightLeft, heightRight) + 1;
}

int countNode(Node* root) {
    if (root == nullptr) 
        return 0;
    return countNode(root->left) + countNode(root->right) + 1;
}

int countInternal(Node* root) {
    if (root == nullptr || (root->left == nullptr && root->right == nullptr)) 
        return 0;
    return countInternal(root->left) + countInternal(root->right) + 1;
}

int sumNode(Node* root) {
    if (root == nullptr) 
        return 0;
    return sumNode(root->left) + sumNode(root->right) + root->key;
}

int countLeaf(Node* root) {
    if (root == nullptr)
        return 0;
    if (root->left == nullptr && root->right == nullptr)
        return 1;
    return countLeaf(root->left) + countLeaf(root->right);
}

int countLess(Node* root, int x) {
    if (root == nullptr)
        return 0;
    if (root->key < x) 
        return countLess(root->left, x) + countLess(root->right, x) + 1;
    return countLess(root->left, x);
}

int countGreater(Node* root, int x) {
    if (root == nullptr)
        return 0;
    if (root->key > x) 
        return countGreater(root->left, x) + countGreater(root->right, x) + 1;
    return countGreater(root->right, x);
}

int main() {
    Node* root = nullptr;
    root = insert(root, 8);
    root = insert(root, 6);
    root = insert(root, 5);
    root = insert(root, 7);
    root = insert(root, 10);
    root = insert(root, 9);

    cout << "Pre-Order: ";
    NLR(root);
    cout << "\nIn-order: ";
    LNR(root);
    cout <<"\nPost-order: ";
    LRN(root);

    Delete(root, 8);
    cout << "\nLevel Order: ";
    LevelOrder(root);

    int x = 7;

    cout << "\nHeight: " << height(root);
    cout << "\nCount the number of Node: " << countNode(root);
    cout << "\nCount the number of internal nodes: " << countInternal(root);
    cout << "\nThe total value of all Nodes: " << sumNode(root);
    cout << "\nCount the number leaves: " << countLeaf(root);
    cout << "\nCount the number of Nodes which key value is less than " << x << ": " << countLess(root, x);
    cout << "\nCount the number of Nodes which key value is greater than " << x << ": " << countGreater(root, x);
    return 0;
}