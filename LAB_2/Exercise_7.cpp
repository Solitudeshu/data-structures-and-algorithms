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

void generatePermutations(int arr[], int n, int current[], bool used[], int depth) {
    if (depth == n) {
        for (int i = 0; i < n; ++i) {
            cout << current[i];
        }
        cout << '\n';
        return;
    }

    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            used[i] = true;            
            current[depth] = arr[i];    
            
            generatePermutations(arr, n, current, used, depth + 1);
            
            used[i] = false;           
        }
    }
}

int main() {
    int n;
    int arr[MAX_N];
    int current[MAX_N];
    bool used[MAX_N] = {false};

    if (cin >> n) {
        for (int i = 0; i < n; ++i) {
            cin >> arr[i];
        }

        Sort(arr, n); 

        generatePermutations(arr, n, current, used, 0);
    }
    return 0;
}