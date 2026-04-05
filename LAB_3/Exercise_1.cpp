#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool readFile(const string &filename, int &n, int *&a) {
    fstream fi(filename, ios::in);
    if (!fi) return false;
    fi >> n;
    a = new int[n + 1];
    for (int i = 0; i < n; i++) fi >> a[i];
    fi.close();
    return true;
}

bool writeFile(const string &filename, int pos) {
    fstream fo(filename, ios::out);
    if (!fo) return false;
    fo << pos << '\n';
    fo.close();
    return true;
}

int linearSearch(int n, int *a, int x) {
    int i = 0;
    while (i < n && a[i] != x) i++;
    return (i < n) ? i : -1;
}

int linearSearchSentinel(int n, int *a, int x) {
    int i = 0; 
    a[n] = x;
    while (a[i] != x) i++;
    return (i < n) ? i : -1;
}



int binarySearch(int n, int *a, int x) {
    int l = 0, r = n - 1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (a[mid] == x) {
            while (mid > 0 && a[mid - 1] == x) mid--;
            return mid;
        }
        if (a[mid] > x) r = mid - 1;
        else l = mid + 1;
    }
    return -1;
}

int interpolationSearch(int n, int *a, int x) {
    int l = 0, r = n - 1;
    while (l <= r && x >= a[l] && x <= a[r]) {
        if (l == r) {
            if (a[l] == x) return l;
            return -1;
        }
        int pos = l + ((x - a[l]) * (r - l) / (a[r] - a[l]));
        if (a[pos] == x) return pos;
        if (a[pos] < x) l = pos + 1;
        else r = pos - 1;
    }
    return -1;
}

int main(int argc, char** argv) {

}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        cout << "Invalid syntax!";
        return 1;
    }
    
    int algorithm = stoi(argv[1]), x = stoi(argv[2]);
    int n, res;
    int *a = nullptr;

    if (!readFile(argv[3], n, a)) {
        cerr << "Cannot open file!";
        return 1;
    }
    
    switch (algorithm) {
        case 1:
            res = linearSearch(n, a, x);
            break;
        case 2:
            res = linearSearchSentinel(n, a, x);
            break;
        case 3:
            res = binarySearch(n, a, x);
            break;
        case 4:
            res = interpolationSearch(n, a, x);
            break;
        default:
            cout << "Invalid number!";
            delete[] a;
            return 1;
    }
    
    if (!writeFile(argv[4], res)) {
        cerr << "Cannot open file!";
        delete[] a;
        return 1;
    }
    delete[] a;
    return 0;
}