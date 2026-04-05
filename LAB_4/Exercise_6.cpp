#include <iostream>
#include <cstdlib>
#include <chrono>
#include <string>
#include <vector>
#include <cmath>

using namespace std;
using namespace std::chrono;

struct Sorts {
    string name;
    int time;
};

void merge(vector<int> &a, int l, int mid, int r) {
    int n1 = mid -l + 1, n2 = r - mid;
    vector<int> left(n1), right(n2);

    for (int i = 0; i < n1; i++) left[i] = a[l + i];
    for (int i = 0; i < n2; i++) right[i] = a[mid + i + 1];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (left[i] < right[j]) a[k++] = left[i++];
        else a[k++] = right[j++];
    }

    while (i < n1) a[k++] = left[i++];
    while (j < n2) a[k++] = right[j++];

}

void mergeSort(vector<int> &a, int l, int r) {
    if (l < r) {
        int mid = (l + r) / 2;
        mergeSort(a, l, mid);
        mergeSort(a, mid + 1, r);
        merge(a, l, mid, r);
    }
}

int getMax(vector<int> a, int n) {
    int max = a[0];
    for (int i = 1; i < n; i++) if (max < a[i]) max = a[i];
    return max;
}

int countingSort(vector<int> &a, int n) {
    auto start = high_resolution_clock::now();

    vector<int> b(n);
    int sz = getMax(a, n) + 1;
    vector<int> f(sz, 0);
    for (int i = 0; i < n; i++) f[a[i]]++;
    for (int i = 1; i < sz; i++) f[i] += f[i - 1];
    for (int i = n - 1; i >= 0; i--) b[f[a[i]] - 1] = a[i], f[a[i]]--;
    for (int i = 0; i < n; i++) a[i] = b[i];

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Counting Sort: " << duration.count() << " microseconds\n";
    return duration.count();
}

int digit(int x, int k) {
    int temp = pow(10, k);
    return (x / temp) % 10;
}

int radixSort(vector<int> &a, int n) {
    auto start = high_resolution_clock::now();

    int d = 0, max = getMax(a, n);
    while (max) max /= 10, d++;
    for (int i = 0; i < d; i++) {
        vector<int> b(n);
        vector<int> f(10, 0);
        for (int j = 0; j < n; j++) f[digit(a[j], i)]++;
        for (int j = 1; j < 10; j++) f[j] += f[j - 1];
        for (int j = n - 1; j >= 0; j--) {
            int l = digit(a[j], i);
            b[f[l] - 1] = a[j];
            f[l]--;
        }
        for (int j = 0; j < n; j++) a[j] = b[j];
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Radix Sort: " << duration.count() << " microseconds\n";
    return duration.count();
}

int flashSort(vector<int> &a, int n) {
    auto start = high_resolution_clock::now();

    int min = a[0], maxIndex = 0;
    for (int i = 1; i < n; i++) {
        if (a[i] < min) min = a[i];
        else if (a[i] > a[maxIndex]) maxIndex = i;
    }

    if (a[maxIndex] == min) {
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Flash Sort: " << duration.count() << " microseconds\n";
        return duration.count();
    }

    int m = (int)(0.43 * n);
    vector<int> l(m, 0);
    double temp = (double)((m - 1) / (a[maxIndex] - min));

    for (int i = 0; i < n; i++) {
        int k = (int)(temp * (a[i] - min));
        l[k]++;
    }

    for (int i = 1; i < m; i++) l[i] += l[i - 1];

    swap(a[0], a[maxIndex]);
    int count = 0, i = 0, k = m - 1;
    while (count < n - 1) {
        while (i > l[k] - 1) {
            i++;
            k = (int)(temp * (a[i] - min));
        }
        int x = a[i];
        while (i <= l[k] - 1) {
            k = (int)(temp * (x - min));
            swap(a[--l[k]], x);
            count++;
        }
    }

    for (int i = 1; i < n; i++) {
        int x = a[i], j = i - 1;
        while (j >= 0 && a[j] > x) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = x;
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Flash Sort: " << duration.count() << " microseconds\n";
    return duration.count();
}

int main() {
    int n = 1e6;

    srand(time(0));
    vector<int> arr(n);
    for (int i = 0; i < n; i++) arr[i] = rand() % 1000000;

    vector<Sorts> sort(4);
    vector<int> a = arr;

    auto start = high_resolution_clock::now();
    sort[0].name = "Merge Sort";
    mergeSort(a, 0, n - 1); 
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    sort[0].time =  duration.count();
    cout << "Merge Sort: " << duration.count() << " microseconds\n";

    a = arr;
    sort[1].name = "Counting Sort";
    sort[1].time = countingSort(a, n);

    a = arr;
    sort[2].name = "Radix Sort";
    sort[2].time = radixSort(a, n);

    a = arr;
    sort[3].name = "Flash Sort";
    sort[3].time = flashSort(a, n);

    int min = 0, max = 0;
    for (int i = 1; i < 4; i++) {
        if (sort[i].time > sort[max].time) max = i;
        else if (sort[i].time < sort[min].time) min = i;
    }

    cout << "The fastest algorithm: " << sort[min].name << '\n';
    cout << "The slowest algorithm: " << sort[max].name << '\n';
    return 0;
}