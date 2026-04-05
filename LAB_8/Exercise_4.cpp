#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

const int INF = 1e9 + 7;

bool inputFile(const string &filename, vector<vector<int>> &a, int &n) {
    fstream fi(filename, ios::in);
    if (!fi) return false;

    fi >> n;
    a.resize(n);
    for (int i = 0; i < n; i ++) {
        a[i].resize(n);
        for (int j = 0; j < n; j++) fi >> a[i][j];
    }

    fi.close();
    return true;
}

int findRoot(int u, vector<int> &parent) {
    if (parent[u] == -1) return u;
    return parent[u] = findRoot(parent[u], parent);
}

void addEdge(const vector<vector<int>> &a, int n, vector<tuple<int, int, int>> &edges) {
    for (int i = 0; i < n; i++) 
        for (int j = i + 1; j < n; j++) 
            if (a[i][j]) edges.push_back(std::tuple<int, int, int>(a[i][j], i, j));
}

void sortEdges(vector<tuple<int, int, int>> &edges) {
    int size = edges.size();
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (get<0>(edges[j]) > get<0>(edges[j + 1])) {
                tuple<int, int, int> temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

void Kruskal(int n, vector<tuple<int, int, int>> edges, vector<int> &parent) {
    parent.resize(n, -1);
    sortEdges(edges); 

    queue<pair<pair<int, int>, int>> q;
    for (int i = 0; i < edges.size(); i++) {
        int u = std::get<1>(edges[i]);
        int v = std::get<2>(edges[i]);
        int ru = findRoot(u, parent);
        int rv = findRoot(v, parent);
        if (ru != rv) {
            parent[ru] = rv;
            q.push({{u, v}, std::get<0>(edges[i])});
        }
    }

    if(!q.empty()) cout << "Edge\tWeight" << '\n';
	while(!q.empty()) {
		pair<pair<int, int>, int> top = q.front();
		q.pop();
		if(top.first.first == -1) continue;
		cout << top.first.first << " - " << top.first.second << "\t" << top.second << '\n';
	}
}

int main() {
    int n;
    vector<vector<int>> a;
    
    if (!inputFile("grap.txt", a, n)) {
        cerr << "Can not open file!";
        return 1;
    }

    vector<tuple<int, int, int>> edges;
	vector<int> parent;

	addEdge(a, n, edges);
	Kruskal(n, edges, parent);

    return 0;
}