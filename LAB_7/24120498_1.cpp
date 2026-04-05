#include <iostream>
#include <queue>

using namespace std;

enum Color {
    RED,
    BLACK
};

struct Node {
    int key;
    Color color;
    Node* left;
    Node* right;
    Node* parent;
};

Node *nil, *root;

Node* newNode(int data) {
	return new Node{data, RED, nil, nil, nil};
}

void leftRotate(Node* &root, Node* x) {
	Node* y = x->right;
	x->right = y->left;
	if (y->left != nil) y->left->parent = x;

	y->parent = x->parent;

	if (x->parent == nil) root = y;
	else if (x == x->parent->left) x->parent->left = y;
	else x->parent->right = y;
	y->left = x;
	x->parent = y;
}

void rightRotate(Node* &root, Node* y) {
	Node* x = y->left;
	y->left = x->right;
	if (x->right != nil) x->right->parent = y;
	
	x->parent = y->parent;

	if (y->parent == nil) root = x;
	else if (y == y->parent->left) y->parent->left = x;
	else y->parent->right = x;
	
	x->right = y;
	y->parent = x;
}

void insLeft(Node* &root, Node* &x) {
	Node* u = x->parent->parent->right;
	if (u->color == RED) {
		x->parent->color = u->color = BLACK;
		x->parent->parent->color = RED;
		x = x->parent->parent;
	}
	else {
		if (x == x->parent->right) {
			x = x->parent;
			leftRotate(root, x);
		}
		x->parent->color = BLACK;
		x->parent->parent->color = RED;
		rightRotate(root, x->parent->parent);
	}
}

void insRight(Node* &root, Node* &x) {
	Node* u = x->parent->parent->left;
	if (u->color == RED) {
		x->parent->color = u->color = BLACK;
		x->parent->parent->color = RED;
		x = x->parent->parent;
	}
	else {
		if (x == x->parent->left) {
			x = x->parent;
			rightRotate(root, x);
		}
		x->parent->color = BLACK;
		x->parent->parent->color = RED;
		leftRotate(root, x->parent->parent);
	}
}

void insertionFixUp(Node* &root, Node* x) {
	while (x->parent->color == RED) 
		if (x->parent == x->parent->parent->left) insLeft(root, x);
		else insRight(root, x);
		
	root->color = BLACK;
}

void RBTInsert(Node* &root, Node *x) {
	Node *y = nil;
	Node *z = root;
	while (z != nil) {
		y = z;
		if (x->key < z->key) z = z->left;
		else if (x->key > z->key) z = z->right;
		else return;
	}

	x->parent = y;

	if (y == nil) root = x;
	else if (x->key < y->key) y->left = x;
	else y->right = x;
	
}

Node* insert(Node* root, int data) {
	Node* x = newNode(data);
	RBTInsert(root, x);
	insertionFixUp(root, x);
	return root;
}

Node* search(Node* root, int data) {
	Node* x = root;
	while (x != nil) 
		if (data < x->key) x = x->left;
		else if (data > x->key) x = x->right;
		else return x;
	return NULL;
}

void delLeft(Node* &root, Node* &x) {
	Node* w = x->parent->right;
	if (w->color == RED) {
		w->color = BLACK;
		x->parent->color = RED;
		leftRotate(root, x->parent);
		w = x->parent->right;
	}
	if (w->left->color == BLACK && w->right->color == BLACK) {
		w->color = RED;
		x = x->parent;
	}
	else {
		if (w->right->color == BLACK) {
			w->left->color = BLACK;
			w->color = RED;
			rightRotate(root, w);
			w = x->parent->right;
		}
		w->color = x->parent->color;
		x->parent->color = w->right->color = BLACK;
		leftRotate(root, x->parent);
		x = root;
	}
}

void delRight(Node* &root, Node* &x) {
	Node* w = x->parent->left;
	if (w->color == RED) {
		w->color = BLACK;
		x->parent->color = RED;
		rightRotate(root, x->parent);
		w = x->parent->left;
	}
	if (w->right->color == BLACK && w->left->color == BLACK) {
		w->color = RED;
		x = x->parent;
	}
	else {
		if (w->left->color == BLACK) {
			w->right->color = BLACK;
			w->color = RED;
			leftRotate(root, w);
			w = x->parent->left;
		}
		w->color = x->parent->color;
		x->parent->color = w->left->color = BLACK;
		rightRotate(root, x->parent);
		x = root;
	}
}

void Del_FixUp(Node* &root, Node *x){
	while (x != root && x->color == BLACK) 
		if (x == x->parent->left) delLeft(root, x);
		else delRight(root, x);
	x->color = BLACK;
}

Node *successor(Node *x) {
	Node *y = x->left;
	while (y->right != nil) y = y->right;
	return y;
}

Node *deleteNode(Node *root, int data) {
	Node *z = search(root, data);
	if (z == nil) return root;
	
	Node *y = (z->left == nil || z->right == nil) ? z : successor(z);
	Node *x = (y->left != nil) ? y->right : y->left;
	x->parent = y->parent;
	if (y->parent == nil) root = x;
	else if (y == y->parent->left) y->parent->left = x;
	else y->parent->right = x;
	
	if (y != z) z->key = y->key;

	if (y->color == BLACK) Del_FixUp(root, x);

	delete y;
	return root;
}

void LevelOrder(Node * root) {
	if (root == nil) return;

	queue<pair<Node*, int>> q;
	q.push({root, 0});
	int tmp = -1;
	while (!q.empty()) {
		std::pair<Node *, int> temp = q.front();
		if(temp.second != tmp) {
			cout << "\nLevel " << temp.second << ": ";
			tmp = temp.second;
		}
		cout << temp.first->key << " ";
		q.pop();
		if (temp.first->left != nil) q.push({temp.first->left, temp.second + 1});
		if (temp.first->right != nil) q.push({temp.first->right, temp.second + 1});
	}
}

void freeTree(Node *root) {
	if (root == nil) return;
	freeTree(root->left);
	freeTree(root->right);
	delete root;
}

int main() {
	nil = newNode(0);
	nil->color = BLACK;
	root = nil;

	root = insert(root, 20);
	root = insert(root, 15);
	root = insert(root, 10);
	root = insert(root, 30);
	root = insert(root, 50);
	root = insert(root, 45);
	
	cout << "Level Order:";
	LevelOrder(root);
	cout << "\n";
	
	cout << "Search 30: ";
	Node *temp = search(root, 30);	
	if (temp != NULL) cout << "Found 30";
	else cout << "Not Found";

	std::cout << "\n\nDelete 15\n";
	root = deleteNode(root, 15);
	std::cout << "Level Order: ";
	LevelOrder(root);

	freeTree(root);
	delete nil;
	return 0;
}