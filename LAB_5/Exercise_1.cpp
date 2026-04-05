#include <iostream>
#include <sstream>
#include <fstream>
#include <queue>

using namespace std;

const int N = 1e5 + 5; 

typedef struct leader *lref;
typedef struct trailer *tref;

struct leader {
    int key;
    int count;
    lref next;
    tref trail;
};

struct trailer {
    lref id;
    tref next;
};

struct list {
    lref head;
    lref tail;
};

lref nodes[N]; 

lref addList(list &multiLinkedList, int w, int &n) {
    if (nodes[w] == nullptr) { 
        nodes[w] = new leader();
        nodes[w]->key = w;
        nodes[w]->count = 0;
        nodes[w]->trail = nullptr;
        nodes[w]->next = multiLinkedList.tail;
        multiLinkedList.tail = nodes[w];
        n++;
    }
    return nodes[w];
}


void update(lref p, lref q) {
    p->trail = new trailer{q, p->trail};
    q->count++;
}

bool readFile(const string &filename, list &multiLinkedList, int &n) {
    fstream fi(filename, ios::in);
    if (!fi) return false;
    
    string line;
    int x, y;
    char c;
    getline(fi, line);
    stringstream ss(line);
    while (ss >> c >> x >> c >> y) {
        lref p = addList(multiLinkedList, x, n);
        lref q = addList(multiLinkedList, y, n);
        update(p, q);
        ss >> c;
    }

    fi.close();
    return true;
}

void topoSort(list multiLinkedList, int &n, queue<int> &res) {
    lref p = multiLinkedList.tail;
    lref q = p;
    multiLinkedList.head = nullptr;

    while (p) {
        q = p;
        p = p->next;
        if (q->count == 0) {
            q->next = multiLinkedList.head;
            multiLinkedList.head = q;
        }
    }

    q = multiLinkedList.head;
    while (q) {
        res.push(q->key);
        tref t = q->trail;
        q = q->next;
        while (t) {
            p = t->id;
            p->count--;
            if (p->count == 0) {
                p->next = q;
                q = p;
            }
            t = t->next;
        }
    }
}

bool writeFile(const string &filename, queue<int> &res, int &n) {
    fstream fo(filename, ios::out);
    if (!fo) return false;

    if (res.size() != n) fo << "-1\n";
    else {
        while (!res.empty()) {
            fo << res.front() << ' ';
            res.pop();
        }
    }

    fo.close();
    return true;
}

void deleteTrailers(tref t) {
    while (t) {
        tref temp = t;
        t = t->next;
        delete temp;
    }
}

void deleteLeaders() {
    for (int i = 0; i < N; ++i) {
        if (nodes[i]) {
            deleteTrailers(nodes[i]->trail);
            delete nodes[i];
        }
    }
}

int main() {
    list multiLinkedList;
    multiLinkedList.head = nullptr;
    multiLinkedList.tail = nullptr;
    int n = 0;

    for (int i = 0; i < N; ++i) nodes[i] = nullptr;

    if (!readFile("input.txt", multiLinkedList, n)) {
        cerr << "Can not open file!";
        deleteLeaders();
        return 1;
    }

    queue<int> res;
    topoSort(multiLinkedList, n, res);

    if (!writeFile("output.txt", res, n)) {
        cerr << "Can not open file!";
        return 1;
    }

    deleteLeaders();
    return 0;
}
