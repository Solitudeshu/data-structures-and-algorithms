#include <iostream>
#include <queue>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};

Node* newNode(int data) {
    Node* p = new Node{data, nullptr, nullptr, 1};
    return p;
}

int height(Node* root) {
    if (root == nullptr) return 0;
    return root->height;
}

Node* rotateRight(Node* p) {
    Node* p1 = p->left;
    p->left = p1->right;
    p1->right = p;
    p->height = (height(p->left) > height(p->right) ? height(p->left) : height(p->right)) + 1;
    p1->height = (height(p1->left) > height(p1->right) ? height(p1->left) : height(p1->right)) + 1;
    return p1;
}

Node* rotateLeft(Node* p) {
    Node* p1 = p->right;
    p->right = p1->left;
    p1->left = p;
    p->height = (height(p->left) > height(p->right) ? height(p->left) : height(p->right)) + 1;
    p1->height = (height(p1->left) > height(p1->right) ? height(p1->left) : height(p1->right)) + 1;
    return p1;
}

int getBalance(Node* root) {
    if (root == nullptr) return 0;
    return height(root->left) - height(root->right);
}

Node* insertNode(Node* root, int data) {
    if (root == nullptr) 
        return newNode(data);
    
    if (data < root->key) root->left = insertNode(root->left, data);
    else if (data > root->key) root->right = insertNode(root->right, data);
    else return root;

    root->height = (height(root->left) > height(root->right) ? height(root->left) : height(root->right)) + 1;

    int balance = getBalance(root);

    if (balance > 1 && data < root->left->key) 
        return rotateRight(root);
    if (balance < -1 && data > root->right->key)
        return rotateLeft(root);
    if (balance > 1 && data > root->left->key) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && data < root->right->key) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

Node* searchNode(Node* root, int data) {
    if (root == nullptr || root->key == data) 
        return root;
    if (root->key < data) return searchNode(root->right, data);
    return searchNode(root->left, data);
}

Node * deleteNode(Node * root, int data) {
	if (root == NULL) 
		return root;

	if (data < root->key) root->left = deleteNode(root->left, data);
	else if (data > root->key) root->right = deleteNode(root->right, data);
	else {
		if (root->left == nullptr) {
			Node * temp = root->right;
			delete root;
			return temp;
		} else if (root->right == nullptr) {
			Node * temp = root->left;
			delete root;
			return temp;
		}
		Node * temp = root->left;
		while (temp->right) temp = temp->right;
		root->key = temp->key;
		root->left = deleteNode(root->left, temp->key);
	}
	
	root->height = (height(root->left) > height(root->right) ? height(root->left) : height(root->right)) + 1;
	
	int balance = getBalance(root);
	
	if (balance > 1 && getBalance(root->left) >= 0) 
		return rotateRight(root);
	if (balance < -1 && getBalance(root->right) <= 0) 
		return rotateLeft(root);
	if (balance > 1 && getBalance(root->left) < 0) {
		root->left = rotateLeft(root->left);
		return rotateRight(root);
	}
	if (balance < -1 && getBalance(root->right) > 0) {
		root->right = rotateRight(root->right);
		return rotateLeft(root);
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

bool isFull(Node* root) {
    if (root == nullptr) return true;
    if (root->left == nullptr && root->right == nullptr) return true;
    if (root->left && root->right) 
        return isFull(root->left) && isFull(root->right);
    return false;
}

bool isComplete(Node* root) {
    if (root == nullptr) return true;

    bool check = false;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();
        
        if (temp->left) {
            if (check) return false;
            q.push(temp->left);
        }
        else check = true;

        if (temp->right) {
            if (check) return false;
            q.push(temp->right);
        }
        else check = true;
    }
    return true;
}

bool isPerfect(Node* root) {
    return isFull(root) && isComplete(root);
}

int findCommonAncestor(Node* root, int x, int y) {
    if (root == nullptr) return -1;
    if (root->key > x && root->key > y) 
        return findCommonAncestor(root->left, x, y);
    if (root->key < x && root->key < y)
        return findCommonAncestor(root->right, x, y);
    return root->key;
}

void printSpecialNodes(Node* root) {
    if (root == nullptr) return;

    if (root->left && root->right) 
        if (root->right->key % root->left->key == 0) cout << root->key << ' ';
    
    printSpecialNodes(root->left);
    printSpecialNodes(root->right);
}

void Free(Node* root) {
    if (root) {
        Free(root->left);
        Free(root->right);
        delete root;
    }
}

int main() {
    Node* root = nullptr;
    root = insertNode(root, 8);
    root = insertNode(root, 6);
    root = insertNode(root, 5);
    root = insertNode(root, 7);
    root = insertNode(root, 10);
    root = insertNode(root, 9);

    cout << "Pre-Order: ";
    NLR(root);
    cout << "\nIn-order: ";
    LNR(root);
    cout <<"\nPost-order: ";
    LRN(root);

    deleteNode(root, 8);
    cout << "\nLevel Order: ";
    NLR(root);
    // LevelOrder(root);

    int x = 9, y = 5;

    cout << "\nCheck if the given AVL Tree is a full tree: " << isFull(root);
    cout << "\nCheck if the given AVL Tree is a complete tree: " << isComplete(root);
    cout << "\nCheck if the given AVL Tree is a perfect tree: " << isPerfect(root);
    cout << "\nThe least common ancestor of " << x << " and " << y << ": " << findCommonAncestor(root, x, y);
    cout << "\nSpecial Nodes: ";
    printSpecialNodes(root);

    Free(root);
    return 0;
}