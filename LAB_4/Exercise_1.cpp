#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <vector>

using namespace std;
using namespace std::chrono;

struct Sorts {
    string name;
    double time;
};

double insertionSort(vector<int> &a, int n) {
    auto start = high_resolution_clock::now();

    for (int i = 0; i < n; i++) {
        int v = a[i], j = i - 1;
        while (j >= 0 && a[j] > v) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = v;
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Insertion Sort Time: " << duration.count() << " microseconds\n";
    return duration.count();
}

double selectionSort(vector<int> &a, int n) {
    auto start = high_resolution_clock::now();

    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) 
            if (a[j] < a[min]) min = j;
        swap(a[i], a[min]);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Selection Sort Time: " << duration.count() << " microseconds\n";
    return duration.count();
}

double interchangeSort(vector<int> &a, int n) {
    auto start = high_resolution_clock::now();

    for (int i = 0; i < n - 1; i++) 
        for (int j = i + 1; j < n; j++) 
            if (a[i] > a[j]) swap(a[i], a[j]);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Interchange Sort Time: " << duration.count() << " microseconds\n";
    return duration.count();
}

int main() {
    int n;
    cout << "Enter size of array n = ";
    cin >> n;

    vector<int> arr(n);
    srand(time(0));
    for (int i = 0; i < n; i++) 
        arr[i] = rand() % 100000;

    vector<Sorts> sort(3);
    vector<int> a = arr;
    

    sort[0].name = "Insertion Sort";
    sort[0].time = insertionSort(a, n);

    a = arr;
    sort[1].name = "Selection Sort";
    sort[1].time = selectionSort(a, n);

    a = arr;
    sort[2].name = "Interchange Sort";
    sort[2].time = interchangeSort(a, n);

    int min = 0, max = 0;
    for (int i = 1; i < 3; i++) {
        if (sort[i].time > sort[max].time) max = i;
        else if (sort[i].time < sort[min].time) min = i;
    }

    cout << "The fastest algorithm: " << sort[min].name << '\n';
    cout << "The slowest algorithm: " << sort[max].name << '\n';
    return 0;
}