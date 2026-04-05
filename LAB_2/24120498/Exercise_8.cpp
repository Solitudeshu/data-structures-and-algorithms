#include <iostream>

using namespace std;

const int MAX_N = 15;

void Sort(int arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void generateSubsetsOfSize(int arr[], int n, int current[], int k, int depth, int start_index) {
    if (depth == k) {
        cout << "{";
        for (int i = 0; i < k; ++i) {
            cout << current[i];
            if (i < k - 1) cout << ",";
        }
        cout << "}\n";
        return;
    }

    for (int i = start_index; i < n; ++i) {
        current[depth] = arr[i]; 
        generateSubsetsOfSize(arr, n, current, k, depth + 1, i + 1);
    }
}

int main() {
    int n;
    int arr[MAX_N];
    int current[MAX_N];

    if (cin >> n) {
        for (int i = 0; i < n; ++i) {
            cin >> arr[i];
        }

        Sort(arr, n); 

        for (int k = 0; k <= n; ++k) {
            generateSubsetsOfSize(arr, n, current, k, 0, 0);
        }
    }
    return 0;
}