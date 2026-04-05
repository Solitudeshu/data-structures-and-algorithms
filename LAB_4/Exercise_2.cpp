#include <iostream>
#include <vector>

using namespace std;

void quickSort(vector<int> &a, int left, int right) {
    if (left < right) {
        int p = a[left], i = left, j = right + 1;
        do {
            do i++; while (a[i] < p);
            do j--; while (a[j] > p);
            swap(a[i], a[j]);
        } while (i < j);
        swap(a[i], a[j]);
        swap(a[left], a[j]);
        quickSort(a, left, j - 1);
        quickSort(a, j + 1, right);
    }
}

int main() {
    int n;
    cin >> n;

    vector<int> v, even, odd;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        v.push_back(x);
        if (x % 2) odd.push_back(x); 
        else even.push_back(x);
    }

    quickSort(even, 0, even.size() - 1);
    quickSort(odd, 0, odd.size() - 1);

    int evenIndex = 0, oddIndex = odd.size() - 1;
    for (int &x : v) {
        if (x % 2) x = odd[oddIndex--];
        else x = even[evenIndex++];
    }

    for (int x : v) cout << x << ' ';
    return 0;
}