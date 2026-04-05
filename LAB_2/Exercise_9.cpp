#include <iostream>

using namespace std;

void generateBinary(int n, string cur) {
    if (cur.length() == n) {
        cout << cur << '\n';
        return;
    }
    generateBinary(n, cur + '0');
    generateBinary(n, cur + '1');
}

int main() {
    int n;
    cin >> n;
    generateBinary(n, "");
    return 0;
}