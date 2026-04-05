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

void prim(vector<vector<int>> a, int n) {
	priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;	
	
	vector<int> dist(n);
	for (int i = 0; i < n; i++) dist[i] = INF;

	dist[0] = 0;
	pq.push({0, {0, -1}});
	queue<pair<pair<int, int>, int>> q;
    
	while (!pq.empty()) {
		pair<int, pair<int, int>> top = pq.top();
		pq.pop();

		int curDis = top.first;
		int u = top.second.first;
		int p = top.second.second;

		if (curDis != dist[u]) continue;

		q.push({{p, u}, curDis});

		for (int v = 0; v < n; v++) {
			if (a[u][v] != 0 && dist[v] > a[u][v]) {
				dist[v] = a[u][v];
				pq.push({dist[v], {v, u}});
			}
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

    prim(a, n);

    return 0;
}