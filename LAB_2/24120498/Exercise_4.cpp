#include <iostream>

using namespace std;

const int N = 105;

bool checkStrictlyIncreasing(int a[], int n)
{
    if (!n)
        return true;
    if (a[n] <= a[n - 1])
        return false;
    return checkStrictlyIncreasing(a, n - 1);
}

int main()
{
    int n, a[N];
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    if (checkStrictlyIncreasing(a, n - 1))
        cout << "Yes";
    else
        cout << "No";
    return 0;
}