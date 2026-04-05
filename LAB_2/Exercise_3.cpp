#include <iostream>

using namespace std;

int greatestCommonDivisor(int a, int b)
{
    if (!b)
        return a;
    return greatestCommonDivisor(b, a % b);
}

int main()
{
    int a, b;
    cin >> a >> b;
    cout << greatestCommonDivisor(a, b);
    return 0;
}