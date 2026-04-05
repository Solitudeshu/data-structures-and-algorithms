#include <iostream>
#include <vector>

using namespace std;

int main() {
    int m, n;
    cout << "Enter the number of rows m = ";
    cin >> m;
    cout << "Enter the number of columns n = ";
    cin >> n;

    if (!m || !n) {
        cout << "Matrix dimensions cannot be zero";
        return 0;
    }

    int **a = new int *[m];
    for (int i = 0; i < m; i++) {
        a[i] = new int[n];
        for (int j = 0; j < n; j++) 
            cin >> a[i][j];
    }

    int sz = m * n;
    int *b = new int[sz];

    int top = 0, bottom = m - 1;
    int left = 0, right = n - 1;
    int cnt = 0;

    while (cnt < sz) {
        for (int j = left; j <= right && cnt < sz; j++) b[cnt++] = a[top][j];
        top++;
        for (int i = top; i <= bottom && cnt < sz; i++) b[cnt++] = a[i][right];
        right--;
        for (int j = right; j >= left && cnt < sz; j--) b[cnt++] = a[bottom][j];
        bottom--;
        for (int i = bottom; i >= top && cnt < sz; i--) b[cnt++] = a[i][left];
        left++;
    }
    
    cout << "Spiral order:\n";
    for (int i = 0; i < sz; i++) cout << b[i] << ' ';

    for (int i = 0; i < m; i++) delete[] a[i];
    delete[] a;
    delete[] b;
    return 0;
}