#include <iostream>
#include <stdlib.h>

using namespace std;

void inputArray(int *&arr, int n) {
    arr = new int[n + 1];
    for (int i = 0; i < n; i++)
        cin >> arr[i];
}

void printArray(int *arr, int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << ' ';
}

int findMax(int *arr, int n) {
    if (!n) return 0;
    int Max = arr[0];
    for (int i = 1; i < n; i++) 
        if (Max < arr[i]) Max = arr[i];
    return Max;
}

int sumArray(int *arr, int n) {
    if (!n) return 0;
    int sum = arr[0];
    for (int i = 1; i < n; i++)
        sum += arr[i];
    return sum;
}

void concatArrays(int *a, int na, int *b, int nb, int *&res, int &nres) {
    nres = na + nb;
    res = new int[nres + 1];
    for (int i = 0; i < na; i++)
        res[i] = a[i];
    for (int i = 0; i < nb; i++)
        res[na + i] = b[i];
}

void findLongestAscendingSubarray(int *arr, int n, int *&res, int &nres) {
    nres = 1;
    int cnt = 1, start = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] > arr[i - 1]) {
            ++cnt;
            if (cnt > nres) {
                nres = cnt;
                start = i - nres + 1;
            }
        }
        else cnt = 1;
    }
    res = new int[nres + 1];
    for (int i = 0; i < nres; i++) res[i] = arr[start + i];
}

int main() {
    int *a, *b, *c, *subArray;
    int na, nb, nc, nsubArray;

    cout << "Enter the number of elements in array a: ";
    cin >> na;
    cout << "Enter the array a: ";
    inputArray(a, na);

    cout << "Enter the number of elements in array b: ";
    cin >> nb;
    cout << "Enter the array b: ";
    inputArray(b, nb);

    cout << "The array is the concatenation of arrays a and b: ";
    concatArrays(a, na, b, nb, c, nc);
    printArray(c, nc);

    cout << "\nThe maximum value in the array c: ";
    cout << findMax(c, nc) << '\n';

    cout << "The sum of elements int the array c: ";
    cout << sumArray(c, nc) << '\n';

    cout << "The longest  ascending subarray in the array c: ";
    findLongestAscendingSubarray(c, nc, subArray, nsubArray);
    printArray(subArray, nsubArray);

    delete[] a;
    delete[] b;
    delete[] c;
    delete[] subArray;

    return 0;
}