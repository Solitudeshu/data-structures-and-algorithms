#include <iostream>

using namespace std;

long long Factorial(int n)
{
    if (!n)
        return 1;
    return n * Factorial(n - 1);
}

int main()
{
    int n;
    cin >> n;
    cout << Factorial(n);
    return 0;
}