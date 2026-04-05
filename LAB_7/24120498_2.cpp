#include <iostream>
#include <queue>

using namespace std;

const int MAX = 3; 
const int MIN = MAX / 2; 

struct Node {
    int keys[MAX];
    Node* children[MAX + 1];
    int numKeys;
    bool isLeaf;
};

Node* newNode(bool isLeaf) {
    Node* node = new Node;
    node->numKeys = 0;
    node->isLeaf = isLeaf;
    for (int i = 0; i <= MAX; i++) node->children[i] = nullptr;
    return node;
}

void splitChild(Node * parent, int index, Node * child) {
    Node * newChild = newNode(child->isLeaf);
    newChild->numKeys = MIN;

    for (int i = 0; i < MIN; i++) newChild->keys[i] = child->keys[i + MIN + 1];
    

    if (!child->isLeaf) 
        for (int i = 0; i <= MIN; i++) {
            newChild->children[i] = child->children[i + MIN + 1];
            child->children[i + MIN + 1] = NULL;
            child->numKeys--;
        }

    child->numKeys = MIN;

    for (int i = parent->numKeys; i > index; i--) 
        parent->children[i + 1] = parent->children[i];

    parent->children[index + 1] = newChild;

    for (int i = parent->numKeys - 1; i >= index; i--) 
        parent->keys[i + 1] = parent->keys[i];

    parent->keys[index] = child->keys[MIN];
    parent->numKeys++;

}

void insertNonFull(Node * root, int data) {
    int i = root->numKeys - 1;

    if (root->isLeaf) {
        while (i >= 0 && root->keys[i] > data) {
            root->keys[i + 1] = root->keys[i];
            i--;
        }
        root->keys[i + 1] = data;
        root->numKeys++;
    }
    else {
        while (i >= 0 && root->keys[i] > data) i--;

        i++;
        if (root->children[i]->numKeys == MAX) {
            splitChild(root, i, root->children[i]);
            if (root->keys[i] < data) {
                i++;
            }
        }
        insertNonFull(root->children[i], data);
    }
}

Node * insert(Node * root, int data) {
    if (root == NULL) {
        root = newNode(true);
        root->keys[0] = data;
        root->numKeys = 1;
        return root;
    }
    else 
    if (root->numKeys == MAX) {
        Node * newRoot = newNode(false);

        newRoot->children[0] = root;

        splitChild(newRoot, 0, root);

        int i = 0;
        if (newRoot->keys[0] < data) i++;
        
        insertNonFull(newRoot->children[i], data);

        root = newRoot;
        return root;
    }
    else {
        insertNonFull(root, data);
        return root;
    }
}

void PreOrder(Node * root) {
    if (root == NULL) return;
    
    std::cout << "[";
    for (int i = 0; i < root->numKeys; i++) 
        std::cout << root->keys[i] << " ]"[i == root->numKeys - 1];

    for (int i = 0; i <= root->numKeys; i++) 
        PreOrder(root->children[i]);
}

void InOrder(Node * root) {
    if (root == NULL) return;
    
    for (int i = 0; i < root->numKeys; i++) {
        InOrder(root->children[i]);
        std::cout << root->keys[i] << " ";
    }
    InOrder(root->children[root->numKeys]);
}

void PostOrder(Node * root) {
    if (root == NULL) return;

    for (int i = 0; i <= root->numKeys; i++) 
        PostOrder(root->children[i]);
    
    std::cout << "[";
    for (int i = 0; i < root->numKeys; i++) 
        std::cout << root->keys[i] << " ]"[i == root->numKeys - 1];
}

void LevelOrder(Node * root) {
    if (root == NULL) return;
    
    queue<std::pair<Node*, int>> q;
    q.push({root, 0});
    int tmp = -1;
    while (!q.empty()) {
        std::pair<Node *, int> temp = q.front();
        q.pop();
        if(temp.second != tmp) {
            std::cout << "\nLevel " << temp.second << ": ";
            tmp = temp.second;
        }
        std::cout << "[";
        for (int i = 0; i < temp.first->numKeys; i++) 
            std::cout << temp.first->keys[i] << " ]"[i == temp.first->numKeys - 1];
        
        for (int i = 0; i <= temp.first->numKeys; i++) 
            if (temp.first->children[i] != NULL) 
                q.push({temp.first->children[i], temp.second + 1});
    }
}

int findKey(Node * root, int data) {
    int index = 0;
    while (index < root->numKeys && root->keys[index] < data) index++;
    return index;
}

int getPred(Node * root, int index) {
    Node * cur = root->children[index];
    while (!cur->isLeaf) cur = cur->children[cur->numKeys];
    return cur->keys[cur->numKeys - 1];
}

int getSucc(Node * root, int index) {
    Node * cur = root->children[index + 1];
    while (!cur->isLeaf) cur = cur->children[0];
    return cur->keys[0];
}


void borrowFromPrev(Node * root, int index) {
    Node * child = root->children[index];
    Node * sibling = root->children[index - 1];

    for (int i = child->numKeys - 1; i >= 0; i--) 
        child->keys[i + 1] = child->keys[i];

    if (!child->isLeaf) 
        for (int i = child->numKeys; i >= 0; i--) 
            child->children[i + 1] = child->children[i];
        
    child->keys[0] = root->keys[index - 1];

    if (!child->isLeaf) 
        child->children[0] = sibling->children[sibling->numKeys];

    root->keys[index - 1] = sibling->keys[sibling->numKeys - 1];

    child->numKeys++;
    sibling->numKeys--;
}

void borrowFromNext(Node * root, int index) {
    Node * child = root->children[index];
    Node * sibling = root->children[index + 1];

    child->keys[child->numKeys] = root->keys[index];

    if (!child->isLeaf) 
        child->children[child->numKeys + 1] = sibling->children[0];

    root->keys[index] = sibling->keys[0];

    for (int i = 1; i < sibling->numKeys; i++) 
        sibling->keys[i - 1] = sibling->keys[i];

    if (!sibling->isLeaf) 
        for (int i = 1; i <= sibling->numKeys; i++) 
            sibling->children[i - 1] = sibling->children[i];

    child->numKeys++;
    sibling->numKeys--;
}

void merge(Node * root, int index) {
    Node * child = root->children[index];
    Node * sibling = root->children[index + 1];

    child->keys[MIN] = root->keys[index];

    for (int i = 0; i < sibling->numKeys; i++) 
        child->keys[MIN + 1 + i] = sibling->keys[i];

    if (!child->isLeaf) 
        for (int i = 0; i <= sibling->numKeys; i++) 
            child->children[MIN + 1 + i] = sibling->children[i];

    for (int i = index + 1; i < root->numKeys; i++) 
        root->keys[i - 1] = root->keys[i];
    
    for (int i = index + 2; i <= root->numKeys; i++) 
        root->children[i - 1] = root->children[i];
    
    child->numKeys += sibling->numKeys + 1;
    root->numKeys--;
    delete sibling;
}

void fillTree(Node * root, int index) {
    if (index != 0 && root->children[index - 1]->numKeys > MIN) 
        borrowFromPrev(root, index);
    else if (index != root->numKeys && root->children[index + 1]->numKeys > MIN) 
        borrowFromNext(root, index);
    else {
        if (index != root->numKeys) merge(root, index);
        else merge(root, index - 1);
    }
}
void removeFromLeaf(Node * root, int index) {
    for (int i = index + 1; i < root->numKeys; i++) 
        root->keys[i - 1] = root->keys[i];
    root->numKeys--;
}

Node * deleteNode(Node * root, int data);

void removeFromNonLeaf(Node* root, int index) {
    int data = root->keys[index];
    if (root->children[index]->numKeys > MIN) {
        int pred = getPred(root, index);
        root->keys[index] = pred;
        deleteNode(root->children[index], pred);
    }
    else if (root->children[index + 1]->numKeys > MIN) {
        int succ = getSucc(root, index);
        root->keys[index] = succ;
        deleteNode(root->children[index + 1], succ);
    }
    else {
        merge(root, index);
        deleteNode(root->children[index], data);
    }
}

Node * deleteNode(Node* root, int data) {
    int index = findKey(root, data);

    if(index < root->numKeys && root->keys[index] == data) {
        if (root->isLeaf) removeFromLeaf(root, index);
        else removeFromNonLeaf(root, index);
    }
    else {
        if (root->isLeaf) return NULL;

        bool flag = (index == root->numKeys);
        
        if (root->children[index]->numKeys <= MIN) fillTree(root, index);
    
        if (flag && index > root->numKeys) 
            deleteNode(root->children[index - 1], data);
        else deleteNode(root->children[index], data);
    }
    return root;
}

Node * search (Node * root, int data) {
    if (root == NULL) return NULL;
    int i = 0;
    while (i < root->numKeys && root->keys[i] < data) i++;
    
    if (root->keys[i] == data) return root;
    
    if (root->isLeaf) return NULL;

    return search(root->children[i], data);
}

void freeTree(Node * root) {
    if (root == NULL) return;
    for (int i = 0; i <= root->numKeys; i++) 
        freeTree(root->children[i]);

    delete root;
}

int main() {
    Node * root = NULL;
	root = insert(root, 20);
	root = insert(root, 15);
	root = insert(root, 10);
	root = insert(root, 30);
	root = insert(root, 50);
	root = insert(root, 45);

    cout << "PreOrder: ";
    PreOrder(root);
    cout << "\n";

    cout << "InOrder: ";
    InOrder(root);
    cout << "\n";

    cout << "PostOrder: ";
    PostOrder(root);
    cout << "\n";

    cout << "Level Order: ";
    LevelOrder(root);
    cout << "\n";

    cout << "Search 45: ";
    if (search(root, 45) != NULL) cout << "Found 45\n";
    else cout << "Not Found\n";

    std::cout << "Delete 20\n";
    deleteNode(root, 20);
    std::cout << "Level Order: ";
    LevelOrder(root);

    freeTree(root); 
    return 0;
}

