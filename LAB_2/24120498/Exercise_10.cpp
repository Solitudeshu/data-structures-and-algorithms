#include <iostream>

using namespace std;

const int N = 15;

bool check(int a[], int row, int col) {
    for (int i = 0; i < row; i++) {
        if (a[i] == col || a[i] - col == i - row || a[i] - col == row - i) {
            return false;
        }
    }
    return true;
}

void NQueens(int pos, int a[], int n) {
    if (pos == n) {
        cout << '[';
        for (int i = 0; i < n - 1; i++) cout << a[i] + 1 << ", ";
        cout << a[n - 1] + 1 << "]\n";
        return;
    }
    for (int i = 0; i < n; i++) {
        if (check(a, pos, i)) {
            a[pos] = i;
            NQueens(pos + 1, a, n);
        }
    }
}

int main() {
    int n, a[N];
    if (cin >> n) { 
        NQueens(0, a, n);
    }
    return 0;
}