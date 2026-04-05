#include <iostream>
#include <cstdlib>
#include <chrono>
#include <string>
#include <vector>

using namespace std;
using namespace std::chrono;

struct Sorts {
    string name;
    int time;
};

void sift(vector<int> &a, int left, int right) {
    int i = left, j = 2 * i, x = a[i];
    while (j <= right) {
        if (j < right) 
            if (a[j] > a[j + 1]) j++;
        if (x <= a[j]) break;
        a[i] = a[j];
        i = j;
        j = 2 * i;
    }
    a[i] = x;
}

int heapSort(vector<int> &a, int n) {
    auto start = high_resolution_clock::now(); 

    int left = n / 2 - 1;
    while (left >= 0) {
        sift(a, left, n - 1);
        left--;
    }

    int right = n - 1;
    while (right > 0) {
        swap(a[0], a[right]);
        right--;
        sift(a, 0, right);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Heap Sort: " << duration.count() << " microseconds\n";
    return duration.count();
}

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
    int n = 1e5;

    srand(time(0));
    vector<int> arr(1e5);
    for (int i = 0; i < n; i++) arr[i] = rand() % 1000000;

    vector<Sorts> sort(2);
    vector<int> a = arr;

    sort[0].name = "Heap Sort";
    sort[0].time = heapSort(a, n); 

    a = arr;
    sort[1].name = "Quick Sort";
    auto start = high_resolution_clock::now();
    quickSort(a, 0, n - 1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Quick Sort: " << duration.count() << " microseconds\n";
    sort[1].time = duration.count();

    if (sort[0].time > sort[1].time) swap(sort[0], sort[1]); 

    cout << "The fastest algorithm: " << sort[0].name << '\n';
    cout << "The slowest algorithm: " << sort[1].name << '\n';
    return 0;
}