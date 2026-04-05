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

void dijkstra(vector<vector<int>> a, int n, int &source, vector<int> &dist, vector<int> &trace) {
    cout << "Enter source vertex: ";
	cin >> source;

	for(int i = 0; i < n; i++) dist[i] = INF, trace[i] = -1;

    dist[source] = 0;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
	
    q.push({0, source});
	while (!q.empty()) {
		int u = q.top().second;
		q.pop();

		for (int v = 0; v < n; v++) {
			if (a[u][v] != 0 && dist[v] > dist[u] + a[u][v]) {
				dist[v] = dist[u] + a[u][v];
				trace[v] = u;
				q.push({dist[v], v});
			}
		}
	}
}

void output(int n, int source, vector<int> trace) {
    for (int i = 0; i < n; i++) {
        if (i == source) continue;
        stack<int> path;
        int temp = i;
        while (temp != -1) path.push(temp), temp = trace[temp];
        
        cout << "The shortest path from " << source << " to " << i << ": ";
        while (!path.empty()) {
            cout << path.top() << (path.top() == i ? ".\n" : " -> ");
			path.pop();
        }
    } 
}

int main() {
    int n;
    vector<vector<int>> a;

    if (!inputFile("grap.txt", a, n)) {
        cerr << "Can not open file!";
        return 1;
    }

    int source;
    vector<int> dist(n), trace(n);

    dijkstra(a, n, source, dist, trace);
    output(n, source, trace);

    return 0;
}